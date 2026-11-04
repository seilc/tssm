#ifndef ZPENDULUM_H
#define ZPENDULUM_H

#include "xEntMotion.h"

#include "zEnt.h"

typedef struct _zPendulum : zEnt
{
    xEntMotion motion;
    F32 lt;
    F32 q1t;
    F32 q3t;
} zPendulum;

void zPendulum_Init(void* pend, void* asset);
void zPendulum_Init(zPendulum* pend, xEntAsset* asset);
void zPendulum_Save(zPendulum* pend, xSerial* s);
void zPendulum_Load(zPendulum* pend, xSerial* s);
void zPendulum_Setup(zPendulum* pend, xScene* sc);
void zPendulum_Reset(zPendulum* pend, xScene* sc);
void zPendulum_Update(zPendulum* pend, xScene* sc, F32 dt);
void zPendulum_Move(zPendulum* pend, xScene* sc, F32 dt, xEntFrame* frame);
void zPendulumTranslate(xEnt* xent, xVec3* dpos, xMat4x3* dmat);
S32 zPendulumEventCB(xBase* from, xBase* to, U32 event, const F32* toParam,
                       xBase* toParamWidget);

#endif
