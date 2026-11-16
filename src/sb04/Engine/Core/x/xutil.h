#ifndef XUTIL_H
#define XUTIL_H

#include <types.h>

#define IDTAG(a,b,c,d) (((U32)(a)<<24)|((U32)(b)<<16)|((U32)(c)<<8)|((U32)(d)))
#define ARRAY_LENGTH(a) (sizeof(a) / sizeof(a[0]))

S32 xUtilStartup();
S32 xUtilShutdown();
char* xUtil_idtag2string(U32 srctag, S32 bufidx);
U32 xUtil_crc_init();
U32 xUtil_crc_update(U32 crc_accum, char* data, S32 datasize);
S32 xUtil_yesno(F32 wt_yes);
void xUtil_wtadjust(F32* wts, S32 cnt, F32 arbref);

template <typename T>
T* xUtil_select(T** arg0, S32 arg1, const F32* arg3);

#define XUTIL_SWAP(a, b, width)                 \
do {                                            \
    U8* _b0 = (a);                              \
    U8* _b1 = (b);                              \
    U8* _endb0 = (a) + (width);                 \
    while (_b0 != _endb0) {                     \
        U32 _temp = *(U32*)_b0;                 \
        *(U32*)_b0 = *(U32*)_b1;                \
        *(U32*)_b1 = _temp;                     \
        _b0 += 4, _b1 += 4;                     \
    }                                           \
} while (0)

template <class T>
void quicksort(void* base, size_t num, size_t width, T cmp)
{
    size_t thresh = width * 7;
    U8* stack[40];
    U8** sp = stack;
    U8 *pivot = (U8*)base, *tail = pivot + num * width;

    for (;;) {
        if (tail - pivot <= thresh) {
            U8 *v = pivot, *next = v + width;
            for (; next < tail; v = next, next += width) {
                while (cmp(v, v + width) > 0) {
                    XUTIL_SWAP(v, v + width, width);
                    if (v == pivot) {
                        break;
                    }
                    v -= width;
                }
            }

            if (sp == stack) {
                break;
            }

            pivot = sp[-2];
            tail = sp[-1]; sp -= 2;
            continue;
        }

        size_t half = (size_t)(tail - pivot) / 2;
        half -= half % width;
        XUTIL_SWAP(pivot + half, pivot, width);
        U8 *left = pivot + width, *right = tail - width;
        if (cmp(left, right) > 0) {
            XUTIL_SWAP(left, right, width);
        }
        if (cmp(pivot, right) > 0)
            XUTIL_SWAP(pivot, right, width);
        else if (cmp(left, pivot) > 0)
            XUTIL_SWAP(left, pivot, width);

        for (;;) {
            do left += width; while (cmp(left, pivot) < 0);
            do right -= width; while (cmp(right, pivot) > 0);
            if (left > right) {
                break;
            }
            XUTIL_SWAP(left, right, width);
        }
        XUTIL_SWAP(pivot, right, width);

        if (right - pivot > tail - left) {
            sp[0] = pivot; sp[1] = right;
            pivot = left;
        } else {
            sp[0] = left; sp[1] = tail;
            tail = right;
        }
        sp += 2;
    }
}

#endif
