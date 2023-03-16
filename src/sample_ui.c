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
#include "sprite.h"
#include "string_util.h"
#include "pokemon_icon.h"
#include "graphics.h"
#include "data.h"
#include "pokedex.h"
#include "gpu_regs.h"

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
 *          hotswapping itself for `Task_SampleUiMainInput' which reads input and updates the menu state.
 *       2) Starts a palette fade to bring the screen from black back to regular colors
 *       3) Sets our VBlank callback to `SampleUi_VBlankCB' (which is called every VBlank as part of
 *          the VBlank interrupt service routine). This callback transfers our OAM and palette
 *          buffers into VRAM, among other things
 *       4) Sets gMainCallback2 to our menu's main callback `SampleUi_MainCB', which does the
 *          standard processing of tasks, animating of sprites, etc.
 *
 * 4) We have reached our standard menu state. Every frame `SampleUi_MainCB' runs, which calls
 *    `Task_SampleUiMainInput` to get input from the user and update menu state and backing graphics
 *    buffers. `SampleUi_MainCB' also updates other important gamestate. Then, when VBlank occurs,
 *    our `SampleUi_VBlankCB' copies palettes and OAM into VRAM before pending DMA transfers fire
 *    and copy any screen graphics updates into VRAM.
 */

/*
 * Various state for the UI -- we'll allocate this on the heap since none of it needs to be
 * preserved after we exit the menu.
 */
struct SampleUiState
{
    // Save the callback to run when we exit: i.e. where do we want to go after closing the menu
    MainCallback savedCallback;
    // We will use this later to track some loading state
    u8 loadState;
    // Use these to track dex state and mon icon info
    u8 mode;
    u8 region;
    u8 monIconSpriteId;
    u16 monIconDexNum;

    // Sliding panel state
    u8 panelY;
    bool8 panelIsOpen;

    /*
     * Save the sprite IDs for each button so we can manipulate their positions and change their
     * attributes through the global sprite table. The array is indexed by the region defines below, so
     * for e.g. Kanto is index 0, Sinnoh is index 3, etc.
     */
    u8 regionButtonSpriteIds[6];
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
static EWRAM_DATA struct SampleUiState *sSampleUiState = NULL;
static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;
static EWRAM_DATA u8 *sBg2TilemapBuffer = NULL;

/*
 * Defines and read-only data for on-screen dex. These should be self-explanatory.
 */
#define MON_ICON_X     39
#define MON_ICON_Y     36
#define REGION_NONE    0xFF
#define REGION_KANTO   0
#define REGION_JOHTO   1
#define REGION_HOENN   2
#define REGION_SINNOH  3
#define REGION_UNOVA   4
#define REGION_KALOS   5
static const u16 sDexRanges[6][2] = {
    // Kanto goes from Bulbasaur to Mew
    [REGION_KANTO]   = {1, 151},
    // Johto goes from Chikorita to Celebi
    [REGION_JOHTO]   = {152, 251},
    // Etc.
    [REGION_HOENN]   = {252, 386},
    [REGION_SINNOH]  = {387, 493},
    [REGION_UNOVA]   = {494, 649},
    [REGION_KALOS]   = {650, 721}
};
static const u8 sRegionNameKanto[] =  _("Kanto");
static const u8 sRegionNameJohto[] =  _("Johto");
static const u8 sRegionNameHoenn[] =  _("Hoenn");
static const u8 sRegionNameSinnoh[] = _("Sinnoh");
static const u8 sRegionNameUnova[] =  _("Unova");
static const u8 sRegionNameKalos[] =  _("Kalos");
static const u8 *const sRegionNames[6] = {
    [REGION_KANTO]   = sRegionNameKanto,
    [REGION_JOHTO]   = sRegionNameJohto,
    [REGION_HOENN]   = sRegionNameHoenn,
    [REGION_SINNOH]  = sRegionNameSinnoh,
    [REGION_UNOVA]   = sRegionNameUnova,
    [REGION_KALOS]   = sRegionNameKalos
};
/*
 * Define some colors for the main bg, we will use the palette loading function to hotswap them when
 * the user changes regions. These colors are encoded using BGR555 encoding. If you'd like to change
 * these colors, you may find this online BGR555 color picker helpful.
 * Make sure to use Big Endian mode:
 * https://orangeglo.github.io/BGR555/
 */
static const u16 sRegionBgColors[] = {
    [REGION_KANTO]   = 0x6a93,
    [REGION_JOHTO]   = 0x527a,
    [REGION_HOENN]   = 0x4f55,
    [REGION_SINNOH]  = 0x4b7c,
    [REGION_UNOVA]   = 0x5ef7,
    [REGION_KALOS]   = 0x76fb
};
struct RegionSelection
{
    u8 upRegion;
    u8 downRegion;
    u8 leftRegion;
    u8 rightRegion;
};

static const struct RegionSelection sRegionSelections[] =
{
    [REGION_KANTO] = {
        .upRegion    = REGION_NONE,
        .downRegion  = REGION_SINNOH,
        .leftRegion  = REGION_NONE,
        .rightRegion = REGION_JOHTO
    },
    [REGION_JOHTO] = {
        .upRegion    = REGION_NONE,
        .downRegion  = REGION_UNOVA,
        .leftRegion  = REGION_KANTO,
        .rightRegion = REGION_HOENN
    },
    [REGION_HOENN] = {
        .upRegion    = REGION_NONE,
        .downRegion  = REGION_KALOS,
        .leftRegion  = REGION_JOHTO,
        .rightRegion = REGION_NONE
    },
    [REGION_SINNOH] = {
        .upRegion    = REGION_KANTO,
        .downRegion  = REGION_NONE,
        .leftRegion  = REGION_NONE,
        .rightRegion = REGION_UNOVA
    },
    [REGION_UNOVA] = {
        .upRegion    = REGION_JOHTO,
        .downRegion  = REGION_NONE,
        .leftRegion  = REGION_SINNOH,
        .rightRegion = REGION_KALOS
    },
    [REGION_KALOS] = {
        .upRegion    = REGION_HOENN,
        .downRegion  = REGION_NONE,
        .leftRegion  = REGION_UNOVA,
        .rightRegion = REGION_NONE
    }
};

#define MODE_INFO   0
#define MODE_STATS  1
#define MODE_OTHER  2
static const u8 sModeNameInfo[] =  _("Info");
static const u8 sModeNameStats[] =  _("Stats");
static const u8 sModeNameOther[] =  _("Other");
static const u8 *const sModeNames[3] = {
    [MODE_INFO]   = sModeNameInfo,
    [MODE_STATS]  = sModeNameStats,
    [MODE_OTHER]  = sModeNameOther
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
        // Draw the text windows on top of the main BG
        .priority = 1
    },
    {
        // The Main BG: we will use BG1 for the menu graphics
        .bg = 1,
        // Use charblock 3 for BG1 tiles
        .charBaseIndex = 3,
        // Use screenblock 30 for BG1 tilemap
        .mapBaseIndex = 30,
        // Draw this BG below BG0, since we want text drawn on top of the menu graphics
        .priority = 2
    },
    {
        // We will use BG2 for the sliding panel
        .bg = 2,
        // The sliding panel shares the same tileset as the main BG, so use charblock 3
        .charBaseIndex = 3,
        // Sliding panel tilemap will go in screenblock 29
        .mapBaseIndex = 29,
        // Draw the sliding panel on top of everything else
        .priority = 0
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
        .height = 7,
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
        .baseBlock = 1 + (16 * 7),
    },
    // Mark the end of the templates so the `InitWindow' library function doesn't run past the end
    DUMMY_WIN_TEMPLATE
};


