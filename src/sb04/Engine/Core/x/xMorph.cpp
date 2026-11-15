#include "xCommon.h"
#include "xMorph.h"

#include <string.h>

#define xMAGIC(a, b, c, d) ((((U32)a) << 0) | (((U32)b) << 8) | (((U32)c) << 16) | (((U32)d) << 24))

xMorphSeqFile* xMorphSeqSetup(void* data, xMorphFindAssetCallback FindAssetCB)
{
    S32 i, j;
    RpAtomic* model;
    xMorphTargetFile* mphtgt;

    xASSERT(data);
    xASSERT(*((U32*)data) == xMAGIC('M','P','S','Q'));

    xMorphSeqFile* header;
    F32* timelist;
    xMorphFrame* framelist;
    U32* assetlist;
    char* namelist;
    void* assetPtr;
    U32 skipsize;

    header = (xMorphSeqFile*)data;
    timelist = (F32*)(header + 1);
    framelist = (xMorphFrame*)(timelist + header->TimeCount);
    assetlist = (U32*)(framelist + header->TimeCount);
    namelist = (char*)(assetlist + header->ModelCount * 2);

    if (header->Flags & 0x80000000) {
        return header;
    }

    header->Flags |= 0x80000000;
    if (!(header->Flags & 0x1)) {
        namelist = NULL;
    }

    for (i = 0; i < (S32)header->ModelCount * 2; i++) {
        if (assetlist[i]) {
            assetPtr = FindAssetCB(assetlist[i], namelist);
            xASSERT(assetPtr);
            assetlist[i] = (U32)assetPtr;
        }
        if (namelist) namelist = strlen(namelist) + 1 + namelist;
    }

    for (i = 0; i < (S32)header->ModelCount; i++) {
        if (assetlist[i*2+1]) {
            model = (RpAtomic*)assetlist[i*2];
            mphtgt = (xMorphTargetFile*)assetlist[i*2+1];
            iMorphOptimize(model, mphtgt->Flags & 0x1);
        }
    }

    for (i = 0; i < (S32)header->TimeCount; i++) {
        model = (RpAtomic*)assetlist[(U32)framelist[i].Model*2];
        mphtgt = (xMorphTargetFile*)assetlist[(U32)framelist[i].Model*2+1];
        framelist[i].Model = model;
        for (j = 0; j < 4; j++) {
            if ((U32)framelist[i].Targets[j] + 0x10000 == 0xFFFF) {
                framelist[i].Targets[j] = NULL;
            } else {
                xASSERT(mphtgt);
                skipsize = (mphtgt->NumVerts * 3 + 7) & ~7;
                if (mphtgt->Flags & 0x1) {
                    skipsize *= 2;
                }
                if (j == 0) {
                    framelist[i].Flags = mphtgt->Flags;
                    framelist[i].NumVerts = mphtgt->NumVerts;
                    framelist[i].Scale *= mphtgt->Scale;
                }
                framelist[i].Targets[j] = (S16*)((U8*)(mphtgt + 1) + skipsize * (U32)framelist[i].Targets[j] * 2);
            }
        }
    }

    return header;
}

F32 xMorphSeqDuration(xMorphSeqFile* seq)
{
    return ((F32*)(seq+1))[seq->TimeCount-1];
}
