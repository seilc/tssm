#ifndef ZUIUSERSTRING_H
#define ZUIUSERSTRING_H

#include "zUIText.h"

struct zUIUserStringAsset : zUITextAsset
{
    U8 hardMaxChars;
    U8 softMaxChars;
};

struct zUIUserString : zUIText
{
    char* textBuffer;
    S32 length;
    S32 maxLength;

    U32 GetSortKey() const;
    void DoHandleEvent(xBase* from, U32 toEvent, F32* toParam, xBase* toParamWidget,
                       U32 toParamWidgetID);
    void DoReset();
    void DoInit();
};

#endif