/*
 * These files are generated from properly indexed tile PNG images. You MUST use an indexed PNG with
 * 4bpp indexing (you technically can get away with 8bpp indexing as long as each individual index
 * is between 0-15). The easiest way to make indexed PNGs is using Aseprite's Index mode, or using
 * GraphicsGale.
 */
static const u32 sSampleUiTiles[] = INCBIN_U32("graphics/sample_ui/tiles.4bpp.lz");
static const u32 sSampleUiKantoButton[] = INCBIN_U32("graphics/sample_ui/kanto.4bpp");
static const u32 sSampleUiJohtoButton[] = INCBIN_U32("graphics/sample_ui/johto.4bpp");
static const u32 sSampleUiHoennButton[] = INCBIN_U32("graphics/sample_ui/hoenn.4bpp");
static const u32 sSampleUiSinnohButton[] = INCBIN_U32("graphics/sample_ui/sinnoh.4bpp");
static const u32 sSampleUiUnovaButton[] = INCBIN_U32("graphics/sample_ui/unova.4bpp");
static const u32 sSampleUiKalosButton[] = INCBIN_U32("graphics/sample_ui/kalos.4bpp");

/*
 * I created these tilemaps in TilemapStudio using the above tile PNG. I highly recommend
 * TilemapStudio for exporting maps like this.
 */
