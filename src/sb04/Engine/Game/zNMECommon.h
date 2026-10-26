#ifndef ZNMECOMMON_H
#define ZNMECOMMON_H

#include "xNPCBasic.h"
#include "xDynAsset.h"
#include "xListItem.h"
#include "xEntDrive.h"
#include "xBehaveMgr.h"
#include "xEnt.h"
#include "xEvent.h"
#include "xSFX.h"

#include "iSnd.h"

#include "zNPCSndTable.h"
#include "zMovePoint.h"
#include "zShrapnel.h"

// DIRECTLY PORTED FROM BFBB

typedef struct NPCMsg;

enum en_npcparm
{
    NPC_PARM_NONE,
    NPC_PARM_MOVERATE,
    NPC_PARM_TURNRATE,
    NPC_PARM_ACCEL,
    NPC_PARM_DRIFT,
    NPC_PARM_MASS,
    NPC_PARM_TOSSGRAV,
    NPC_PARM_TOSSELASTIC,
    NPC_PARM_BND_ISBOX,
    NPC_PARM_BND_CENTER,
    NPC_PARM_BND_EXTENT,
    NPC_PARM_HITPOINTS,
    NPC_PARM_MODELSCALE,
    NPC_PARM_DETECT_RAD,
    NPC_PARM_DETECT_HYT,
    NPC_PARM_DETECT_OFF,
    NPC_PARM_ATTACK_RAD,
    NPC_PARM_ATTACK_FOV,
    NPC_PARM_SND_RAD,
    NPC_PARM_TIMEFIDGET,
    NPC_PARM_TIMEATTACK,
    NPC_PARM_TIMESTUN,
    NPC_PARM_TIMEALERT,
    NPC_PARM_VTX_ATTACKBASE,
    NPC_PARM_VTX_ATTACK,
    NPC_PARM_VTX_ATTACK1,
    NPC_PARM_VTX_ATTACK2,
    NPC_PARM_VTX_ATTACK3,
    NPC_PARM_VTX_ATTACK4,
    NPC_PARM_VTX_EYEBALL,
    NPC_PARM_VTX_DMGSMOKEA,
    NPC_PARM_VTX_DMGSMOKEB,
    NPC_PARM_VTX_DMGSMOKEC,
    NPC_PARM_VTX_DMGFLAMEA,
    NPC_PARM_VTX_DMGFLAMEB,
    NPC_PARM_VTX_DMGFLAMEC,
    NPC_PARM_VTX_PROPEL,
    NPC_PARM_VTX_EXHAUST,
    NPC_PARM_VTX_GEN01,
    NPC_PARM_VTX_GEN02,
    NPC_PARM_VTX_GEN03,
    NPC_PARM_VTX_GEN04,
    NPC_PARM_VTX_GEN05,
    NPC_PARM_ATK_SIZE01,
    NPC_PARM_ATK_FRAMES01,
    NPC_PARM_ATK_FRAMES01A,
    NPC_PARM_ATK_FRAMES01B,
    NPC_PARM_ATK_FRAMES02,
    NPC_PARM_ATK_FRAMES02A,
    NPC_PARM_ATK_FRAMES02B,
    NPC_PARM_ATK_FRAMES03,
    NPC_PARM_ATK_FRAMES03A,
    NPC_PARM_ATK_FRAMES03B,
    NPC_PARM_ESTEEM_A,
    NPC_PARM_ESTEEM_B,
    NPC_PARM_ESTEEM_C,
    NPC_PARM_ESTEEM_D,
    NPC_PARM_ESTEEM_E,
    NPC_PARM_SHADOW_CASTDIST,
    NPC_PARM_SHADOW_RADCACHE,
    NPC_PARM_SHADOW_RADRASTER,
    NPC_PARAM_TEST_COUNT,
    NPC_PARM_ENDTAG_INI,
    NPC_PARM_FIRSTMVPT,
    NPC_PARM_ENDTAG_PROPS,
    NPC_PARM_BOGUSSHARE,
    NPC_PARM_ENDTAG_SHARE,
    NPC_PARM_NOMORE,
    NPC_PARM_FORCEINT = 0x7fffffff
};

enum en_NPC_GOAL_SPOT
{
    NPC_GSPOT_START = 0x20,
    NPC_GSPOT_RESUME,
    NPC_GSPOT_FINISH,
    NPC_GSPOT_STARTALT,
    NPC_GSPOT_ALTA,
    NPC_GSPOT_ALTB,
    NPC_GSPOT_PATROLPAUSE,
    NPC_GSPOT_NOMORE,
    NPC_GSPOT_FORCEINT = 0x7fffffff
};

enum en_NPC_CARRY_STATE
{
    zNPCCARRY_NONE,
    zNPCCARRY_PICKUP,
    zNPCCARRY_THROW,
    zNPCCARRY_ATTEMPTPICKUP,
    zNPCCARRY_FORCEINT = 0x7fffffff
};

enum en_npcvibe
{
    NPC_VIBE_SOFT,
    NPC_VIBE_NORM,
    NPC_VIBE_HARD,
    NPC_VIBE_BUILD_A,
    NPC_VIBE_BUILD_B,
    NPC_VIBE_BUILD_C,
    NPC_VIBE_NOMORE,
    NPC_VIBE_FORCE = 0x7fffffff
};

struct xEntNPCAsset
{
    S32 npcFlags;
    S32 npcModel;
    S32 npcProps;
    U32 movepoint;
    U32 taskWidgetPrime;
    U32 taskWidgetSecond;
};

// struct xEntNPCAssetIN : xEntNPCAsset
// {
//     U32 navigation_mesh_id;
//     U32 settings;
// };

enum en_npcbtyp
{
    NPCP_BASIS_NONE,
    NPCP_BASIS_EVILROBOT,
    NPCP_BASIS_FRIENDLYROBOT,
    NPCP_BASIS_LOVINGCITIZEN,
    NPCP_BASIS_GRUMPYCITIZEN,
    NPCP_BASIS_NOMORE,
    NPCP_BASIS_FORCE = 0x7fffffff
};

enum en_dupowavmod
{
    NPCP_DUPOWAVE_CONTINUOUS,
    NPCP_DUPOWAVE_DISCREET,
    NPCP_DUPOWAVE_NOMORE,
    NPCP_DUPOWAVE_FORCE = 0x7fffffff
};

