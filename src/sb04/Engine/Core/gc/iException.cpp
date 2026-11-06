#include "iException.h"

void iExceptionMemCrash(const char* location, U32 size, const char* optionalString)
{
    OSReport("Out of memory crash, Loc=%s   Size=%d\n", location, size);
    OSReport("%s\n", optionalString);
    OSPanic("iException.cpp", 25, "");
}