static const u32 sSampleUiTilemap[] = INCBIN_U32("graphics/sample_ui/tilemap.bin.lz");
static const u32 sSampleUiPanelTilemap[] = INCBIN_U32("graphics/sample_ui/panel_tilemap.bin.lz");

/*
 * These palettes are built from JASC palette files that you can export using GraphicsGale or
 * Aseprite. Please note: the palette conversion tool REQUIRES that JASC palette files end in CRLF,
 * the standard Windows line ending. If you are using the Mac/Linux version of a tool like Aseprite,
 * you may get errors complaining that your lines end in LF and not CRLF. To remedy this, run your
 * JASC palette file through a tool like unix2dos and you shouldn't have any more problems.
 */
static const u16 sSampleUiPalette[] = INCBIN_U16("graphics/sample_ui/00.gbapal");
static const u16 sSampleUi_KantoJohtoHoennPalette[] = INCBIN_U16("graphics/sample_ui/kanto_johto_hoenn.gbapal");
static const u16 sSampleUi_SinnohUnovaKalosPalette[] = INCBIN_U16("graphics/sample_ui/sinnoh_unova_kalos.gbapal");

#define PALETTE_TAG_KANTO_JOHTO_HOENN 0x1000
#define PALETTE_TAG_SINNOH_UNOVA_KALOS 0x1001
const struct SpritePalette sKantoJohtoHoennButtonsSpritePalette =
{
    .data = sSampleUi_KantoJohtoHoennPalette,
    .tag = PALETTE_TAG_KANTO_JOHTO_HOENN
};
const struct SpritePalette sSinnohUnovaKalosButtonsSpritePalette =
{
    .data = sSampleUi_SinnohUnovaKalosPalette,
    .tag = PALETTE_TAG_SINNOH_UNOVA_KALOS
};

#define DEFAULT_ANIM  0
#define SELECTED_ANIM 0
static const union AnimCmd sButtonDefaultAnim[] =
{
    ANIMCMD_FRAME(0, 30),
    ANIMCMD_END
};
static const union AnimCmd *const sButtonAnims[] =
{
    [DEFAULT_ANIM] = sButtonDefaultAnim
};
static const union AffineAnimCmd sButtonSelectedAnim[] =
{
    AFFINEANIMCMD_FRAME(1, 1, 0, 30),
    AFFINEANIMCMD_FRAME(-1, -1, 0, 30),
    AFFINEANIMCMD_JUMP(0)
};
static const union AffineAnimCmd * const sButtonAffineAnims[] =
{
    [SELECTED_ANIM] = sButtonSelectedAnim
};

