#ifndef XRAY3_H
#define XRAY3_H

#include "xMath3.h"

// xRay3::flags
#define XRAY3_USE_MIN (1<<10)
#define XRAY3_USE_MAX (1<<11)

struct xRay3
{
    xVec3 origin;
    xVec3 dir;
    F32 min_t;
    F32 max_t;
    S32 flags;
};

#endif
