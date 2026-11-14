#ifndef XIM_H
#define XIM_H

#include "xMath3.h"
#include "xMath2.h"
#include "xColor.h"

enum xIMFormat
{
    XIM_TRISTRIP = 4,
    XIM_TRILIST = 3
};

struct xIMLockContext
{
    void* data;
    xVec3* pos;
    xVec2* uv;
    xColor* color;
    S32 vertCount;
    xIMFormat format;
};

void xIMLock(xIMLockContext& context, xIMFormat format, S32 vertCount);
void xIMUnlock(xIMLockContext& context);
void xIMRender(xIMLockContext& context, const xMat4x3* mat);

#endif
