#ifndef GUARD_LION_COUNTER_H
#define GUARD_LION_COUNTER_H

s8 Lion_isMonEnabled(u16 species);
void Lion_SetMonEnabled(u16 species);
void LionCounter_DecrementLionCounter(u32 count);
void LionCounter_SetLionCounter(u16 mil, u16 thou, u16 hund);

#endif // GUARD_LION_COUNTER_H