static const struct SpriteFrameImage sKantoButtonPicTable[] =
{
    obj_frame_tiles(sSampleUiKantoButton)
};
static const struct OamData sKantoButtonOam =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};
const struct SpriteTemplate sKantoButtonSpriteTemplate =
{
    .tileTag = TAG_NONE,
    .paletteTag = PALETTE_TAG_KANTO_JOHTO_HOENN,
    .oam = &sKantoButtonOam,
    .anims = sButtonAnims,
    .images = sKantoButtonPicTable,
    .affineAnims = sButtonAffineAnims,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteFrameImage sJohtoButtonPicTable[] =
{
    obj_frame_tiles(sSampleUiJohtoButton)
};
static const struct OamData sJohtoButtonOam =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};
const struct SpriteTemplate sJohtoButtonSpriteTemplate =
{
    .tileTag = TAG_NONE,
    .paletteTag = PALETTE_TAG_KANTO_JOHTO_HOENN,
    .oam = &sJohtoButtonOam,
    .anims = sButtonAnims,
    .images = sJohtoButtonPicTable,
    .affineAnims = sButtonAffineAnims,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteFrameImage sHoennButtonPicTable[] =
{
    obj_frame_tiles(sSampleUiHoennButton)
};
static const struct OamData sHoennButtonOam =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};
const struct SpriteTemplate sHoennButtonSpriteTemplate =
{
    .tileTag = TAG_NONE,
    .paletteTag = PALETTE_TAG_KANTO_JOHTO_HOENN,
    .oam = &sHoennButtonOam,
    .anims = sButtonAnims,
    .images = sHoennButtonPicTable,
    .affineAnims = sButtonAffineAnims,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteFrameImage sSinnohButtonPicTable[] =
{
    obj_frame_tiles(sSampleUiSinnohButton)
};
static const struct OamData sSinnohButtonOam =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};
const struct SpriteTemplate sSinnohButtonSpriteTemplate =
{
    .tileTag = TAG_NONE,
    .paletteTag = PALETTE_TAG_SINNOH_UNOVA_KALOS,
    .oam = &sSinnohButtonOam,
    .anims = sButtonAnims,
    .images = sSinnohButtonPicTable,
    .affineAnims = sButtonAffineAnims,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteFrameImage sUnovaButtonPicTable[] =
{
    obj_frame_tiles(sSampleUiUnovaButton)
};
static const struct OamData sUnovaButtonOam =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};
const struct SpriteTemplate sUnovaButtonSpriteTemplate =
{
    .tileTag = TAG_NONE,
    .paletteTag = PALETTE_TAG_SINNOH_UNOVA_KALOS,
    .oam = &sUnovaButtonOam,
    .anims = sButtonAnims,
    .images = sUnovaButtonPicTable,
    .affineAnims = sButtonAffineAnims,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteFrameImage sKalosButtonPicTable[] =
{
    obj_frame_tiles(sSampleUiKalosButton)
};
static const struct OamData sKalosButtonOam =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};
const struct SpriteTemplate sKalosButtonSpriteTemplate =
{
    .tileTag = TAG_NONE,
    .paletteTag = PALETTE_TAG_SINNOH_UNOVA_KALOS,
    .oam = &sKalosButtonOam,
    .anims = sButtonAnims,
    .images = sKalosButtonPicTable,
    .affineAnims = sButtonAffineAnims,
    .callback = SpriteCallbackDummy,
};

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
static void Task_SampleUiMainInput(u8 taskId);
static void Task_SampleUiPanelInput(u8 taskId);
static void Task_SampleUiPanelSlide(u8 taskId);
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
static void SampleUi_CreateRegionButtons(void);
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
    sSampleUiState = AllocZeroed(sizeof(struct SampleUiState));
    if (sSampleUiState == NULL)
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

    sSampleUiState->loadState = 0;
    sSampleUiState->savedCallback = callback;

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
            sSampleUiState->loadState = 0;
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
        sSampleUiState->region = REGION_KANTO;
        sSampleUiState->monIconDexNum = sDexRanges[sSampleUiState->region][0];

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
        SampleUi_DrawMonIcon(sSampleUiState->monIconDexNum);

        // Print the UI button hints in the top-right
        SampleUi_PrintUiButtonHints(WIN_UI_HINTS, FONT_WHITE);

        // Print the mon info in the main text box
        SampleUi_PrintUiMonInfo(WIN_MON_INFO, FONT_BLACK);

        // Set sliding panel initial state
        sSampleUiState->panelY = 0;
        sSampleUiState->panelIsOpen = FALSE;

        // LTODO remove this, just here for testing
        SampleUi_CreateRegionButtons();

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
        gTasks[taskId].func = Task_SampleUiMainInput;
    }
}

