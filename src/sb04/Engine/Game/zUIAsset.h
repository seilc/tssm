#ifndef ZUIASSET_H
#define ZUIASSET_H

#include "xDynAsset.h"

struct zUIAsset : xDynAsset
{
    F32 x;
    F32 y;
    F32 z;
    F32 width;
    F32 height;
    S32 flags;
    U32 color;
    U32 selectedMotion;
    U32 unselectedMotion;
    U8 brightness;
    U8 pad[3];
    U32 autoMenuUp;
    U32 autoMenuDown;
    U32 autoMenuLeft;
    U32 autoMenuRight;
    U32 custom;
    U32 customWidget;
};

// zUIAsset::flags
#define k_ZUIASSET_VISIBLE (1 << 0)
#define k_ZUIASSET_FOCUS (1 << 1)
#define k_ZUIASSET_SELECTED (1 << 2)
#define k_ZUIASSET_FOCUS_ON_VISIBLE (1 << 3)
#define k_ZUIASSET_UNFOCUS_ON_INVISIBLE (1 << 4)
#define k_ZUIASSET_ALWAYS_INPUT (1 << 5)
#define k_ZUIASSET_SELECTED_MOTION (1 << 6)
#define k_ZUIASSET_UNSELECTED_MOTION (1 << 7)
#define k_ZUIASSET_VISIBLE_WITH_FOCUS (1 << 8)
#define k_ZUIASSET_BRIGHTEN (1 << 9)
#define k_ZUIASSET_AUTO_MENU (1 << 10)
#define k_ZUIASSET_SELECTED_MOTION_RESET (1 << 11)
#define k_ZUIASSET_UNSELECTED_MOTION_RESET (1 << 12)
#define k_ZUIASSET_SELECTED_MOTION_LOOP (1 << 13)
#define k_ZUIASSET_UNSELECTED_MOTION_LOOP (1 << 14)

#endif
