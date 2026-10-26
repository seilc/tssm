#ifndef ZENTPLAYERCAR_H
#define ZENTPLAYERCAR_H

#include "xEnt.h"
#include "zCar.h"

void zEntPlayerCarHandleEvents(xBase* from, xBase* to, U32 toEvent, F32* toParam,
                               xBase* toParamWidget, U32 toParamWidgetID);
void zEntPlayerCarUpdateHealth(xEnt* ent, F32 dt);
void zEntPlayerCarRenderFX(xEnt* ent);
U8 zEntPlayerCarUpdate(xEnt* ent, xScene* sc, F32 dt);
void zEntPlayerCarExit();
//zCar* zEntPlayerCarGetCar();

#endif
