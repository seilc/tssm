#ifndef ZENV_H
#define ZENV_H

#include "xBase.h"
#include "xEnv.h"
#include "iEnv.h"

void zEnvEventCB(xBase* a0, xBase* a1, U32 a2, const F32* a3, xBase* a4, U32 a5);
void zEnvLoad(zEnv* ent, xSerial* s);
void zEnvSave(zEnv* ent, xSerial* s);
void zEnvRender(xEnv* env);
void zEnvStartingCamera();
void zEnvSetup(zEnv* env);
void zEnvInit(zEnv* env, xEnvAsset* easset);
void zEnvInit(void* env, void* easset);

#endif
