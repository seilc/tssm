#ifndef XCAM_H
#define XCAM_H

#include "xMath3.h"
#include "xPad.h"

struct xCamGroup;
struct xCamBlend;
struct xCamConfigFollow;
struct xScene;

enum xCamCoordType
{
    XCAM_COORD_INVALID = -1,
    XCAM_COORD_CART = 0,
    XCAM_COORD_CYLINDER,
    XCAM_COORD_SPHERE,
    XCAM_COORD_MAX
};

enum xCamOrientType
{
    XCAM_ORIENT_INVALID = -1,
    XCAM_ORIENT_QUAT = 0,
    XCAM_ORIENT_EULER,
    XCAM_ORIENT_MAX
};

struct xCamCoordCylinder
{
    xVec3 origin;
    F32 dist;
    F32 height;
    F32 theta;
};

struct xCamCoordSphere
{
    xVec3 origin;
    F32 dist;
    xQuat dir;
};

struct xCamOrientEuler
{
    F32 yaw;
    F32 pitch;
    F32 roll;
};

struct xCamConfigCommon
{
    U8 priority;
    U8 pad1;
    U8 pad2;
    U8 pad3;
    F32 blend_time;
};

struct xCam
{
public:
    xMat4x3 mat;
    F32 fov;
    S32 flags;
    U32 owner;
    xCamGroup* group;
    analog_data analog;
    F32 motion_factor;
    xCamCoordType coord_type;
    xCamOrientType orient_type;
    union
    {
        xVec3 cart;
        xCamCoordCylinder cylinder;
        xCamCoordSphere sphere;
    } coord;
    union
    {
        xQuat quat;
        xCamOrientEuler euler;
    } orient;
    xCamConfigCommon cfg_common;

    bool active();

    static void scene_enter();
    static void scene_exit();

    void refresh_mat();

    static void coord_to_local(xVec3& c, const xVec3& loc);
    static void orient_to_local(xQuat& o, const xMat3x3& mat);

    virtual void create();
    virtual void destroy() {}
    virtual void start();
    virtual void stop();
    virtual void update(xScene& scene, F32 dt) = 0;
    virtual xCam* get_next() { return NULL; }
    virtual xCamConfigFollow* config_follow() { return NULL; }

    S32 group_index;
    S32 group_flags;
    xCamBlend* blender;
};

inline void xCam::coord_to_local(xVec3& c, const xVec3& loc)
{
    c = loc;
}

inline void xCam::orient_to_local(xQuat& o, const xMat3x3& mat)
{
    xQuatFromMat(&o, &mat);
}

#endif
