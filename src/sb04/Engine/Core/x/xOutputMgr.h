#ifndef XOUTPUTMGR_H
#define XOUTPUTMGR_H

#include "iDebug.h"

#if DEBUG || RELEASE
void xOutInfo(char* name, const char* fmt, ...);
#else
#define xOutInfo
#endif

#endif
