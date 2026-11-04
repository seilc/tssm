#ifndef XCLIMATE_H
#define XCLIMATE_H

#include "xVec3.h"

struct xEnvAsset;
struct zParEmitter;

extern const float snow_life;

typedef struct _tagRain
{
    S32 rain;
    F32 strength;
    zParEmitter* rain_emitter;
    zParEmitter* snow_emitter;
} Rain;

typedef struct _tagWind
{
    F32 strength;
    F32 angle;
    xVec3 dir;
} Wind;

typedef struct _tagClimate
{
    Rain rain;
    Wind wind;
} Climate;

void xClimateUpdate(Climate* climate, F32 seconds);
void UpdateRain(Climate* climate, F32 seconds);
void UpdateWind(Climate* climate, F32 seconds);
void xClimateSetRain(F32 stre);
void xClimateSetSnow(F32 stre);
void xClimateInitAsset(Climate* climate, xEnvAsset* easset);
void xClimateInit(Climate* climate);

#endif
