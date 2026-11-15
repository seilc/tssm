#include "xCommon.h"
#include "xMath.h"

#include <stdlib.h>

static S32 xmath_inited;
static S32 xmath_exited;
static U32 rndseed;

S32 binom_triangle[MAX_BINOM_SIZE];

static void xBinomInit();

void xMathInit()
{
    if (xmath_inited) {
        return;
    }

    xmath_inited = TRUE;
    rndseed = 0;
    xBinomInit();
}

void xMathExit()
{
    if (xmath_exited) {
        return;
    }

    xmath_exited = TRUE;
}

F32 xatof(const char* x)
{
    return atof(x);
}

U32 xMathSolveQuadratic(F32 a, F32 b, F32 c, F32* x1, F32* x2)
{
    F32 d, dx, p;

    if (a == 0.0f) {
        if (b == 0.0f) {
            return 0;
        }

        *x1 = -c / b;
        return 1;
    }

    d = b * b - 4.0f * a * c;
    if (d < 0.0f) {
        return 0;
    }

    p = 1.0f / (2.0f * a);
    *x1 = -b * p;
    if (d == 0.0f) {
        return 1;
    }

    *x2 = *x1;
    dx = p * xsqrt(d);
    if (a > 0.0f) {
        *x1 -= dx;
        *x2 += dx;
    } else {
        *x1 += dx;
        *x2 -= dx;
    }

    return 2;
}

U32 xMathSolveCubic(F32 a, F32 b, F32 c, F32 d, F32* x1, F32* x2, F32* x3)
{
    F32 arecip, fA, fB, fOffset, fDiscr, fHalfB, fTemp, fDist, fAngle, fCos, fSin;

    if (a == 0.0f) {
        return xMathSolveQuadratic(b, c, d, x1, x2);
    }

    if (a != 1.0f) {
        arecip = 1.0f / a;
        b *= arecip;
        c *= arecip;
        d *= arecip;
    }

    fA = (1.0f / 3.0f) * (3.0f * c - b * b);
    fB = (1.0f / 27.0f) * (2.0f * (b * b * b) - 9.0f * b * c + 27.0f * d);
    fOffset = (1.0f / 3.0f) * b;
    fDiscr = 0.25f * (fB * fB) + (1.0f / 27.0f) * (fA * fA * fA);
    fHalfB = 0.5f * fB;

    if (xabs(fDiscr) < 0.000001f) {
        fDiscr = 0.0f;
    }

    if (fDiscr > 0.0f) {
        fTemp = xsqrt(fDiscr);

        if (-fHalfB + fTemp >= 0.0f) {
            *x1 = xpow(-fHalfB + fTemp, 1.0f / 3.0f);
        } else {
            *x1 = -xpow(-(-fHalfB + fTemp), 1.0f / 3.0f);
        }

        if (-fHalfB - fTemp >= 0.0f) {
            *x1 += xpow(-fHalfB - fTemp, 1.0f / 3.0f);
        } else {
            *x1 -= xpow(-(-fHalfB - fTemp), 1.0f / 3.0f);
        }

        *x1 -= fOffset;
        return 1;
    } else if (fDiscr < 0.0f) {
        fDist = xsqrt(-(1.0f / 3.0f) * fA);
        fAngle = (1.0f / 3.0f) * xatan2(xsqrt(-fDiscr), -fHalfB);
        fCos = icos(fAngle);
        fSin = isin(fAngle);
        *x1 = 2.0f * fDist * fCos - fOffset;
        *x2 = -fDist * (fCos + 1.7320508f * fSin) - fOffset;
        *x3 = -fDist * (fCos - 1.7320508f * fSin) - fOffset;
        return 3;
    } else {
        fTemp = (fHalfB >= 0.0f) ? -xpow(fHalfB, 1.0f / 3.0f) : xpow(-fHalfB, 1.0f / 3.0f);

        *x1 = 2.0f * fTemp - fOffset;
        *x2 = -fTemp - fOffset;
        return 2;
    }
}

F32 xAngleClamp(F32 a)
{
    F32 b = xfmod(a, 2.0f * PI);
    if (b < 0.0f) {
        b += 2.0f * PI;
    }

    return b;
}

F32 xAngleClampFast(F32 a)
{
    if (a < 0.0f) {
        a += 2.0f * PI;
    } else if (a >= 2.0f * PI) {
        a -= 2.0f * PI;
    }

    return a;
}

F32 xDangleClamp(F32 a)
{
    F32 b = xfmod(a, 2.0f * PI);
    if (b >= PI) {
        b -= 2.0f * PI;
    } else if (b < -PI) {
        b += 2.0f * PI;
    }

    return b;
}

static void xBinomInit()
{
    binom_triangle[0] = 1;
    S32 *row0 = binom_triangle, *row1 = binom_triangle + 1;

    for (S32 i = 1; i < 32; i++) {
        row1[0] = row1[i] = 1;

        const S32 *col00 = row0, *col01 = row0 + 1; S32 *col1 = row1 + 1, *end_col1 = row1 + i;
        for (; col1 < end_col1; ++col00, ++col01, ++col1)
            *col1 = *col00 + *col01;

        row0 = row1;
        row1 += i + 1;
    }
}

