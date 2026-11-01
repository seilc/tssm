#include "xRMemData.h"

#include "xBase.h"
#include "xMemMgr.h"

#include <string.h>

void* RyzMemData::operator new(size_t amt, S32, RyzMemGrow* growCtxt)
{
    void* mem = NULL;

    S32 dogrow = TRUE;

    if (!growCtxt) dogrow = FALSE;
    else if (!growCtxt->IsEnabled()) dogrow = FALSE;

    if (dogrow) {
        mem = xMEMGROWALLOC(amt);
    } else {
        mem = xMEMALLOC(amt, 0);
    }

    memset(mem, 0, 4);

    return mem;
}

void RyzMemData::operator delete(void*)
{
}

RyzMemGrow* RyzMemGrow::Init(xBase* growuser)
{
    if (this->ptr) {
        return this;
    }

    this->amt_last = 0;
    this->ptr_last = NULL;
    this->user_last = NULL;

    this->amt = RMEM_GROWSTUB_SIZE;
    this->ptr = (char*)xMEMALLOC(this->amt, 0);
    this->user = growuser;
    this->flg_grow = RMEM_GROW_ENABLED;

    return this;
}

RyzMemGrow* RyzMemGrow::Resume(xBase*)
{
    this->amt = this->amt_last;
    this->ptr = this->ptr_last;
    this->user = this->user_last;
    this->flg_grow = 0x3;

    return this;
}

void RyzMemGrow::Done()
{
    this->amt_last = this->amt;
    this->ptr_last = this->ptr;
    this->user_last = this->user;

    this->amt = 0;
    this->ptr = NULL;
    this->user = NULL;
    this->flg_grow = 0;
}
