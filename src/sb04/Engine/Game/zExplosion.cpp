#include "zParticleGenerator.h"
#include <PowerPC_EABI_Support\MSL_C\MSL_Common\bsearch.h>
#include <PowerPC_EABI_Support\MSL_C\MSL_Common\stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include "mem.h"

#include "extras.h"
#include "xString.h"

#include "zExplosion.h"
#include "zParticleCustom.h"

U32 decal_type_ids[4];
S32 decal_blend_mode[3];

void zExplosion::emit(S32 type, const xVec3& loc)
{
}

// WIP
S32 zExplosion::find_type(U32 id)
{
    for (S32 i = 0; i < configs_size; i++)
    {
        // non-matching offset until runtime_config's structure is done
        if (id == runtime_configs[i].id)
        {
            return i;
        }
    }

    return 0;
}

void zExplosion::render()
{
}

void zExplosion::pre_render()
{
    ptank_render();
}

void zExplosion::update(F32 dt)
{
}

void zExplosion::scene_exit()
{
}

void zExplosion::scene_enter()
{
}

void zExplosion::startup()
{
    load_ini_configs();
}

namespace
{
    void load_runtime_configs()
    {
        ini_config* icfg;
        ini_config* end_icfg;
        runtime_config* ocfg;
    }

    void update_sparks(F32 dt)
    {
        spark_particle* spark;
        spark_particle* end_spark;
    }

    void update_spark_emitters(F32 dt)
    {
        //spark_emitter* emitter;
        //spark_emitter* end_emitter;
        F32 time;
        //runtime_config & cfg;
        S32 emit;
    }

    void update_streaks(F32 dt)
    {
        //streak_particle* streak;
        //streak_particle* end_streak;
    }

    void update_streak_emitters(F32 dt)
    {
        //streak_emitter* emitter;
        //streak_emitter* end_emitter;
        F32 time;
        //runtime_config & cfg;
        S32 emit;
    }

    void load_ini_configs()
    {
        xIniFile* ini;
        xIniSection* sections;
        U32 memsize;
        void* mem;
        xIniSection* isec;
        xIniSection* end_isec;
        xIniSection* osec;
        U8 is_default;
        //default_type_loader* dtl;
        //default_type_loader* end_dtl;
        ini_config* cfg;
        ini_config* end_cfg;
        S32 i;
        xIniSection* sec;
    }

    void load_default_config_just_sparks(ini_config& cfg)
    {
        load_default_config_fire(cfg);
        cfg.vel_decay = 0.0f;
        cfg.emit_radius = 0.0f;
        cfg.motes_min = 50;
        cfg.motes_max = 60;
        cfg.life_min = 0.6f;
        cfg.life_max = 1.3f;
        cfg.scale_min = 0.4f;
        cfg.scale_max = 0.5f;
        cfg.scale_fire = 0.0f;
        cfg.scale_smoke = 0.0f;
        cfg.vel_min = 1.0f;
        cfg.vel_max = 2.0f;
        cfg.sound = 0;
        cfg.glare.life = 0.0f;
        cfg.glare.scale = 0.0f;
        cfg.glare.color.r = 0xFF;
        cfg.glare.color.g = 0xFF;
        cfg.glare.color.b = 0xFF;
        cfg.glare.color.a = 0;
        memset(&cfg.warp, 0, sizeof(_class_0));
        memset(&cfg.streak, 0, sizeof(streak_config));
        memset(&cfg.shake, 0, sizeof(shake_config));
        memset(&cfg.presence, 0, sizeof(presence_config));
        memset(&cfg.decal, 0, sizeof(decal_config));
        memset(&cfg.texture, 0, sizeof(_class_1));
        cfg.texture.spark = xStrHash("spark_single2");
        cfg.spark.life = 0.75f;
        cfg.spark.rate = 40.0f;
        cfg.spark.emit_delay = 0.0f;
        cfg.spark.emit_time = 0.2f;
        cfg.spark.scale = 0.15f;
        cfg.spark.vel_min = 1.0f;
        cfg.spark.vel_max = 0.5f;
        cfg.spark.radius = 0.2f;
        cfg.spark.gravity = -9.8f;
        cfg.spark.alpha = 2.0f;
    }

