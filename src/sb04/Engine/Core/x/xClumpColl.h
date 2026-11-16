#ifndef XCLUMPCOLL_H
#define XCLUMPCOLL_H

#include <types.h>

#include <rwcore.h>
#include <rpworld.h>

struct xClumpCollBSPBranchNode
{
    U32 leftInfo;
    U32 rightInfo;
    F32 leftValue;
    F32 rightValue;
};

struct xClumpCollBSPVertInfo
{
    U16 atomIndex;
    U16 meshVertIndex;
};

struct xClumpCollBSPTriangle
{
    union
    {
        xClumpCollBSPVertInfo i;
        U32 rawIdx;
        RwV3d* p;
    } v;
    U8 flags;
    U8 detailed_info_cache_index;
    U16 matIndex;
};

struct xClumpCollBSPTree
{
    S32 numBranchNodes;
    xClumpCollBSPBranchNode* branchNodes;
    S32 numTriangles;
    xClumpCollBSPTriangle* triangles;
};

struct nodeInfo
{
    U32 type;
    U32 index;
};

struct xClumpCollV3dGradient
{
    F32 dydx;
    F32 dzdx;
    F32 dxdy;
    F32 dzdy;
    F32 dxdz;
    F32 dydz;
};

typedef S32 (*xClumpCollBSPLeafCB)(xClumpCollBSPTriangle* triangles, void* data);

#define xClumpCollV3dGradientMacro(grad, vec)                                                     \
MACRO_START                                                                                       \
{                                                                                                 \
    RwReal recip;                                                                                 \
                                                                                                  \
    recip = ((vec)->x != 0.0f) ? (1.0f / (vec)->x) : 0.0f;                                        \
    (grad)->dydx = (vec)->y * recip;                                                              \
    (grad)->dzdx = (vec)->z * recip;                                                              \
                                                                                                  \
    recip = ((vec)->y != 0.0f) ? (1.0f / (vec)->y) : 0.0f;                                        \
    (grad)->dxdy = (vec)->x * recip;                                                              \
    (grad)->dzdy = (vec)->z * recip;                                                              \
                                                                                                  \
    recip = ((vec)->z != 0.0f) ? (1.0f / (vec)->z) : 0.0f;                                        \
    (grad)->dxdz = (vec)->x * recip;                                                              \
    (grad)->dydz = (vec)->y * recip;                                                              \
}                                                                                                 \
MACRO_STOP

struct RwMeshCache
{
    U32 lengthOfMeshesArray;
    RwResEntry* meshes[1];
};

struct TempAtomicList
{
    RpAtomic* atomic;
    RpGeometry* geom;
    RpMeshHeader* meshHeader;
    RwMeshCache* meshCache;
};

void xClumpColl_InstancePointers(xClumpCollBSPTree* tree, RpClump* clump);
xClumpCollBSPTree* xClumpColl_StaticBufferInit(void* data, U32);
xClumpCollBSPTree* xClumpColl_ForAllCapsuleLeafNodeIntersections(xClumpCollBSPTree* tree, RwLine* line, F32 radius, xClumpCollV3dGradient* grad, xClumpCollBSPLeafCB callBack, void* data);

#endif