struct zNPCSettings : xDynAsset
{
    en_npcbtyp basisType;
    S8 allowDetect;
    U8 allowPatrol;
    U8 allowWander;
    U8 reduceCollide;
    S8 useNavSplines;
    S8 pad[3];
    S8 allowChase;
    S8 allowAttack;
    S8 assumeLOS;
    S8 assumeFOV;
    en_dupowavmod duploWaveMode;
    F32 duploSpawnDelay;
    S32 duploSpawnLifeMax;
};

struct NPCConfig : xListItem<NPCConfig>
{
    U32 modelID;
    S32 flg_config;
    F32 spd_turnMax;
    F32 spd_moveMax;
    F32 fac_accelMax;
    F32 fac_driftMax;
    F32 fac_gravKnock;
    F32 fac_elastic;
    S32 pts_damage;
    S32 useBoxBound;
    xVec3 off_bound;
    xVec3 dim_bound;
    F32 npcMass;
    F32 npcMassInv;
    F32 rad_detect;
    F32 hyt_detect;
    F32 off_detect;
    F32 rad_attack;
    F32 fov_attack;
    xVec3 scl_model;
    F32 tym_attack;
    F32 tym_fidget;
    F32 tym_stun;
    F32 tym_alert;
    F32 dst_castShadow;
    F32 rad_shadowCache;
    F32 rad_shadowRaster;
    F32 rad_dmgSize;
    S32 flg_vert;
    xModelTag tag_vert[20];
    xVec3 animFrameRange[9];
    S32 cnt_esteem[5];
    F32 rad_sound;
    NPCSndTrax* snd_trax; // 0x39C
    NPCSndTrax* snd_traxShare; // 0x3A0
    S32 test_count;
    U8 talk_filter[4];
    U8 talk_filter_size;
};

enum en_LASSO_STATUS
{
    LASS_STAT_DONE,
    LASS_STAT_PENDING,
    LASS_STAT_GRABBING,
    LASS_STAT_TOSSING,
    LASS_STAT_NOMORE,
    LASS_STAT_UNK_5, // needed to match switch in zNPCCommon::LassoNotify, checks value of 5
    LASS_STAT_FORCEINT = 0x7fffffff
};

enum en_mdlvert
{
    NPC_MDLVERT_ATTACKBASE,
    NPC_MDLVERT_ATTACK,
    NPC_MDLVERT_ATTACK1,
    NPC_MDLVERT_ATTACK2,
    NPC_MDLVERT_ATTACK3,
    NPC_MDLVERT_ATTACK4,
    NPC_MDLVERT_LOSEYEBALL,
    NPC_MDLVERT_DMGSMOKE_A,
    NPC_MDLVERT_DMGSMOKE_B,
    NPC_MDLVERT_DMGSMOKE_C,
    NPC_MDLVERT_DMGFLAME_A,
    NPC_MDLVERT_DMGFLAME_B,
    NPC_MDLVERT_DMGFLAME_C,
    NPC_MDLVERT_PROPEL,
    NPC_MDLVERT_EXHAUST,
    NPC_MDLVERT_GEN01,
    NPC_MDLVERT_GEN02,
    NPC_MDLVERT_GEN03,
    NPC_MDLVERT_GEN04,
    NPC_MDLVERT_GEN05,
    NPC_MDLVERT_NOMORE,
    NPC_MDLVERT_FORCEINT = 0x7fffffff
};

enum en_LASSO_EVENT
{
    LASS_EVNT_BEGIN,
    LASS_EVNT_ENDED,
    LASS_EVNT_GRABSTART,
    LASS_EVNT_GRABEND,
    LASS_EVNT_YANK,
    LASS_EVNT_ABORT,
    LASS_EVNT_NOMORE,
    LASS_EVNT_FORCEINT = 0x7fffffff
};

enum en_NPC_MSG_ID
{
    NPC_MID_NONE,
    NPC_MID_SYSEVENT,
    NPC_MID_RESPAWN,
    NPC_MID_DAMAGE,
    NPC_MID_EXPLOSION,
    NPC_MID_BUNNYHOP,
    NPC_MID_DTRON_NPCEMIT,
    NPC_MID_DTRON_NPCAVAIL,
    NPC_MID_DTRON_ISDEAD,
    NPC_MID_CHAT_REQUEST,
    NPC_MID_CHAT_DECLINE,
    NPC_MID_CHAT_ACCEPT,
    NPC_MID_CHAT_DONE,
    NPC_MID_CHAT_ABORT,
    NPC_MID_TALKSTART,
    NPC_MID_TALKON,
    NPC_MID_TALKOFF,
    NPC_MID_SAWPLYR,
    NPC_MID_NEEDMEDIC,
    NPC_MID_UNDERATTACK,
    NPC_MID_NPCDIED,
    NPC_MID_PLYRSPATULA,
    NPC_MID_BECOMESCARED,
    NPC_MID_NOLONGERSCARED,
    NPC_MID_CELEBRATE,
    NPC_MID_STUN,
    NPC_MID_SCRIPTBEGIN,
    NPC_MID_SCRIPTEND,
    NPC_MID_SCRIPTHALT,
    NPC_MID_DEV_ANIMSPIN,
    NPC_MID_DEV_ANIMCYCLE,
    NPC_MID_DEV_HEROMODE,
    NPC_MID_DEV_DONE,
    NPC_MID_NOMORE,
    NPC_MID_FORCE = 0x7fffffff
};

enum en_NPC_MSG_DATA
{
    NPC_MDAT_BLANK,
    NPC_MDAT_SYSEVENT,
    NPC_MDAT_BLAST,
    NPC_MDAT_CHAT,
    NPC_MDAT_SPAWN,
    NPC_MDAT_TARGET,
    NPC_MDAT_DAMAGE,
    NPC_MDAT_STUN,
    NPC_MDAT_SCRIPT,
    NPC_MDAT_MOUNT,
    NPC_MDAT_AREANOTIFY,
    NPC_MDAT_NOMORE,
    NPC_MDAT_FORCE = 0x7fffffff
};

enum en_SM_NOTICES
{
    SM_NOTE_NPCDIED,
    SM_NOTE_NPCSTANDBY,
    SM_NOTE_NPCALIVE,
    SM_NOTE_DUPPAUSE,
    SM_NOTE_DUPRESUME,
    SM_NOTE_DUPSETDELAY,
    SM_NOTE_DUPDEAD,
    SM_NOTE_KILLKIDS,
    SM_NOTE_NOMORE,
    SM_NOTE_FORCE = 0x7fffffff
};

