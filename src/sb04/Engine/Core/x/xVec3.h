#ifndef XVEC3_H
#define XVEC3_H

#include "xMath.h"

#include <types.h>
#include "rwplcore.h"

//movies dwarf
// struct xVec3
// {
//     union
//     {
//         RwV3d m_RwV3d;
//         F32 x;
//     };
//     F32 y;
//     F32 z;
//     F32 a[3];
// };

struct xVec3
{
    union
    {
        RwV3d m_RwV3d;
        struct
        {
            F32 x, y, z;
        };
        F32 a[3];
    };

    static const xVec3 m_Null;
    static const xVec3 m_Ones;
    static const xVec3 m_NegOnes;
    static const xVec3 m_UnitAxisX;
    static const xVec3 m_UnitAxisY;
    static const xVec3 m_UnitAxisZ;
    static const xVec3 m_HalfVec;
    static const xVec3 m_NegHalfVec;
    static const xVec3 m_DoubleVec;
    static const xVec3 m_NegDoubleVec;

    static xVec3 create(F32 x, F32 y, F32 z);
    static xVec3 create(F32 f);

    xVec3& operator=(F32 f)
    {
        x = y = z = f;
        return *this;
    }
    // FIXME: This should not be declared. Declaring it causes the assignment operator for the
    //        anonymous struct "camera" in hook_asset to call it rather than just copy the vec members.
    //xVec3& operator=(const xVec3& v);
    xVec3 operator+(const xVec3&) const;
    xVec3 operator-(const xVec3&) const;
    xVec3 operator*(F32) const;
    xVec3& operator+=(const xVec3&);
    xVec3& operator+=(F32 f)
    {
        this->x += f;
        this->y += f;
        this->z += f;

        return *this;
    }
    xVec3& operator-=(const xVec3&);
    xVec3& operator-=(F32 f)
    {
        this->x -= f;
        this->y -= f;
        this->z -= f;

        return *this;
    }

    xVec3& operator*=(F32);
    xVec3& operator/=(F32);

    xVec3& right_normalize();
    xVec3& safe_normalize(const xVec3& val);
    xVec3& up_normalize();
    xVec3 up_normal() const;
    xVec3& assign(F32 x, F32 y, F32 z) { this->x = x; this->y = y; this->z = z; return *this; }
    F32 length() const;
    F32 length2() const;
    xVec3& invert();
    inline F32 dot(const xVec3& c) const; // UNUSED
    xVec3& normalize();
    xVec3& assign(F32 val);
};

#define xVec3NormalizeMacro(o, v, outlen)                                                         \
{                                                                                                 \
    F32 len2 = xsqr((v)->x) + xsqr((v)->y) + xsqr((v)->z);                                        \
    if (xeq(len2, 1.0f, EPSILON)) {                                                               \
        (o)->x = (v)->x;                                                                          \
        (o)->y = (v)->y;                                                                          \
        (o)->z = (v)->z;                                                                          \
        *(outlen) = 1.0f;                                                                         \
    } else if (xeq(len2, 0.0f, EPSILON)) {                                                        \
        (o)->x = 0.0f;                                                                            \
        (o)->y = 1.0f;                                                                            \
        (o)->z = 0.0f;                                                                            \
        *(outlen) = 0.0f;                                                                         \
    } else {                                                                                      \
        *(outlen) = xsqrt(len2);                                                                  \
        F32 len_inv = 1.0f / *(outlen);                                                           \
        (o)->x = (v)->x * len_inv;                                                                \
        (o)->y = (v)->y * len_inv;                                                                \
        (o)->z = (v)->z * len_inv;                                                                \
    }                                                                                             \
}

#define xVec3NormalizeFastMacro(o, v, outlen)                                                     \
{                                                                                                 \
    F32 len2 = xsqr((v)->x) + xsqr((v)->y) + xsqr((v)->z);                                        \
    if (xeq(len2, 1.0f, EPSILON)) {                                                               \
        (o)->x = (v)->x;                                                                          \
        (o)->y = (v)->y;                                                                          \
        (o)->z = (v)->z;                                                                          \
        *(outlen) = 1.0f;                                                                         \
    } else if (xeq(len2, 0.0f, EPSILON)) {                                                        \
        (o)->x = 0.0f;                                                                            \
        (o)->y = 1.0f;                                                                            \
        (o)->z = 0.0f;                                                                            \
        *(outlen) = 0.0f;                                                                         \
    } else {                                                                                      \
        xsqrtfast(*(outlen), len2);                                                               \
        F32 len_inv = 1.0f / *(outlen);                                                           \
        (o)->x = (v)->x * len_inv;                                                                \
        (o)->y = (v)->y * len_inv;                                                                \
        (o)->z = (v)->z * len_inv;                                                                \
    }                                                                                             \
}

F32 xVec3Normalize(xVec3* o, const xVec3* v);
F32 xVec3NormalizeFast(xVec3* o, const xVec3* v);
void xVec3Copy(xVec3* o, const xVec3* v);
F32 xVec3Dot(const xVec3* vec1, const xVec3* vec2);

#endif
