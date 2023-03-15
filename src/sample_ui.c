#include "sample_ui.h"

#include "gba/types.h"
#include "gba/defines.h"
#include "global.h"
#include "main.h"
#include "bg.h"
#include "text_window.h"
#include "window.h"
#include "characters.h"
#include "palette.h"
#include "task.h"
#include "overworld.h"
#include "malloc.h"
#include "gba/macro.h"
#include "menu_helpers.h"
#include "menu.h"
#include "scanline_effect.h"
#include "sprite.h"
#include "constants/rgb.h"
#include "decompress.h"
#include "constants/songs.h"
#include "sound.h"
#include "string_util.h"
#include "pokemon_icon.h"
#include "graphics.h"
#include "data.h"
#include "pokedex.h"

// This code is based on Ghoulslash's excellent UI tutorial:
// https://www.pokecommunity.com/showpost.php?p=10441093

/*
 * Glossary of acronyms and abbreviations -- because sometimes I go crazy with these
 *
 * BG = background
 * GF = Game Freak
 * DMA = Direct Memory Access
 * GBA = Game Boy Advance
 */

/*
 * Some general resources you should bookmark:
 * TONC GBA tutorial: https://www.coranac.com/tonc/text/toc.htm
 * Computer systems course with focus on GBA: https://ianfinlayson.net/class/cpsc305/
 * GBATEK reference docs: https://problemkaputt.de/gbatek.htm
 * Copetti GBA Architecture: https://www.copetti.org/writings/consoles/game-boy-advance/
 */

/*
 * The meat of the menu code lives in this file. The tutorial comments assume the following:
 *
 * 1) You understand the basics of GBA graphics i.e. the multiple BG layers and how they are
 *    controlled, the various GBA graphics modes, the basics of hardware sprites, etc
 *
 * 2) You are familiar with the concept of tiles (tilesets) vs tilemaps. These are two distinct
 *    concepts and you need to understand them to understand any UI code.
 *
 * 3) You are familiar with the concept of a charblock and a screenblock, which are crucial to
 *    proper VRAM layout.
 *
 * 4) You understand the basics of the pokeemerald Callback and Task systems, which structure the
 *    menu's control flow.
 *
 * 5) You have a basic grasp of the GBA memory layout -- you know the difference between VRAM,
 *    EWRAM, IWRAM, etc.
 *
 * 6) Some of the UI code makes use of DMA (Direct Memory Access). This assumes you are familiar
 *    with what DMA is and how it works on the GBA. Also note that a lot of the GF library code
 *    does not perform DMA directly, rather it schedules a DMA copy to occur during the next VBlank
 *    using a circle buffer of DMA transfer request objects. See the code in
 *    `gflib/dma3_manager.{h,c} for more details.
 *
 * If you are unsure about any of these concepts, please check the following resources:
 *
 * GBA graphics basics:
 *     + https://www.coranac.com/tonc/text/video.htm
 *     + https://ianfinlayson.net/class/cpsc305/notes/06-gba1
 *
 * Tiles, tilemaps, charblocks, screenblocks:
 *     + https://www.coranac.com/tonc/text/objbg.htm
 *     + https://www.coranac.com/tonc/text/regbg.htm
 *     + https://ianfinlayson.net/class/cpsc305/notes/13-tiles <--- this is a highly recommended resource
 *
 * Callbacks and Tasks:
 *     + https://github.com/pret/pokeemerald/wiki/Overview%E2%88%B6-The-Game-Loop
 *     + https://github.com/pret/pokeemerald/wiki/Overview%E2%88%B6-The-Task-System
 *
 * GBA Memory Layout:
 *     + https://www.coranac.com/tonc/text/hardware.htm#sec-memory
 *     + https://problemkaputt.de/gbatek.htm#gbamemorymap
 *
 * DMA:
 *     + https://www.coranac.com/tonc/text/dma.htm
 *     + https://ianfinlayson.net/class/cpsc305/notes/14-memory
 */

/*
 * Basic Code Flow
 * A summary of the basic control flow path for this code. This may help aid in understanding which
 * functions get called, and when.
 *
 * 1) Any code that would like to launch this menu must include `sample_ui.h' so it has the right
 *    hook-in, specifically `Task_OpenSampleUi'. It must then setup the transition (however is
 *    relevant based on its context) and set the active task to `Task_OpenSampleUi'. In our case,
 *    `start_menu.c' is the caller of this task.
 *
 * 2) `Task_OpenSampleUi' waits for any active fades to finish, then it calls our init code in
 *     `SampleUi_Init' which changes the gMainCallback2 to our `SampleUi_SetupCB'.
 *
 * 3) `SampleUi_SetupCB' runs each frame, bit-by-bit getting our menu initialized. Once
 *     initialization has finished, this callback:
 *       1) Sets up a new task `Task_SampleUiWaitFadeIn' which waits until we fade back in before
 *          hotswapping itself for `Task_SampleUiMain' which reads input and updates the menu state.
 *       2) Starts a palette fade to bring the screen from black back to regular colors
 *       3) Sets our VBlank callback to `SampleUi_VBlankCB' (which is called every VBlank as part of
 *          the VBlank interrupt service routine). This callback transfers our OAM and palette
 *          buffers into VRAM, among other things
 *       4) Sets gMainCallback2 to our menu's main callback `SampleUi_MainCB', which does the
 *          standard processing of tasks, animating of sprites, etc.
 *
 * 4) We have reached our standard menu state. Every frame `SampleUi_MainCB' runs, which calls
 *    `Task_SampleUiMain` to get input from the user and update menu state and backing graphics
 *    buffers. `SampleUi_MainCB' also updates other important gamestate. Then, when VBlank occurs,
 *    our `SampleUi_VBlankCB' copies palettes and OAM into VRAM before pending DMA transfers fire
 *    and copy any screen graphics updates into VRAM.
 */