enum en_allow
{
    ALLOW_NEVER,
    ALLOW_NORMAL,
    ALLOW_ALWAYS,
    ALLOW_NOMORE
};

enum en_npcgol
{
    NME_GOAL_UNKNOWN,
    NME_GOAL_CRIT_IDLE = 0x4e474300,
    NME_GOAL_CRIT_PATROL,
    NME_GOAL_CRIT_DYING,
    NME_GOAL_CRIT_DEAD,
    NME_GOAL_CRIT_BATTACK,
    NME_GOAL_CRIT_JATTACK,
    NME_GOAL_CRIT_JDYING,
    NME_GOAL_TURR_IDLE = 0x4e474700,
    NME_GOAL_TURR_RELOAD,
    NME_GOAL_TURR_HURT,
    NME_GOAL_TURR_DEAD,
    NME_GOAL_TURR_TREADY,
    NME_GOAL_TURR_TTURN,
    NME_GOAL_TURR_TSHOOT,
    NME_GOAL_TURR_PDORMANT,
    NME_GOAL_TURR_PALERT,
    NME_GOAL_TURR_PPATALPHA,
    NME_GOAL_TURR_BIDLE,
    NME_GOAL_TURR_BTURN,
    NME_GOAL_TURR_BSHOOT,
    NME_GOAL_TURR_BHURT,
    NME_GOAL_TURR_SPIRAL,
    NME_GOAL_IDLE = 0x4e474e00,
    NME_GOAL_PATROL,
    NME_GOAL_WANDER,
    NME_GOAL_FIDGET,
    NME_GOAL_WAITING,
    NME_GOAL_DEAD,
    NME_GOAL_NOMANLAND,
    NME_GOAL_LIMBO,
    NME_GOAL_DEV_ANIMVIEW = 0x4e474400,
    NME_GOAL_DEV_HEROMODE,
    NME_GOAL_TIKI_IDLE = 0x4e475400,
    NME_GOAL_TIKI_PATROL,
    NME_GOAL_TIKI_HIDE,
    NME_GOAL_TIKI_COUNT,
    NME_GOAL_TIKI_DYING,
    NME_GOAL_TIKI_DEAD,
    NME_GOAL_AFTERLIFE = 0x4e475300,
    NME_GOAL_SPAWN,
    NME_GOAL_WOUND,
    NME_GOAL_SPOOKED,
    NME_GOAL_NOTICE,
    NME_GOAL_SCAREWAIT,
    NME_GOAL_SCARE,
    NME_GOAL_TAUNT,
    NME_GOAL_EVILPAT = 0x4e475000,
    NME_GOAL_STUNNED,
    NME_GOAL_PATCARRY,
    NME_GOAL_PATTWIRL,
    NME_GOAL_PATTHROW,
    NME_GOAL_TRIGGER_NORMAL = 0x4e475800,
    NME_GOAL_TRIGGER_SCARY,
    NME_GOAL_TRIGGER_DETECT,
    NME_GOAL_TRIGGER_ALERT,
    NME_GOAL_TRIGGER_BATTLE,
    NME_GOAL_TRIGGER_WOUND,
    NME_GOAL_TRIGGER_ATTACK,
    NME_GOAL_TRIGGER_VINIVICIVIDI,
    NME_GOAL_FOGGER_AWARE = 0x4e474500,
    NME_GOAL_FOGGER_BATTLE,
    NME_GOAL_FOGGER_ATTACK,
    NME_GOAL_SLAMMER_AWARE,
    NME_GOAL_SLAMMER_BATTLE,
    NME_GOAL_SLAMMER_ATTACK,
    NME_GOAL_SPINNER_AWARE,
    NME_GOAL_SPINNER_BATTLE,
    NME_GOAL_FLINGER_NORMAL,
    NME_GOAL_FLINGER_AWARE,
    NME_GOAL_FLINGER_BATTLE,
    NME_GOAL_FLINGER_ATTACK,
    NME_GOAL_FLINGER_BOING,
    NME_GOAL_FLINGER_FLEE,
    NME_GOAL_FLINGER_PANIC,
    NME_GOAL_FLINGER_MOVE,
    NME_GOAL_POPPER_NORMAL,
    NME_GOAL_POPPER_AWARE,
    NME_GOAL_POPPER_WOUND,
    NME_GOAL_POPPER_EVADE,
    NME_GOAL_POPPER_BATTLE,
    NME_GOAL_POPPER_ATTACK,
    NME_GOAL_ZAP_NORMAL,
    NME_GOAL_ZAP_AWARE,
    NME_GOAL_ZAP_BATTLE,
    NME_GOAL_ZAP_WOUND,
    NME_GOAL_ZAP_ZAP,
    NME_GOAL_ZAP_MOVE,
    NME_GOAL_MERV_NORMAL,
    NME_GOAL_MERV_AWARE,
    NME_GOAL_MERV_BATTLE,
    NME_GOAL_MERV_ZAP,
    NME_GOAL_MERV_BOMB,
    NME_GOAL_MERV_BOWL,
    NME_GOAL_MERV_WOUND,
    NME_GOAL_MERV_MOVE,
    NME_GOAL_BUCK_RUNNING,
    NME_GOAL_BUCK_BIRTHING,
    NME_GOAL_BUCK_DYING,
    NME_GOAL_BUCK_DEAD,
    NME_GOAL_DENNIS_NORMAL,
    NME_GOAL_DENNIS_EVADE,
    NME_GOAL_DENNIS_BATTLE,
    NME_GOAL_DENNIS_ATTACK,
    NME_GOAL_DENNIS_TAUNT,
    NME_GOAL_DENNIS_DAMAGE,
    NME_GOAL_DENNIS_DEAD,
    NME_GOAL_DENTOO_NORMAL,
    NME_GOAL_DENTOO_EVADE,
    NME_GOAL_DENTOO_BATTLE,
    NME_GOAL_DENTOO_ATTACK,
    NME_GOAL_DENTOO_TAUNT,
    NME_GOAL_DENTOO_DAMAGE,
    NME_GOAL_DENTOO_DEAD,
    NME_GOAL_SBBAT_IDLE,
    NME_GOAL_SBBAT_DEAD,
    NME_GOAL_NOMORE,
    NME_GOAL_FORCE = 0x7fffffff
};

