#ifndef XWAD5_H
#define XWAD5_H

#include <types.h>

#include <PowerPC_EABI_Support/MSL_C/MSL_Common/ctype_api.h>

#include "zGlobals.h"
#include "xVec3.h"
#include "stdlib.h"
#include <types.h>
#include "fastmath.h"
#include "xVolume.h"
#include "xutil.h"
#include "xUpdateCull.h"
#include "xTRC.h"
#include "zGameState.h"
#include "xTimer.h"
#include "xSurface.h"
#include "xstransvc.h"
#include "xpkrsvc.h"
#include "xSkyDome.h"
#include "iModel.h"
#include "xserializer.h"

void xSndMgrPauseSounds(S16 eSoundCategory, bool bPaused, bool bPauseFutureSoundsOfThisType);

#endif