static void Task_SampleUiMainInput(u8 taskId)
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
        FreeAndDestroyMonIconSprite(&gSprites[sSampleUiState->monIconSpriteId]);
        if (sSampleUiState->monIconDexNum < sDexRanges[sSampleUiState->region][1])
        {
            sSampleUiState->monIconDexNum++;
        }
        else
        {
            // Wrap dex number around
            sSampleUiState->monIconDexNum = sDexRanges[sSampleUiState->region][0];
        }
        SampleUi_DrawMonIcon(sSampleUiState->monIconDexNum);
        SampleUi_PrintUiMonInfo(WIN_MON_INFO, FONT_BLACK);
    }
    // User pressed or held DPAD_UP, scroll up through dex list
    if (JOY_REPEAT(DPAD_UP))
    {
        PlaySE(SE_SELECT);
        // Destroy the old mon sprite, update the selected dex num, and draw the new sprite
        FreeAndDestroyMonIconSprite(&gSprites[sSampleUiState->monIconSpriteId]);
        if (sSampleUiState->monIconDexNum > sDexRanges[sSampleUiState->region][0])
        {
            sSampleUiState->monIconDexNum--;
        }
        else
        {
            // Wrap dex number around
            sSampleUiState->monIconDexNum = sDexRanges[sSampleUiState->region][1];
        }
        SampleUi_DrawMonIcon(sSampleUiState->monIconDexNum);
        SampleUi_PrintUiMonInfo(WIN_MON_INFO, FONT_BLACK);
    }
    // User pressed A, cycle to next dex mode
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        if (sSampleUiState->mode == MODE_OTHER)
        {
            // Wrap back around to Info after the last mode
            sSampleUiState->mode = MODE_INFO;
        }
        else
        {
            sSampleUiState->mode++;
        }
        SampleUi_PrintUiButtonHints(WIN_UI_HINTS, FONT_WHITE);
        SampleUi_PrintUiMonInfo(WIN_MON_INFO, FONT_BLACK);
    }
    if (JOY_NEW(START_BUTTON))
    {
        gTasks[taskId].func = Task_SampleUiPanelSlide;
        PlaySE(SE_SELECT);
    }
}

static void Task_SampleUiPanelInput(u8 taskId)
{
    //Exit panel when Start or B is pressed
    if (JOY_NEW(START_BUTTON | B_BUTTON))
    {
        gTasks[taskId].func = Task_SampleUiPanelSlide;
        PlaySE(SE_SELECT);
    }
    if (JOY_NEW(A_BUTTON))
    {
        // LTODO fix affine anim
        gSprites[sSampleUiState->regionButtonSpriteIds[0]].oam.affineMode = ST_OAM_AFFINE_DOUBLE;
        StartSpriteAffineAnim(&gSprites[sSampleUiState->regionButtonSpriteIds[0]], SELECTED_ANIM);
        CalcCenterToCornerVec(&gSprites[sSampleUiState->regionButtonSpriteIds[0]], SPRITE_SHAPE(64x32), SPRITE_SIZE(64x32), ST_OAM_AFFINE_DOUBLE);
    }
    if (JOY_NEW(R_BUTTON))
    {
        gSprites[sSampleUiState->regionButtonSpriteIds[0]].oam.affineMode = ST_OAM_AFFINE_OFF;
        StartSpriteAnim(&gSprites[sSampleUiState->regionButtonSpriteIds[0]], DEFAULT_ANIM);
        CalcCenterToCornerVec(&gSprites[sSampleUiState->regionButtonSpriteIds[0]], SPRITE_SHAPE(64x32), SPRITE_SIZE(64x32), ST_OAM_AFFINE_OFF);
    }
    // Sneakily swap out color 2 in BG1's palette
    // LoadPalette(&sRegionBgColors[sSampleUiState->region], BG_PLTT_ID(0) + 2, 2);
}

