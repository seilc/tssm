#include "xVec3.h"

struct spark_particle
{
    xVec3 loc;
    F32 scale;
    xVec3 vel;
    F32 life;
    U8 group_index;
    U8 pad1;
    U8 pad2;
    U8 pad3;
    F32 alpha;
    F32 alpha_vel;
    F32 gravity;
};
