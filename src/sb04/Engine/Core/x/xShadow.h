#ifndef XSHADOW_H
#define XSHADOW_H

#include "xEnt.h"

#include <rwcore.h>
#include <rpworld.h>

#define SHADOW_CACHE_ENT_MAX 16

struct xShadowPoly
{
    xVec3 vert[3];
    xVec3 norm;
};

struct xShadowCache
{
    xVec3 pos;
    F32 radius;
    S32 entCount;
    S32 polyCount;
    F32 polyRayDepth[5];
    U16 castOnEnt;
    U16 castOnPoly;
    U32 pad;
    xEnt* ent[SHADOW_CACHE_ENT_MAX];
    xShadowPoly poly[256];
};

struct xShadowMgr
{
    xEnt* ent;
    xShadowCache* cache;
    int priority;
    int cacheReady;
};

void xShadow_ListAdd(xEnt* ent);
void xShadowSetWorld(RpWorld* world);
void xShadowSetLight(xVec3* param1, xVec3* param2, F32 param3);
void xShadowCameraUpdate(void* model, void (*renderCB)(void*), xVec3* center, F32 radius, S32 shadowMode);
void xShadowManager_Init(S32 numEnts);
void xShadowManager_Reset();
void xShadowManager_Render();
void xShadowRender(xEnt* ent, F32 max_dist);
void xShadowVertical_FillCache(xShadowCache* cache, xVec3* pos, F32 r, F32 depth, F32 minNormY);
void xShadowVertical_DrawCache(xShadowCache* cache, F32 shadowFactor, F32 fadeDist, S32 shadowMode, RwMatrix* shadowMat, RwRaster* shadowRast);

#endif
