#ifndef XFXHIGHDYNAMICRANGE_H
#define XFXHIGHDYNAMICRANGE_H

#include "types.h"

#include <rwcore.h>
#include <rpworld.h>

struct xFXHighDynamicRangeConfiguration
{
    S32 glow;
    S32 darken;
    S32 downsamples;
    F32 overbrighten;
    F32 overbrighten_decay;
    bool blur_faster;
};

extern bool HDR_brightening;

void xFXHighDynamicRangeInit();
void xFXHighDynamicRangeSceneEnter();
void xFXHighDynamicRangeSceneExit();
void xFXHighDynamicRangeReset();
void xFXHighDynamicRangeStartRender();
void xFXHighDynamicRangeRender(RwCamera*);
U32 xFXHighDynamicRangeBrightenPtank(RpAtomic* ptank, bool bright);
void xFXHighDynamicRangeRestorePtank(RpAtomic* ptank, U32 oldtest);
void xFXHighDynamicRangeTunePalette(RwRaster* raster, F32 base_alpha, bool additive);
void xFXHighDynamicRangeUpdate(F32 dt);
void xFXHighDynamicRangeEnable(bool enable);
S32 xFXHighDynamicRangeGetBackgroundGlow();
void xFXHighDynamicRangeSetConfiguration(const xFXHighDynamicRangeConfiguration& configuration);
void xFXHighDynamicRangeGetConfiguration(xFXHighDynamicRangeConfiguration& configuration);
void xFXHighDynamicRangeSetGlowClamp(S32 glow_min, bool dest_test);
void xFXHighDynamicRangeResetGlowClamp();
void xFXHighDynamicRangeSetBackgroundDefault(S32 glow, S32 darken, bool apply);

#endif
