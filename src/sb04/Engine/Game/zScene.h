#ifndef ZSCENE_H
#define ZSCENE_H

#include "xScene.h"
#include "xClimate.h"

#include "zPortal.h"
#include "xEnt.h"
#include "xEnv.h"
#include "zBase.h"
#include "xDynAsset.h"

struct zEnt;

struct zSceneParameters : xDynAsset
{
    U32 idle03ExtraCount;
    xAnimFile** idle03Extras;
    U32 idle04ExtraCount;
    xAnimFile** idle04Extras;
    U8 bombCount;
    U8 extraIdleDelay;
    U8 hdrGlow;
    U8 hdrDarken;
    U32 uDefaultMusicHash;
    U32 flags;
    F32 waterTileWidth;
    F32 lodFadeDistance;
    U32 pad[4];
};

struct zScene : xScene
{
    _zPortal* pendingPortal;
    S32 num_base;
    xBase** base;
    U32 num_update_base;
    xBase** update_base;
    S32 baseCount[141];
    xBase* baseList[141];
    _zEnv* zen;
    zSceneParameters* parameters;
    U8 enableDrawing;
};

struct zSceneObjectInstanceDesc
{
    const char* name;
    S32 baseType;
    U32 assetType;
    U32 sizeRuntime;
    U32 (*func)(zScene* s, zSceneObjectInstanceDesc* desc, U32 base_idx);
    void (*objectInitFunc)(void* ent, void* asset);
    U32 (*querySubObjects)(void*);
};

extern _tagClimate gClimate;
extern _zEnv* gCurEnv;
extern U32 gTransitionSceneID;
extern F32 gSceneUpdateTime;

void zSceneSet(xBase* b, U32 index);
void zSceneInitEnvironmentalSoundEffect();
void zSceneInit(U32 theSceneID, S32 reloadInProgress);
void zSceneExit(S32 beginReload);
void zSceneUpdateSFXWidgets();
void zSceneSwitch(_zPortal* p, S32 forceSameScene);
void zSceneSave(zScene* ent, xSerial* s);
void zSceneLoad(zScene* ent, xSerial* s);
void zSceneSetup();
void zSceneUpdate(F32 dt);
void zSceneRender();
xBase* zSceneFindObject(U32 gameID);
xBase* zSceneGetObject(S32 type, S32 idx);
const char* zSceneGetName(U32 gameID);
const char* zSceneGetName(xBase* b);
void zSceneForAllBase(xBase* (*func)(xBase*, zScene*, void*), void* data);
void zSceneForAllBase(xBase* (*func)(xBase*, zScene*, void*), S32 baseType, void* data);
void zSceneMemLvlChkCB();
U32 zSceneLeavingLevel();
const char* zSceneGetLevelName(U32 sceneID);
U32 zSceneGetLevelIndex();
U32 zSceneGetLevelIndex(U32 sceneID);
const char* zSceneGetLevelPrefix(U32 index);
const char* zSceneGetAreaname(U32);
U32 zSceneCalcProgress();
void zScene_UpdateFlyToInterface(F32 dt);
void zSceneCardCheckStartup_set(S32 needed, S32 available, S32 files);
void zSceneEnableVisited(zScene* s);
void zSceneEnableScreenAdj(U32 enable);
void zSceneSetOldScreenAdj();
U32 zScene_ScreenAdjustMode();
void zSceneSpawnRandomBubbles();

#endif
