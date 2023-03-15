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

// This file is identical to sample_ui.c, just without comments. In case you find them distracting.

struct SampleUiState
{
    MainCallback savedCallback;
    u8 loadState;
    u8 sMode;
    u8 sMonIconSpriteId;
    u16 sMonIconDexNum;
};

enum WindowIds
{
    WIN_UI_HINTS,
    WIN_MON_INFO
};

extern const struct PokedexEntry gPokedexEntries[];

static EWRAM_DATA struct SampleUiState *sSampleUiSavedState = NULL;
static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;

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
    [MODE_KANTO]   = {1, 151},
    [MODE_JOHTO]   = {152, 251},
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

static const u16 sModeBgColors[] = {
    [MODE_KANTO]   = 0x6a93,
    [MODE_JOHTO]   = 0x527a,
    [MODE_HOENN]   = 0x4f55,
    [MODE_SINNOH]  = 0x4b7c,
    [MODE_UNOVA]   = 0x5ef7,
    [MODE_KALOS]   = 0x76fb,
    [MODE_ALOLA]   = 0x471f,
};

static const struct BgTemplate sSampleUiBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .priority = 1
    },
    {
        .bg = 1,
        .charBaseIndex = 3,
        .mapBaseIndex = 30,
        .priority = 2
    },
};

static const struct WindowTemplate sSampleUiWindowTemplates[] =
{
    [WIN_UI_HINTS] =
    {
        .bg = 0,
        .tilemapLeft = 14,
        .tilemapTop = 0,
        .width = 16,
        .height = 6,
        .paletteNum = 15,
        .baseBlock = 1,
    },
    [WIN_MON_INFO] =
    {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 9,
        .width = 25,
        .height = 10,
        .paletteNum = 15,
        .baseBlock = 1 + (16 * 6),
    }
};

static const u32 sSampleUiTiles[] = INCBIN_U32("graphics/sample_ui/tiles.4bpp.lz");
static const u32 sSampleUiTilemap[] = INCBIN_U32("graphics/sample_ui/tilemap.bin.lz");
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
    [FONT_BLACK]  = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY,  TEXT_COLOR_LIGHT_GRAY},
    [FONT_WHITE]  = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE,      TEXT_COLOR_DARK_GRAY},
    [FONT_RED]    = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_RED,        TEXT_COLOR_LIGHT_GRAY},
    [FONT_BLUE]   = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_BLUE,       TEXT_COLOR_LIGHT_GRAY},
};

static void SampleUi_SetupCB(void);
static void SampleUi_MainCB(void);
static void SampleUi_VBlankCB(void);

static void Task_SampleUiWaitFadeIn(u8 taskId);
static void Task_SampleUiMain(u8 taskId);
static void Task_SampleUiWaitFadeAndBail(u8 taskId);
static void Task_SampleUiWaitFadeAndExitGracefully(u8 taskId);

void SampleUi_Init(MainCallback callback);
static bool8 SampleUi_InitBgs(void);
static void SampleUi_FadeAndBail(void);
static bool8 SampleUi_LoadGraphics(void);
static void SampleUi_InitWindows(void);
static void SampleUi_PrintUiButtonHints(u8 windowId, u8 colorIdx);
static void SampleUi_PrintUiMonInfo(u8 windowId, u8 colorIdx);
static void SampleUi_DrawMonIcon(u16 dexNum);
static void SampleUi_FreeResources(void);

void Task_OpenSampleUi(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        SampleUi_Init(CB2_ReturnToFieldWithOpenMenu);
        DestroyTask(taskId);
    }
}

void SampleUi_Init(MainCallback callback)
{
    sSampleUiSavedState = AllocZeroed(sizeof(struct SampleUiState));
    if (sSampleUiSavedState == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    sSampleUiSavedState->loadState = 0;
    sSampleUiSavedState->savedCallback = callback;

    SetMainCallback2(SampleUi_SetupCB);
}

static void SampleUi_SetupCB(void)
{
    u8 taskId;
    switch (gMain.state)
    {
    case 0:
        DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000);
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        gMain.state++;
        break;
    case 2:
        if (SampleUi_InitBgs())
        {
            sSampleUiSavedState->loadState = 0;
            gMain.state++;
        }
        else
        {
            SampleUi_FadeAndBail();
            return;
        }
        break;
    case 3:
        if (SampleUi_LoadGraphics() == TRUE)
        {
            gMain.state++;
        }
        break;
    case 4:
        SampleUi_InitWindows();
        gMain.state++;
        break;
    case 5:
        sSampleUiSavedState->sMode = MODE_KANTO;
        sSampleUiSavedState->sMonIconDexNum = sDexRanges[sSampleUiSavedState->sMode][0];

        FreeMonIconPalettes();
        LoadMonIconPalettes();

        SampleUi_DrawMonIcon(sSampleUiSavedState->sMonIconDexNum);
        SampleUi_PrintUiButtonHints(WIN_UI_HINTS, FONT_WHITE);
        SampleUi_PrintUiMonInfo(WIN_MON_INFO, FONT_BLACK);

        taskId = CreateTask(Task_SampleUiWaitFadeIn, 0);
        gMain.state++;
        break;
    case 6:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    case 7:
        SetVBlankCallback(SampleUi_VBlankCB);
        SetMainCallback2(SampleUi_MainCB);
        break;
    }
}

