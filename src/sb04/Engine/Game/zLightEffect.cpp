#include "zLightEffect.h"

void zLightEffectInitCauldron(zLight* zlight)
{
    *zlight->reg = 0.0f;
    zlight->flags = zlight->flags | 1;
}

void zLightEffectRandomColFast(zLight* zlight, F32)
{
}

void zLightEffectRandomCol(zLight* zlight, F32)
{
}

void zLightEffectRandomColSlow(zLight* zlight, F32)
{
}

void zLightEffectHalfDimFast(zLight* zlight, F32)
{
}

void zLightEffectHalfDim(zLight* zlight, F32)
{
}

void zLightEffectHalfDimSlow(zLight* zlight, F32)
{
}

void zLightEffectDimFast(zLight* zlight, F32)
{
}

void zLightEffectDim(zLight* zlight, F32)
{
}

void zLightEffectDimSlow(zLight* zlight, F32)
{
}

void zLightEffectStrobeFast(zLight* zlight, F32)
{
}

void zLightEffectStrobe(zLight* zlight, F32)
{
}

void zLightEffectStrobeSlow(zLight* zlight, F32)
{
}

void zLightEffectInitFlicker(zLight* zlight)
{
    *zlight->reg = 0.0f;
    zlight->flags = zlight->flags | 1;
}

void zLightEffectInitRandomCol(zLight*)
{
}

void zLightEffectInitHalfDim(zLight*)
{
}

void zLightEffectInitDim(zLight*)
{
}

void zLightEffectInitStrobe(zLight*)
{
}