enum en_nmesimp
{
    NME_SIMP_HAPPY,
    NME_SIMP_DEAD,
    NME_SIMP_IGNORANT,
    NME_SIMP_WARYDETECT,
    NME_SIMP_WARY,
    NME_SIMP_WORRIED,
    NME_SIMP_CONFUSED,
    NME_SIMP_BIGBULLY,
    NPC_STAT_NOMORE
};

enum en_haztyp
{
    HAZ_TYP_UNKNOWN,
    HAZ_TYP_EXPLODE,
    HAZ_TYP_IMPACT,
    HAZ_TYP_IMPACTWET,
    HAZ_TYP_IMPACTBOOM,
    HAZ_TYP_DAZED,
    HAZ_TYP_SPAWNBALL_XX,
    HAZ_TYP_SPAWNBALL_GG,
    HAZ_TYP_SPAWNBALL_TR,
    HAZ_TYP_SPAWNBALL_PT,
    HAZ_TYP_SPAWNGROW,
    HAZ_TYP_BUCKOBOOM_V1,
    HAZ_TYP_TIKIBOOM,
    HAZ_TYP_SLAMWAVE_V1,
    HAZ_TYP_SLAMWAVE_V2,
    HAZ_TYP_SLAMWAVE_V3,
    HAZ_TYP_FLING_V1,
    HAZ_TYP_FLING_V2,
    HAZ_TYP_FLING_V3,
    HAZ_TYP_FLING_FROGFISH,
    HAZ_TYP_SPITPUDDLE_V1,
    HAZ_TYP_SPITPUDDLE_V2,
    HAZ_TYP_SPITPUDDLE_V3,
    HAZ_TYP_ICECREAMSPLAT,
    HAZ_TYP_SPITSTEAM,
    HAZ_TYP_SPITSPLASH,
    HAZ_TYP_POPPER_V1,
    HAZ_TYP_POPPER_V2,
    HAZ_TYP_POPPER_V3,
    HAZ_TYP_MERVBOMB_V1,
    HAZ_TYP_MERVBOMB_V2,
    HAZ_TYP_MERVBOMB_V3,
    HAZ_TYP_MERVLET_V1,
    HAZ_TYP_MERVLET_V2,
    HAZ_TYP_MERVLET_V3,
    HAZ_TYP_ZAPBALL_V1,
    HAZ_TYP_ZAPBALL_V2,
    HAZ_TYP_ZAPBOOM_V1,
    HAZ_TYP_ZAPBOOM_V2,
    HAZ_TYP_TURBALL_V1,
    HAZ_TYP_TURBALL_V2,
    HAZ_TYP_TURBALL_V3,
    HAZ_TYP_TURBOOM,
    HAZ_TYP_GOLFBALL,
    HAZ_TYP_GOLFBOOM,
    HAZ_TYP_GOLFJUNK_A,
    HAZ_TYP_GOLFJUNK_B,
    HAZ_TYP_GOLFJUNK_C,
    HAZ_TYP_GOLFJUNK_D,
    HAZ_TYP_GOLFJUNK_E,
    HAZ_TYP_DENNIS_KNIFE,
    HAZ_TYP_DENNIS_KNIFEBOOM,
    HAZ_TYP_TUNEBORN,
    HAZ_TYP_TUNEBANG,
    HAZ_TYP_TUNEBOOM,
    HAZ_TYP_TUNEFLYT,
    HAZ_TYP_SWIMWAKE,
    HAZ_TYP_BOWWAVE,
    HAZ_TYP_SPLASH_RING,
    HAZ_TYP_SPLISH_DROP,
    HAZ_TYP_VISSPLASH_WAVE,
    HAZ_TYP_VISSPLASH_DROP,
    HAZ_TYP_VISSPLASH_WATER,
    HAZ_TYP_VISSPLASH_CHOC,
    HAZ_TYP_VISSPLASH_LAVA,
    HAZ_TYP_VISSPLASH_BILE,
    HAZ_TYP_VISSPLASH_OIL,
    HAZ_TYP_VISSPLASH_SAUCE,
    HAZ_TYP_VISSPLASH_TOXIC,
    HAZ_TYP_REFLECT_V1,
    HAZ_TYP_PLYRBANG_V1,
    HAZ_TYP_POWERUP_EXPLOSION_V1,
    HAZ_TYP_NOMORE,
    HAZ_TYP_FORCE = 0x7fffffff
};

enum en_npcdmg
{
    DMGTYP_UNDECIDED,
    DMGTYP_ABOVE,
    DMGTYP_BELOW,
    DMGTYP_SIDE,
    DMGTYP_INSTAKILL,
    DMGTYP_WOUNDEVENT,
    DMGTYP_KILLEVENT,
    DMGTYP_NMEATTACK,
    DMGTYP_HITBYTOSS,
    DMGTYP_NMEKNOCKED,
    DMGTYP_ROPE,
    DMGTYP_CRUISEBUBBLE,
    DMGTYP_FRIENDLYFIRE,
    DMGTYP_REFLECTED,
    DMGTYP_BOULDER,
    DMGTYP_BUBBOWL,
    DMGTYP_THUNDER_TIKI_EXPLOSION,
    DMGTYP_DAMAGE_SURFACE,
    DMGTYP_BUNGEED,
    DMGTYP_SURFACE,
    DMGTYP_CARTWHEEL,
    DMGTYP_CARSMASH,
    DMGTYP_SLIDE,
    DMGTYP_EXPLOSION,
    DMGTYP_BBOWLZAP,
    DMGTYP_NOMORE,
    DMGTYP_FORCEINT = 0x7fffffff
};

enum en_plyrpup
{
    ePowerupLevelDisabled,
    ePowerupLevelNormal,
    ePowerupLevelLevelMax,
    ePowerupLevelHealthMax,
    ePowerupLevelCount
};

enum en_carystat
{
    zNMECARRY_NONE,
    zNMECARRY_PICKUP,
    zNMECARRY_TWIRL,
    zNMECARRY_THROW,
    zNMECARRY_ATTEMPTPICKUP,
    zNMECARRY_FORCEINT = 0x7fffffff
};

