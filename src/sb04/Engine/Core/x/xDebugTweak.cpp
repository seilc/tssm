#include "xCommon.h"
#include "xDebugTweak.h"

void tweak_rtod(const tweak_info&, void*)
{
}

void tweak_dtor(const tweak_info&, void*)
{
}

const tweak_callback cb_tweak_convert_degrees = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, tweak_rtod, tweak_dtor };

void tweak_force_lt(const tweak_info&)
{
}

void tweak_force_gt(const tweak_info&)
{
}

void tweak_force_lteq(const tweak_info&)
{
}

void tweak_force_gteq(const tweak_info&)
{
}

const tweak_callback cb_tweak_force_lt = { tweak_force_lt };
const tweak_callback cb_tweak_force_gt = { tweak_force_gt };
const tweak_callback cb_tweak_force_lteq = { tweak_force_lteq };
const tweak_callback cb_tweak_force_gteq = { tweak_force_gteq };

// UNUSED: needed to match (code from Rat GC)
const char* tweak_blend_mode_labels[11] =
{
    "ZERO",
    "ONE",
    "SRCCOLOR",
    "INVSRCCOLOR",
    "SRCALPHA",
    "INVSRCALPHA",
    "DESTALPHA",
    "INVDESTALPHA",
    "DESTCOLOR",
    "INVDESTCOLOR",
    "SRCALPHASAT"
};

const U32 tweak_blend_mode_values[11] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
const U8 tweak_blend_mode_values8[11] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
