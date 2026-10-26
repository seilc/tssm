#ifndef XMODELBLUR_H
#define XMODELBLUR_H

#include "xFX.h"

struct activity_data_2
{
    struct tier_queue
    {
        U32 first;
        U32 _size;
        U32 wrap_mask;
        tier_queue_allocator* alloc;
        U8 blocks[32];
    };
    xFXRibbon* owner;
    activity_data_2** position;
    tier_queue joints;
    S32 curve_index;
    F32 ilife;
    U32 mtime;
    U32 mlife;
};

struct xModelBlur
{
    activity_data_2* activity;
};

#endif
