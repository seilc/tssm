#ifndef ITIME_H
#define ITIME_H

#include "types.h"

#include <dolphin.h>

typedef OSTime iTime;

void iTimeInit();
void iTimeExit();
iTime iTimeGet();
F32 iTimeDiffSec(iTime time);
F32 iTimeDiffSec(iTime t0, iTime t1);
F32 iTimeGetGame();
void iTimeGameAdvance(F32 elapsed);
void iTimeSetGame(F32 time);
void iProfileClear(U32 sceneID);
void iFuncProfileDump();
void iFuncProfileFuncs(S32, S32, F32);
void iFuncMasterLoad(const char* filename); // UNUSED

#define JANUARY 1
#define FEBRUARY 2
#define MARCH 3
#define APRIL 4
#define MAY 5
#define JUNE 6
#define JULY 7
#define AUGUST 8
#define SEPTEMBER 9
#define OCTOBER 10
#define NOVEMBER 11
#define DECEMBER 12

S32 iGetMinute();
S32 iGetHour();
S32 iGetDay();
S32 iGetMonth();
char* iGetCurrFormattedDate(char* input);
char* iGetCurrFormattedTime(char* input);

#endif
