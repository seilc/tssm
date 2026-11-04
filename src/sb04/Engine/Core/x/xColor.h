#ifndef XCOLOR_H
#define XCOLOR_H

#include "iColor.h"

extern const iColor g_RED;
extern const iColor g_GREEN;
extern const iColor g_BLUE;
extern const iColor g_CYAN;
extern const iColor g_YELLOW;
extern const xColor g_BLACK;
extern const iColor g_WHITE;
extern const iColor g_GRAY50;
extern const xColor g_CLEAR;
extern const iColor g_NEON_RED;
extern const iColor g_NEON_GREEN;
extern const iColor g_NEON_BLUE;
extern const iColor g_PIMP_GOLD;
extern const iColor g_ORANGE;
extern const iColor g_LAVENDER;
extern const iColor g_PINK;

iColor xColorFromRGBA(U8 r, U8 g, U8 b, U8 a);

#endif
