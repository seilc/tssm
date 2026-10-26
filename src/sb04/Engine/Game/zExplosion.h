#include "xColor.h"
#include "rwplcore.h"
#include "xIni.h"
#include "xVec3.h"

class zExplosion
{
public:
    struct trail_emitter
    {
        void update(xVec3& loc, F32 dt, F32 intensity);
        void stop();
        void start(S32 type, xVec3& loc);
    };
    void emit(S32 type, const xVec3& loc);
    S32 find_type(U32 id);
    void render();
    void pre_render();
    void update(F32 dt);
    void scene_exit();
    void scene_enter();
    void startup();
};

namespace
{
    struct glare_config
    {
        F32 life;
        F32 scale;
        xColor_tag color;
    };

    struct streak_config
    {
        F32 life;
        F32 rate;
        F32 emit_delay;
        F32 emit_time;
        F32 width;
        F32 length;
        F32 vel;
        F32 radius;
        F32 gravity;
        F32 alpha;
    };

    struct spark_config
    {
        F32 life;
        F32 rate;
        F32 emit_delay;
        F32 emit_time;
        F32 scale;
        F32 vel_min;
        F32 vel_max;
        F32 radius;
        F32 gravity;
        F32 alpha;
    };

    struct shake_config
    {
        F32 time;
        F32 mag;
        F32 cycle;
        F32 rot_mag;
        F32 radius;
    };

    struct presence_config
    {
        U32 hurt_whom;
        F32 delay;
        F32 life;
        F32 knockback;
        F32 radius_begin;
        F32 radius_end;
        F32 damage_player;
        F32 damage_npc;
        F32 damage_other;
    };

    struct decal_config
    {
        S32 type;
        F32 radius;
        F32 life;
        F32 width;
        F32 max_dist;
    };

    struct _class_0
    {
        U32 type;
        F32 radius;
        F32 duration;
        F32 intensity;
        F32 freq;
    };

    struct _class_1
    {
        U32 fire;
        U32 smoke;
        U32 streak;
        U32 spark;
        U32 glare;
        U32 decal;
    };

    // WIP
    struct runtime_config
    {
        U32 id;
        F32 vel_decay;
        F32 emit_radius;
        U32 motes_min;
        U32 motes_max;
        F32 life_min;
        F32 life_max;
        F32 scale_min;
        F32 scale_max;
        F32 scale_fire;
        F32 scale_smoke;
        F32 vel_min;
        F32 vel_max;
        //	iSndGroupHandle sound;
        S32 material_index;
        S32 streak_group_index;
        S32 spark_group_index;
        //	xResponseCurve anim;
        glare_config glare;
        //	_class_6 warp;
        streak_config streak;
        spark_config spark;
        shake_config shake;
        presence_config presence;
        decal_config decal;
        //	_class_7 texture;
        F32 vel_decay_mult;
    };

    struct anim_data
    {
        F32 alpha;
        F32 scale;
        F32 heat;
        F32 rise;
        F32 glow;
    };

    struct curve_node_0
    {
        F32 t;
        anim_data anim;
    };

    struct ini_config
    {
        char name[64];
        F32 vel_decay;
        F32 emit_radius;
        U32 motes_min;
        U32 motes_max;
        F32 life_min;
        F32 life_max;
        F32 scale_min;
        F32 scale_max;
        F32 scale_fire;
        F32 scale_smoke;
        F32 vel_min;
        F32 vel_max;
        U32 sound;
        curve_node_0* anim;
        U32 anim_size;
        glare_config glare;
        _class_0 warp;
        streak_config streak;
        spark_config spark;
        shake_config shake;
        presence_config presence;
        decal_config decal;
        _class_1 texture;
    };

    runtime_config* runtime_configs;
    U32 configs_size;

    void load_runtime_configs();
    void update_sparks(F32 dt);
    void update_spark_emitters(F32 dt);
    void update_streaks(F32 dt);
    void update_streak_emitters(F32 dt);
    void load_ini_configs();
    void load_default_config_just_sparks(ini_config& cfg);
    void load_default_config_gauntlet_boom(ini_config& cfg);
    void load_default_config_fire_trail(ini_config& cfg);
    void load_default_config_plasma(ini_config& cfg);
    void load_default_config_fire(ini_config& cfg);
    void load_config(ini_config& cfg, xIniSection& sec, xIniFile& ini);
    void reset_config(ini_config& cfg);
    S32 compare_ini_values(const void* e1, const void* e2);
    S32 compare_ini_sections(const void* e1, const void* e2);
    void ptank_render();
    void ptank_render_sparks();
    void ptank_render_streaks();
} // namespace
