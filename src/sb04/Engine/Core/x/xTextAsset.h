#ifndef XTEXTASSET_H
#define XTEXTASSET_H

#include <types.h>

struct xTextAsset
{
    U32 len;
};

#define xTextAssetGetText(t) ((char*)((xTextAsset*)(t) + 1))

const char* xTextFindString(U32 key, U32* len);
const char* xTextFindString(const char* key, U32* len);

#endif