static void SampleUi_MainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void SampleUi_VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void Task_SampleUiWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        gTasks[taskId].func = Task_SampleUiMain;
    }
}

static void Task_SampleUiMain(u8 taskId)
{
    if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_PC_OFF);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_SampleUiWaitFadeAndExitGracefully;
    }
    if (JOY_REPEAT(DPAD_DOWN))
    {
        PlaySE(SE_SELECT);
        FreeAndDestroyMonIconSprite(&gSprites[sSampleUiSavedState->sMonIconSpriteId]);
        if (sSampleUiSavedState->sMonIconDexNum < sDexRanges[sSampleUiSavedState->sMode][1])
        {
            sSampleUiSavedState->sMonIconDexNum++;
        }
        else
        {
            sSampleUiSavedState->sMonIconDexNum = sDexRanges[sSampleUiSavedState->sMode][0];
        }
        SampleUi_DrawMonIcon(sSampleUiSavedState->sMonIconDexNum);
        SampleUi_PrintUiMonInfo(WIN_MON_INFO, FONT_BLACK);
    }
    if (JOY_REPEAT(DPAD_UP))
    {
        PlaySE(SE_SELECT);
        FreeAndDestroyMonIconSprite(&gSprites[sSampleUiSavedState->sMonIconSpriteId]);
        if (sSampleUiSavedState->sMonIconDexNum > sDexRanges[sSampleUiSavedState->sMode][0])
        {
            sSampleUiSavedState->sMonIconDexNum--;
        }
        else
        {
            sSampleUiSavedState->sMonIconDexNum = sDexRanges[sSampleUiSavedState->sMode][1];
        }
        SampleUi_DrawMonIcon(sSampleUiSavedState->sMonIconDexNum);
        SampleUi_PrintUiMonInfo(WIN_MON_INFO, FONT_BLACK);
    }
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        if (sSampleUiSavedState->sMode == MODE_ALOLA)
        {
            sSampleUiSavedState->sMode = MODE_KANTO;
        }
        else
        {
            sSampleUiSavedState->sMode++;
        }
        sSampleUiSavedState->sMonIconDexNum = sDexRanges[sSampleUiSavedState->sMode][0];
        FreeAndDestroyMonIconSprite(&gSprites[sSampleUiSavedState->sMonIconSpriteId]);

        SampleUi_DrawMonIcon(sSampleUiSavedState->sMonIconDexNum);
        SampleUi_PrintUiButtonHints(WIN_UI_HINTS, FONT_WHITE);
        SampleUi_PrintUiMonInfo(WIN_MON_INFO, FONT_BLACK);

        LoadPalette(&sModeBgColors[sSampleUiSavedState->sMode], BG_PLTT_ID(0) + 2, 2);
    }
}

static void Task_SampleUiWaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sSampleUiSavedState->savedCallback);
        SampleUi_FreeResources();
        DestroyTask(taskId);
    }
}

static void Task_SampleUiWaitFadeAndExitGracefully(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sSampleUiSavedState->savedCallback);
        SampleUi_FreeResources();
        DestroyTask(taskId);
    }
}

#define TILEMAP_BUFFER_SIZE (1024 * 2)
static bool8 SampleUi_InitBgs(void)
{
    ResetAllBgsCoordinates();

    sBg1TilemapBuffer = Alloc(TILEMAP_BUFFER_SIZE);
    if (sBg1TilemapBuffer == NULL)
    {
        return FALSE;
    }

    memset(sBg1TilemapBuffer, 0, TILEMAP_BUFFER_SIZE);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sSampleUiBgTemplates, NELEMS(sSampleUiBgTemplates));
    SetBgTilemapBuffer(1, sBg1TilemapBuffer);
    ScheduleBgCopyTilemapToVram(1);

    ShowBg(0);
    ShowBg(1);

    return TRUE;
}
#undef TILEMAP_BUFFER_SIZE