static void Task_SampleUiPanelSlide(u8 taskId)
{
    #define PANEL_MAX_Y 95
    /*
     * Register BG2VOFS controls the vertical offset of background 2. Our sliding panel lives on
     * BG2, so by setting the value of this register we can change the starting Y position of the
     * background. We increase it a bit each frame to make the BG look like it is sliding into view.
     */
    SetGpuReg(REG_OFFSET_BG2VOFS, sSampleUiState->panelY);

    // Panel is open, so slide it down out of view
    if (sSampleUiState->panelIsOpen)
    {
        if (sSampleUiState->panelY > 0)
        {
            sSampleUiState->panelY -= 5;
            gSprites[sSampleUiState->regionButtonSpriteIds[REGION_KANTO]].y += 5;
            gSprites[sSampleUiState->regionButtonSpriteIds[REGION_JOHTO]].y += 5;
            gSprites[sSampleUiState->regionButtonSpriteIds[REGION_HOENN]].y += 5;
            gSprites[sSampleUiState->regionButtonSpriteIds[REGION_SINNOH]].y += 5;
            gSprites[sSampleUiState->regionButtonSpriteIds[REGION_UNOVA]].y += 5;
            gSprites[sSampleUiState->regionButtonSpriteIds[REGION_KALOS]].y += 5;
        }
        else if (sSampleUiState->panelY == 0)
        {
            // Panel is done closing, so set state to closed and change task to read main input
            sSampleUiState->panelIsOpen = FALSE;
            gTasks[taskId].func = Task_SampleUiMainInput;
        }
    }
    // Panel is closed, so slide it up into view
    else
    {
        if (sSampleUiState->panelY < PANEL_MAX_Y)
        {
            sSampleUiState->panelY += 5;
            gSprites[sSampleUiState->regionButtonSpriteIds[REGION_KANTO]].y -= 5;
            gSprites[sSampleUiState->regionButtonSpriteIds[REGION_JOHTO]].y -= 5;
            gSprites[sSampleUiState->regionButtonSpriteIds[REGION_HOENN]].y -= 5;
            gSprites[sSampleUiState->regionButtonSpriteIds[REGION_SINNOH]].y -= 5;
            gSprites[sSampleUiState->regionButtonSpriteIds[REGION_UNOVA]].y -= 5;
            gSprites[sSampleUiState->regionButtonSpriteIds[REGION_KALOS]].y -= 5;
        }
        else if (sSampleUiState->panelY == PANEL_MAX_Y)
        {
            // Panel is done opening, so set state to open and change task to read panel input
            sSampleUiState->panelIsOpen = TRUE;
            gTasks[taskId].func = Task_SampleUiPanelInput;
        }
    }
    #undef PANEL_MAX_Y
}