/*
 * Various save state for the UI -- we'll allocate this on the heap since none of it needs to be
 * preserved after we exit the menu.
 */
struct SampleUiState
{
    // Save the callback to run when we exit: i.e. where do we want to go after closing the menu
    MainCallback savedCallback;
    // We will use this later to track some loading state
    u8 loadState;
    // Use these to track dex state and mon icon info
    u8 sMode;
    u8 sMonIconSpriteId;
    u16 sMonIconDexNum;
};

// GF window system passes window IDs around, so define this to avoid using magic numbers everywhere
enum WindowIds
{
    WIN_UI_HINTS,
    WIN_MON_INFO
};

/*
 * We'll need this data in order to access the Pokedex descriptions. We have declared it `extern'
 * because the actual data is defined in pokedex.c (which becomes pokedex.o) as .rodata, so if we
 * tried to include the array directly here we'd get duplicate definition errors.
 */
extern const struct PokedexEntry gPokedexEntries[];

/*
 * Both of these can be pointers that live in EWRAM -- allocating the actual data on the
 * heap will save precious WRAM space since none of this data matters outside the context of
 * our menu. We can easily cleanup when we're done. It's worth noting that every time the game
 * re-loads into the overworld, the heap gets nuked from orbit. However, it is still good practice
 * to clean up after oneself, so we will be sure to free everything before exiting.
 */
static EWRAM_DATA struct SampleUiState *sSampleUiSavedState = NULL;
static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;

/*
 * Defines and read-only data for on-screen dex. These should be self-explanatory.
 */
#define MON_ICON_X   39
#define MON_ICON_Y   36
#define MODE_KANTO   0
#define MODE_JOHTO   1
#define MODE_HOENN   2
#define MODE_SINNOH  3
#define MODE_UNOVA   4
#define MODE_KALOS   5
#define MODE_ALOLA   6
static const u16 sDexRanges[7][2] = {
    // Kanto goes from Bulbasaur to Mew
    [MODE_KANTO]   = {1, 151},
    // Johto goes from Chikorita to Celebi
    [MODE_JOHTO]   = {152, 251},
    // Etc.
    [MODE_HOENN]   = {252, 386},
    [MODE_SINNOH]  = {387, 493},
    [MODE_UNOVA]   = {494, 649},
    [MODE_KALOS]   = {650, 721},
    [MODE_ALOLA]   = {722, 809}
};
static const u8 sModeNameKanto[] =  _("Kanto");
static const u8 sModeNameJohto[] =  _("Johto");
static const u8 sModeNameHoenn[] =  _("Hoenn");
static const u8 sModeNameSinnoh[] = _("Sinnoh");
static const u8 sModeNameUnova[] =  _("Unova");
static const u8 sModeNameKalos[] =  _("Kalos");
static const u8 sModeNameAlola[] =  _("Alola");
static const u8 *const sModeNames[7] = {
    [MODE_KANTO]   = sModeNameKanto,
    [MODE_JOHTO]   = sModeNameJohto,
    [MODE_HOENN]   = sModeNameHoenn,
    [MODE_SINNOH]  = sModeNameSinnoh,
    [MODE_UNOVA]   = sModeNameUnova,
    [MODE_KALOS]   = sModeNameKalos,
    [MODE_ALOLA]   = sModeNameAlola
};
/*
 * Define some colors for the main bg, we will use the palette loading function to hotswap them when
 * the user changes modes. These colors are encoded using BGR555 encoding. If you'd like to change
 * these colors, you may find this online BGR555 color picker helpful.
 * Make sure to use Big Endian mode:
 * https://orangeglo.github.io/BGR555/
 */
static const u16 sModeBgColors[] = {
    [MODE_KANTO]   = 0x6a93,
    [MODE_JOHTO]   = 0x527a,
    [MODE_HOENN]   = 0x4f55,
    [MODE_SINNOH]  = 0x4b7c,
    [MODE_UNOVA]   = 0x5ef7,
    [MODE_KALOS]   = 0x76fb,
    [MODE_ALOLA]   = 0x471f,
};


/*
 * BgTemplates are just a nice way to setup various BG attributes without having to deal with
 * manually writing to the various display and BG control registers that the Game Boy actually
 * cares about. GF handles that for you with lots of clever BG management code. All you have to
 * do is tell it what you want. If you want to see the gory details of BG control registers,
 * check out this resource and the code in `gflib/bg.{h,c}':
 * https://problemkaputt.de/gbatek.htm#lcdiobgcontrol
 */
static const struct BgTemplate sSampleUiBgTemplates[] =
{
    {
        // We will use BG0 for the text windows
        .bg = 0,
        // Use charblock 0 for BG0 tiles
        .charBaseIndex = 0,
        // Use screenblock 31 for BG0 tilemap
        // (It has become customary to put tilemaps in the final few screenblocks)
        .mapBaseIndex = 31,
        // Draw this BG on top
        .priority = 1
    },
    {
        // We will use BG1 for the menu graphics
        .bg = 1,
        // Use charblock 3 for BG1 tiles
        .charBaseIndex = 3,
        // Use screenblock 30 for BG1 tilemap
        .mapBaseIndex = 30,
        // Draw this BG below BG0, since we want text drawn on top of the menu graphics
        .priority = 2
    },
    /*
     * I encourage you to open the mGBA Tools/Game State Views/View Tiles menu to see how this
     * above code gets translated into an actual VRAM layout. Quiz yourself by changing the
     * charBaseIndex and mapBaseIndex and guessing what will happen before looking at the Tile Viewer.
     */
};