static void SampleUi_FadeAndBail(void)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_SampleUiWaitFadeAndBail, 0);

    SetVBlankCallback(SampleUi_VBlankCB);
    SetMainCallback2(SampleUi_MainCB);
}

static bool8 SampleUi_LoadGraphics(void)
{
    switch (sSampleUiSavedState->loadState)
    {
    case 0:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(1, sSampleUiTiles, 0, 0, 0);
        sSampleUiSavedState->loadState++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            LZDecompressWram(sSampleUiTilemap, sBg1TilemapBuffer);
            sSampleUiSavedState->loadState++;
        }
        break;
    case 2:
        LoadPalette(sSampleUiPalette, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
        LoadPalette(&sModeBgColors[MODE_KANTO], BG_PLTT_ID(0) + 2, 2);
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
    InitWindows(sSampleUiWindowTemplates);
    DeactivateAllTextPrinters();
    ScheduleBgCopyTilemapToVram(0);
    FillWindowPixelBuffer(WIN_UI_HINTS, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    FillWindowPixelBuffer(WIN_MON_INFO, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    PutWindowTilemap(WIN_UI_HINTS);
    PutWindowTilemap(WIN_MON_INFO);
    CopyWindowToVram(WIN_UI_HINTS, 3);
    CopyWindowToVram(WIN_MON_INFO, 3);
}

static const u8 sText_SampleUiDex[] = _("DEX");
static const u8 sText_SampleUiButtonHint1[] = _("{DPAD_UPDOWN}Change POKéMON");
static const u8 sText_SampleUiButtonHint2[] = _("{A_BUTTON}Mode: {STR_VAR_1}");
static const u8 sText_SampleUiButtonHint3[] = _("{B_BUTTON}Exit");
static void SampleUi_PrintUiButtonHints(u8 windowId, u8 colorIdx)
{
    StringCopy(gStringVar1, sModeNames[sSampleUiSavedState->sMode]);
    StringExpandPlaceholders(gStringVar2, sText_SampleUiButtonHint2);

    FillWindowPixelBuffer(windowId, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    AddTextPrinterParameterized4(windowId, FONT_NORMAL, 0, 3, 0, 0, sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, sText_SampleUiDex);
    AddTextPrinterParameterized4(windowId, FONT_SMALL, 47, 0, 0, 0, sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, sText_SampleUiButtonHint1);
    AddTextPrinterParameterized4(windowId, FONT_SMALL, 47, 10, 0, 0, sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, gStringVar2);
    AddTextPrinterParameterized4(windowId, FONT_SMALL, 47, 20, 0, 0, sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, sText_SampleUiButtonHint3);
    CopyWindowToVram(windowId, COPYWIN_GFX);
}

static const u8 sText_SampleUiMonInfoSpecies[] = _("{NO}{STR_VAR_1} {STR_VAR_2}");
static void SampleUi_PrintUiMonInfo(u8 windowId, u8 colorIdx)
{
    u16 speciesId = NationalPokedexNumToSpecies(sSampleUiSavedState->sMonIconDexNum);

    ConvertIntToDecimalStringN(gStringVar1, sSampleUiSavedState->sMonIconDexNum, STR_CONV_MODE_LEADING_ZEROS, 3);
    StringCopy(gStringVar2, gSpeciesNames[speciesId]);
    StringExpandPlaceholders(gStringVar3, sText_SampleUiMonInfoSpecies);
    StringCopy(gStringVar4, gPokedexEntries[sSampleUiSavedState->sMonIconDexNum].description);

    FillWindowPixelBuffer(windowId, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    AddTextPrinterParameterized4(windowId, FONT_SHORT, 5, 3, 0, 0, sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, gStringVar3);
    AddTextPrinterParameterized4(windowId, FONT_SMALL, 5, 25, 0, 0, sSampleUiWindowFontColors[colorIdx], TEXT_SKIP_DRAW, gStringVar4);
    CopyWindowToVram(windowId, COPYWIN_GFX);
}

static void SampleUi_DrawMonIcon(u16 dexNum)
{
    u16 speciesId = NationalPokedexNumToSpecies(dexNum);
    sSampleUiSavedState->sMonIconSpriteId = CreateMonIcon(speciesId, SpriteCB_MonIcon, MON_ICON_X, MON_ICON_Y, 4, 0);
    gSprites[sSampleUiSavedState->sMonIconSpriteId].oam.priority = 0;
}

static void SampleUi_FreeResources(void)
{
    if (sSampleUiSavedState != NULL)
    {
        Free(sSampleUiSavedState);
    }
    if (sBg1TilemapBuffer != NULL)
    {
        Free(sBg1TilemapBuffer);
    }
    FreeAllWindowBuffers();
    ResetSpriteData();
}
