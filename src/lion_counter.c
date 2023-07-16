#include "global.h"
#include "event_data.h"
#include "pokedex.h"
#include "pokemon_storage_system.h"
#include "pokemon.h"
#include "script_pokemon_util.h"
#include "lion_counter.h"

static void HandleHundreds(u16 count);
static void HandleLarger(u32 count);
static u32 GetCurrentLionCount(void);

void ResetUnlockedPokemon(void)
{
    s32 i;
    int boxId, boxPosition;
    u32 personality;
    struct Pokemon mon;
    u16 species = SPECIES_BULBASAUR;

    for (i = 0; i < NUMBER_OF_MON_TYPES; i++)
        gSaveBlock1Ptr->lionsDefeated[i] = 0;

    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        for (boxPosition = 0; boxPosition < IN_BOX_COUNT; boxPosition++)
        {
            if (!GetBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition], MON_DATA_SANITY_HAS_SPECIES))
            {
                CreateMon(&mon, species, 100, 31,
                            0, 0, OT_ID_PLAYER_ID, 0);

                CopyMon(GetBoxedMonPtr(boxId, boxPosition), &(mon.box), sizeof(mon.box));
                GetSetPokedexFlag(species, FLAG_SET_SEEN);
                GetSetPokedexFlag(species, FLAG_SET_CAUGHT);
                species++;

                if(species > SPECIES_CALYREX) break;
            }
        }
    }

    LionCounter_SetLionCounter(1000,000,000);
    Lion_SetMonEnabled(SPECIES_BULBASAUR);
    Lion_SetMonEnabled(SPECIES_CHARMANDER);
    Lion_SetMonEnabled(SPECIES_SQUIRTLE);

    ScriptGiveMon(SPECIES_BULBASAUR, 20, ITEM_NONE, 0, 0, 0);
    ScriptGiveMon(SPECIES_CHARMANDER, 20, ITEM_NONE, 0, 0, 0);
    ScriptGiveMon(SPECIES_SQUIRTLE, 20, ITEM_NONE, 0, 0, 0);

    FlagSet(FLAG_SYS_POKEMON_GET);
}

s8 Lion_isMonEnabled(u16 species)
{
    u32 index, bit, mask;

    if(SPECIES_UNOWN_B <= species && species <= SPECIES_UNOWN_QMARK)
        species = SPECIES_UNOWN;

    index = species / 8;
    bit = species % 8;
    mask = 1 << bit;

    return ((gSaveBlock1Ptr->monEnabled[index] & mask) != 0);
}

void Lion_SetMonEnabled(u16 species)
{
    u32 index, bit, mask;
    u16 i;
    index = species / 8;
    bit = species % 8;
    mask = 1 << bit;

    gSaveBlock1Ptr->monEnabled[index] |= mask;
}

static void HandleHundreds(u16 count)
{
    u16 val1, val2, val3;
    val1 = VarGet(VAR_BIL_DIGITS_7_TO_9);
    if(val1 >= count) 
    {
        VarSet(VAR_BIL_DIGITS_7_TO_9, val1 - count);
        return;
    }
    
    val2 = VarGet(VAR_BIL_DIGITS_4_TO_6);
    if(val2 > 0)
    {
        VarSet(VAR_BIL_DIGITS_4_TO_6, val2 - 1);
        VarSet(VAR_BIL_DIGITS_7_TO_9, 1000 - (count - val1));
        return;
    }

    val3 = VarGet(VAR_BIL_DIGITS_0_TO_3);
    if(val3 > 0) 
    {
        VarSet(VAR_BIL_DIGITS_0_TO_3, val3 - 1);
        VarSet(VAR_BIL_DIGITS_4_TO_6, 999);
        VarSet(VAR_BIL_DIGITS_7_TO_9, 1000 - (count - val1));
        return;
    }
    
    //The amount we want to decrement by is more than the total lions remaining
    VarSet(VAR_BIL_DIGITS_7_TO_9, 0);
}

static void HandleLarger(u32 amount)
{
    u32 LionCount = GetCurrentLionCount();
    if(amount >= LionCount) 
    {
        VarSet(VAR_BIL_DIGITS_0_TO_3, 0);
        VarSet(VAR_BIL_DIGITS_4_TO_6, 0);
        VarSet(VAR_BIL_DIGITS_7_TO_9, 0);
    }
    else
    {
        LionCount -= amount;
        LionCounter_SetLionCounter(LionCount / 1000000, (LionCount / 1000) % 1000, LionCount % 1000);   
    }
}

static u32 GetCurrentLionCount(void)
{
    u32 CurrLions = 
          VarGet(VAR_BIL_DIGITS_0_TO_3) * 1000000
        + VarGet(VAR_BIL_DIGITS_4_TO_6) * 1000
        + VarGet(VAR_BIL_DIGITS_7_TO_9);
    return CurrLions;
}

void CMD_LionCounter_DecrementCounter(void)
{
    u32 amount = VarGet(VAR_DECREMENT_COUNT) + (VarGet(VAR_DECREMENT_THOUSANDS) * 1000);
    VarSet(VAR_DECREMENT_COUNT, 0);
    VarSet(VAR_DECREMENT_THOUSANDS, 0);
    LionCounter_DecrementLionCounter(amount);
}

void LionCounter_DecrementLionCounter(u32 amount)
{
    //Trying to make the most common case fastest
    if(amount < 1000)
        HandleHundreds(amount);
    else
        HandleLarger(amount);
}

void LionCounter_SetLionCounter(u16 mil, u16 thou, u16 hund)
{
    if (mil > 1000)     mil = 1000;
    if (thou > 1000)    thou = 999;
    if (hund > 1000)    hund = 999;
    VarSet(VAR_BIL_DIGITS_0_TO_3, mil);
    VarSet(VAR_BIL_DIGITS_4_TO_6, thou);
    VarSet(VAR_BIL_DIGITS_7_TO_9, hund);
}