/*
 * Like the above BgTemplates, WindowTemplates are just an easy way to setup some software windows
 * (which are provided by the GameFreak library). GF's window system is used primarily for drawing
 * dynamic text on the background layers. Their inner workings are quite confusing, so hopefully
 * this tutorial clears some things up.
 *
 * One big thing to note is that GF windows use a technique called tile rendering to draw text.
 * With normal BG rendering, you have a pre-drawn tileset, and then you dynamically update the
 * tilemap, based on gamestate, to change what's shown on screen. With tile rendering, this process
 * is basically flipped on its head. GF tile-rendered windows instead write a preset increasing
 * sequence of tile indexes into the parts of the BG tilemap that represent a given window. Then,
 * to draw text, it dynamically draws to a backing pixel buffer (the `u8 *tileData' in the Window
 * struct) that is copied into VRAM as if it were tile data. This effectively allows the text
 * rendering code to treat the window BG as a pseudo-framebuffer, as if we were in a simple bitmap
 * mode like Mode 3. This technique is advantageous because it allows for maximum flexibility with
 * font sizing and spacing. You aren't locked into 8x8 tiles for each character.
 *
 * For more information about tile rendering and text rendering sytems in general, check out the
 * TTE TONC tutorial and the tile rendering section specifically. You can also consult Game Freak's
 * code in `gflib/window.c' and `gflib/text.c'.
 * https://www.coranac.com/tonc/text/tte.htm#sec-chr
 */
static const struct WindowTemplate sSampleUiWindowTemplates[] =
{
    [WIN_UI_HINTS] =
    {
        // This window will print on BG0
        .bg = 0,
        /*
         * The tilemap position for this window, if we imagine the tilemap as a 2D matrix.
         * These positions refer to tiles, so to get the actual pixel position you should
         * multiply by 8.
         */
        .tilemapLeft = 14,
        .tilemapTop = 0,
        /*
         * The tilemap dimensions for this window, if we imagine the tilemap as a 2D matrix.
         * These dimensions refer to tiles, so to get the actual pixel dimensions you should
         * multiply by 8.
         */
        .width = 16,
        .height = 6,
        /*
         * Use BG palette 15 for all tilemap entries that fall within this window. Tilemap entries
         * store the palette for the given tile in bits F, E, D, C (top four) of the entry. We'll
         * need to load the right palette into BG palette slot 15.
         */
        .paletteNum = 15,

        /*
         * This next parameter is where things get interesting. The window base block is the offset,
         * relative to the window BG's charblock, where the window's graphics live in VRAM. Since we
         * might be cramming multiple windows into the same BG, we need to tell the engine where
         * exactly to place each window's graphics, lest they overlap.
         *
         * Typically, you want each subsequent window's baseBlock to be at least:
         *     previousBaseBlock + (prevWindowWidth * prevWindowHeight)
         * which makes sense if you think about it. (Try changing the second window's baseBlock
         * to see how important this parameter is!)
         *
         * And another thing -- why is this value set to 1 and not 0? You will understand this
         * better once you finish going through the tutorial code, but I will put the explanation
         * here:
         *
         * It's because this window lives on BG0. If we set the baseBlock to 0, then the text
         * writing code will draw the first section of window text into tile 0 of charblock 0
         * (because baseBlock=0 and BG0_charblock=0). When we init our window, BG0's tilemap buffer
         * is zeroed out (because it gets AllocZeroed'd by the window init code). But since the
         * tilemap buffer ultimately gets copied into BG0's screenblock, it is effectively telling
         * the hardware to draw tile 0 across the entire screen. And since we put some text in
         * tile 0, you are going to end up seeing a small bit of text drawn across the screen, which
         * looks really bad.
         *
         * We obviously don't want that, so we offset the window text by one so that tile 0 of
         * charblock 0 is empty. And as a result our zeroed BG tilemap draws transparent tiles
         * instead of the text fragment. (Recall that the value in each tilemap buffer entry is
         * basically a pointer into our charblock, so `tilemapBuffer[i] == 0' means draw `tile 0'
         * onto wherever `tilemap position i' maps on the LCD. (The various LCD register settings
         * will define where on the LCD that `tilemap position i' is actually drawn.)
         *
         * If this is confusing, try changing this value to 0, rebuild and see what the menu does.
         * Looking at the mGBA tile viewer will illuminate what is happening.
         */
        .baseBlock = 1,
        /*
         * Just like with the BgTemplates, I encourage you to open:
         *     "mGBA Tools/Game State Views/View Tiles"
         * to see how this above code gets translated into an actual VRAM layout. In this case,
         * try changing the baseBlock value for this window and see where in VRAM the text gets
         * drawn. If you want to really work your brain, change the charblock base for BG0 *and* the
         * baseBlock for this window and try to guess where in VRAM your window text will show up.
         */
    },
    [WIN_MON_INFO] =
    {
        // This window will also print on BG0
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 9,
        .width = 25,
        .height = 10,
        // We will use the same palette for this window, since it's also just regular text
        .paletteNum = 15,
        /*
         * Here we will set the baseBlock to the previous window's baseblock + the width*height in
         * tiles of the previous window. Try changing this value around and use the mGBA tile viewer
         * to see what happens.
         */
        .baseBlock = 1 + (16 * 6),
    },
    // Mark the end of the templates so the `InitWindow' library function doesn't run past the end
    DUMMY_WIN_TEMPLATE
};


/*
 * This file is generated from a properly indexed tile PNG image. You MUST use an indexed PNG with
 * 4bpp indexing (you technically can get away with 8bpp indexing as long as each individual index
 * is between 0-15). The easiest way to make indexed PNGs is using Aseprite's Index mode, or using
 * GraphicsGale.
 */
static const u32 sSampleUiTiles[] = INCBIN_U32("graphics/sample_ui/tiles.4bpp.lz");
/*
 * I created this tilemap in TilemapStudio using the above tile PNG. I highly recommend
 * TilemapStudio for exporting maps like this.
 */
