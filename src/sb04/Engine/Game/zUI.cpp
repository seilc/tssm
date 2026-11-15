#include "xCommon.h"
#include "zUI.h"

#include "xstransvc.h"

void zUI::DoInit()
{
    selectedMotion = GetAsset()->selectedMotion == 0 ? NULL : (zUIMotionAsset*)xSTFindAsset(GetAsset()->selectedMotion, NULL);
    unselectedMotion = GetAsset()->unselectedMotion == 0 ? NULL : (zUIMotionAsset*)xSTFindAsset(GetAsset()->unselectedMotion, NULL);
    hdrPass = false;
    locked = false;
}