enum en_npcmsg
{
    NME_MID_NONE,
    NME_MID_SYSEVENT,
    NME_MID_RESPAWN,
    NME_MID_DAMAGE,
    NME_MID_EXPLOSION,
    NME_MID_BUNNYHOP,
    NME_MID_NEWDEST,
    NME_MID_DTRON_NMEEMIT,
    NME_MID_DTRON_NMEAVAIL,
    NME_MID_DTRON_ISDEAD,
    NME_MID_CHAT_REQUEST,
    NME_MID_CHAT_DECLINE,
    NME_MID_CHAT_ACCEPT,
    NME_MID_CHAT_DONE,
    NME_MID_CHAT_ABORT,
    NME_MID_TALKSTART,
    NME_MID_TALKON,
    NME_MID_TALKOFF,
    NME_MID_SAWPLYR,
    NME_MID_NEEDMEDIC,
    NME_MID_UNDERATTACK,
    NME_MID_NMEDIED,
    NME_MID_PLYRSPATULA,
    NME_MID_BECOMESCARED,
    NME_MID_NOLONGERSCARED,
    NME_MID_CELEBRATE,
    NME_MID_STUN,
    NME_MID_SCRIPTBEGIN,
    NME_MID_SCRIPTEND,
    NME_MID_SCRIPTHALT,
    NME_MID_NOMORE,
    NME_MID_FORCE = 0x7fffffff
};

enum en_msgdata
{
    NME_MDAT_BLANK,
    NME_MDAT_SYSEVENT,
    NME_MDAT_BLAST,
    NME_MDAT_CHAT,
    NME_MDAT_SPAWN,
    NME_MDAT_TARGET,
    NME_MDAT_DAMAGE,
    NME_MDAT_STUN,
    NME_MDAT_SCRIPT,
    NME_MDAT_MOUNT,
    NME_MDAT_AREANOTIFY,
    NME_MDAT_NOMORE,
    NME_MDAT_FORCE = 0x7fffffff
};

struct zNPCLassoInfo
{
    en_LASSO_STATUS stage;
    xEnt* lassoee;
    xAnimState* holdGuideAnim;
    xModelInstance* holdGuideModel;
    xAnimState* grabGuideAnim;
    xModelInstance* grabGuideModel;
};

struct zNPCCommon : xNPCBasic //Size of zNPCCommon: 0x2A0
{
    xEntAsset* entass; // 0x1BC
    xEntNPCAsset* npcass; // 0x1C0
    zNPCSettings* npcsetass; // 0x1C4
    S32 flg_vuln; // 0x1C8
    S32 flg_move; // 0x1CC
    S32 flg_misc; // 0x1D0
    S32 flg_able; // 0x1D4
    NPCConfig* cfg_npc; // 0x1D8
    zNPCSettings npcset; // 0x1DC
    zMovePoint* nav_past; // 0x208
    zMovePoint* nav_curr; // 0x20C
    zMovePoint* nav_dest; // 0x210
    zMovePoint* nav_lead;
    xSpline3* spl_mvptspline;
    F32 len_mvptspline;
    F32 dst_curspline;
    xEntDrive* drv_data;
    xPsyche* psy_instinct; // 0x228
    zNPCCommon* npc_duplodude;
    F32 spd_throttle; //0x230
    S32 flg_xtrarend;
    F32 tmr_fidget; //0x238
    F32 tmr_invuln; // 0x23C
    zShrapnelAsset* explosion; // 0x240
    xModelAssetParam* parmdata; // 0x244
    U32 pdatsize; //0x248
    zNPCLassoInfo* lassdata; //0x24C
    NPCSndQueue snd_queue[4]; //0x250

    zNPCCommon(S32 myType);

    F32 TurnToFace(F32 dt, const xVec3* dir_want, F32 useTurnRate);
    F32 ThrottleApply(F32 dt, const xVec3* dir, S32 force3D);
    F32 ThrottleAccel(F32 dt, S32 speedup, F32 pct_max);
    F32 ThrottleAdjust(F32 dt, F32 spd_want, F32 accel);

    F32 BoundAsRadius(int useCfg);
    void VelStop();
    static void ConfigSceneDone();
    U32 LassoInit();
    zNPCLassoInfo* GimmeLassInfo();
    void AddDEVGoals(xPsyche*);
    U32 DBG_Name(); // return type might be wrong
    void DBG_AddTweakers();
    void DBG_RptDataSize();
    U32 DBG_InstName(); // return type might be wrong
    xAnimTable* AnimGetTable();
    F32 AnimTimeRemain(xAnimState* ast);
    F32 AnimTimeCurrent();
    F32 AnimDuration(xAnimState* ast);
    bool IsMountableType(en_ZBASETYPE type);
    void MvptReset(zMovePoint* nav_goto);
    S32 MvptCycle();
    S32 HaveLOSToPos(xVec3*, float, xScene*, xBase*, xCollis*);
    void ModelScaleSet(F32 x, F32 y, F32 z);
    void ModelScaleSet(F32 unk);
    void ModelScaleSet(const xVec3* vec);
    xModelInstance* ModelAtomicFind(int index, int idx_prev, xModelInstance* mdl_prev);
    xModelInstance* ModelAtomicHide(int index, xModelInstance* mdl);
    xModelInstance* ModelAtomicShow(int index, xModelInstance* mdl);
    S32 AnimStart(U32 animID, S32 forceRestart);
    xAnimState* AnimFindState(U32 animID);
    xAnimState* AnimCurState();
    xAnimSingle* AnimCurSingle();
    U32 AnimCurStateID();
    void GiveReward();
    S32 SndPlayFromSFX(xSFX* sfx, U32* sid_played);
    S32 SndPlayRandom(en_NPC_SOUND sndtype);
    S32 SndChanIsBusy(S32 flg_chan);
    S32 LassoUseGuides(S32 idx_grabmdl, S32 idx_holdmdl);
    S32 GetVertPos(en_mdlvert vid, xVec3* pos);
    void Vibrate(en_npcvibe vibe, F32 duration);
    void AddScripting(xPsyche* psy, S32 (*eval_script)(xGoal*, void*, en_trantype*, F32, void*),
                      S32 (*eval_playanim)(xGoal*, void*, en_trantype*, F32, void*),
                      S32 (*eval_attack)(xGoal*, void*, en_trantype*, F32, void*),
                      S32 (*eval_move)(xGoal*, void*, en_trantype*, F32, void*),
                      S32 (*eval_follow)(xGoal*, void*, en_trantype*, F32, void*),
                      S32 (*eval_lead)(xGoal*, void*, en_trantype*, F32, void*),
                      S32 (*eval_wait)(xGoal*, void*, en_trantype*, F32, void*));
    void AddBaseline(xPsyche*, int (*)(xGoal*, void*, en_trantype*, float, void*),
                     int (*)(xGoal*, void*, en_trantype*, float, void*),
                     int (*)(xGoal*, void*, en_trantype*, float, void*),
                     int (*)(xGoal*, void*, en_trantype*, float, void*),
                     int (*)(xGoal*, void*, en_trantype*, float, void*));