static const u32 sSampleUiTilemap[] = INCBIN_U32("graphics/sample_ui/tilemap.bin.lz");
/*
 * This palette is built from a JASC palette file that you can export using GraphicsGale or
 * Aseprite. Please note: the palette conversion tool REQUIRES that JASC palette files end in CRLF,
 * the standard Windows line ending. If you are using Aseprite or another Mac/Linux program, you may
 * get errors complaining that your lines end in LF and not CRLF. To remedy this, run your JASC
 * palette file through a tool like unix2dos and you shouldn't have any more problems.
 */
static const u16 sSampleUiPalette[] = INCBIN_U16("graphics/sample_ui/00.gbapal");

enum FontColor
{
    FONT_BLACK,
    FONT_WHITE,
    FONT_RED,
    FONT_BLUE,
};
static const u8 sSampleUiWindowFontColors[][3] =
{
    /*
     * The TEXT_COLOR_X macros here are just palette indexes. Specifically, these indexes match the
     * colors in gMessageBox_Pal, so we will need to make sure that palette is loaded. Since our
     * window is set to use palette 15, we'll load it into BG palette slot 15 in the menu loading
     * code.
     */
    [FONT_BLACK]  = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY,  TEXT_COLOR_LIGHT_GRAY},
    [FONT_WHITE]  = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE,      TEXT_COLOR_DARK_GRAY},
    [FONT_RED]    = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_RED,        TEXT_COLOR_LIGHT_GRAY},
    [FONT_BLUE]   = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_BLUE,       TEXT_COLOR_LIGHT_GRAY},
};

// Callbacks for the sample UI
static void SampleUi_SetupCB(void);
static void SampleUi_MainCB(void);
static void SampleUi_VBlankCB(void);

// Sample UI tasks
static void Task_SampleUiWaitFadeIn(u8 taskId);
static void Task_SampleUiMain(u8 taskId);
static void Task_SampleUiWaitFadeAndBail(u8 taskId);
static void Task_SampleUiWaitFadeAndExitGracefully(u8 taskId);

// Sample UI helper functions
void SampleUi_Init(MainCallback callback);
static bool8 SampleUi_InitBgs(void);
static void SampleUi_FadeAndBail(void);
static bool8 SampleUi_LoadGraphics(void);
static void SampleUi_InitWindows(void);
static void SampleUi_PrintUiButtonHints(u8 windowId, u8 colorIdx);
static void SampleUi_PrintUiMonInfo(u8 windowId, u8 colorIdx);
static void SampleUi_DrawMonIcon(u16 dexNum);
static void SampleUi_FreeResources(void);

// Declared in sample_ui.h
void Task_OpenSampleUi(u8 taskId)
{
    /*
     * We are still in the overworld callback, so wait until the palette fade
     * is finished (i.e. the screen is entirely black) before we start cleaning
     * things up and changing callbacks (which might affect displayed graphics
     * and cause artifacting)
     */
    if (!gPaletteFade.active)
    {
        /*
         * Free overworld related heap stuff -- if you are entering this menu from somewhere else
         * you may want to do other cleanup. We're entering from overworld start menu so this works
         * for us.
         */
        CleanupOverworldWindowsAndTilemaps();
        // Allocate heap space for menu state and set up callbacks
        SampleUi_Init(CB2_ReturnToFieldWithOpenMenu);
        // Our setup is done, so destroy ourself.
        DestroyTask(taskId);
    }
}

void SampleUi_Init(MainCallback callback)
{
    sSampleUiSavedState = AllocZeroed(sizeof(struct SampleUiState));
    if (sSampleUiSavedState == NULL)
    {
        /*
         * If the heap allocation failed for whatever reason, then set the callback
         * to just return to the overworld. This really shouldn't ever happen but
         * if it does, this is better than hard crashing and making the user think you
         * bricked their Game Boy.
         */
        SetMainCallback2(callback);
        return;
    }

    sSampleUiSavedState->loadState = 0;
    sSampleUiSavedState->savedCallback = callback;

    /*
     * Next frame start running UI setup code. SetMainCallback2 also resets gMain.state
     * to zero, which we will need for the SetupCB
     */
    SetMainCallback2(SampleUi_SetupCB);
}

