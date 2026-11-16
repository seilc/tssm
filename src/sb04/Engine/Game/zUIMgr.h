#ifndef ZUIMGR_H
#define ZUIMGR_H

#include "xFXHighDynamicRange.h"

class zUI;
struct zScene;

struct zUIMgrHDRContext
{
    bool renderedHDR;
    xFXHighDynamicRangeConfiguration oldConfiguration;
};

void zUIMgrInit(zScene* s);
void zUIMgrReset();
void zUIMgrUpdate(F32 dt);
void zUIMgrRender();
void zUIMgrExit(zScene*);
void zUIMgrUpdateOrder();
void zUIMgrEnableHDR(bool enabled);
void zUIMgrSortList(zUI** list, S32 count);
void zUIMgrSetHDR(zUIMgrHDRContext& context);
void zUIMgrFinishHDR(zUIMgrHDRContext& context);
void zUIMgrRenderElementHDR(zUIMgrHDRContext& context, zUI* ui);
void zUIMgrSignalActive();

#endif
