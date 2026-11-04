#ifndef ZLIGHTEFFECT_H
#define ZLIGHTEFFECT_H

#include "iLight.h"
#include "xBase.h"
#include "zLight.h"

typedef void (*lightInitFunc)(zLight*);

void zLightEffectSet(zLight* zlight, S32 idx);
void zLightOn(zLight* zl, S32 on);
static F32 leGetRandom();
void zLightEffectInitStrobe(zLight* zlight);
void zLightEffectInitDim(zLight* zlight);
void zLightEffectInitHalfDim(zLight* zlight);
void zLightEffectInitRandomCol(zLight* zlight);
void zLightEffectInitFlicker(zLight* zlight);
static void EffectFlicker(zLight* zlight, F32 seconds, F32 min, F32 rnd);
void zLightEffectFlicker(zLight* zlight, F32 seconds);
void zLightEffectFlickerSlow(zLight* zlight, F32 seconds);
void zLightEffectFlickerErratic(zLight* zlight, F32 seconds);

void zLightEffectInitCauldron(zLight* zlight);
static F32 leBlendToCol(F32 f1, F32 f2, F32 f3);
void zLightEffectCauldron(zLight* zlight, F32 seconds);

#endif
