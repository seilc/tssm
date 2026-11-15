#include "xCommon.h"
#include "xMemoryManagerFixed.h"

void xMemoryManagerFixed::Init(void* start, U32 elements, U32 elementSize)
{
    DoInit(start, elements * elementSize, false);

    this->elements = elements;
    this->elementSize = elementSize;

    InitMemory();
}

void* xMemoryManagerFixed::DoAllocate(U32 size, U32 options)
{
    xASSERT((options & xMEMORYOPT_ALIGN_MASK) >> xMEMORYOPT_ALIGN_SHIFT <= 2);

    if (!freeList)
        return NULL;

    xASSERT(size <= elementSize);

    FixedHeader* ret = freeList;

    freeList = freeList->next;

    return ret;
}

void xMemoryManagerFixed::DoFree(void* pointer)
{
    S32 TESTVALUE = (S32)((S32)pointer - (S32)GetArenaStart());
    xASSERT(TESTVALUE % elementSize == 0);

    FixedHeader* header = (FixedHeader*)pointer;
    header->next = freeList;
    this->freeList = header;
}

void* xMemoryManagerFixed::DoReallocate(void* pointer, U32 size, U32)
{
    xASSERT(size <= elementSize);
    return pointer;
}

U32 xMemoryManagerFixed::DoGetBlockSize(void*) const
{
    return elementSize;
}

void xMemoryManagerFixed::InitMemory()
{
    freeList = (FixedHeader*)GetArenaStart();

    FixedHeader* cur = (FixedHeader*)freeList;
    for (U32 i = 0; i < elements - 1; i++) {
        cur->next = xMEMADVANCE(cur, elementSize);
        cur = cur->next;
    }
    cur->next = NULL;
}
