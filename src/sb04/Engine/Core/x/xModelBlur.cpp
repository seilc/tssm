#include "xModelBlur.h"

#include "xFX.h"
#include "xColor.h"
#include "xMathInlines.h"
#include "xMemMgr.h"

#define MAX_PATH_NODES 32

namespace {

    bool sModelBlurEnabled = true;

    struct interpolator
    {
        F32 value;
        F32 start;
        F32 end;
        F32 t;
        F32 trate;

        void reset(F32 value)
        {
            this->value = start = end = value;
            t = trate = 0.0f;
        }

        void go(F32 value, F32 time)
        {
            if (time <= 0.0f || value == this->value) {
                reset(value);
                return;
            }

            start = this->value;
            end = value;
            t = 0.0f;
            trate = 1.0f / time;
        }

        void update(F32 dt)
        {
            if (trate == 0.0f) return;

            t += trate * dt;
            if (t >= 1.0f) {
                value = start = end;
                t = 0.0f;
                trate = 0.0f;
            } else {
                F32 s = t;
                value = (1.0f - s) * start + s * end;
            }
        }
    };

    struct path_node
    {
        bool just_added;
        F32 age;
        xVec3 center;
    };

    struct card_data
    {
        F32 alpha;
        xVec3 center;
    };

    xFXCameraTexture camtex;

}

struct xModelBlur::activity_data
{
    S32 index;
    xModelBlur* owner;
    const config_data* cfg;
    xModelInstance* model;
    xVec3 center;
    path_node path[MAX_PATH_NODES];
    card_data cards[MAX_PATH_NODES];
    S32 path_start;
    S32 path_size;
    S32 cards_size;
    interpolator lifetime;
    interpolator alpha;
};

xModelBlur::activity_data* xModelBlur::activity_buffer;
xModelBlur::activity_data* xModelBlur::activities[MAX_ACTIVE];
S32 xModelBlur::activities_used;

void xModelBlur::scene_enter()
{
    camtex.create(8, 8, true, 32, 32);
    camtex.set_background(g_CLEAR);

    activity_buffer = (activity_data*)xMEMALLOC(sizeof(activity_data) * MAX_ACTIVE, 0);

    for (S32 i = 0; i < MAX_ACTIVE; i++) {
        activity_data* activity = activity_buffer + i;
        activities[i] = activity;
        activity->index = i;
        activity->owner = NULL;
    }

    activities_used = 0;
}

void xModelBlur::scene_exit()
{
    camtex.destroy();
}

void xModelBlur::reset_all()
{
    for (S32 i = 0; i < activities_used; i++) {
        if (activities[i]->owner)
            activities[i]->owner->activity = NULL;
    }

    for (S32 i = 0; i < MAX_ACTIVE; i++) {
        activity_data* activity = activity_buffer + i;
        activities[i] = activity;
        activity->index = i;
        activity->owner = NULL;
    }

    activities_used = 0;
}

void xModelBlur::update_all(F32 dt)
{
    activity_data** activity = activities, **end_activity = activity + activities_used;
    while (activity != end_activity) {
        if ((*activity)->cfg->flags & 0x8) {
            activity++;
        }
        else if ((*activity)->owner->update(dt))
            activity++;
        else
            end_activity--;
    }
}

void xModelBlur::render_all()
{
    if (!sModelBlurEnabled) {
        return;
    }

    activity_data** activity = activities, **end_activity = activity + activities_used;
    for (; activity != end_activity; activity++) {
    }
}

void xModelBlur::render_enable(bool enabled)
{
    sModelBlurEnabled = enabled;
}

void xModelBlur::create()
{
    activity = NULL;
}

bool xModelBlur::activate(F32 lifetime, F32 alpha, const config_data& cfg, xModelInstance* model)
{
    if (activity) {
        activity->lifetime.reset(lifetime);
        activity->alpha.reset(alpha);
        return true;
    }

    if (activities_used >= MAX_ACTIVE)
        return false;

    activity = alloc_activity();
    activity->owner = this;
    activity->cfg = &cfg;
    activity->model = model;
    activity->path_start = 0;
    activity->path_size = 0;
    activity->lifetime.reset(lifetime);
    activity->alpha.reset(alpha);
    return true;
}

void xModelBlur::deactivate()
{
    if (!activity) {
        return;
    }

    activity->owner = NULL;
    free_activity(activity);
    activity = NULL;
}