    // defined from zNPCGoalRobo.cpp
    xVec3* Center();
    xVec3* Pos();
    RwMatrix* BoneMat(S32 unk) const;
    RwV3d* BonePos(S32 unk) const;
    void XZVecToPlayer(xVec3* unk1, F32* unk2);
    F32 XZDstSqToPos(const xVec3* unk1, xVec3* unk2, F32* unk3);
    void XZVecToPos(xVec3* unk1, const xVec3* unk2, F32* unk3);
    void XYZVecToPos(xVec3* dest, xVec3* unk2)
    {
        xVec3Sub(dest, unk2, Pos());
    }
    F32 XYZDstSqToPlayer(xVec3* unk);
    F32 XYZDstSqToPos(xVec3* unk1, xVec3* dest)
    {
        xVec3 dest_vec;
        if (dest == NULL)
        {
            dest = &dest_vec;
        }
        XYZVecToPos(dest, unk1);
        return xVec3Length2(dest);
    }
    void WonderOfTalking(S32 inprogress, xBase* owner);
    // return type is probably wrong
    S32 SomethingWonderful();
    S32 SndIsAnyPlaying();

    // vTable (xNPCBasic)

    virtual void Init(xEntAsset* asset);
    virtual void Reset();
    virtual void Setup();
    virtual void Process(xScene* xscn, F32 dt);
    virtual void BUpdate(xVec3* pos);
    virtual void NewTime(xScene* xscn, F32 dt);
    virtual void Move(xScene* xscn, F32 dt, xEntFrame*);
    virtual S32 SysEvent(xBase* from, xBase* to, U32 toEvent, const F32* toParam,
                         xBase* toParamWidget, S32* handled);
    virtual void CollideReview();
    virtual void Destroy();

    // vTable (zNPCCommon)
    // Not going to be correct, needs complete update
    virtual S32 NPCMessage(NPCMsg* mail);
    virtual void RenderExtra();
    virtual void RenderExtraPostParticles();
    virtual void ParseINI();
    virtual void ParseLinks();
    virtual void ParseProps();
    virtual void SelfSetup();
    virtual void SelfDestroy();
    virtual S32 IsHealthy();
    virtual S32 IsAlive();
    //virtual void Damage(en_npcdmg damtype, xBase* who, const xVec3* vec_hit);
    virtual S32 Respawn(const xVec3* pos, zMovePoint* mvptFirst, zMovePoint* mvptSpawnRef);
    virtual void DuploOwner(zNPCCommon* duper);
    virtual void DuploNotice(en_SM_NOTICES, void*);
    virtual S32 CanRope();
    virtual void LassoNotify(en_LASSO_EVENT event);
    virtual S32 SetCarryState(en_NPC_CARRY_STATE);
    virtual void Stun(F32 stuntime);
    virtual void SpeakBegin();
    virtual void SpeakEnd();
    virtual void SpeakStart(U32 sound, U32 param_2, S32 param_3);
    virtual void SpeakStop();

    virtual U32 AnimPick(S32 animID, en_NPC_GOAL_SPOT gspot, xGoal* goal)
    {
        return 0;
    }

    virtual void GetParm(en_npcparm pid, void* val);
    virtual void GetParmDefault(en_npcparm pid, void* val);
    virtual F32 GenShadCacheRad();
    virtual xEntDrive* PRIV_GetDriverData();
    virtual zNPCLassoInfo* PRIV_GetLassoData();
    virtual S32 LassoSetup();

protected:
    // This prevents implicit destructors from being generated in subclasses of zNPCCommon
    ~zNPCCommon();
};

struct NPCSysEvent
{
    S32 doLinkEvents;
    S32 handled;
    xBase* from;
    xBase* to;
    U32 toEvent;
    F32 toParam[4];
    xBase* toParamWidget;
};

struct NPCBlastInfo
{
    xVec3 pos_blast;
    F32 rad_blast;
    F32 spd_expand;
};

struct NPCChatInfo
{
    xVec3 pos_chat;
    F32 tym_chat;
};

struct NPCSpawnInfo
{
    xVec3 pos_spawn;
    zMovePoint* nav_firstMovepoint;
    zMovePoint* nav_spawnReference;
    S32 spawnSuccess;
};

struct NPCTargetInfo
{
    xBase* bas_tgt;
    xVec3 pos_tgt;
};

struct NPCDamageInfo
{
    // This struct shouldnt exist, only here to keep building
    // Needs removed as soon as the NMECommon revamp is done

    //en_NPC_DAMAGE_TYPE dmg_type;
    xBase* dmg_from;
    xVec3 vec_dmghit;
};

struct NPCStunInfo
{
    F32 tym_stuntime;
    en_NPC_CARRY_STATE carrystate;
    S32 allowStun;
};

struct NPCScriptInfo
{
    U32 aid_playanim;
};

struct NPCMountInfo
{
    xEnt* ent_toMount;
    xCollis* col_forMount;
};

struct NPCAreaInfo
{
    zNPCCommon* npc_origin;
    xVec3 pos_origin;
};

struct NPCMsg
{
    en_NPC_MSG_ID msgid;
    U32 sendto;
    U32 from;
    en_NPC_MSG_DATA infotype; // 0xC
    union
    {
        NPCSysEvent sysevent;
        NPCBlastInfo blastarea;
        NPCChatInfo chatter;
        NPCSpawnInfo spawning;
        NPCTargetInfo target;
        NPCDamageInfo dmgdata; // 0x10
        NPCStunInfo stundata;
        NPCScriptInfo scriptdata;
        NPCMountInfo mountdata;
        NPCAreaInfo areadata;
    };
    void* attached; // 0x38
    NPCMsg* next;
    F32 tmr_delay; // 0x40
};

struct zNMEAsset : xDynAsset
{
    xEntAsset ent_asset;
};

struct Damage_1
{
    F32 tym_invuln;
};

struct Physics
{
    F32 acc_grav;
    F32 spd_maxFall;
};

struct Movement_1
{
    F32 spd_move;
    F32 acc_move;
    F32 dst_deviant;
    F32 spd_turnrate;
};

struct NMECfgCommon
{
    Damage_1 damage;
    Physics physics;
    Movement_1 movement;
};

