#ifndef ZUIMOTIONCMDASSET_H
#define ZUIMOTIONCMDASSET_H

#include "types.h"

struct zUIMotionCmdAsset
{
    U32 type;
    F32 startTime;
    F32 endTime;
    F32 accelTime;
    F32 decelTime;
    U8 enabled;
};

// zUIMotionCmdAsset::type
#define k_ZUIMOTIONCMD_MOVE 0
#define k_ZUIMOTIONCMD_SCALE 1
#define k_ZUIMOTIONCMD_ROTATE 2
#define k_ZUIMOTIONCMD_OPACITY 3
#define k_ZUIMOTIONCMD_ABSOLUTE_SCALE 4
#define k_ZUIMOTIONCMD_BRIGHTNESS 5
#define k_ZUIMOTIONCMD_COLOR 6
#define k_ZUIMOTIONCMD_UV_SCROLL 7

struct zUIMotionCmdMove : zUIMotionCmdAsset
{
    F32 distX;
    F32 distY;
};

struct zUIMotionCmdScale : zUIMotionCmdAsset
{
    F32 amountX;
    F32 amountY;
    U8 centerPivot;
    F32 centerOffsetX;
    F32 centerOffsetY;
};

struct zUIMotionCmdRotate : zUIMotionCmdAsset
{
    F32 rotation;
    F32 centerOffsetX;
    F32 centerOffsetY;
};

struct zUIMotionCmdOpacity : zUIMotionCmdAsset
{
    U8 startOpacity;
    U8 endOpacity;
};

struct zUIMotionCmdAbsoluteScale : zUIMotionCmdAsset
{
    F32 startX;
    F32 startY;
    F32 endX;
    F32 endY;
    U8 centerPivot;
    U8 textScale;
};

struct zUIMotionCmdBrightness : zUIMotionCmdAsset
{
    U8 startBrightness;
    U8 endBrightness;
};

struct zUIMotionCmdColor : zUIMotionCmdAsset
{
    U8 startRed;
    U8 startGreen;
    U8 startBlue;
    U8 endRed;
    U8 endGreen;
    U8 endBlue;
};

struct zUIMotionCmdUVScroll : zUIMotionCmdAsset
{
    F32 amountU;
    F32 amountV;
};

#endif
