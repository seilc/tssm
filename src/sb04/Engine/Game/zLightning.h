#ifndef ZLIGHTNING_H
#define ZLIGHTNING_H

#include "xMath3.h"
#include "iColor.h"

#include "zFX.h"

typedef struct _tagLightningAdd
{
    U32 type;
    F32 setup_degrees;
    F32 move_degrees;
    F32 rot_radius;
    xVec3* start;
    xVec3* end;
    S16 total_points;
    S16 end_points;
    F32 time;
    F32 arc_height;
    F32 thickness;
    iColor color;
    F32 rand_radius;
    U32 flags;
    F32 zeus_normal_offset;
    F32 zeus_back_offset;
    F32 zeus_side_offset;
} LightningAdd;

typedef struct _tagLightningLine
{
    F32 unused;
} LightningLine;

typedef struct _tagLightningRot
{
    F32 deg[16];
    F32 degrees;
    F32 height;
} LightningRot;

typedef struct _tagLightningZeus
{
    F32 normal_offset;
    F32 back_offset;
    F32 side_offset;
} LightningZeus;

struct zLightning
{
    U32 type;
    U32 flags;
    union
    {
        struct
        {
            xVec3 base_point[16];
            xVec3 point[16];
            S16 total_points;
            S16 end_points;
            F32 arc_height;
            xVec3 arc_normal;
            F32 thickness[16];
            union
            {
                LightningLine line;
                LightningRot rot;
                LightningZeus zeus;
            };
            F32 rand_radius;
        } legacy;
        struct
        {
            xVec3 endPoint[2];
            xVec3 direction;
            F32 length;
            F32 scale;
            F32 width;
            F32 endParam[2];
            F32 endVel[2];
            F32 paramSpan[2];
            F32 arc_height;
            xVec3 arc_normal;
        } func;
    };
    iColor color;
    F32 time_left;
    F32 time_total;
};

struct zLightningFuncPiece
{
    xVec3 coef0;
    F32 param;
    xVec3 coef1;
    U32 pad;
};

void lightningTweakChangeType(tweak_info& t);
void lightningTweakStart(tweak_info& t);
void zLightningInit();
zLightning* zLightningAdd(LightningAdd* add);
void UpdateLightning(zLightning* l, F32 seconds);
void zLightningUpdate(F32 seconds);
void zLightningFunc_Render(zLightning* l);
void zLightningShow(zLightning* l, S32 show);
void zLightningKill(zLightning* l);
void RenderLightning(zLightning* l);
void zLightningRender();
void zLightningModifyEndpoints(zLightning* l, xVec3* start, xVec3* end);
void zLightningInit();
void zLightningUpdate(F32 seconds);
void zLightningRender();

#endif
