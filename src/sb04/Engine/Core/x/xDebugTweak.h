#ifndef XDEBUGTWEAK_H
#define XDEBUGTWEAK_H

#include "xString.h"

struct tweak_info;

struct tweak_callback
{
    typedef void(*event_callback)(const tweak_info&);
    typedef void(*convert_callback)(const tweak_info&, void*);

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

struct tweak_info
{
    substr name;
    void* value;
    const tweak_callback* cb;
    void* context;
    U8 type;
    U8 value_size;
    U16 flags;
    union
    {
        struct
        {
            S32 value_def;
            S32 value_min;
            S32 value_max;
        } int_context;
        struct
        {
            U32 value_def;
            U32 value_min;
            U32 value_max;
        } uint_context;
        struct
        {
            F32 value_def;
            F32 value_min;
            F32 value_max;
        } float_context;
        struct
        {
            bool value_def;
        } bool_context;
        struct
        {
            U32 value_def;
            U32 labels_size;
            const char** labels;
            void* values;
        } select_context;
        struct
        {
            U32 value_def;
            U32 mask;
        } flag_context;
        struct
        {
            U8 pad[16];
        } all_context;
    };
};

void tweak_rtod(const tweak_info& info, void* value);
void tweak_dtor(const tweak_info& info, void* value);
void tweak_force_lt(const tweak_info& info);
void tweak_force_gt(const tweak_info& info);
void tweak_force_lteq(const tweak_info& info);
void tweak_force_gteq(const tweak_info& info);

extern const tweak_callback cb_tweak_force_lt;
extern const tweak_callback cb_tweak_force_gt;
extern const tweak_callback cb_tweak_force_lteq;
extern const tweak_callback cb_tweak_force_gteq;
extern const tweak_callback cb_tweak_convert_degrees;

extern const char* tweak_blend_mode_labels[11];
extern const U32 tweak_blend_mode_values[11];
extern const U8 tweak_blend_mode_values8[11];

#endif
