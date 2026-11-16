#ifndef XMATH_H
#define XMATH_H

#include "iMath.h"

#include <math.h>

#define EPSILON 1e-5f
#define PI 3.14159265358979323846f
#define HUGE 1e38f

#define xabs(x) iabs(x)
#define xeq(a,b,e) (xabs((a) - (b)) <= (e))
#define xfeq0(x) (((x) >= -EPSILON) && ((x) <= EPSILON))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MAX3(a,b,c) (MAX(MAX((a), (b)), (c)))
#define CLAMP(x,a,b) MAX((a), MIN((x), (b)))
#define xsqr(x) ((x) * (x))
#define xsignbit(x) ((x) < 0.0f ? 1 : 0)
#define xsamesign(a,b) (xsignbit(a) == xsignbit(b))

#define SQR(x) ((x) * (x))

#define ALIGN(x, a) ((x) + ((a)-1) & ~((a)-1))

#define PI_DOUBLE 3.141592653589793
#define ONEEIGHTY 180.0f

#define DEG2RAD(x) ((PI_DOUBLE) * (x) / (ONEEIGHTY))
#define RAD2DEG(x) ((ONEEIGHTY) * (x) / (PI_DOUBLE))

#define FLOAT_MAX 1e38f
#define FLOAT_MIN -1e38f

F32 xrmod(F32 ang);

template <class T>
T range_limit(T v, T minv, T maxv)
{
    return v <= minv ? minv : (v >= maxv ? maxv : v);
}

enum { MAX_BINOM_SIZE = 528 };
extern S32 binom_triangle[MAX_BINOM_SIZE];

struct xFuncPiece
{
    F32 coef[5];
    F32 end;
    S32 order;
    xFuncPiece* next;
};

F32 xlog(F32 f);

void xMathInit();
void xMathExit();
F32 xatof(const char* x);
void xsrand(U32 seed);
U32 xrand();
F32 xurand();
U32 xMathSolveQuadratic(F32 a, F32 b, F32 c, F32* x1, F32* x2);
U32 xMathSolveCubic(F32 a, F32 b, F32 c, F32 d, F32* x1, F32* x2, F32* x3);
F32 xAngleClamp(F32 a);
F32 xAngleClampFast(F32 a);
F32 xDangleClamp(F32 a);
void xAccelMove(F32& x, F32& v, F32 a, F32 dt, F32 endx, F32 maxv);
void xAccelMove(F32& x, F32& v, F32 a, F32 dt, F32 maxv);
void xAccelStop(F32& x, F32& v, F32 a, F32 dt);
void xFuncPiece_EndPoints(xFuncPiece* func, F32 pi, F32 pf, F32 fi, F32 ff);
void xFuncPiece_ShiftPiece(xFuncPiece* shift, xFuncPiece* func, F32 newZero);
F32 xSCurve(F32 t, F32 softness);
F32 xSCurve(F32 t);
void xsqrtfast(F32& o, F32 fVal);

struct xResponseCurve
{
    struct node
    {
        F32 t;
    };

    struct inode : node
    {
        F32 value[1];
    };

    void reset(U32 values, const void* curve, U32 nodes);
    void eval_linear(F32 t, F32* value) const;

    inode* get_node(size_t index) const
    {
        return (inode*)((U8*)curve + index * (_values * sizeof(F32) + sizeof(node)));
    }

    F32 start_t() const
    {
        return curve->t;
    }

    F32 end_t() const
    {
        return get_node(_nodes - 1)->t;
    }

private:
    void find_active_node(F32 t, size_t stride) const
    {
        const U8* it = (const U8*)curve + stride * active_node;
        while (true) {
            inode& n = *(inode*)it;
            inode& next = *(inode*)(it + stride);
            if (t < n.t) {
                it -= stride;
                active_node--;
            }
            else if (t > next.t) {
                it += stride;
                active_node++;
            } else {
                break;
            }
        }
    }

    U32 _values;
    const inode* curve;
    U32 _nodes;
    mutable U32 active_node;
};

#include "xMathInlines.h"

#endif