static void SampleUi_SetupCB(void)
{
    u8 taskId;
    switch (gMain.state)
    {
    case 0:
        // Use DMA to completely clear VRAM
        DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000);
        // Null out V/H blanking callbacks since we are not drawing anything atm
        SetVBlankHBlankCallbacksToNull();
        /*
         * If previous game state had scheduled any copies to VRAM, cancel these now
         * so we don't accidentally draw garbage to the screen.
         */
        ClearScheduledBgCopiesToVram();
        gMain.state++;
        break;
    case 1:
        /*
         * Unclear on what this does, I think it is related to some of the screen transition
         * effects. In any case, we don't want any of those since this is a menu, dammit
         */
        ScanlineEffect_Stop();
        // Clear all sprite palette tags in the sprite system
        FreeAllSpritePalettes();
        /*
         * Reset palette fade settings -- we are currently in a fade-to-black initiated by whatever
         * code opened this menu screen. Since we don't know what they were doing with the palettes,
         * just reset everything so we can do a simple fade-in when we're done loading.
         */
        ResetPaletteFade();
        // Completely clear all sprite buffers and settings
        ResetSpriteData();
        /*
         * Completely clear all task data. There should be no tasks running right now so make sure
         * nothing is hanging around from whatever code got us into this menu.
         */
        ResetTasks();
        gMain.state++;
        break;
    case 2:
        // Try to run the BG init code
        if (SampleUi_InitBgs())
        {
            // If we successfully init the BGs, we can move on
            sSampleUiSavedState->loadState = 0;
            gMain.state++;
        }
        else
        {
            /*
             * Otherwise, fade out, free the heap data, and return to main menu. Like before,
             * this shouldn't ever really happen but it's better to handle it then have a
             * surprise hard-crash.
             */
            SampleUi_FadeAndBail();
            return;
        }
        break;
    case 3:
        if (SampleUi_LoadGraphics() == TRUE)
        {
            /*
             * Only advance the state of this load switch statment once all the LoadGraphics
             * logic has finished.
             */
            gMain.state++;
        }
        break;
    case 4:
        // Set up our text windows
        SampleUi_InitWindows();
        gMain.state++;
        break;
    case 5:
        // Setup initial draw of Pokemon icon sprite
        sSampleUiSavedState->sMode = MODE_KANTO;
        sSampleUiSavedState->sMonIconDexNum = sDexRanges[sSampleUiSavedState->sMode][0];

        /*
         * Free all mon icon palettes just to make sure nothing is left over from previous screen.
         * The sprite system uses a technique called palette tagging to help the game keep track of
         * which palettes are in use, and by which sprites.
         */
        FreeMonIconPalettes();

        /*
         * Since this is a small demo without many sprites, we can just load all 6 default mon icon
         * palettes at once. If you have a more complex UI with lots of unique-palette sprites in
         * addition to mon icons, you may instead want to manage mon icon palettes dynamically based
         * on which mon icons are currently on screen. You can do this with the more granular
         * `LoadMonIconPalette(u16 species)' and `FreeMonIconPalette(u16 species)' functions.
         */
        LoadMonIconPalettes();

        // Draw the mon icon
        SampleUi_DrawMonIcon(sSampleUiSavedState->sMonIconDexNum);

        // Print the UI button hints in the top-right
        SampleUi_PrintUiButtonHints(WIN_UI_HINTS, FONT_WHITE);

        // Print the mon info in the main text box
        SampleUi_PrintUiMonInfo(WIN_MON_INFO, FONT_BLACK);

        /*
         * Create a task that does nothing until the palette fade is done. We will start the palette
         * fade next frame.
         */
        taskId = CreateTask(Task_SampleUiWaitFadeIn, 0);
        gMain.state++;
        break;
    case 6:
        /*
         * Fade screen in from black, this will take multiple frames to finish so we'll want
         * the above active task poll the fade to completion before continuing processing.
         */
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    case 7:
        // Finally we can set our main callbacks since loading is finished
        SetVBlankCallback(SampleUi_VBlankCB);
        SetMainCallback2(SampleUi_MainCB);
        break;
    }
}

static void SampleUi_MainCB(void)
{
    // Iterate through the Tasks list and run any active task callbacks
    RunTasks();
    // For all active sprites, call their callbacks and update their animation state
    AnimateSprites();
    /*
     * After all sprite state is updated, we need to sort their information into the OAM buffer
     * which will be copied into actual OAM during VBlank. This makes sure sprites are drawn at the
     * correct positions and in the correct order (recall sprite draw order determines which sprites
     * appear on top of each other).
     */
    BuildOamBuffer();
    /*
     * This one is a little confusing because there are actually two layers of scheduling. Regular
     * game code can call `ScheduleBgCopyTilemapToVram(u8 bgId)' which will simply mark the tilemap
     * for `bgId' as "ready to be copied". Then, calling `DoScheduledBgTilemapCopiesToVram' here
     * does not actually perform the copy. Rather it simply adds a DMA transfer request to the DMA
     * manager for this buffer copy. Only during VBlank when DMA transfers are processed does the
     * copy into VRAM actually occur.
     */
    DoScheduledBgTilemapCopiesToVram();
    // If a palette fade is active, tick the udpate
    UpdatePaletteFade();
}

static void SampleUi_VBlankCB(void)
{
    /*
     * Handle direct CPU copies here during the VBlank period. All of these transfers affect
     * what is displayed on screen, so we wait until VBlank to make the copies from the backbuffers.
     */

    // Transfer OAM buffer into VRAM OAM area
    LoadOam();
    /*
     * Sprite animation code may have updated frame image for sprites, so copy all these updated
     * frames into the correct VRAM location.
     */
    ProcessSpriteCopyRequests();
    // Transfer the processed palette buffer into VRAM palette area
    TransferPlttBuffer();
}

static void Task_SampleUiWaitFadeIn(u8 taskId)
{
     // Do nothing until the palette fade finishes, then replace ourself with the main menu task.
    if (!gPaletteFade.active)
    {
        gTasks[taskId].func = Task_SampleUiMain;
    }
}