static void Task_SampleUiWaitFadeAndBail(u8 taskId)
{
    // Wait until the screen fades to black before we start doing cleanup
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sSampleUiState->savedCallback);
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
        SetMainCallback2(sSampleUiState->savedCallback);
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

    // Allocate our tilemap buffers on the heap
    sBg1TilemapBuffer = Alloc(TILEMAP_BUFFER_SIZE);
    if (sBg1TilemapBuffer == NULL)
    {
        // Bail if the allocation fails
        return FALSE;
    }
    sBg2TilemapBuffer = Alloc(TILEMAP_BUFFER_SIZE);
    if (sBg2TilemapBuffer == NULL)
    {
        // Bail if the allocation fails
        return FALSE;
    }

    // Clear whatever junk data is in the buffers
    memset(sBg1TilemapBuffer, 0, TILEMAP_BUFFER_SIZE);
    memset(sBg2TilemapBuffer, 0, TILEMAP_BUFFER_SIZE);

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

    // Set the BG manager to use our newly allocated tilemap buffers for BG1 and 2's tilemap
    SetBgTilemapBuffer(1, sBg1TilemapBuffer);
    SetBgTilemapBuffer(2, sBg2TilemapBuffer);

    /*
     * Schedule to copy the tilemap buffer contents (remember we zeroed it out earlier) for the next
     * VBlank. So right now, BG1 and 2 will just use Tile 0 for every tile. We will change this once
     * we load in our true tilemap values from sSampleUiTilemap and sSampleUiPanelTilemap.
     */
    ScheduleBgCopyTilemapToVram(1);
    ScheduleBgCopyTilemapToVram(2);

    // Set reg DISPCNT to show BG0, BG1, BG2
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);

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
    switch (sSampleUiState->loadState)
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
         * BgTemplates at the top -- we pass 1 for the bgId so it uses the charblock setting from
         * the BG1 template. Our BG2 panel shares these tiles, but we set BG2 to use the same
         * charblock so everything should work OK.
         * Size, offset, mode set to 0:
         * Size is 0 because that tells the function to set the size dynamically based on the
         * decompressed data. Offset is 0 because we want to tiles loaded right at whatever
         * charblock we set in the BgTemplate. And mode is 0 because we are copying tiles and not a
         * tilemap.
         *
         * `menu.c' also has a alternative function `DecompressAndLoadBgGfxUsingHeap', which does
         * the same thing but automatically frees the decompression buffer for you. If you want, you
         * can use that here instead and remove the `ResetTempTileDataBuffers' call above, since it
         * doesn't use the temp tile data buffers.
         */
        DecompressAndCopyTileDataToVram(1, sSampleUiTiles, 0, 0, 0);
        sSampleUiState->loadState++;
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
             * to a WRAM location given in `dest' (argument 2). In our case `dest' are just the
             * tilemap buffers we heap-allocated earlier.
             */
            LZDecompressWram(sSampleUiTilemap, sBg1TilemapBuffer);
            LZDecompressWram(sSampleUiPanelTilemap, sBg2TilemapBuffer);
            sSampleUiState->loadState++;
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
         * We are going to dynamically change the BG color depending on the region. We set up our
         * tiles so that the UI BG color is stored in Palette 0, slot 2. So we hot swap that to our
         * saved color for Kanto, since the UI starts in Kanto region. We will need to perform this
         * mini-swap each time the user changes regions.
         */
        LoadPalette(&sRegionBgColors[REGION_KANTO], BG_PLTT_ID(0) + 2, 2);
        /*
         * Copy the message box palette into BG palette buffer, slot 15. Our window is set to use
         * palette 15 and our text color constants are defined assuming we are indexing in this
         * palette.
         */
        LoadPalette(gMessageBox_Pal, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        sSampleUiState->loadState++;
    default:
        sSampleUiState->loadState = 0;
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

static const u8 sText_SampleUiButtonHint1[] = _("{DPAD_UPDOWN}Change POKéMON");
static const u8 sText_SampleUiButtonHint2[] = _("{A_BUTTON}Mode: {STR_VAR_1}");
static const u8 sText_SampleUiButtonHint3[] = _("{START_BUTTON}Region");
static const u8 sText_SampleUiButtonHint4[] = _("{B_BUTTON}Exit");
static void SampleUi_PrintUiButtonHints(u8 windowId, u8 colorIdx)
{
    // Copy the current mode name into a temp string variable
    StringCopy(gStringVar1, sModeNames[sSampleUiState->mode]);
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
        sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, sRegionNames[sSampleUiState->region]);
    AddTextPrinterParameterized4(windowId, FONT_SMALL, 47, 0, 0, 0,
        sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, sText_SampleUiButtonHint1);
    AddTextPrinterParameterized4(windowId, FONT_SMALL, 47, 10, 0, 0,
        sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, gStringVar2);
    AddTextPrinterParameterized4(windowId, FONT_SMALL, 47, 20, 0, 0,
        sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, sText_SampleUiButtonHint3);
        AddTextPrinterParameterized4(windowId, FONT_SMALL, 47, 30, 0, 0,
        sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, sText_SampleUiButtonHint4);
    /*
     * Explicitly copy to VRAM now that all text is draw into the window pixel buffer. We use
     * COPYWIN_GFX here since no changes were made to the BG tilemap, so no need to copy it again
     * (recall that GF windows use tile rendering).
     */
    CopyWindowToVram(windowId, COPYWIN_GFX);
}

