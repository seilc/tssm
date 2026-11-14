#ifndef XBASE_H
#define XBASE_H

#include "xBaseAsset.h"
#include "xLinkAsset.h"
#include "xserializer.h"

struct xBase;

typedef void(*xBaseEventCallback)(xBase* from, xBase* to, U32 toEvent, const F32* toParam, xBase* toParamWidget, U32 toParamWidgetID);

// Size: 0x10
struct xBase
{
    U32 id; // 0x0
    U8 baseType; // 0x4
    U8 linkCount; // 0x5
    U16 baseFlags; // 0x6
    xLinkAsset* link; // 0x8
    xBaseEventCallback eventFunc; // 0xC
};

// xBase::baseFlags
#define k_XBASE_RECEIVES_SHADOWS ((U16)(1 << 4))

void xBaseInit(xBase* xb, const xBaseAsset* asset);
void xBaseSetup(xBase* xb);
void xBaseSave(xBase* ent, xSerial* s);
void xBaseLoad(xBase* ent, xSerial* s);
void xBaseReset(xBase* xb, xBaseAsset* asset);
U32 xBaseIsValid(xBase* xb);
void xBaseValidate(xBase* xb);
bool xBaseIsEnabled(const xBase* xb);
void xBaseDisable(xBase* xb);
void xBaseEnable(xBase* xb);

#endif