static void Task_SampleUiMain(u8 taskId)
{
    // Exit the menu when the player presses B
    if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_PC_OFF);
        // Fade screen to black
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        // Replace ourself with the "exit gracefully" task function
        gTasks[taskId].func = Task_SampleUiWaitFadeAndExitGracefully;
    }
    // User pressed or held DPAD_DOWN, scroll down through dex list
    if (JOY_REPEAT(DPAD_DOWN))
    {
        PlaySE(SE_SELECT);
        // Destroy the old mon sprite, update the selected dex num, and draw the new sprite
        FreeAndDestroyMonIconSprite(&gSprites[sSampleUiSavedState->sMonIconSpriteId]);
        if (sSampleUiSavedState->sMonIconDexNum < sDexRanges[sSampleUiSavedState->sMode][1])
        {
            sSampleUiSavedState->sMonIconDexNum++;
        }
        else
        {
            // Wrap dex number around
            sSampleUiSavedState->sMonIconDexNum = sDexRanges[sSampleUiSavedState->sMode][0];
        }
        SampleUi_DrawMonIcon(sSampleUiSavedState->sMonIconDexNum);
        SampleUi_PrintUiMonInfo(WIN_MON_INFO, FONT_BLACK);
    }
    // User pressed or held DPAD_UP, scroll up through dex list
    if (JOY_REPEAT(DPAD_UP))
    {
        PlaySE(SE_SELECT);
        // Destroy the old mon sprite, update the selected dex num, and draw the new sprite
        FreeAndDestroyMonIconSprite(&gSprites[sSampleUiSavedState->sMonIconSpriteId]);
        if (sSampleUiSavedState->sMonIconDexNum > sDexRanges[sSampleUiSavedState->sMode][0])
        {
            sSampleUiSavedState->sMonIconDexNum--;
        }
        else
        {
            // Wrap dex number around
            sSampleUiSavedState->sMonIconDexNum = sDexRanges[sSampleUiSavedState->sMode][1];
        }
        SampleUi_DrawMonIcon(sSampleUiSavedState->sMonIconDexNum);
        SampleUi_PrintUiMonInfo(WIN_MON_INFO, FONT_BLACK);
    }
    // User pressed A, cycle to next dex mode
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        if (sSampleUiSavedState->sMode == MODE_ALOLA)
        {
            // Wrap back around to Kanto after Alola
            sSampleUiSavedState->sMode = MODE_KANTO;
        }
        else
        {
            sSampleUiSavedState->sMode++;
        }
        // Get lower bound dex num for this mode
        sSampleUiSavedState->sMonIconDexNum = sDexRanges[sSampleUiSavedState->sMode][0];
        // Destroy the currently displayed mon icon sprite
        FreeAndDestroyMonIconSprite(&gSprites[sSampleUiSavedState->sMonIconSpriteId]);

        /*
         * Draw:
         * 1) First mon sprite for the new mode
         * 2) New button hints with updated mode reflected
         * 3) Mon info for new mon
         */
        SampleUi_DrawMonIcon(sSampleUiSavedState->sMonIconDexNum);
        SampleUi_PrintUiButtonHints(WIN_UI_HINTS, FONT_WHITE);
        SampleUi_PrintUiMonInfo(WIN_MON_INFO, FONT_BLACK);

        // Sneakily swap out color 2 in BG1's palette
        LoadPalette(&sModeBgColors[sSampleUiSavedState->sMode], BG_PLTT_ID(0) + 2, 2);
    }
}

static void Task_SampleUiWaitFadeAndBail(u8 taskId)
{
    // Wait until the screen fades to black before we start doing cleanup
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sSampleUiSavedState->savedCallback);
        SampleUi_FreeResources();
        DestroyTask(taskId);
    }
}

static void Task_SampleUiWaitFadeAndExitGracefully(u8 taskId)
{
    /*
     * This function is basically the same as Task_SampleUiWaitFadeAndBail. However, for this sample
     * we broke it out because typically you might want to do something different if the user
     * gracefully exits a menu vs if you got booted from a menu due to heap allocation failure.
     */

    // E.g. you could do some other processing here

    // Wait until the screen fades to black before we start doing final cleanup
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sSampleUiSavedState->savedCallback);
        SampleUi_FreeResources();
        DestroyTask(taskId);
    }
}

/*
 * 1 screenblock is 2 KiB, so that should be a good size for our tilemap buffer. We don't need
 * more than one screenblock since BG1's size setting is 0, which tells the GBA we are using a 32x32
 * tile background. (32 tile * 32 tile * 2 bytes/tile = 2048)
 * For more info on tilemap entries and how they work:
 * https://www.coranac.com/tonc/text/regbg.htm#sec-map
 */
#define TILEMAP_BUFFER_SIZE (1024 * 2)
static bool8 SampleUi_InitBgs(void)
{
    /*
     * BG registers may have scroll values left over from the previous screen.
     * Reset all scroll values to 0.
     */
    ResetAllBgsCoordinates();

    // Allocate our tilemap buffer on the heap
    sBg1TilemapBuffer = Alloc(TILEMAP_BUFFER_SIZE);
    if (sBg1TilemapBuffer == NULL)
    {
        // Bail if the allocation fails
        return FALSE;
    }

    // Clear whatever junk data is in the buffer
    memset(sBg1TilemapBuffer, 0, TILEMAP_BUFFER_SIZE);

    /*
     * Clear all BG-related data buffers and mark DMAs as ready. Also resets the BG and mode bits of
     * reg DISPCNT to 0. This will effectively turn off all BGs and activate Mode 0.
     */
    ResetBgsAndClearDma3BusyFlags(0);

    /*
     * Use the BG templates defined at the top of the file to init various
     * cached BG attributes. These attributes will be used by the various load methods
     * to correctly setup VRAM per the user template. Some of the attributes can also be
     * pushed into relevant video regs using the provided functions in `bg.h'
     */
    InitBgsFromTemplates(0, sSampleUiBgTemplates, NELEMS(sSampleUiBgTemplates));

    // Set the BG manager to use our newly allocated tilemap buffer for BG1's tilemap
    SetBgTilemapBuffer(1, sBg1TilemapBuffer);

    /*
     * Schedule to copy the tilemap buffer contents (remember we zeroed it out earlier) for the next
     * VBlank. So right now, BG1 will just use Tile 0 for every tile. We will change this once we
     * load in our true tilemap values from sSampleUiTilemap.
     */
    ScheduleBgCopyTilemapToVram(1);

    // Set reg DISPCNT to show BG0 and BG1 only
    ShowBg(0);
    ShowBg(1);

    return TRUE;
}
#undef TILEMAP_BUFFER_SIZE

static void SampleUi_FadeAndBail(void)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_SampleUiWaitFadeAndBail, 0);

    /*
     * Set callbacks to ours while we wait for the fade to finish, then our above task will
     * cleanup and swap the callbacks back to the one we saved earlier (which should re-load the
     * overworld)
     */
    SetVBlankCallback(SampleUi_VBlankCB);
    SetMainCallback2(SampleUi_MainCB);
}

