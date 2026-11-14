#ifndef XRAND_H
#define XRAND_H

#include "types.h"

enum xRandomChoiceRule
{
    xRandomChoiceRule_ANY_EXCEPT_LAST,
    xRandomChoiceRule_ANY,
    xRandomChoiceRule_ANY_NOT_CHOSEN,
    xRandomChoiceRule_IN_ORDER,
    xRandomChoiceRule_IN_ORDER_RANDOM,
    xRandomChoiceRule_COUNT
};

void init_by_array(U32* init_key, U32 key_length);
void xrand_RandomInit();
void xrand_SetRandomSeed(U32 nNewSeed); // UNUSED
U32 xrand_GenRandInt32();
F32 xrand_GenRandFloat();
U32 xrand_RandomChoice(U32& chosenMask, U8& setBits, U32 maxCount, xRandomChoiceRule rule);

U16 xrand_RandomInt16();
U32 xrand_RandomInt32();

inline U16 xrand_RandomInt16()
{
    return (U16)xrand_RandomInt32();
}

inline U32 xrand_RandomInt32()
{
    return xrand_GenRandInt32();
}

inline U32 xrand_RandomChoice(U32 nChoice)
{
    return (nChoice * xrand_RandomInt16()) / 0x10000;
}

#endif
