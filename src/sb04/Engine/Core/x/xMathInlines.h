#ifndef XMATHINLINES_H
#define XMATHINLINES_H

#include <types.h>

inline F32 xsqrt(register F32 x)
{
    register F32 c_half = 0.5f;
    register F32 c_three = 3.0f;
    register F32 rsqrt;
    register F32 nwork0;
    register F32 nwork1;

    if (x <= 0.0f || isinf(x)) {
        return x;
    }

    asm {
        frsqrte rsqrt, x
        fmuls nwork0, rsqrt, rsqrt
        fmuls nwork1, rsqrt, c_half
        fnmsubs nwork0, nwork0, x, c_three
        fmuls rsqrt, nwork0, nwork1
    }

    if (rsqrt > 0.00001f) {
        return 1.0f / rsqrt;
    }

    return 100000.0f;
}

F32 xfmod(F32 a, F32 b);
F32 xatan2(F32 y, F32 x);
F32 xasin(F32 x);
F32 xacos(F32 x);
F32 xexp(F32 x);
F32 xpow(F32 x, F32 y);

F32 SQ(F32 x);

void xsqrtfast(F32& out, F32 x);

#endif