    void load_default_config_gauntlet_boom(ini_config& cfg)
    {
        load_default_config_plasma(cfg);
        cfg.texture.fire = xStrHash("ExplosionFlash_Tan_64");
        cfg.texture.smoke = xStrHash("ExplosionFlash_Smoke_tan_64");
        cfg.texture.streak = xStrHash("spark_single2");
        cfg.texture.spark = xStrHash("spark_single2");
        cfg.texture.glare = xStrHash("LensFlare01");
        cfg.texture.decal = 0;
        cfg.spark.life = 0.75f;
        cfg.spark.rate = 50.0f;
        cfg.spark.emit_delay = 0.0f;
        cfg.spark.emit_time = 0.2f;
        cfg.spark.scale = 0.15f;
        cfg.spark.vel_min = 2.0f;
        cfg.spark.vel_max = 15.0f;
        cfg.spark.radius = 1.0f;
        cfg.spark.gravity = -9.8f;
        cfg.spark.alpha = 2.0f;
        memset(&cfg.shake, 0, sizeof(shake_config));
    }

    void load_default_config_fire_trail(ini_config& cfg)
    {
        cfg.vel_decay = 12.0f;
        cfg.emit_radius = 0.0f;
        cfg.motes_min = 50;
        cfg.motes_max = 60;
        cfg.life_min = 0.6f;
        cfg.life_max = 1.3f;
        cfg.scale_min = 0.4f;
        cfg.scale_max = 0.5f;
        cfg.scale_fire = 0.5f;
        cfg.scale_smoke = 0.69999999f;
        cfg.vel_min = 1.0f;
        cfg.vel_max = 2.0f;
        cfg.sound = 0;
        static curve_node_0 anim[] = {
            { 0.0f, { 1.0f, 1.0f, 1.0f, 0.0f, 1.0f } }, { 0.18f, { 1.0f, 2.0f, 0.6f, 0.0f, 1.0f } },
            { 0.5f, { 1.0f, 2.5f, 0.3f, 0.4f, 1.0f } }, { 0.75f, { 1.0f, 3.0f, 0.0f, 0.4f, 1.0f } },
            { 1.0f, { 0.0f, 3.5f, 0.0f, 0.4f, 1.0f } },
        };
        cfg.anim = anim;
        cfg.anim_size = 5;
        cfg.glare.life = 1.0f;
        cfg.glare.scale = 4.0f;
        cfg.glare.color.r = 0xff;
        cfg.glare.color.g = 0xff;
        cfg.glare.color.b = 0xff;
        cfg.glare.color.a = 100;
        cfg.warp.type = 0;
        cfg.warp.radius = 0.6f;
        cfg.warp.duration = 0.5f;
        cfg.warp.intensity = 0.3f;
        cfg.warp.freq = 1.0f;
        cfg.streak.life = 0.15f;
        cfg.streak.rate = 40.0f;
        cfg.streak.emit_delay = 0.0f;
        cfg.streak.emit_time = 0.0f;
        cfg.streak.width = 0.015f;
        cfg.streak.length = 6.0f;
        cfg.streak.vel = 7.5f;
        cfg.streak.radius = 0.0f;
        cfg.streak.gravity = -9.8f;
        cfg.streak.alpha = 1.0f;
        cfg.spark.life = 0.75f;
        cfg.spark.rate = 0.0f;
        cfg.spark.emit_delay = 0.0f;
        cfg.spark.emit_time = 0.0f;
        cfg.spark.scale = 0.2f;
        cfg.spark.vel_min = 2.0f;
        cfg.spark.vel_max = 15.0f;
        cfg.spark.radius = 1.0f;
        cfg.spark.gravity = -9.8f;
        cfg.spark.alpha = 2.0f;
        cfg.shake.time = 0.0f;
        cfg.shake.mag = 0.0f;
        cfg.shake.cycle = 0.05f;
        cfg.shake.rot_mag = 0.2f;
        cfg.shake.radius = 7.0f;
        cfg.presence.delay = 0.0f;
        cfg.presence.life = 0.0f;
        cfg.presence.knockback = 0.0f;
        cfg.presence.radius_begin = 0.0f;
        cfg.presence.radius_end = 0.0f;
        cfg.presence.damage_player = 0.0f;
        cfg.presence.damage_npc = 0.0f;
        cfg.presence.damage_other = 0.0f;
        cfg.decal.type = 0;
        cfg.decal.radius = 0.0f;
        cfg.decal.life = 0.0f;
        cfg.decal.width = 0.0f;
        cfg.decal.max_dist = 0.0f;
        cfg.texture.fire = xStrHash("ExplosionFlash_Tan_64");
        cfg.texture.smoke = xStrHash("ExplosionFlash_Smoke_tan_64");
        cfg.texture.streak = xStrHash("spark_single2");
        cfg.texture.spark = xStrHash("spark_single2");
        cfg.texture.glare = xStrHash("LensFlare01");
        cfg.texture.decal = 0;
    }

