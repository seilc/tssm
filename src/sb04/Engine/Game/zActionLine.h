#ifndef ZACTIONLINE_H
#define ZACTIONLINE_H

#include "xVec3.h"

typedef struct _tagActionLine
{
    U32 flags;
    xVec3 pos[4];
    F32 time_left;
} ActionLine;

void zActionLineInit();
void zActionLineUpdate(F32 seconds);
void zActionLineRender();

#endif
