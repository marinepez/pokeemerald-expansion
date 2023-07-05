#include "global.h"
#include "event_data.h"
#include "lion_counter.h"

static void HandleHundreds(u16 count);
static void HandleLarger(u32 count);
static u32 GetCurrentLionCount(void);

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