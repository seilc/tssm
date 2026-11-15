#ifndef XDEBUG_H
#define XDEBUG_H

#include "iDebug.h"
#include "xString.h"

#define xVALIDATE(cond) do { if (0) { (void)(cond); } } while (0)

#define xASSERT(cond) do { if (0) { (void)(cond); } } while (0)

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
    typedef void (*event_callback)(const tweak_info&);
    typedef void (*convert_callback)(const tweak_info&, void*);

    event_callback on_change;
    event_callback on_select;
    event_callback on_unselect;
    event_callback on_start_edit;
    event_callback on_stop_edit;
    event_callback on_expand;
    event_callback on_collapse;
    event_callback on_update;
    convert_callback convert_mem_to_tweak;
    convert_callback convert_tweak_to_mem;
};

void xprintf(const char* fmt, ...);
void xDebugInit();
void xDebugUpdate();
void xDebugExit();
void xDebugTimestampScreen();
void xDrawTextInit(U32 uBufferSize, U32 uNumLinesMax);
void xDrawTextRender();

extern U32 gFrameCount;
extern U32 gSceneFrameCount;

#endif
