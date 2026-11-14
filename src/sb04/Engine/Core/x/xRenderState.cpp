#include "xCommon.h"
#include "xRenderState.h"

#include <dolphin.h>

void xRenderSceneEnter()
{
}

void xRenderSceneExit()
{
}

static S32 sRenderStateBlendTable[] = {
    rwBLENDZERO, rwBLENDONE, rwBLENDSRCCOLOR, rwBLENDINVSRCCOLOR, rwBLENDSRCALPHA, rwBLENDINVSRCALPHA,
    rwBLENDDESTALPHA, rwBLENDINVDESTALPHA, rwBLENDDESTCOLOR, rwBLENDINVDESTCOLOR, rwBLENDSRCALPHASAT
};

static void* old_alpha_discard_value_gc;
static bool alphaDiscardCurrentlySet;

void xRenderStateSetAlphaDiscard(RwInt32 value)
{
    alphaDiscardCurrentlySet = true;
    RwRenderStateGet(rwRENDERSTATEALPHATESTFUNCTIONREF, &old_alpha_discard_value_gc);

    RwGameCubeSetAlphaCompare(GX_GEQUAL, value, GX_AOP_AND, GX_GEQUAL, value);

    if (value > 0) {
        _rwDlRenderStateSetZCompLoc(FALSE);
    } else {
        _rwDlRenderStateSetZCompLoc(TRUE);
    }
}

void xRenderStateResetAlphaDiscard()
{
    alphaDiscardCurrentlySet = false;

    RwGameCubeSetAlphaCompare(GX_GEQUAL, (RwUInt8)old_alpha_discard_value_gc, GX_AOP_AND, GX_GEQUAL,
                              (RwUInt8)old_alpha_discard_value_gc);

    if ((RwUInt8)old_alpha_discard_value_gc > 0) {
        _rwDlRenderStateSetZCompLoc(FALSE);
    } else {
        _rwDlRenderStateSetZCompLoc(TRUE);
    }
}

void xRenderFixUntexturedBegin(RpAtomic*)
{
}

void xRenderFixUntexturedEnd(RpAtomic*)
{
}

void xRenderFixIMBegin()
{
}

void xRenderFixIMEnd()
{
}
