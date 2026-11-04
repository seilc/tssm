#ifndef ZENTTELEPORTBOX_H
#define ZENTTELEPORTBOX_H

#include "zEnt.h"
#include "xDynAsset.h"

struct teleport_asset : xDynAsset
{
    U32 marker;
    U32 opened;
    U32 launchAngle;
    U32 camAngle;
    U32 targetID;
};

typedef struct _zEntTeleportBox : zEnt
{
    U32 status;
    teleport_asset* tasset;
    zEnt* target;
    U32 currPlrState;
    U32 prevPlrState;
    U32 jumpInAnim;
    U32 jumpOutAnim;
    U32 JOtoOpenAnim;
    U32 JItoOpenAnim;
    xBox trig[2];
    U32 currPlayerIn;
    U32 prevPlayerIn;
    U32 currPlayerNear;
    U32 prevPlayerNear;
    F32 lastdt;
    F32 plrCtrlTimer;
} zEntTeleportBox;

void zEntTeleportBox_Init(xBase& data, xDynAsset& asset, size_t);
void zEntTeleportBox_Init(zEntTeleportBox* ent, teleport_asset* asset);
void zEntTeleportBox_InitAll();
void zEntTeleportBox_Setup(zEntTeleportBox* ent);
void zEntTeleportBox_Update(xEnt* rawent, xScene* sc, F32 dt);
void zEntTeleportBox_Save(zEntTeleportBox* ent, xSerial* s);
void zEntTeleportBox_Load(zEntTeleportBox* ent, xSerial* s);
void zEntTeleportBox_Open(zEntTeleportBox* ent);
void zEntTeleportBox_Close(zEntTeleportBox* ent);
S32 zEntTeleportBox_isOpen(zEntTeleportBox* ent);
S32 zEntTeleportBox_isClosed(zEntTeleportBox* ent);
S32 zEntTeleportBox_playerIn();
S32 zEntTeleportBoxEventCB(xBase*, xBase* to, U32 toEvent, const F32*, xBase*);

#endif