    void load_default_config_plasma(ini_config& cfg)
    {
        cfg.vel_decay = 10.0f;
        cfg.emit_radius = 0.1f;
        cfg.motes_min = 32;
        cfg.motes_max = 32;
        cfg.life_min = 0.5f;
        cfg.life_max = 1.5f;
        cfg.scale_min = 0.4f;
        cfg.scale_max = 0.5f;
        cfg.scale_fire = 1.1f;
        cfg.scale_smoke = 1.4f;
        cfg.vel_min = 2.0f;
        cfg.vel_max = 10.0f;
        cfg.sound = 0;
        static curve_node_0 anim[] = {
            { 0.0f, { 1.0f, 1.0f, 1.0f, 0.0f, 1.0f } },
            { 0.03f, { 1.0f, 2.0f, 1.0f, 0.0f, 1.0f } },
            { 0.5f, { 1.0f, 2.5f, 0.2f, 0.4f, 1.0f } },
            { 1.0f, { 0.0f, 3.0f, 0.0f, 0.4f, 1.0f } },
        };
        cfg.anim = anim;
        cfg.anim_size = 4;
        cfg.glare.life = 0.4f;
        cfg.glare.scale = 9.0f;
        cfg.glare.color.r = 0xff;
        cfg.glare.color.g = 0xff;
        cfg.glare.color.b = 0xff;
        cfg.glare.color.a = 128;
        cfg.warp.type = xStrHash("Shockwave");
        cfg.warp.radius = 1.0f;
        cfg.warp.duration = 0.5f;
        cfg.warp.intensity = 1.0f;
        cfg.warp.freq = 1.0f;
        cfg.streak.life = 0.2f;
        cfg.streak.rate = 200.0f;
        cfg.streak.emit_delay = 0.0f;
        cfg.streak.emit_time = 0.1f;
        cfg.streak.width = 0.05f;
        cfg.streak.length = 2.0f;
        cfg.streak.vel = 15.0f;
        cfg.streak.radius = 0.2f;
        cfg.streak.gravity = -9.8f;
        cfg.streak.alpha = 2.0f;
        cfg.spark.life = 0.75f;
        cfg.spark.rate = 0.0f;
        cfg.spark.emit_delay = 0.0f;
        cfg.spark.emit_time = 0.0f;
        cfg.spark.scale = 0.2f;
        cfg.spark.vel_min = 2.0f;
        cfg.spark.vel_max = 15.0f;
        cfg.spark.radius = 1.0f;
        cfg.spark.gravity = -9.8f;
        cfg.spark.alpha = 2.0f;
        cfg.shake.time = 0.0f;
        cfg.shake.mag = 0.0f;
        cfg.shake.cycle = 0.05f;
        cfg.shake.rot_mag = 0.2f;
        cfg.shake.radius = 7.0f;
        cfg.presence.delay = 0.0f;
        cfg.presence.life = 0.0f;
        cfg.presence.knockback = 0.0f;
        cfg.presence.radius_begin = 1.0f;
        cfg.presence.radius_end = 1.0f;
        cfg.presence.damage_player = 0.0f;
        cfg.presence.damage_npc = 0.0f;
        cfg.presence.damage_other = 1.0f;
        cfg.decal.type = 3;
        cfg.decal.radius = 1.0f;
        cfg.decal.life = 5.0f;
        cfg.decal.width = 0.5f;
        cfg.decal.max_dist = 2.0f;
        cfg.texture.fire = xStrHash("ExplosionFlash_Tan_64");
        cfg.texture.smoke = xStrHash("ExplosionFlash_Smoke_tan_64");
        cfg.texture.streak = 0;
        cfg.texture.spark = 0;
        cfg.texture.glare = xStrHash("LensFlare01");
        cfg.texture.decal = xStrHash("WallCrackDecal");
    }