struct SimpShadParm
{
    F32 rad_shadow;
    char* nam_shadowTexture;
    RwRaster* rast_shadow;
};

struct FullShadParm
{
    S32 tobeDetermined;
};

struct ShadowRadii
{
    F32 rad_noShadow;
    F32 rad_complexShadow;
};

struct NMEShadParms
{
    SimpShadParm simpshad;
    FullShadParm fullshad;
    ShadowRadii shadrad;
};

struct OriginalBackupData
{
    struct
    {
        S32 flg_enableWander : 1;
        S32 flg_enablePatrol : 1;
        S32 flg_enableDetect : 1;
        S32 flg_activeOn : 1;
        S32 flg_takeNoDamage : 1;
        S32 flg_unused : 27;
    };
    union
    {
        en_allow overrideDetect;
        S32 alignmeproperly;
    };
    union
    {
        en_allow overrideAttack;
        S32 alignmeproperlyToo;
    };
};

struct Restore
{
    U8 chkby;
    U8 penby;
    U8 padpad[2];
    union
    {
        en_npcgol gid_compare;
        S32 gid_COMPARE;
    };
};

struct NMERuntime
{
    struct
    {
        S32 flg_enableWander : 1;
        S32 flg_enablePatrol : 1;
        S32 flg_enableDetect : 1;
        S32 flg_activeOn : 1;
        S32 flg_takeNoDamage : 1;
        S32 flg_unused : 27;
    };
    union
    {
        en_allow overrideDetect;
        S32 alignmeproperly;
    };
    union
    {
        en_allow overrideAttack;
        S32 alignmeproperlyToo;
    };
    OriginalBackupData orig;
    Restore restore;
};

struct zNMEDriver
{
    xEnt* ent_driver;
    F32 tym_mount;
    xMat4x3 mat_parLast;
    xMat4x3 mat_ownerLast;
    struct
    {
        S32 flg_inContact : 1;
        S32 flg_matchOrient : 1;
        S32 flg_unused : 30;
    };

    void WheelTurnsYou_C(xMat4x3* mat_owner);
    void ReviewCollide(xEntCollis* npccol);
};

struct zNMECommon;

struct zNMENavNet
{
    zMovePoint* nav_past;
    zMovePoint* nav_curr;
    zMovePoint* nav_dest;
    zMovePoint* nav_lead;
    xSpline3* spl_mvptspline;
    F32 len_mvptspline;
    F32 dst_curspline;
    zNMECommon* nme_owner;

    S32 MvptCycle();
};

struct xEntNPCAssetIN;

struct base : xEnt, xFactoryInst
{
    S16 bound_bone;
    U16 sound_id_offset;
    U16 global_parameters_size;
    U16 local_parameters_size;
    U32 type;
    xModelAssetParam* global_parameters;
    xModelAssetParam* local_parameters;
    union
    {
        xMovePoint* movepoint;
        U32 movepoint_asset_id;
    };
    xEntNPCAssetIN* npc_asset;
    xModelAssetInfo* model_asset;
    F32 shadow_strength;
    F32 shadow_cache_fudge_factor;
    xVec3 bound_offset;
};

struct zNMENPCWrapper : base
{
    void (*fun_setup)(xEnt*);
    void (*fun_reset)(xEnt*);
    S32 colFreq;
    U8 flg_colCheck;
    U8 flg_penCheck;
    U16 flg_unusedCollFlags;
    struct
    {
        S32 aflg_basenme : 8;
        S32 flg_upward : 8;
        S32 flg_xtrarend : 1;
        S32 flg_inUpdate : 1;
        S32 flg_newtime : 1;
        S32 flg_postproc : 1;
        S32 flg_profProc : 1;
        S32 flg_hudrend : 1;
        S32 flg_moreUnusedSpace : 10;
    };

    void InitFromNPCMgr(xEntAsset* asset);
    void Init(xEntAsset* asset);
    void PostInit();
    void PostSetup();
    void Load();
    void NewTime();
    void RenderExtra();
    void RenderHud();
    void Move();
    S32 ColFreqReset();
    void init(xEntAsset* asset);
    void SelfSetup();
    void setup();
    void Reset();
    void Setup();
    void reset();
    void update_npc(F32 dt);
    void Process();
    void update_bound();
    void change_bounds();
    U8 system_event();
    void render_npc();
    void Render();
    void debug_render();
    void render_extra();
    void damage();
    void destroy();
    void Destroy();
    void scene_setup();
    void add_states();
    void add_transitions();
    S32 SysEvent();
    void BUpdate();
    void UpdateWrapper(F32 dt);
    void NMEWrap_Init(xEntAsset* asset);
    xAnimTable* CreateAnimTable();
    void SelfDestroy();
    void CollideReview();
};

struct zNMEArena
{
    S32 flg_arena;
    xVec3 pos_arena;
    F32 rad_arena;
    zMovePoint* nav_arena;
    zMovePoint* nav_refer_dest;
    zMovePoint* nav_refer_curr;

    zMovePoint* NextBestNav(zMovePoint* nav_from);
    S32 Cycle(zNMECommon* npc, S32 peek);
};

struct NMESysEvent
{
    S32 doLinkEvents;
    S32 handled;
    xBase* from;
    xBase* to;
    union
    {
        U32 toEvent;
        en_xEventTags toEvent_asEnum;
    };
    F32 toParam[4];
    xBase* toParamWidget;
    U32 toParamWidgetID;
};

struct NMEBlastInfo
{
    xVec3 pos_blast;
    F32 rad_blast;
    F32 spd_expand;
};

struct NMEChatInfo
{
    xVec3 pos_chat;
    F32 tym_chat;
};

struct NMESpawnInfo
{
    xVec3 pos_spawn;
    zMovePoint* nav_firstMovepoint;
    zMovePoint* nav_spawnReference;
    S32 spawnSuccess;
};

struct NMETargetInfo
{
    xBase* bas_tgt;
    xVec3 pos_tgt;
};

struct NMEDamageInfo
{
    en_npcdmg dmg_type;
    xBase* dmg_from;
    xVec3 vec_dmghit;
    S32 amt_damage;
    union
    {
        S32 fac_powerup;
        en_plyrpup pup_player;
    };
};

struct NMEStunInfo
{
    F32 tym_stuntime;
    en_carystat carrystate;
    S32 allowStun;
};

struct NMEScriptInfo
{
    U32 aid_playanim;
};

