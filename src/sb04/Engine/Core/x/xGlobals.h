#ifndef XGLOBALS_H
#define XGLOBALS_H

#include "xCamera.h"
#include "xPad.h"
#include "xUpdateCull.h"
#include "iCamera.h"
#include "iTime.h"
#include "zScene.h"
#include "xEnt.h"
#include "zEnt.h"

#include <rwcore.h>
#include <rpworld.h>

// U8's may be bools
// chars were originally int8

enum sceDemoEndReason
{
    SCE_DEMO_ENDREASON_ATTRACT_INTERRUPTED,
    SCE_DEMO_ENDREASON_ATTRACT_COMPLETE,
    SCE_DEMO_ENDREASON_PLAYABLE_INACTIVITY_TIMEOUT,
    SCE_DEMO_ENDREASON_PLAYABLE_GAMEPLAY_TIMEOUT,
    SCE_DEMO_ENDREASON_PLAYABLE_COMPLETE,
    SCE_DEMO_ENDREASON_PLAYABLE_QUIT,
    SCE_DEMO_ENDREASON_NETCONFIG_REQUEST,
    SCE_DEMO_ENDREASON_NETCONFIG_COMPLETE
};

// struct zPlayer
// {
//     // Why empty? (iFMV dwarf shows this)
//     // Non-empty ones exist in the zWads
// };

struct zPlayer : zEnt
{
    xVec3 trigLastFramePos;
    S32 zPlayerFlags;
    U32 lorezModelID;
    xModelInstance* lorezModel;
    xModelInstance* hirezModel;
};

struct PS2DemoGlobals
{
    U16 language;
    U16 aspect;
    U16 play_mode;
    U16 inactive_timeout;
    U16 gameplay_timeout;
    sceDemoEndReason exit_code;
    struct
    {
        U32 FMV_playing : 1;
        U32 more_padding : 31;
    };
    F32 bail_timer;
    F32 inactive_timer;
    F32 gameplay_timer;
    s8 subdir[16];
    U16 quit; // 0x30
    U16 vmode;
};

struct xGlobals
{
    xCamera oldSkoolCamera;
    xCamGroup* cam;
    xCamScreen* screen;
    xVec4 frustplane[12];
    _tagxPad* pad0; // 0x3e4
    _tagxPad* pad1;
    _tagxPad* pad2;
    _tagxPad* pad3; // 0x3f0
    _tagxPad* pad[4];
    S32 profile;
    char profFunc[128][6];
    xUpdateCullMgr* updateMgr;
    S32 sceneFirst;
    char sceneStart[32];
    RpWorld* currWorld; // 0x730
    iFogParams fog;
    iFogParams fogA;
    iFogParams fogB;
    S64 fog_t0;
    S64 fog_t1;
    S32 option_vibration;
    S32 option_subtitles;
    U32 slowdown;
    F32 update_dt;
    S16 ForceCinematic;
    S16 ForceAllCinematics;
    S32 useHIPHOP;
    U8 NoMusic;
    U8 NoCutscenes;
    U8 NoPadCheck;
    char currentActivePad;
    U8 firstStartPressed;
    U8 fromLauncher;
    U8 FlashWIP;
    U8 inLoadingScreen;
    U8 LoadingScene;
    U8 InitializingLoadingScreen;
    U8 ForceMono;
    U32 minVSyncCnt;
    U8 dontShowPadMessageDuringLoadingOrCutScene;
    U8 autoSaveFeature;
    S32 asyncLoadingScreen;
    S32 asyncLoadingFlags;
    char fromLauncherUser[32];
    zPlayer* ___player_ent_dont_use_directly;
    zScene* sceneCur; // 0x7f0
    zScene* scenePreload; // 0x7f4
    PS2DemoGlobals* PS2demo;
    char watermark[127];
    U8 watermarkAlpha;
    F32 watermarkSize;
};

#endif
