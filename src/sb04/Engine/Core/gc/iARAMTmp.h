#ifndef IARAMTMP_H
#define IARAMTMP_H

#include <types.h>

bool iARAMTmpEnd(bool);
void* iARAMTmpInARAMTemp(void*);
void* iARAMTmpFree(void*);
U32 iARAMTmpMalloc(unsigned int);
U32 iARAMTmpBegin(unsigned int, unsigned int);
U64 transferDoneCB(unsigned long);

#endif
