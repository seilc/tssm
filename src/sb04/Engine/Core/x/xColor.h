#ifndef XCOLOR_H
#define XCOLOR_H

#include "iColor.h"

extern const xColor g_RED;
extern const xColor g_GREEN;
extern const xColor g_BLUE;
extern const xColor g_CYAN;
extern const xColor g_YELLOW;
extern const xColor g_BLACK;
extern const xColor g_WHITE;
extern const xColor g_GRAY50;
extern const xColor g_CLEAR;
extern const xColor g_NEON_RED;
extern const xColor g_NEON_GREEN;
extern const xColor g_NEON_BLUE;
extern const xColor g_PIMP_GOLD;
extern const xColor g_ORANGE;
extern const xColor g_LAVENDER;
extern const xColor g_PINK;

iColor xColorFromRGBA(U8 r, U8 g, U8 b, U8 a);

#endif
