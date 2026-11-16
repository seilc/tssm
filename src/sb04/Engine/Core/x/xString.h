#ifndef XSTRING_H
#define XSTRING_H

#include "xDebug.h"

#include <stddef.h>

struct substr
{
    const char* text;
    size_t size;

    static substr create(const char* text, size_t size) { substr s = { text, size }; return s; }
};

#define SUBSTR(str) (str), (sizeof((str)) - 1)

U32 xStrHash(const char* str);
U32 xStrHash(const char* str, size_t size);
U32 xStrHashCat(U32 prefix, const char* str);
char* xStrupr(char* string);
S32 xStricmp(const char* string1, const char* string2);
char* xStrTok(char* string, const char* control, char** nextoken);
char* xStrTokBuffer(const char* string, const char* control, void* buffer);
S32 xStrParseFloatList(F32* dest, const char* strbuf, S32 max);

S32 imemcmp(const void* d1, const void* d2, size_t size);
S32 icompare(const substr& s1, const substr& s2);
U32 atox(const substr& s, size_t& read_size);
const char* find_char(const substr& s, const substr& cs);

inline U32 atox(const substr& s) { size_t read_size; return atox(s, read_size); }

inline bool is_ws(char c) { return c == ' ' || c == '\t' || c == '\n'; }

inline const char* skip_ws(const char*& text, size_t& size)
{
    xASSERT((size == 0) || (text != 0));
    for (size_t i = 0; i < size && *text; i++, ++text)
        if (!is_ws(*text)) { size -= i; break; }
    return text;
}

inline const char* skip_ws(substr& s) { return skip_ws(s.text, s.size); }

inline size_t rskip_ws(const char*& text, size_t& size)
{
    xASSERT(text != 0);
    while (size && is_ws(text[size - 1])) size--;
    return size;
}

inline size_t rskip_ws(substr& s) { return rskip_ws(s.text, s.size); }

inline void trim_ws(const char*& text, size_t& size)
{
    skip_ws(text, size);
    rskip_ws(text, size);
}

inline void trim_ws(substr& s) { trim_ws(s.text, s.size); }

inline const char* find_char(const substr& s, char c)
{
    if (!s.text) return NULL;
    const char* p = s.text;
    for (S32 i = s.size; i > 0 && *p; --i, ++p)
        if (*p == c) return p;
    return NULL;
}

extern "C" {
U32 tolower__21_esc__2_unnamed_esc__2_xString_cpp_esc__2_Fc(U32 param_1);
U32 tolower__21_esc__2_unnamed_esc__2_xString_cpp_esc__2_Fi(U32 param_1);
}

#endif
