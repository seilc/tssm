#include "xCommon.h"
#include "xCollideFast.h"

#include "iMath3.h"

U32 xRayHitsSphereFast(const xRay3* r, const xSphere* s)
{
    xASSERT(r);
    xASSERT(s);

    xVec3 diff;
    xVec3Sub(&diff, &r->origin, &s->center);

    F32 c = xVec3Dot(&diff, &diff) - s->r * s->r;
    if (c <= 0.0f) {
        return TRUE;
    }

    if (r->flags & XRAY3_USE_MAX) {
        if (c > (2.0f * s->r + r->max_t) * r->max_t) {
            return FALSE;
        }
    }

    F32 b = xVec3Dot(&diff, &r->dir);
    if (b >= 0.0f) {
        return FALSE;
    }

    return (b * b >= c);
}

U32 xRayHitsBoxFast(const xRay3* r, const xBox* b)
{
    xASSERT(r);
    xASSERT(b);

    xIsect isx;
    iBoxIsectRay(b, r, &isx);

    return (isx.penned <= 0.0f || isx.contained <= 0.0f);
}
