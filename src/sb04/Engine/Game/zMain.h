#ifndef ZMAIN_H
#define ZMAIN_H

#include "types.h"

typedef enum _tagGameVidMode
{
    eGameVidModeNTSC,
    eGameVidModePAL
} eGameVidMode;

extern F32 SECS_PER_VBLANK;
extern eGameVidMode gVidMode;
extern F32 gSkipTimeCutscene;
extern F32 gSkipTimeFlythrough;

#define ZPLAYER (xglobals->___player_ent_dont_use_directly)

inline bool zMainIsPAL() { return gVidMode == eGameVidModePAL; }

inline bool zMainIsNTSC() { return gVidMode == eGameVidModeNTSC; }

#endif
