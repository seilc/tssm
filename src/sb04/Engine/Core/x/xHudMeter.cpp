#include "xCommon.h"
#include "xHudMeter.h"

#include "xHudAsset.h"
#include "xSndMgr.h"

namespace xhud {

namespace {

F32 tweak_accel = 50.0f;
F32 tweak_min_ping_time = 0.05f;
F32 tweak_pitch_scale = 0.01f;

}

void meter_widget::set_value(F32 v)
{
    if (v < value - 0.01f) {
        if (res->decrement_time < 0.01f) {
            set_value_immediate(v);
        } else {
            end_value = v;
            inc_value = -1.0f / res->decrement_time;
            inc_accel = -1.0f * tweak_accel;
            xSndMgrPlay(xSndMgrGetSoundGroup(res->sound.start_decrement), 0, NULL, NULL, NULL, NULL, NULL);
        }
    } else if (v > value + 0.01f) {
        if (res->increment_time < 0.01f) {
            set_value_immediate(v);
        } else {
            end_value = v;
            inc_value = 1.0f / res->increment_time;
            inc_accel = tweak_accel;
            xSndMgrPlay(xSndMgrGetSoundGroup(res->sound.start_increment), 0, NULL, NULL, NULL, NULL, NULL);
        }
    } else {
        set_value_immediate(v);
    }
}

void meter_widget::set_value_immediate(F32 v)
{
    value = v;
    end_value = v;
    inc_value = 0.0f;
}

meter_widget::meter_widget(const meter_asset& a)
    : widget(a)
    , res(&a)
    , value(a.start_value)
    , min_value(a.min_value)
    , max_value(a.max_value)
    , inc_value(0.0f)
    , end_value(a.start_value)
    , ping_delay(10.0f)
    , pings()
{
    static bool registered = false;
    if (!registered) {
        registered = true;
    }
}

void meter_widget::destruct() { widget::destruct(); }

U32 meter_widget::type() const
{
    static U32 myid = xStrHash(meter_asset::type_name());
    return myid;
}

bool meter_widget::is(U32 id) const
{
    return id == meter_widget::type() || widget::is(id);
}

void meter_widget::updater(F32 dt)
{
    widget::updater(dt);

    ping_delay += dt;

    if (inc_value == 0.0f) return;

    F32 old_value = value;

    value += inc_value * dt;
    inc_value += inc_accel * dt;

    if ((inc_value < 0.0f) ? 1 : 0) {
        if (value <= end_value) {
            value = end_value;
            inc_value = 0.0f;
        }
        if ((S32)value != (S32)old_value && res->sound.decrement && ping_delay > tweak_min_ping_time) {
            F32 pitch = tweak_pitch_scale * -inc_value;
            ping_delay = 0.0f;
            pings.play(xSndMgrGetSoundGroup(res->sound.decrement), 0, NULL, NULL, NULL, &pitch, NULL);
        }
    } else {
        if (value >= end_value) {
            value = end_value;
            inc_value = 0;
        }
        if ((S32)value != (S32)old_value && res->sound.increment && ping_delay > tweak_min_ping_time) {
            F32 pitch = tweak_pitch_scale * inc_value;
            ping_delay = 0.0f;
            pings.play(xSndMgrGetSoundGroup(res->sound.increment), 0, NULL, NULL, NULL, &pitch, NULL);
        }
    }
}

}
