#ifndef ZPORTAL_H
#define ZPORTAL_H

#include "xBase.h"

struct xPortalAsset : xBaseAsset
{
    U32 assetCameraID;
    U32 assetMarkerID;
    F32 ang;
    U32 sceneID;
};

typedef struct _zPortal : xBase
{
    xPortalAsset* passet;
} zPortal;

void zPortalInit(void* portal, void* passet);
void zPortalInit(zPortal* portal, xPortalAsset* passet);
void zPortalSave(zPortal* ent, xSerial* s);
void zPortalLoad(zPortal* ent, xSerial* s);
S32 zPortalEventCB(xBase* from, xBase* to, U32 toEvent, const F32* toParam, xBase* b3);

#endif