static bool8 SampleUi_LoadGraphics(void)
{
    switch (sSampleUiSavedState->loadState)
    {
    case 0:
        /*
         * Reset leftover temp buffers from any previous code that used them to load graphics. The
         * loading code in `menu.c' basically saves pointers to the decompression buffers after it
         * copies to VRAM. Here, we just reset all the pointers to NULL and set the tracking index
         * to 0. This obviously assumes the previous screen freed the buffers for us.
         */
        ResetTempTileDataBuffers();

        /*
         * Decompress our tileset and copy it into VRAM using the parameters we set in the
         * BgTemplates at the top -- we are using BG1 here. Size, offset, mode set to 0. Size is
         * 0 because that tells the function to set the size dynamically based on the decompressed
         * data. Offset is 0 because we want to tiles loaded right at whatever charblock we set in
         * the BgTemplate. And mode is 0 because we are copying tiles and not a tilemap.
         *
         * `menu.c' also has a alternative function `DecompressAndLoadBgGfxUsingHeap', which does
         * the same thing but automatically frees the decompression buffer for you. If you want, you
         * can use that here instead and remove the `ResetTempTileDataBuffers' call above, since it
         * doesn't use the temp tile data buffers.
         */
        DecompressAndCopyTileDataToVram(1, sSampleUiTiles, 0, 0, 0);
        sSampleUiSavedState->loadState++;
        break;
    case 1:
        /*
         * Each frame, keep trying to free the temp data buffer we used last frame to copy the tile
         * data into VRAM. We have to do a poll here because this free may not occur depending on
         * the state of the DMA manager. If instead you chose to load graphics using the alternative
         * `DecompressAndLoadBgGfxUsingHeap', you can remove this call and wrapping if statement
         * since the polling/freeing is handled for you under the hood.
         */
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            /*
             * This basically just wraps the LZ77UnCompWram system call. It reads and decompresses
             * whatever data is provided in the `src' (argument 1), and writes the decompressed data
             * to a WRAM location given in `dest' (argument 2). In our case `dest' is just the
             * tilemap buffer we heap-allocated earlier.
             */
            LZDecompressWram(sSampleUiTilemap, sBg1TilemapBuffer);
            sSampleUiSavedState->loadState++;
        }
        break;
    case 2:
        /*
         * Copy our palette into the game's BG palette buffer, slot 0 -- this step does not directly
         * get the palette into VRAM. That only happens during VBlank if the current callback
         * specifies a buffer transfer.
         */
        LoadPalette(sSampleUiPalette, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
        /*
         * We are going to dynamically change the BG color depending on the mode. We set up our
         * tiles so that the UI BG color is stored in Palette 0, slot 2. So we hot swap that to our
         * saved color for Kanto, since the UI starts in Kanto mode. We will need to perform this
         * mini-swap each time the user changes modes.
         */
        LoadPalette(&sModeBgColors[MODE_KANTO], BG_PLTT_ID(0) + 2, 2);
        /*
         * Copy the message box palette into BG palette buffer, slot 15. Our window is set to use
         * palette 15 and our text color constants are defined assuming we are indexing in this
         * palette.
         */
        LoadPalette(gMessageBox_Pal, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        sSampleUiSavedState->loadState++;
    default:
        sSampleUiSavedState->loadState = 0;
        return TRUE;
    }
    return FALSE;
}

static void SampleUi_InitWindows(void)
{
    /*
     * Initialize windows from the window templates we specified above. This makes two important
     * allocations:
     *
     * 1) It allocates a tilemap buffer for the window tilemap, the size of which is based on the
     *    screen size setting specified in the BgTemplate. See BGXCNT register documentation for
     *    more details here. For this UI, the size setting is 0 which just means use a single
     *    screen. We only allocate a single tilemap for the entire BG layer. So if you have multiple
     *    windows on the same BG, they will all share the same tilemap buffer.
     *
     * 2) It allocates the `tileData' buffer (often also called the pixel buffer in the code) for
     *    each window. Each window has its own pixel buffer. This is the buffer into which we
     *    actually draw text, and it gets copied upon request to the tile area of VRAM based on the
     *    BG charblock and window baseblock.
     *
     * It's also worth noting that the window API allows you to allocate and set your own tilemap
     * buffer for the window BG layer, just like we did earlier for BG1. However, it's better to
     * just let the window API do the allocation and setup for you through `InitWindows()' -- just
     * make sure to call `FreeAllWindowBuffers()' before closing up shop to return your memory.
     */
    InitWindows(sSampleUiWindowTemplates);

    // Marks all text printers as inactive. Basically just setting flags. That's it.
    DeactivateAllTextPrinters();

    /*
     * Schedule a copy of BG0 tilemap buffer to VRAM. This buffer was allocated for us by
     * `InitWindows()' since we specified a window on BG0 and had not yet set that layer's
     * tilemap buffer. Note that the buffer was also zeroed for us by `InitWindows()'
     */
    ScheduleBgCopyTilemapToVram(0);

    /*
     * Fill each entire window pixel buffer (i.e. window.tileData) with the given value. In this
     * case, fill it with 0s to make the window completely transparent. We will draw text into the
     * window pixel buffer later.
     */
    FillWindowPixelBuffer(WIN_UI_HINTS, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    FillWindowPixelBuffer(WIN_MON_INFO, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));

    /*
     * Write a sequence into each window's tilemap buffer. Why? Because the window text will be
     * drawn onto the tiles themselves. So we just want each subsequent tilemap entry to point to
     * the next tile in VRAM. That way, we can treat the tiles as a pseudo-framebuffer and render
     * our text however we want.
     */
    PutWindowTilemap(WIN_UI_HINTS);
    PutWindowTilemap(WIN_MON_INFO);

    /*
     * Copy (well, schedule to copy) each window into VRAM using DMA3 under the hood. The mode=3
     * argument means we copy BOTH the tilemap buffer (which recall is just an incrementing sequence
     * of references into our tile canvas) and the tiles themselves. Typically when updating text on
     * a window, you only need to copy the tile canvas since the tilemap should never change. But to
     * init the window we need to get both into VRAM.
     */
    CopyWindowToVram(WIN_UI_HINTS, 3);
    CopyWindowToVram(WIN_MON_INFO, 3);
}

static const u8 sText_SampleUiDex[] = _("DEX");
static const u8 sText_SampleUiButtonHint1[] = _("{DPAD_UPDOWN}Change POKéMON");
static const u8 sText_SampleUiButtonHint2[] = _("{A_BUTTON}Mode: {STR_VAR_1}");
static const u8 sText_SampleUiButtonHint3[] = _("{B_BUTTON}Exit");
static void SampleUi_PrintUiButtonHints(u8 windowId, u8 colorIdx)
{
    // Copy the current mode name into a temp string variable
    StringCopy(gStringVar1, sModeNames[sSampleUiSavedState->sMode]);
    /*
     * `StringExpandPlaceholders' takes the src string, expands all placeholders (i.e. those bits in
     * braces that look like {FOO}), then copies the expanded string into dest. The {STR_VAR_1}
     * placeholder will expand to the current contents of temp string gStringVar1, which is very
     * useful for constructing dynamic strings. Note that above we saved the mode name into
     * gStringVar1.
     */
    StringExpandPlaceholders(gStringVar2, sText_SampleUiButtonHint2);

    /*
     * Fill the window with transparent. You normally want to do this before drawing new text
     * to remove the old text from the window (otherwise you'll see strange remnants of the previous
     * text's pixels underneath your new text).
     */
    FillWindowPixelBuffer(windowId, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));

    /*
     * Use the text printing system to add text to this window. We set the speed value to
     * TEXT_SKIP_DRAW to tell the printer to draw into the pixel buffer but skip the actual VRAM
     * copy. Why? Because we want to wait until all the text is rendered before we actually copy to
     * VRAM and make the text visible. This prevents flickering from occuring (because drawing text
     * is relatively slow). Try changing the speed parameter TEXT_SKIP_DRAW to 0 (which tells the
     * text printer to copy to VRAM on the next VBlank) and observe the slight flicker that occurs.
     */
    AddTextPrinterParameterized4(windowId, FONT_NORMAL, 0, 3, 0, 0,
        sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, sText_SampleUiDex);
    AddTextPrinterParameterized4(windowId, FONT_SMALL, 47, 0, 0, 0,
        sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, sText_SampleUiButtonHint1);
    AddTextPrinterParameterized4(windowId, FONT_SMALL, 47, 10, 0, 0,
        sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, gStringVar2);
    AddTextPrinterParameterized4(windowId, FONT_SMALL, 47, 20, 0, 0,
        sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, sText_SampleUiButtonHint3);
    /*
     * Explicitly copy to VRAM now that all text is draw into the window pixel buffer. We use
     * COPYWIN_GFX here since no changes were made to the BG tilemap, so no need to copy it again
     * (recall that GF windows use tile rendering).
     */
    CopyWindowToVram(windowId, COPYWIN_GFX);
}