    void load_default_config_fire(ini_config& cfg)
    {
        cfg.vel_decay = 18.0f;
        cfg.emit_radius = 0.1f;
        cfg.motes_min = 32;
        cfg.motes_max = 32;
        cfg.life_min = 0.6f;
        cfg.life_max = 1.3f;
        cfg.scale_min = 0.4f;
        cfg.scale_max = 0.5f;
        cfg.scale_fire = 1.1f;
        cfg.scale_smoke = 1.4f;
        cfg.vel_min = 3.0f;
        cfg.vel_max = 14.0f;
        cfg.sound = 0;
        static curve_node_0 anim[] = {
            { 0.0f, { 1.0f, 1.0f, 1.0f, 0.0f, 1.0f } },
            { 0.18f, { 1.0f, 2.0f, 1.0f, 0.0f, 1.0f } },
            { 0.5f, { 1.0f, 2.5f, 0.2f, 0.4f, 1.0f } },
            { 1.0f, { 0.0f, 3.0f, 0.0f, 0.4f, 1.0f } },
        };
        cfg.anim = anim;
        cfg.anim_size = 4;
        cfg.glare.life = 0.5f;
        cfg.glare.scale = 8.0f;
        cfg.glare.color.r = 0xff;
        cfg.glare.color.g = 0xff;
        cfg.glare.color.b = 0xff;
        cfg.glare.color.a = 200;
        cfg.warp.type = xStrHash("Shockwave");
        cfg.warp.radius = 1.0f;
        cfg.warp.duration = 0.5f;
        cfg.warp.intensity = 1.0f;
        cfg.warp.freq = 1.0f;
        cfg.streak.life = 0.15f;
        cfg.streak.rate = 200.0f;
        cfg.streak.emit_delay = 0.0f;
        cfg.streak.emit_time = 0.2f;
        cfg.streak.width = 0.02f;
        cfg.streak.length = 1.5f;
        cfg.streak.vel = 15.0f;
        cfg.streak.radius = 1.0f;
        cfg.streak.gravity = -30.0f;
        cfg.streak.alpha = 2.0f;
        cfg.spark.life = 0.75f;
        cfg.spark.rate = 50.0f;
        cfg.spark.emit_delay = 0.0f;
        cfg.spark.emit_time = 0.2f;
        cfg.spark.scale = 0.15f;
        cfg.spark.vel_min = 2.0f;
        cfg.spark.vel_max = 15.0f;
        cfg.spark.radius = 1.0f;
        cfg.spark.gravity = -9.8f;
        cfg.spark.alpha = 2.0f;
        cfg.shake.time = 1.0f;
        cfg.shake.mag = 0.2f;
        cfg.shake.cycle = 0.05f;
        cfg.shake.rot_mag = 0.2f;
        cfg.shake.radius = 10.0f;
        cfg.presence.delay = 0.0f;
        cfg.presence.life = 0.0f;
        cfg.presence.knockback = 0.0f;
        cfg.presence.radius_begin = 1.0f;
        cfg.presence.radius_end = 1.0f;
        cfg.presence.damage_player = 0.0f;
        cfg.presence.damage_npc = 0.0f;
        cfg.presence.damage_other = 1.0f;
        cfg.decal.type = 1;
        cfg.decal.radius = 1.0f;
        cfg.decal.life = 5.0f;
        cfg.decal.width = 0.5f;
        cfg.decal.max_dist = 2.0f;
        cfg.texture.fire = xStrHash("ExplosionFlash_Tan_64");
        cfg.texture.smoke = xStrHash("ExplosionFlash_Smoke_tan_64");
        cfg.texture.streak = xStrHash("spark_single2");
        cfg.texture.spark = xStrHash("spark_single2");
        cfg.texture.glare = xStrHash("LensFlare01");
        cfg.texture.decal = xStrHash("WallCrackDecal");
    }

