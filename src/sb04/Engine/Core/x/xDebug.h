#ifndef XDEBUG_H
#define XDEBUG_H

#include "iDebug.h"
#include "xFont.h"

#include <types.h>

enum en_VERBOSE_MSGLEVEL
{
    DBML_NONE,
    DBML_RELDISP,
    DBML_DISP,
    DBML_USER,
    DBML_ERR,
    DBML_TIME,
    DBML_WARN,
    DBML_VALID,
    DBML_INFO,
    DBML_DBG,
    DBML_TEST,
    DBML_VDBG,
    DBML_SPEW
};

#if DEBUG || RELEASE
#define xWARN(...) DBprintf(DBML_WARN, __VA_ARGS__)
#define xVERBOSE(...) DBprintf(DBML_VDBG, __VA_ARGS__)
#else
#define xWARN(...)
#define xVERBOSE(...)
#endif

#if DEBUG
#define _xVALIDATE(line, cond, msg)                                                               \
do {                                                                                              \
    static S32 been_here;                                                                         \
    if (!(cond) && !been_here) {                                                                  \
        DBprintf(DBML_VALID, "%s(%d) : (" msg ") in '%s'\n", __FILE__, line, __FUNCTION__);       \
        xDebugValidateFailed();                                                                   \
        been_here = TRUE;                                                                         \
    }                                                                                             \
} while (0)

#define xVALIDATE(cond) _xVALIDATE(__LINE__, cond, #cond)
#define xVALIDATE_L(line, cond) _xVALIDATE(line, cond, #cond)
#define xVALIDATE_FAIL_L(line) _xVALIDATE(line, 0, "*always*")
#define xVALIDATE_MSG_L(line, cond, msg) _xVALIDATE(line, cond, msg)
#else
#define xVALIDATE(cond)
#define xVALIDATE_L(line, cond)
#define xVALIDATE_FAIL_L(line)
#define xVALIDATE_MSG_L(line, cond, msg)
#endif

#define xVALIDATE_FAIL() xVALIDATE_FAIL_L(__LINE__)
#define xVALIDATE_MSG(cond, msg) xVALIDATE_MSG_L(__LINE__, cond, msg)

#if DEBUG || RELEASE
#define _xSTR(x) #x

#define _xFAIL(line, condstr, ...)                                                                \
{                                                                                                 \
    xDebug_assert2_info(__FUNCTION__, __FILE__, line, condstr);                                   \
    xDebug_assert2(__VA_ARGS__);                                                                  \
    xDebugStackTrace();                                                                           \
    if (xDebugBoing()) iDebugBreak();                                                             \
}

#define _xASSERT(line, cond, condstr, ...)                                                        \
do {                                                                                              \
    if (!(cond)) {                                                                                \
        _xFAIL(line, condstr, __VA_ARGS__);                                                       \
    }                                                                                             \
} while (0)

#define xASSERT(cond) _xASSERT(__LINE__, cond, _xSTR(cond), "%s", #cond)
#define xASSERT_L(line, cond) _xASSERT(line, cond, _xSTR(cond), "%s", #cond)
#define xASSERT_FMT(cond, ...) _xASSERT(__LINE__, cond, #cond, __VA_ARGS__)
#define xASSERT_FMT_L(line, cond, ...) _xASSERT(line, cond, #cond, __VA_ARGS__)
#else
#define _xFAIL(line, condstr, ...)
#define xASSERT(cond)
#define xASSERT_L(line, cond)
#define xASSERT_FMT(cond, ...)
#define xASSERT_FMT_L(line, cond, ...)
#endif

extern U32 gFrameCount;

struct uint_data
{
    U32 value_def;
    U32 value_min;
    U32 value_max;
};

struct float_data
{
    F32 value_def;
    F32 value_min;
    F32 value_max;
};

struct bool_data
{
    U8 value_def;
};

struct select_data
{
    U32 value_def;
    U32 labels_size;
    char** labels;
    void* values;
};

struct flag_data
{
    U32 value_def;
    U32 mask;
};

struct raw_data
{
    U8 pad[16];
};

struct int_data
{
    S32 value_def;
    S32 value_min;
    S32 value_max;
};

struct tweak_callback;
struct tweak_info
{
    substr name;
    void* value;
    tweak_callback* cb;
    void* context;
    U8 type;
    U8 value_size;
    U16 flags;
    union
    {
        int_data int_context;
        uint_data uint_context;
        float_data float_context;
        bool_data bool_context;
        select_data select_context;
        flag_data flag_context;
        raw_data all_context;
    };
};

struct tweak_callback
{
    void (*on_change)(tweak_info&);
    void (*on_select)(tweak_info&);
    void (*on_unselect)(tweak_info&);
    void (*on_start_edit)(tweak_info&);
    void (*on_stop_edit)(tweak_info&);
    void (*on_expand)(tweak_info&);
    void (*on_collapse)(tweak_info&);
    void (*on_update)(tweak_info&);
    void (*convert_mem_to_tweak)(tweak_info&, void*);
    void (*convert_tweak_to_mem)(tweak_info&, void*);
};

void xDebugValidateFailed();
void xprintf(const char* msg, ...);
S32 xDebugModeAdd(char* mode, void(*debugFunc));
void xDebugInit();
void xDebugUpdate();
void xDebugExit();
void xDebugTimestampScreen();

#if DEBUG || RELEASE
void DBprintf(en_VERBOSE_MSGLEVEL msglvl, const char* fmt, ...);
#endif

void xDebug_assert2_info(const char* func, const char* file, U32 line, const char* expr);
void xDebug_assert2(const char* fmt, ...);
U32 xDebugBoing();
void xDebugStackTrace();

void xDebugAddTweak(const char*, F32*, F32, F32, const tweak_callback*, void*, U32);
void xDebugRemoveTweak(const char*);
void xDebugUpdate();

F32 NSCREENY(F32 scale);
F32 NSCREENX(F32 scale);

#endif
