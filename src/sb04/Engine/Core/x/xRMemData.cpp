#include "xRMemData.h"

#include "xBase.h"
#include "xMemMgr.h"
#include "xDebug.h"
#include "xOutputMgr.h"

#include <string.h>

void* RyzMemData::operator new(size_t amt, S32, RyzMemGrow* growCtxt)
{
    void* mem = NULL;

    xASSERT_MSG((amt>1), "Don't be shy");

    S32 dogrow = TRUE;

    if (!growCtxt) dogrow = FALSE;
    else if (!growCtxt->IsEnabled()) dogrow = FALSE;

    if (dogrow) {
        xASSERT_MSG(growCtxt->ptr, "Missing base address");

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
    xASSERT_MSG(this->ptr_last, "Resume has bad last info");

    this->amt = this->amt_last;
    this->ptr = this->ptr_last;
    this->user = this->user_last;
    this->flg_grow = 0x3;

    xOutInfo("RyzMemData",
             "RMemGrow (0x%08X [0x%08X]) base 0x%08X resume\n",
             this->user,
             this->user ? this->user->id : 0,
             this->ptr);

    return this;
}

void RyzMemGrow::Done()
{
    xOutInfo("RyzMemData",
             "RMemGrow (0x%08X [0x%08X]) base 0x%08X end\n",
             this->user,
             this->user ? this->user->id : 0,
             this->ptr);

    xASSERT(this->flg_grow & RMEM_GROW_ENABLED);
    xASSERT(this->amt==RMEM_GROWSTUB_SIZE);
    xASSERT(this->ptr);

    this->amt_last = this->amt;
    this->ptr_last = this->ptr;
    this->user_last = this->user;

    this->amt = 0;
    this->ptr = NULL;
    this->user = NULL;
    this->flg_grow = 0;
}
