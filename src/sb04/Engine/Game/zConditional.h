#ifndef ZCONDITIONAL_H
#define ZCONDITIONAL_H

#include "xBase.h"

#define CONDITION_EQ 0
#define CONDITION_GT 1
#define CONDITION_LT 2
#define CONDITION_GE 3
#define CONDITION_LE 4
#define CONDITION_NE 5

struct zCondAsset : xBaseAsset
{
    U32 constNum;
    U32 expr1;
    U32 op;
    U32 value_asset;
};

typedef struct _zConditional : xBase
{
    zCondAsset* asset;
} zConditional;

void zConditionalInit(xBase* base, zCondAsset* asset);
void zConditionalInit(void* b, void* asset);
void zConditionalLoad(zConditional* ent, xSerial* s);
void zConditionalSave(zConditional* ent, xSerial* s);
U32 zConditional_Evaluate(zConditional* c);

#endif