static const u8 sText_SampleUiMonInfoSpecies[] = _("{NO}{STR_VAR_1} {STR_VAR_2}");
static void SampleUi_PrintUiMonInfo(u8 windowId, u8 colorIdx)
{
    u16 speciesId = NationalPokedexNumToSpecies(sSampleUiSavedState->sMonIconDexNum);

    /*
     * Use the string manipulation library to get the National Dex num, species name, and dex
     * description into strings, ready to be drawn.
     */
    ConvertIntToDecimalStringN(gStringVar1, sSampleUiSavedState->sMonIconDexNum,
        STR_CONV_MODE_LEADING_ZEROS, 3);
    StringCopy(gStringVar2, gSpeciesNames[speciesId]);
    StringExpandPlaceholders(gStringVar3, sText_SampleUiMonInfoSpecies);
    StringCopy(gStringVar4, gPokedexEntries[sSampleUiSavedState->sMonIconDexNum].description);

    // The window drawing code here works just like in `SampleUi_PrintUiButtonHints'
    FillWindowPixelBuffer(windowId, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    AddTextPrinterParameterized4(windowId, FONT_SHORT, 5, 3, 0, 0,
        sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, gStringVar3);
    AddTextPrinterParameterized4(windowId, FONT_SMALL, 5, 25, 0, 0,
        sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, gStringVar4);
    CopyWindowToVram(windowId, COPYWIN_GFX);
}

static void SampleUi_DrawMonIcon(u16 dexNum)
{
    // Convert the dex number to a species ID.
    u16 speciesId = NationalPokedexNumToSpecies(dexNum);

    /*
     * Create a new mon icon sprite and save off its sprite ID so we can easily free it when we need
     * to update which icon is displayed. We set the sprite callback to a preset supplied by the
     * GF's mon icon code. This call back updates the little bounce animation of the icon.
     * `CreateMonIcon' handles all the details of sprite initialization for us. Feel free to dive
     * into the implementation to see the gory details.
     */
    sSampleUiSavedState->sMonIconSpriteId =
            CreateMonIcon(speciesId, SpriteCB_MonIcon, MON_ICON_X, MON_ICON_Y, 4, 0);
    // Set prio to 0 so the icon sprite draws on top of everything
    gSprites[sSampleUiSavedState->sMonIconSpriteId].oam.priority = 0;
}

static void SampleUi_FreeResources(void)
{
    // Free our data struct and our BG1 tilemap buffer
    if (sSampleUiSavedState != NULL)
    {
        Free(sSampleUiSavedState);
    }
    if (sBg1TilemapBuffer != NULL)
    {
        Free(sBg1TilemapBuffer);
    }
    // Free all allocated tilemap and pixel buffers associated with the windows.
    FreeAllWindowBuffers();
    // Reset all sprite data
    ResetSpriteData();
}
