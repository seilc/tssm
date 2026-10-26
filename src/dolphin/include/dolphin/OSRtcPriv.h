#ifndef _DOLPHIN_OSRTCPRIV
#define _DOLPHIN_OSRTCPRIV

#include <dolphin/types.h>
#include <dolphin/os/OSRtc.h>

OSSram *__OSLockSram();
OSSramEx *__OSLockSramEx();
void OSSetWirelessID(s32 chan, u16 id);
u16 OSGetWirelessID(s32 chan);
u16 OSGetGbsMode();
void OSSetGbsMode(u16 mode);

#endif // _DOLPHIN_OSRTCPRIV