static const u8 sText_SampleUiMonInfoSpecies[] = _("{NO}{STR_VAR_1} {STR_VAR_2}");
static const u8 sText_SampleUiMonStats[] = _("Put stats info here");
static const u8 sText_SampleUiMonOther[] = _("Put other info here");
static void SampleUi_PrintUiMonInfo(u8 windowId, u8 colorIdx)
{
    u16 speciesId = NationalPokedexNumToSpecies(sSampleUiState->monIconDexNum);

    // Clear the window before drawing new text
    FillWindowPixelBuffer(windowId, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    switch (sSampleUiState->mode)
    {
    case MODE_INFO:
        /*
         * Use the string manipulation library to get the National Dex num, species name, and dex
         * description into strings, ready to be drawn.
         */
        ConvertIntToDecimalStringN(gStringVar1, sSampleUiState->monIconDexNum,
            STR_CONV_MODE_LEADING_ZEROS, 3);
        StringCopy(gStringVar2, gSpeciesNames[speciesId]);
        StringExpandPlaceholders(gStringVar3, sText_SampleUiMonInfoSpecies);
        StringCopy(gStringVar4, gPokedexEntries[sSampleUiState->monIconDexNum].description);

        // The window drawing code here works just like in `SampleUi_PrintUiButtonHints'
        AddTextPrinterParameterized4(windowId, FONT_SHORT, 5, 3, 0, 0,
            sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, gStringVar3);
        AddTextPrinterParameterized4(windowId, FONT_SMALL, 5, 25, 0, 0,
            sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, gStringVar4);
        break;
    case MODE_STATS:
        AddTextPrinterParameterized4(windowId, FONT_SHORT, 5, 3, 0, 0,
            sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, sText_SampleUiMonStats);
        break;
    case MODE_OTHER:
        AddTextPrinterParameterized4(windowId, FONT_SHORT, 5, 3, 0, 0,
            sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, sText_SampleUiMonOther);
        break;
    default:
        break;
    }

    // Copy pixel buffer to VRAM now that we are done drawing text
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
    sSampleUiState->monIconSpriteId =
            CreateMonIcon(speciesId, SpriteCB_MonIcon, MON_ICON_X, MON_ICON_Y, 4, 0);
    // Set prio to 0 so the icon sprite draws on top of everything
    gSprites[sSampleUiState->monIconSpriteId].oam.priority = 0;
}

static void SampleUi_CreateRegionButtons(void)
{
    #define BUTTON_START_X 50
    #define BUTTON_START_Y 184
    LoadSpritePalette(&sKantoJohtoHoennButtonsSpritePalette);
    LoadSpritePalette(&sSinnohUnovaKalosButtonsSpritePalette);
    sSampleUiState->regionButtonSpriteIds[REGION_KANTO] =
        CreateSprite(&sKantoButtonSpriteTemplate, BUTTON_START_X, BUTTON_START_Y, 0);
    sSampleUiState->regionButtonSpriteIds[REGION_JOHTO] =
        CreateSprite(&sJohtoButtonSpriteTemplate, BUTTON_START_X + 70, BUTTON_START_Y, 0);
    sSampleUiState->regionButtonSpriteIds[REGION_HOENN] =
        CreateSprite(&sHoennButtonSpriteTemplate, BUTTON_START_X + 2*70, BUTTON_START_Y, 0);
    sSampleUiState->regionButtonSpriteIds[REGION_SINNOH] =
        CreateSprite(&sSinnohButtonSpriteTemplate, BUTTON_START_X, BUTTON_START_Y + 40, 0);
    sSampleUiState->regionButtonSpriteIds[REGION_UNOVA] =
        CreateSprite(&sUnovaButtonSpriteTemplate, BUTTON_START_X + 70, BUTTON_START_Y + 40, 0);
    sSampleUiState->regionButtonSpriteIds[REGION_KALOS] =
        CreateSprite(&sKalosButtonSpriteTemplate, BUTTON_START_X + 2*70, BUTTON_START_Y + 40, 0);
    #undef BUTTON_START_X
    #undef BUTTON_START_Y
}

static void SampleUi_FreeResources(void)
{
    // Free our data struct and our BG1 tilemap buffer
    if (sSampleUiState != NULL)
    {
        Free(sSampleUiState);
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