struct NMEMountInfo
{
    xEnt* ent_toMount;
    xCollis* col_forMount;
};

struct NMEDestInfo
{
    xVec3 pos_there;
    zMovePoint* nav_there;
};

struct NMEAreaInfo
{
    zNMECommon* npc_origin;
    xVec3 pos_origin;
};

struct NMEMsg
{
    en_npcmsg msgid;
    U32 sendto;
    U32 from;
    en_msgdata infotype;
    union
    {
        NMESysEvent sysevent;
        NMEBlastInfo blastarea;
        NMEChatInfo chatter;
        NMESpawnInfo spawning;
        NMETargetInfo target;
        NMEDamageInfo dmgdata;
        NMEStunInfo stundata;
        NMEScriptInfo scriptdata;
        NMEMountInfo mountdata;
        NMEDestInfo destdata;
        NMEAreaInfo areadata;
    };
    void* attached;
    NMEMsg* next;
    F32 tmr_delay;
};

struct zNMECommon : zNMENPCWrapper
{
    zNMEAsset* nmeass;
    S32 siz_nmeass; // 0x12c
    xPsyche* psy_self; //0x130
    NMECfgCommon* cfg_common;
    NMEShadParms* cfg_shadparm;
    S32 flg_vuln; // 0x13c
    S32 flg_move;
    S32 flg_misc;
    S32 flg_able; // 0x148
    F32 spd_throttle;
    NMERuntime runtimeData;
    zNMEDriver* drv_data;
    zNMENavNet* navnet;
    union
    {
        F32 tmr_common[3];
        F32 tmr_invuln;
    };
    F32 tmr_scary;
    F32 tmr_lastAlert;
    zNMECommon* npc_duplodude;
    zNMESoundTable* snd_table;
    iSndHandle sndID[10];
    zShrapnelAsset* shrapnelAsset;

    void Destroy();
    void Render();
    void SelfDestroy();
    void ProcessInvis();
    void PostProcess();
    S32 IsAlive();
    S32 IsHealthy();
    S32 IsPresent();
    en_nmesimp SimpleStatus();
    F32 HealthRatio();
    void Boo();
    void DuploOwner(zNMECommon* duper);
    void SpeakBegin();
    void SpeakEnd();
    void SpeakStart();
    void SpeakStop();
    S32 CanRope();
    void CollideReview();
    zMovePoint* MvptFirstFollow();
    zMovePoint* MvptFirstTarget();
    xEntFrame* Gimme_xEntFrame();
    zNMEDriver* Gimme_DriveData();
    xEntShadow* Gimme_ShadowData();
    zNMENavNet* Gimme_NavNet();
    zNMEArena* Gimme_NMEArena();
    xShadowSimpleCache* Gimme_SimpShadowCache();
    void Reset();
    void PoofOfBubbles();
    S32 LaunchProjectile(en_haztyp haztyp, F32 spd_proj, F32 dst_minRange, xVec3* pos_launch,
                         F32 tym_predictMax, F32 hyt_offset, F32 rad_min, F32 rad_max);
    void GiveReward();
    void DeathFXKick();
    void DieTheGoodDeath();
    F32 ThrottleAdjust(F32 dt, F32 spd_want, F32 accel);
    xAnimTable* CreateAnimTable(xAnimTable* table);
    xAnimTransition* AnimMakeSmackTran(U32 animID);
    S32 AnimStart(U32 animID, S32 forceRestart);
    S32 MatMoveToPos(xVec3* pos_tobe, F32 dt, F32 spd, S32 doTurn, F32 spd_turnrate);
    F32 MatQRotTowards(F32 dt, xVec3* dir_face, F32 spd_turnrate);
    xModelInstance* ModelAtomicFind(S32 index, S32 idx_prev, xModelInstance* mdl_prev);
    S32 HaveLOSToPos(xVec3* pos, F32 dist, xScene* xscn, xBase* tgt, xCollis* colCallers);
    S32 ReviewCollBounce(xEntCollis* npccol, xVec3* vel, F32 fac_elastic);
    S32 ReviewCollSurfs(xEntCollis* npccol, zNMECommon* npc);
    void RunCollision(F32 dt);
    en_nmesimp Common_SimpStat();
    void ApplyGlowDamp();
    void ShadStufUpdate();
    void FullShadAcquire();
    void ShadowPrep();
    S32 WannaPoolShadow();
    void TellMeVisOnOff(xEnt* ent);
    S32 Respawn(xVec3* pos, zMovePoint* mvptFirst, zMovePoint* mvptSpawnRef);
    void Damage(en_npcdmg dmgtype, xBase* who, xVec3* vec_hit, S32 amt_dmgCaller,
                en_plyrpup pup_fromCaller);
    void ConvertHitEvent(NMESysEvent* sysmail);
    S32 DfltSysEventMail(NMESysEvent* sysmail);
    S32 SysEvent(xBase* from, xBase* to, U32 toEvent, F32* toParam, xBase* toParamWidget,
                 U32 toParamWidgetID, S32* handled);
    S32 NMEMessage(NMEMsg* mail);
    S32 TypeHandleMail();
    void CreateConfig();
    void Setup();
    void Common_Init();
    void Process(F32 dt);
    void BUpdate(xVec3* pos);
    void Init(xEntAsset* entasset);
};

xFactoryInst* ZNPC_Create_Common(S32 who, RyzMemGrow* grow, void*);
void ZNPC_Destroy_Common(xFactoryInst* inst);
void zNPCCommon_ScenePrepare();
void zNPCCommon_ScenePostInit();
void zNPCCommon_SceneFinish();
void zNPCPlyrSnd_Reset();
void zNPCPlyrSnd_Update(F32 dt);
void zNPCCommon_SceneReset();
void ZNPC_Destroy_Common(xFactoryInst* inst);
void zNPCSettings_MakeDummy();
void ZNPC_Common_Startup();
void zNPCCommon_WonderReset();
void ZNPC_Common_Shutdown();
void NPCC_BuildStandardAnimTran(xAnimTable* table, char** namelist, S32* ourAnims, S32 idx_dflt,
                                F32 blend);
void zNPCCommon_Timestep(xScene* xscn, F32 dt);

xAnimTable* ZNPC_AnimTable_Common();
xAnimTable* ZNPC_AnimTable_LassoGuide();
S32 NPCC_NPCIsConversing();
void zNPCCommon_EjectPhlemOnPawz();
U32 xSndIsPlaying(U32 assetID, U32 parid);

#endif
