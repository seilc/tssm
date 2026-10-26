#ifndef XWAD3_H
#define XWAD3_H

#include <PowerPC_EABI_Support\MSL_C\MSL_Common\cmath>
#include <PowerPC_EABI_Support\MSL_C\MSL_Common\stdlib.h>

#include "stdlib.h"
#include <types.h>
#include <rpworld.h>
#include "rwcore.h"
#include "xModel.h"
#include "iModel.h"
#include "xordarray.h"
#include "xMovePoint.h"
#include "xScene.h"
#include "xMorph.h"
#include "xModelBucket.h"
#include "xMemMgr.h"
#include "iSystem.h"
#include "xCamera.h"
#include "xMathInlines.h"

F32 xVec3Hdng(xVec3* a, const xVec3* b, const xVec3* c);

#endif
