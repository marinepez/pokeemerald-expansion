#ifndef GUARD_FIELD_POISON_H
#define GUARD_FIELD_POISON_H

// Exported type declarations

// Exported RAM declarations

// Exported ROM declarations

#define EGG_MOVES_ARRAY_COUNT           19
#define LVL_UP_MOVES_ARRAY_COUNT    (MAX_LEVEL_UP_MOVES > 50 ? MAX_LEVEL_UP_MOVES : 50)

void TryFieldPoisonWhiteOut(void);
s32 DoPoisonFieldEffect(void);
s32 DoExpLossFieldEffect(void);

#endif //GUARD_FIELD_POISON_H
