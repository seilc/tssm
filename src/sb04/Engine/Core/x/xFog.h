#ifndef XFOG_H
#define XFOG_H

#include "xEnt.h"
#include "xBase.h"

struct xFogAsset : xBaseAsset
{
    U8 bkgndColor[4];
    U8 fogColor[4];
    F32 fogDensity;
    F32 fogStart;
    F32 fogStop;
    F32 transitionTime;
    U8 fogType;
    U8 padFog[3];
};

typedef struct _xFog : xBase
{
    xFogAsset* tasset;
} xFog;

void xFogClearFog();
void xFogInit(void* b, void* tasset);
void xFogInit(xBase* ent, xFogAsset* tasset);
void xFogReset(xFog* ent);
void xFogSave(xFog* ent, xSerial* s);
void xFogLoad(xFog* ent, xSerial* s);
S32 xFogEventCB(xBase* to, xBase* from, U32 toEvent, const F32* toParam, xBase* b3);
void xFogUpdate(xBase* ent, xScene* sc, F32 dt);

#endif
