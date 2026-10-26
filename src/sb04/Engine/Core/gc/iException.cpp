#include "iException.h"

void iExceptionMemCrash(const char* loc, U32 size, const char* arg3)
{
    OSReport("Out of memory crash, Loc=%s   Size=%d\n", loc, size);
    OSReport("%s\n", arg3);
    OSPanic("iException.cpp", 25, "");
}
