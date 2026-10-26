#include "zNMECommon.h"
#include "xGlobals.h"

struct xCamBlend;

struct xCamCoordSphere
{
    xVec3 origin;
    F32 dist;
    xQuat dir;
};

struct xCamCoordCylinder
{
    xVec3 origin;
    F32 dist;
    F32 height;
    F32 theta;
};

struct _class_11
{
    union
    {
        xVec3 cart;
        xCamCoordCylinder cylinder;
        xCamCoordSphere sphere;
    };
};

struct xCamOrientEuler
{
    F32 yaw;
    F32 pitch;
    F32 roll;
};

struct _class_16
{
    union
    {
        xQuat quat;
        xCamOrientEuler euler;
    };
};

struct zone_data_1
{
    xVec3 offset;
    xVec3 face;
};

struct xCamConfigFollow
{
    zone_data_1 zone_rest;
    zone_data_1 zone_above;
    zone_data_1 zone_below;
    F32 speed_zone_offset;
    F32 speed_zone_face;
    F32 speed_move_orbit;
};

struct zone_data_0
{
    F32 distance;
    F32 height;
    F32 height_focus;
};

struct config_2
{
    zone_data_0 zone_rest;
    zone_data_0 zone_above;
    zone_data_0 zone_below;
    F32 move_speed;
    F32 turn_speed;
    F32 stick_speed;
    F32 stick_yaw_vel;
    F32 max_yaw_vel;
    F32 margin_angle;
};

struct zBossCam_Binary : xCam
{
    zPlayer* owner;
    xVec3 cam_loc;
    xQuat cam_dir;
    void (*fun_moveover)(zBossCam_Binary*, F32, void*);
    void* ctxt_moveover;
    config_2 cfg;
    S32 camera;
    xVec3* s1;
    xVec3* s2;
    F32 s2_radius;
    xVec2 stick_offset;
};
