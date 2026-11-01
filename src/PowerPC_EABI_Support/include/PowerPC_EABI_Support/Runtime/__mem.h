#ifndef RUNTIME_MEM_H
#define RUNTIME_MEM_H
#include "macros.h"
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

void* memcpy(void* dest, const void* src, size_t n);
void __fill_mem(void* dest, int val, size_t count);
void* memset(void* dest, int val, size_t count);

#ifdef __cplusplus
}
#endif
#endif