void xModelBlur::move(const xVec3& center)
{
    if (activity->path_size > 1) {
        S32 second_index = (activity->path_start + 1) & (MAX_PATH_NODES - 1);
        const xVec3& A = activity->path[activity->path_start].center;
        const xVec3& B = activity->path[second_index].center;
        F32 ABx = B.x - A.x, ABy = B.y - A.y, ABz = B.z - A.z;
        F32 dist2 = ABx * ABx + ABy * ABy + ABz * ABz, min_dist = activity->cfg->card_dist, min_dist2 = min_dist * min_dist;
        if (dist2 < min_dist2) {
            activity->path_size--;
            activity->path_start = second_index;
        }
    }

    if (activity->path_size >= MAX_PATH_NODES) {
        activity->path_size = MAX_PATH_NODES - 1;
    }

    activity->path_start = (activity->path_start - 1) & (MAX_PATH_NODES - 1);
    activity->path_size++;

    path_node& p = activity->path[activity->path_start];
    p.just_added = true;
    p.age = 0.0f;
    p.center = center;

    activity->center = center;
}

void xModelBlur::set_lifetime(F32 value, F32 time)
{
    activity->lifetime.go(value, time);
}

bool xModelBlur::update(F32 dt)
{
    activity->lifetime.update(dt);
    activity->alpha.update(dt);

    S32 i;
    F32 lifetime = activity->lifetime.value;
    if (lifetime <= 0.0f && activity->lifetime.end <= 0.0f && !(activity->cfg->flags & 0x2)) {
        deactivate();
        return false;
    }

    for (i = 0; i < activity->path_size; i++) {
        path_node& p = activity->path[(i + activity->path_start) & (MAX_PATH_NODES - 1)];
        if (p.just_added) {
            p.just_added = false;
        } else {
            p.age += dt;
            if (p.age >= lifetime) {
                if (i == 0) {
                    activity->path_size = 1;
                    break;
                }

                path_node& pp = activity->path[(i - 1 + activity->path_start) & (MAX_PATH_NODES - 1)];
                if (pp.age >= lifetime) {
                    activity->path_size = i;
                    break;
                }
            }
        }
    }

    F32 card_dist = activity->cfg->card_dist;
    S32 max_card_renders = activity->cfg->max_card_renders;
    S32 end = activity->path_size - 1;
    F32 alpha_scale = activity->cfg->color_alpha * activity->alpha.value / lifetime;
    card_data* cards = activity->cards;
    S32 cards_size = 0;
    F32 path_dist = 0.0f;

    for (i = 1; i < activity->path_size; i++) {
        if (cards_size >= max_card_renders) break;

        path_node& p0 = activity->path[(i - 1 + activity->path_start) & (MAX_PATH_NODES - 1)];
        path_node& p1 = activity->path[(i + activity->path_start) & (MAX_PATH_NODES - 1)];
        const xVec3& A = p0.center;
        const xVec3& B = p1.center;
        F32 ABx = B.x - A.x, ABy = B.y - A.y, ABz = B.z - A.z;
        F32 segment_dist = xsqrt(ABx * ABx + ABy * ABy + ABz * ABz);
        if (segment_dist < 0.001f) {
            path_dist += segment_dist;
            continue;
        }

        F32 idist = 1.0f / segment_dist;
        F32 age0 = p0.age;
        F32 dage = p1.age - p0.age;
        F32 dist = -path_dist;
        path_dist += segment_dist;

        for (; cards_size < max_card_renders; cards_size++) {
            if (path_dist < card_dist) break;

            dist += card_dist;
            path_dist -= card_dist;
            F32 t = dist * idist;
            F32 age = age0 + dage * t;
            if (age >= lifetime) break;

            card_data& card = cards[cards_size];
            card.alpha = alpha_scale * (lifetime - age);
            card.center.assign(A.x + ABx * t, A.y + ABy * t, A.z + ABz * t);
        }
    }

    activity->cards_size = cards_size;

    if (activity->path_size > i + 1) {
        activity->path_size = i + 1;
    }

    return true;
}

xModelBlur::activity_data* xModelBlur::alloc_activity()
{
    activity_data* activity = activities[activities_used];
    activities_used++;
    return activity;
}

void xModelBlur::free_activity(activity_data* activity)
{
    activities_used--;
    activity_data** tail_activity = activities + activities_used;
    if (tail_activity != &activity) {
        activity_data* temp = *tail_activity;
        activities[activity->index] = temp;
        *tail_activity = activity;
        temp->index = activity->index;
        activity->index = activities_used;
    }
}
