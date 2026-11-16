#ifndef XDEBUG_H
#define XDEBUG_H

#include "iDebug.h"

#define xVALIDATE(cond) do { if (0) { (void)(cond); } } while (0)
#define xVALIDATE_FAIL() xVALIDATE(0)
#define xVALIDATE_MSG(cond, msg) xVALIDATE(cond)
#define xVALIDATE_EQ(a, b) xVALIDATE((a) == (b))

#define xASSERT(cond) do { if (0) { (void)(cond); } } while (0)
#define xASSERT_MSG(cond, msg) xASSERT(cond)
#define xASSERT_FMT(cond, ...) xASSERT(cond)
#define xASSERT_LE(a, b) xASSERT((a) <= (b))

void xprintf(const char* fmt, ...);
void xDebugInit();
void xDebugUpdate();
void xDebugExit();
void xDebugTimestampScreen();
void xDrawTextInit(U32 uBufferSize, U32 uNumLinesMax);
void xDrawTextRender();

extern U32 gFrameCount;
extern U32 gSceneFrameCount;

#define xTWEAKABLE const

#endif
