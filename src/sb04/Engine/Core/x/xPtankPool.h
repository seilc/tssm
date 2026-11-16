#ifndef XPTANKPOOL_H
#define XPTANKPOOL_H

#include "xMath2.h"
#include "xMath3.h"
#include "xColor.h"
#include "xDebug.h"

#include <rwcore.h>
#include <rpworld.h>
#include <rpptank.h>

typedef struct iColor_tag iColor;

enum { BLOCK_SIZE = 80 };

enum ptank_group_type
{
    PGT_COLOR_MAT,
    PGT_COLOR_MAT_UV2,
    PGT_POS_COLOR_SIZE,
    PGT_POS_COLOR_SIZE_UV2,
    PGT_POS_COLOR_SIZE_ROT,
    PGT_POS_COLOR_SIZE_ROT_UV2,
    MAX_PGT
};

struct ptank_pool
{
    // render_state::flags
    enum
    {
        FLAG_NOZTEST = 0x1,
        FLAG_ZWRITE = 0x2,
        FLAG_ORDERED = 0x4,
        FLAG_BRIGHT = 0x8
    };

    struct render_state
    {
        RwTexture* texture;
        U32 src_blend;
        U32 dst_blend;
        S32 flags;
    };

    render_state rs;
    U32 order_group;
    S32 order_index;
    size_t used;
    RpAtomic* ptank;

    bool valid() const { return ptank != NULL; }

    void reset()
    {
        ptank = NULL;
        used = 0xffff;
    }

    void flush()
    {
        if (valid())
            unlock_block();
    }

    void unlock_block()
    {
        xASSERT(ptank != 0);
        xASSERT(used <= BLOCK_SIZE);
        RpPTankAtomicUnlock(ptank);
        RpPTankAtomicSetActiveParticlesCount(ptank, used);
    }

    void grab_block(ptank_group_type type);
};

struct ptank_pool__color_mat_uv2 : ptank_pool
{
    xColor* color;
    xMat4x3* mat;
    xVec2* uv;
    RwInt32 stride_color;
    RwInt32 stride_mat;
    RwInt32 stride_uv;

    void next()
    {
        if (used >= 80) {
            if (valid()) {
                unlock_block();
            }
            grab_block(PGT_COLOR_MAT_UV2);
            if (!valid()) {
                return;
            }
            lock_block();
        } else {
            color = (xColor*)((U8*)color + stride_color);
            mat = (xMat4x3*)((U8*)mat + stride_mat);
            uv = (xVec2*)((U8*)uv + stride_uv);
        }

        used++;
    }

    void lock_block()
    {
        used = 0;

        RpPTankLockStruct ls_color, ls_mat, ls_uv;
        RpPTankAtomicLock(ptank, &ls_color, rpPTANKLFLAGCOLOR, rpPTANKLOCKWRITE);
        RpPTankAtomicLock(ptank, &ls_mat, rpPTANKLFLAGMATRIX, rpPTANKLOCKWRITE);
        RpPTankAtomicLock(ptank, &ls_uv, rpPTANKLFLAGVTX2TEXCOORDS, rpPTANKLOCKWRITE);

        color = (xColor*)ls_color.data;
        mat = (xMat4x3*)ls_mat.data;
        uv = (xVec2*)ls_uv.data;
        stride_color = ls_color.stride;
        stride_mat = ls_mat.stride;
        stride_uv = ls_uv.stride;
    }
};

struct ptank_pool__pos_color_size_uv2 : public ptank_pool
{
    xVec3* pos;
    iColor* color;
    xVec2* size;
    xVec2* uv;
    S32 stride;

    void next();
    void flush();
};

void xPTankPoolSceneEnter();
void xPTankPoolSceneExit();
void xPTankPoolRender();

#endif
