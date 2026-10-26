#ifndef XENV_H
#define XENV_H

#include "iEnv.h"
#include "xLightKit.h"
#include "xBase.h"

struct xEnv
{
    iEnv* geom;
    iEnv ienv;
    xLightKit* lightKit;
};

struct xEnvAsset : xBaseAsset
{
    U32 bspAssetID;
    U32 startCameraAssetID;
    U32 climateFlags;
    F32 climateStrengthMin;
    F32 climateStrengthMax;
    U32 bspLightKit;
    U32 objectLightKit;
    F32 padF1;
    U32 bspCollisionAssetID;
    U32 bspFXAssetID;
    U32 bspCameraAssetID;
    U32 bspMapperID;
    U32 bspMapperCollisionID;
    U32 bspMapperFXID; // 0x3C
    F32 loldHeight;
};

struct _zEnv : xBase
{
    xEnvAsset* easset;
};

void zEnvInit(void* env, void* easset);
void zEnvInit(_zEnv* env, xEnvAsset* easset);
void zEnvSetup(_zEnv* env);
void zEnvStartingCamera(_zEnv* env);
void zEnvRender(xEnv* env);
void zEnvSave(_zEnv* ent, xSerial* s);
void zEnvLoad(_zEnv* ent, xSerial* s);
void zEnvReset(_zEnv* env);
S32 zEnvEventCB(xBase*, xBase* to, U32 toEvent, const F32* toParam, xBase*);

void xEnvLoadBsp(xEnv* env, const void* data, U32 datasize, S32 dataType);
void xEnvFree(xEnv* env);
void xEnvSetup(xEnv* env);
void xEnvRender(xEnv* env);
void xEnvRender(xEnv* env, bool);

#endif