    // WIP
    void load_config(ini_config& cfg, xIniSection& sec, xIniFile& ini)
    {
        xIniValue* unk;
        xIniValue* values;

        unk = &ini.Values[sec.first];
        qsort((void*)unk, sec.count, sizeof(xIniValue), compare_ini_values);
        values = (xIniValue*)bsearch("vel_decay", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.vel_decay = atof(values->val);
        }
        values = (xIniValue*)bsearch("emit_radius", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.emit_radius = atof(values->val);
        }
        values = (xIniValue*)bsearch("motes_min", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.motes_min = atoi(values->val);
        }
        values = (xIniValue*)bsearch("motes_max", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.motes_max = atoi(values->val);
        }
        values = (xIniValue*)bsearch("life_min", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.life_min = atof(values->val);
        }
        values = (xIniValue*)bsearch("life_max", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.life_max = atof(values->val);
        }
        values = (xIniValue*)bsearch("scale_min", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.scale_min = atof(values->val);
        }
        values = (xIniValue*)bsearch("scale_max", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.scale_max = atof(values->val);
        }
        values = (xIniValue*)bsearch("scale_fire", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.scale_fire = atof(values->val);
        }
        values = (xIniValue*)bsearch("scale_smoke", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.scale_smoke = atof(values->val);
        }
        values = (xIniValue*)bsearch("vel_min", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.vel_min = atof(values->val);
        }
        values = (xIniValue*)bsearch("vel_max", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.vel_max = atof(values->val);
        }
        values = (xIniValue*)bsearch("sound", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.sound = xStrHash(values->val);
        }
        values = (xIniValue*)bsearch("glare.life", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.glare.life = atof(values->val);
        }
        values = (xIniValue*)bsearch("glare.scale", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.glare.scale = atof(values->val);
        }
        values = (xIniValue*)bsearch("glare.color", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            char* buffer = xStrTok(values->val, " \t,;{}", &buffer);
            U32 i = cfg.glare.color.r;
            while (i != cfg.warp.type && (buffer != NULL))
            {
                i = atoi(buffer);
                buffer = xStrTok(NULL, " \t,;{}", &buffer);
                i++;
            }
        }
        values = (xIniValue*)bsearch("warp.type", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.warp.type = xStrHash(values->val);
        }
        values = (xIniValue*)bsearch("warp.radius", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.warp.radius = atof(values->val);
        }
        values = (xIniValue*)bsearch("warp.duration", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.warp.duration = atof(values->val);
        }
        values = (xIniValue*)bsearch("warp.intensity", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.warp.intensity = atof(values->val);
        }
        values = (xIniValue*)bsearch("warp.freq", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.warp.freq = atof(values->val);
        }
        values = (xIniValue*)bsearch("streak.life", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.streak.life = atof(values->val);
        }
        values = (xIniValue*)bsearch("streak.rate", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.streak.rate = atof(values->val);
        }
        values = (xIniValue*)bsearch("streak.emit_delay", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.streak.emit_delay = atof(values->val);
        }
        values = (xIniValue*)bsearch("streak.emit_time", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.streak.emit_time = atof(values->val);
        }
        values = (xIniValue*)bsearch("streak.width", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.streak.width = atof(values->val);
        }
        values = (xIniValue*)bsearch("streak.length", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.streak.length = atof(values->val);
        }
        values = (xIniValue*)bsearch("streak.vel", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.streak.vel = atof(values->val);
        }
        values = (xIniValue*)bsearch("streak.radius", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.streak.radius = atof(values->val);
        }
        values = (xIniValue*)bsearch("streak.gravity", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.streak.gravity = atof(values->val);
        }
        values = (xIniValue*)bsearch("streak.alpha", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.streak.alpha = atof(values->val);
        }
        values = (xIniValue*)bsearch("spark.life", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.spark.life = atof(values->val);
        }
        values = (xIniValue*)bsearch("spark.rate", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.spark.rate = atof(values->val);
        }
        values = (xIniValue*)bsearch("spark.emit_delay", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.spark.emit_delay = atof(values->val);
        }
        values = (xIniValue*)bsearch("spark.emit_time", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.spark.emit_time = atof(values->val);
        }
        values = (xIniValue*)bsearch("spark.scale", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.spark.scale = atof(values->val);
        }
        values = (xIniValue*)bsearch("spark.vel_min", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.spark.vel_min = atof(values->val);
        }
        values = (xIniValue*)bsearch("spark.vel_max", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.spark.vel_max = atof(values->val);
        }
        values = (xIniValue*)bsearch("spark.radius", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.spark.radius = atof(values->val);
        }
        values = (xIniValue*)bsearch("spark.gravity", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.spark.gravity = atof(values->val);
        }
        values = (xIniValue*)bsearch("spark.alpha", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.spark.alpha = atof(values->val);
        }
        values = (xIniValue*)bsearch("shake.time", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.shake.time = atof(values->val);
        }
        values = (xIniValue*)bsearch("shake.mag", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.shake.mag = atof(values->val);
        }
        values = (xIniValue*)bsearch("shake.cycle", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.shake.cycle = atof(values->val);
        }
        values = (xIniValue*)bsearch("shake.rot_mag", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.shake.rot_mag = atof(values->val);
        }
        values = (xIniValue*)bsearch("shake.radius", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.shake.radius = atof(values->val);
        }
        values = (xIniValue*)bsearch("presence.delay", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.presence.delay = atof(values->val);
        }
        values = (xIniValue*)bsearch("presence.life", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.presence.life = atof(values->val);
        }
        values = (xIniValue*)bsearch("presence.knockback", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.presence.knockback = atof(values->val);
        }
        values = (xIniValue*)bsearch("presence.radius_begin", (void*)unk, sec.count,
                                     sizeof(xIniValue), compare_ini_values);
        if (values != NULL)
        {
            cfg.presence.radius_begin = atof(values->val);
        }
        values = (xIniValue*)bsearch("presence.radius_end", (void*)unk, sec.count,
                                     sizeof(xIniValue), compare_ini_values);
        if (values != NULL)
        {
            cfg.presence.radius_end = atof(values->val);
        }
        values = (xIniValue*)bsearch("presence.damage_player", (void*)unk, sec.count,
                                     sizeof(xIniValue), compare_ini_values);
        if (values != NULL)
        {
            cfg.presence.damage_player = atof(values->val);
        }
        values = (xIniValue*)bsearch("presence.damage_npc", (void*)unk, sec.count,
                                     sizeof(xIniValue), compare_ini_values);
        if (values != NULL)
        {
            cfg.presence.damage_npc = atof(values->val);
        }
        values = (xIniValue*)bsearch("presence.damage_other", (void*)unk, sec.count,
                                     sizeof(xIniValue), compare_ini_values);
        if (values != NULL)
        {
            cfg.presence.damage_other = atof(values->val);
        }
        values = (xIniValue*)bsearch("decal.type", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        U32 total = 0; // default type
        if (values != NULL)
        {
            U32 decal_type_hash = xStrHash(values->val);

            for (int i = 0; i < 4; i++)
            {
                if (decal_type_hash == decal_type_ids[i])
                {
                    total = i;
                    break;
                }
            }
        }
        cfg.decal.type = total;
        values = (xIniValue*)bsearch("decal.radius", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.decal.radius = atof(values->val);
        }
        values = (xIniValue*)bsearch("decal.life", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.decal.life = atof(values->val);
        }
        values = (xIniValue*)bsearch("decal.width", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.decal.width = atof(values->val);
        }
        values = (xIniValue*)bsearch("decal.max_dist", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.decal.max_dist = atof(values->val);
        }
        values = (xIniValue*)bsearch("texture.fire", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.texture.fire = xStrHash(values->val);
        }
        values = (xIniValue*)bsearch("texture.smoke", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.texture.smoke = xStrHash(values->val);
        }
        values = (xIniValue*)bsearch("texture.streak", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.texture.streak = xStrHash(values->val);
        }
        values = (xIniValue*)bsearch("texture.spark", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.texture.spark = xStrHash(values->val);
        }
        values = (xIniValue*)bsearch("texture.glare", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.texture.glare = xStrHash(values->val);
        }
        values = (xIniValue*)bsearch("texture.decal", (void*)unk, sec.count, sizeof(xIniValue),
                                     compare_ini_values);
        if (values != NULL)
        {
            cfg.texture.decal = xStrHash(values->val);
        }
        for (U32 i = 0; i < 10; i++)
        {
            char* buffer;
            sprintf(buffer, "anim %d", i);
            values = (xIniValue*)bsearch(buffer, (void*)unk, sec.count, sizeof(xIniValue),
                                         compare_ini_values);
            if (values != NULL)
            {
                char* buffer = xStrTok(values->val, " \t,;{}", &buffer);
                for (U32 j = 0; j < 6 && buffer; j++)
                {
                    char* buffer = xStrTok(values->val, " \t,;{}", &buffer);
                    if (values != NULL)
                    {
                        cfg.texture.decal = xStrHash(values->val);
                    }
                }
            }
        }
    }

    void reset_config(ini_config& cfg)
    {
        cfg.vel_decay = 10.0f;
        cfg.emit_radius = 0.1f;
        cfg.motes_min = 32;
        cfg.motes_max = 32;
        cfg.life_min = 1.0f;
        cfg.life_max = 2.0f;
        cfg.scale_min = 1.0f;
        cfg.scale_max = 2.0f;
        cfg.scale_fire = 1.0f;
        cfg.scale_smoke = 1.0f;
        cfg.vel_min = 1.0f;
        cfg.vel_max = 2.0f;
        cfg.sound = 0;
        cfg.anim = NULL;
        cfg.anim_size = 0;
        cfg.glare.life = 0.0f;
        cfg.glare.scale = 1.0f;
        cfg.glare.color.r = 0;
        cfg.glare.color.g = 0;
        cfg.glare.color.b = 0;
        cfg.glare.color.a = 0;
        cfg.warp.type = 0;
        cfg.warp.radius = 1.0f;
        cfg.warp.duration = 1.0f;
        cfg.warp.intensity = 1.0f;
        cfg.warp.freq = 1.0f;
        cfg.streak.life = 1.0f;
        cfg.streak.rate = 0.0f;
        cfg.streak.emit_delay = 0.0f;
        cfg.streak.emit_time = 0.0f;
        cfg.streak.width = 0.1f;
        cfg.streak.length = 1.0f;
        cfg.streak.vel = 10.0f;
        cfg.streak.radius = 0.1f;
        cfg.streak.gravity = -9.8f;
        cfg.streak.alpha = 1.0f;
        cfg.spark.life = 0.0f;
        cfg.spark.rate = 0.0f;
        cfg.spark.emit_delay = 1.0f;
        cfg.spark.emit_time = 1.0f;
        cfg.spark.scale = 1.0f;
        cfg.spark.vel_min = 0.0f;
        cfg.spark.vel_max = 0.0f;
        cfg.spark.radius = 0.0f;
        cfg.spark.gravity = 0.0f;
        cfg.spark.alpha = 0.0f;
        cfg.shake.time = 0.0f;
        cfg.shake.mag = 0.0f;
        cfg.shake.cycle = 0.0f;
        cfg.shake.rot_mag = 0.0f;
        cfg.shake.radius = 0.0f;
        cfg.presence.delay = 0.0f;
        cfg.presence.life = 0.0f;
        cfg.presence.damage_player = 0.0f;
        cfg.presence.damage_npc = 0.0f;
        cfg.presence.damage_other = 0.0f;
        cfg.presence.knockback = 0.0f;
        cfg.presence.radius_begin = 0.0f;
        cfg.presence.radius_end = 0.0f;
        cfg.decal.type = 0;
        cfg.decal.radius = 0.0f;
        cfg.decal.life = 0.0f;
        cfg.decal.width = 0.0f;
        cfg.decal.max_dist = 0.0f;
        cfg.texture.fire = 0;
        cfg.texture.smoke = 0;
        cfg.texture.streak = 0;
        cfg.texture.spark = 0;
        cfg.texture.glare = 0;
        cfg.texture.decal = 0;
    }

    S32 compare_ini_values(const void* e1, const void* e2)
    {
        return stricmp(*(char* const*)e1, *(char* const*)e2);
    }

    S32 compare_ini_sections(const void* e1, const void* e2)
    {
        return stricmp(*(char* const*)e1, *(char* const*)e2);
    }
} // namespace
