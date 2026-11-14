#ifndef IMEMMGR_H
#define IMEMMGR_H

#include "types.h"

void iMemInit();
void iMemExit();
void* iMemPushTemp(U32 size);
void iMemPopTemp(void* pointer);

#endif