void xAccelMove(F32& x, F32& v, F32 a, F32 dt, F32 endx, F32 maxv)
{
    F32 offset = endx - x;
    F32 t1 = (xabs(v) < 0.001f || !xsamesign(offset, v)) ? HUGE : offset / v;
    F32 t2 = xabs(v / a);

    if (t1 < t2) a *= -1.0f;
    if (offset < 0.0f) a *= -1.0f;

    const F32 oldv = v;
    F32 dv, newv, adx;
    dv = a * dt;
    newv = v + dv;

    if (xabs(newv) <= maxv) { v = newv; adx = 0.5f * dv * dt; }
    else if (xabs(v) <= maxv) {
        v = range_limit(newv, -maxv, maxv);
        if (oldv != v) {
            F32 diff = v - oldv;
            adx = 0.5f * diff * diff / a;
        } else {
            adx = 0.0f;
        }
    }
    else if (!xsamesign(newv, dv)) { v = newv; adx = 0.5f * dv * dt; }
    else adx = 0.0f;

    F32 dx = oldv * dt + adx;

    if (t1 > t2) {
        if (xsamesign(dx, offset) && xabs(dx) > xabs(offset)) {
            dx = offset;
            v = 0.0f;
        }
    } else if (!xsamesign(dx, offset)) {
        dx = offset;
        v = 0.0f;
    }

    x += dx;
}

void xAccelMove(F32& x, F32& v, F32 a, F32 dt, F32 maxv)
{
    if (xabs(v) > xabs(maxv)) {
        if (v < 0.0f) {
            if (a > 0.0f) {
                a = -a;
            }
        } else if (a < 0.0f) {
            a = -a;
        }

        a = -a;
    }

    if (a < 0.0f) {
        if (maxv > 0.0f) {
            maxv = -maxv;
        }
    } else if (maxv < 0.0f) {
        maxv = -maxv;
    }

    F32 diff = maxv - v;
    F32 dv = a * dt;
    if (xabs(diff) < xabs(dv)) {
        x += v * dt + 0.5f * diff * diff / a;
        v = maxv;
    } else {
        x += 0.5f * a * dt * dt + v * dt;
        v += dv;
    }
}

void xAccelStop(F32& x, F32& v, F32 a, F32 dt)
{
    if (xfeq0(v)) {
        return;
    }

    if (v < 0.0f) {
        if (a > 0.0f) {
            a = -a;
        }
    } else if (a < 0.0f) {
        a = -a;
    }

    a = -a;

    F32 oldv = v;
    v += a * dt;
    if (xsamesign(oldv, v)) {
        x += 0.5f * dt * dt * a + oldv * dt;
    } else {
        if (!xfeq0(a)) {
            x -= 0.5f * oldv * oldv / a;
        }

        v = 0.0f;
    }
}

void xFuncPiece_EndPoints(xFuncPiece* func, F32 pi, F32 pf, F32 fi, F32 ff)
{
    xASSERT(func);
    xASSERT(pi != pf);

    F32 fdiff = ff - fi;
    func->end = pf - pi;
    F32 xfinv = 1.0f / func->end;
    func->order = 1;
    func->coef[0] = fi;
    func->coef[1] = fdiff * xfinv;
    xFuncPiece_ShiftPiece(func, func, -pi);
}

void xFuncPiece_ShiftPiece(xFuncPiece* shift, xFuncPiece* func, F32 newZero)
{
    xASSERT(shift);
    xASSERT(func);

    S32 i, j;
    xFuncPiece temp;

    for (i = 0; i < func->order; i++) temp.coef[i] = 0.0f;

    temp.coef[func->order] = func->coef[func->order];
    for (i = func->order - 1; i >= 0; i--) {
        for (j = i; j < func->order; j++) {
            temp.coef[j] += newZero * temp.coef[j + 1];
        }

        temp.coef[i] += func->coef[i];
    }

    shift->order = func->order;
    for (i = 0; i <= shift->order; i++) {
        shift->coef[i] = temp.coef[i];
    }

    shift->end = func->end - newZero;
}

void xResponseCurve::reset(U32 values, const void* curve, U32 nodes)
{
    _values = values;
    this->curve = (const inode*)curve;
    _nodes = nodes;
    active_node = 0;
}

void xResponseCurve::eval_linear(F32 t, F32* value) const
{
    xASSERT(value != 0);

    F32* end = value + _values;
    size_t stride = _values * sizeof(F32) + sizeof(node);
    find_active_node(t, stride);

    const inode& n1 = *(const inode*)((const U8*)curve + active_node * stride);
    const inode& n2 = *(const inode*)((const U8*)&n1 + stride);
    F32 dt = n2.t - n1.t;
    if (xfeq0(dt)) {
        const F32* v1 = n1.value;
        for (; value != end; ++v1, ++value)
            *value = *v1;
        return;
    }

    F32 u = (t - n1.t) / dt;
    const F32 *v1 = n1.value, *v2 = n2.value;
    for (; value != end; ++v1, ++v2, ++value)
        *value = *v1 + u * (*v2 - *v1);
}
