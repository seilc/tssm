#ifndef ZENTPLAYER_H
#define ZENTPLAYER_H

#include "xMath3.h"
#include "xEnt.h"
#include "xAnim.h"
#include "zEnt.h"
#include "zLasso.h"

enum zControlOwner
{
    CONTROL_OWNER_GLOBAL = 0x1,
    CONTROL_OWNER_EVENT,
    CONTROL_OWNER_OOB = 0x4,
    CONTROL_OWNER_BOSS = 0x8,
    CONTROL_OWNER_TALK_BOX = 0x10,
    CONTROL_OWNER_TAXI = 0x20,
    CONTROL_OWNER_BUS_STOP = 0x40,
    CONTROL_OWNER_TELEPORT_BOX = 0x80,
    CONTROL_OWNER_CRUISE_BUBBLE = 0x100,
    CONTROL_OWNER_FLY_CAM = 0x200,
    CONTROL_OWNER_FROZEN = 0x400,
    CONTROL_OWNER_TURRET = 0x800,
    CONTROL_OWNER_REWARDANIM = 0x1000,
    CONTROL_OWNER_BUNGEE = 0x2000,
    CONTROL_OWNER_SPRINGBOARD = 0x4000,
    CONTROL_OWNER_CUTSCENE = 0x8000
};

enum _tagePlayerSnd
{
    ePlayerSnd_Invalid,
    ePlayerSnd_Land,
    ePlayerSnd_Jump,
    ePlayerSnd_DoubleJump,
    ePlayerSnd_BowlWindup,
    ePlayerSnd_BowlRelease,
    ePlayerSnd_BubbleBashStart,
    ePlayerSnd_BubbleBashHit1,
    ePlayerSnd_BubbleBashHitStart = 0x7,
    ePlayerSnd_BubbleBashHit2,
    ePlayerSnd_BubbleBashHitEnd = 0x8,
    ePlayerSnd_BubbleWand,
    ePlayerSnd_CruiseStart,
    ePlayerSnd_CruiseNavigate,
    ePlayerSnd_CruiseHit,
    ePlayerSnd_BounceStrike,
    ePlayerSnd_BoulderStart,
    ePlayerSnd_BoulderRoll,
    ePlayerSnd_BoulderEnd,
    ePlayerSnd_BellyMelee,
    ePlayerSnd_BellySmash,
    ePlayerSnd_Lift1,
    ePlayerSnd_Throw,
    ePlayerSnd_Chop,
    ePlayerSnd_Kick,
    ePlayerSnd_Heli,
    ePlayerSnd_LassoThrow,
    ePlayerSnd_LassoYank,
    ePlayerSnd_LassoStretch,
    ePlayerSnd_Ouch,
    ePlayerSnd_Death,
    ePlayerSnd_FruitCrackle,
    ePlayerSnd_CheckPoint,
    ePlayerSnd_PickupSpatula,
    ePlayerSnd_PickupUnderwear,
    ePlayerSnd_Bus,
    ePlayerSnd_Taxi,
    ePlayerSnd_SlideLoop,
    ePlayerSnd_BeginBungee,
    ePlayerSnd_BungeeWind = 0x24,
    ePlayerSnd_BungeeAttach,
    ePlayerSnd_BungeeRelease,
    ePlayerSnd_EndBungee = 0x26,
    ePlayerSnd_PickupSpatulaComment,
    ePlayerSnd_BungeeDive,
    ePlayerSnd_Sneak,
    ePlayerSnd_SlipLoop,
    ePlayerSnd_BubbleBashMiss,
    ePlayerSnd_WallJumpLand,
    ePlayerSnd_CartwheelLoop,
    ePlayerSnd_HammerThrow,
    ePlayerSnd_HammerThrowLoop,
    ePlayerSnd_GauntletTick,
    ePlayerSnd_Cartwheel2Loop,
    ePlayerSnd_MeleeDeflect,
    ePlayerSnd_BellySmash2,
    ePlayerSnd_Total
};

enum _tagePlayerStreamSnd
{
    ePlayerStreamSnd_Invalid,
    ePlayerStreamSnd_PickupSock,
    ePlayerStreamSnd_UnderwearComment,
    ePlayerStreamSnd_EnterScene1,
    ePlayerStreamSnd_EnterScene2,
    ePlayerStreamSnd_EnterScene3,
    ePlayerStreamSnd_EnterScene4,
    ePlayerStreamSnd_EnterScene5,
    ePlayerStreamSnd_SpatulaComment1,
    ePlayerStreamSnd_ShinyComment,
    ePlayerStreamSnd_SpongeBallComment,
    ePlayerStreamSnd_CruiseComment,
    ePlayerStreamSnd_BowlComment1,
    ePlayerStreamSnd_BowlComment2,
    ePlayerStreamSnd_BowlComment3,
    ePlayerStreamSnd_PushButton,
    ePlayerStreamSnd_BellySmashComment,
    ePlayerStreamSnd_ChopComment,
    ePlayerStreamSnd_KickComment,
    ePlayerStreamSnd_RopingComment,
    ePlayerStreamSnd_HeliComment,
    ePlayerStreamSnd_DestroyTiki,
    ePlayerStreamSnd_DestroyRobot,
    ePlayerStreamSnd_SeeWoodTiki,
    ePlayerStreamSnd_SeeLoveyTiki,
    ePlayerStreamSnd_SeeShhhTiki,
    ePlayerStreamSnd_SeeThunderTiki,
    ePlayerStreamSnd_SeeStoneTiki,
    ePlayerStreamSnd_SeePatrickBoss1,
    ePlayerStreamSnd_SeePatrickBoss2,
    ePlayerStreamSnd_SeeSpongeBobBoss,
    ePlayerStreamSnd_SeeRobotPlankton,
    ePlayerStreamSnd_PickupSpecialGeneric1,
    ePlayerStreamSnd_PickupSpecialGeneric2,
    ePlayerStreamSnd_GoldenUnderwear,
    ePlayerStreamSnd_Combo,
    ePlayerStreamSnd_BigCombo1,
    ePlayerStreamSnd_BigCombo2,
    ePlayerStreamSnd_BigCombo3,
    ePlayerStreamSnd_BigCombo4,
    ePlayerStreamSnd_BigCombo5,
    ePlayerStreamSnd_Lift1,
    ePlayerStreamSnd_Exclaim,
    ePlayerStreamSnd_BeginBungee,
    ePlayerStreamSnd_BungeeAttachComment = 0x2b,
    ePlayerStreamSnd_BungeeBeginDive,
    ePlayerStreamSnd_BungeeDive1 = 0x2c,
    ePlayerStreamSnd_BungeeDive2,
    ePlayerStreamSnd_BungeeEndDive = 0x2d,
    ePlayerStreamSnd_BungeeDeath,
    ePlayerStreamSnd_SharedSpaceStart,
    ePlayerStreamSnd_SBKarateSpin = 0x2f,
    ePlayerStreamSnd_MeleeDeflect,
    ePlayerStreamSnd_SBKarateDeflect = 0x30,
    ePlayerStreamSnd_SBHelmetBash,
    ePlayerStreamSnd_SBHelmetEmbedded,
    ePlayerStreamSnd_SBUnderWearBungee,
    ePlayerStreamSnd_SBBowl,
    ePlayerStreamSnd_SBMachoBowl,
    ePlayerStreamSnd_SBSonicGuitar,
    ePlayerStreamSnd_SBSonicGuitarReleased,
    ePlayerStreamSnd_SBSpongeBallMove,
    ePlayerStreamSnd_SBLastSharedEnum = 0x38,
    ePlayerStreamSnd_PatBellyBounce = 0x2f,
    ePlayerStreamSnd_PatBellyDeflect,
    ePlayerStreamSnd_PatCartwheel,
    ePlayerStreamSnd_PatTongueSwing,
    ePlayerStreamSnd_PatLift,
    ePlayerStreamSnd_PatCarry,
    ePlayerStreamSnd_PatThrow,
    ePlayerStreamSnd_PatHammerThrowRelease,
    ePlayerStreamSnd_PatBellyFlop,
    ePlayerStreamSnd_PatBellyFlopStun,
    ePlayerStreamSnd_PatLastSharedEnum = 0x38,
    ePlayerStreamSnd_Waiting,
    ePlayerStreamSnd_Jumping,
    ePlayerStreamSnd_IntoGoo,
    ePlayerStreamSnd_Icy,
    ePlayerStreamSnd_Defeated,
    ePlayerStreamSnd_StartingOut,
    ePlayerStreamSnd_RunningLong,
    ePlayerStreamSnd_LedgeHang,
    ePlayerStreamSnd_WallJump,
    ePlayerStreamSnd_UpgradeComment1,
    ePlayerStreamSnd_UpgradeCommentsBase = 0x42,
    ePlayerStreamSnd_UpgradeComment2,
    ePlayerStreamSnd_UpgradeComment3,
    ePlayerStreamSnd_UpgradeComment4,
    ePlayerStreamSnd_UpgradeComment4Health,
    ePlayerStreamSnd_UpgradeCommentsHealthBase = 0x46,
    ePlayerStreamSnd_UpgradeComment5Health,
    ePlayerStreamSnd_UpgradeComment6Health,
    ePlayerStreamSnd_Laughing,
    ePlayerStreamSnd_SuggestOtherCharacter,
    ePlayerStreamSnd_SmashTiki,
    ePlayerStreamSnd_SmashWoodTiki,
    ePlayerStreamSnd_SmashLoveyTiki,
    ePlayerStreamSnd_SmashShrinkyTiki,
    ePlayerStreamSnd_SmashExplodeTiki,
    ePlayerStreamSnd_SmashSteelTiki,
    ePlayerStreamSnd_EnemyDefeated,
    ePlayerStreamSnd_SeeFogger,
    ePlayerStreamSnd_SeeSlammer,
    ePlayerStreamSnd_SeePopper,
    ePlayerStreamSnd_SeeSpinner,
    ePlayerStreamSnd_SeeFlinger,
    ePlayerStreamSnd_SeeMiniMerv,
    ePlayerStreamSnd_SeeTurret,
    ePlayerStreamSnd_SeeJellyFish,
    ePlayerStreamSnd_SeeMervyn,
    ePlayerStreamSnd_SeeBucketotron,
    ePlayerStreamSnd_GotManliness,
    ePlayerStreamSnd_GotHealth,
    ePlayerStreamSnd_GotGGToken,
    ePlayerStreamSnd_GotTreasureChest,
    ePlayerStreamSnd_Total
};

struct zDelayedStreamSound
{
    _tagePlayerStreamSnd start;
    _tagePlayerStreamSnd end;
    F32 delay;
};

struct zPlayerSndTimer
{
    F32 timer;
    F32 time;
};

// TODO: Why are there two of these enums with the same effect, should there be?
enum _zPlayerType
{
    ePlayer_SB,
    ePlayer_Patrick,
    ePlayer_Sandy,
    ePlayer_MAXTYPES
};

enum eSNDCurrentPlayer
{
    eCurrentPlayerSpongeBob,
    eCurrentPlayerPatrick,
    eCurrentPlayerSandy,
    eCurrentPlayerCount
};

enum _zPlayerWallJumpState
{
    k_WALLJUMP_NOT,
    k_WALLJUMP_LAUNCH,
    k_WALLJUMP_FLIGHT,
    k_WALLJUMP_LAND
};

struct zJumpParam
{
    F32 PeakHeight;
    F32 TimeGravChange;
    F32 TimeHold;
    F32 ImpulseVel;
};

struct zLedgeGrabParams
{
    F32 animGrab;
    F32 zdist;
    xVec3 tranTable[60];
    S32 tranCount;
    xEnt* optr;
    xMat4x3 omat;
    F32 y0det;
    F32 dydet;
    F32 r0det;
    F32 drdet;
    F32 thdet;
    F32 rtime;
    F32 ttime;
    F32 tmr;
    xVec3 spos;
    xVec3 epos;
    xVec3 tpos;
    S32 nrays;
    S32 rrand;
    F32 startrot;
    F32 endrot;
};

struct zPlayerSettings
{
    _zPlayerType pcType;
    F32 MoveSpeed[6];
    F32 AnimSneak[3];
    F32 AnimWalk[3];
    F32 AnimRun[3];
    F32 JumpGravity;
    F32 GravSmooth;
    F32 FloatSpeed;
    F32 ButtsmashSpeed;
    zJumpParam Jump;
    zJumpParam Bounce;
    zJumpParam Spring;
    zJumpParam Wall;
    zJumpParam Double;
    zJumpParam SlideDouble;
    zJumpParam SlideJump;
    F32 WallJumpVelocity;
    zLedgeGrabParams ledge;
    F32 spin_damp_xz;
    F32 spin_damp_y;
    U8 talk_anims;
    U8 talk_filter_size;
    U8 talk_filter[4];
    U32 Health;
    U32 MaxHealth;
};

struct zPlayerCarryInfo
{
    xEnt* grabbed;
    U32 grabbedModelID;
    xMat4x3 spin;
    xEnt* throwTarget;
    xEnt* flyingToTarget;
    F32 minDist;
    F32 maxDist;
    F32 minHeight;
    F32 maxHeight;
    F32 maxCosAngle;
    F32 throwMinDist;
    F32 throwMaxDist;
    F32 throwMinHeight;
    F32 throwMaxHeight;
    F32 throwMaxStack;
    F32 throwMaxCosAngle;
    F32 throwTargetRotRate;
    F32 targetRot;
    U32 grabTarget;
    xVec3 grabOffset;
    F32 grabLerpMin;
    F32 grabLerpMax;
    F32 grabLerpLast;
    U32 grabYclear;
    F32 throwGravity;
    F32 throwHeight;
    F32 throwDistance;
    F32 fruitFloorDecayMin;
    F32 fruitFloorDecayMax;
    F32 fruitFloorBounce;
    F32 fruitFloorFriction;
    F32 fruitCeilingBounce;
    F32 fruitWallBounce;
    F32 fruitLifetime;
    xEnt* patLauncher;
};

struct zPlayerLassoInfo
{
    xEnt* target; // 0x1880 in globals
    F32 dist;
    U8 destroy;
    U8 targetGuide;
    F32 lassoRot;
    xEnt* swingTarget; // 0x1890
    xEnt* releasedSwing;
    F32 copterTime;
    S32 canCopter;
    zLasso lasso;
    xAnimState* zeroAnim;
};

#define SHINY_MAX 99999

extern eSNDCurrentPlayer gCurrentPlayer;
extern S32 gWaitingToAutoSave;

void zEntPlayer_Load(xEnt*, xSerial*);

S32 zEntPlayer_Damage(xBase* src, U32 damage);
S32 zEntPlayer_Damage(xBase* src, U32 damage, const xVec3* knockback);

xAnimTable* zSandy_AnimTable();
xAnimTable* zPatrick_AnimTable();
xAnimTable* zEntPlayer_AnimTable();
xAnimTable* zSpongeBobTongue_AnimTable();

void zEntPlayerExit(xEnt*);
void zEntPlayerPreReset();
void zEntPlayerReset(xEnt* ent);
void zEntPlayer_LoadSounds();
void zEntPlayer_UnloadSounds();
void zEntPlayer_ShadowModelEnable();
void zEntPlayer_ShadowModelDisable();

void zEntPlayerJumpStart(class xEnt* ent, class zJumpParam* jump);
S32 zEntPlayer_IsSneaking();

void zEntPlayer_setBoulderMode(U32 mode);
void zEntPlayer_GiveHealth(S32);
void zEntPlayer_GiveSpatula(S32);
void zEntPlayer_GivePatsSocksCurrentLevel(S32 quantity);

void zEntPlayer_LoadCheckPoint();

void zEntPlayer_MinimalRender(zEnt* ent);
U8 zEntPlayer_MinimalUpdate(xEnt* ent, xScene* sc, F32 dt, xVec3& drive_motion);

S32 zEntPlayer_MoveInfo();

void zEntPlayer_SNDPlay(_tagePlayerSnd player_snd, F32 delay);
void zEntPlayer_SNDPlayRandom(_tagePlayerSnd player_snd_start, _tagePlayerSnd player_snd_end,
                              F32 delay);
void zEntPlayer_SNDPlayStream(_tagePlayerStreamSnd player_snd);
void zEntPlayer_SNDPlayStream(_tagePlayerStreamSnd player_snd, U32 flags);
// Only plays sound if player's spatula count is between lower and upper
void zEntPlayer_SNDPlayStream(U32 lower, U32 upper, _tagePlayerStreamSnd player_snd, U32 flags);

// Only plays sound if player's spatula count is between lower and upper
void zEntPlayer_SNDPlayStreamRandom(U32 lower, U32 upper, _tagePlayerStreamSnd player_snd_start,
                                    _tagePlayerStreamSnd player_snd_end, F32 delay);
void zEntPlayer_SNDPlayStreamRandom(_tagePlayerStreamSnd player_snd_start,
                                    _tagePlayerStreamSnd player_snd_end, F32 delay);

void zEntPlayer_SNDSetVol(_tagePlayerSnd player_snd, F32 new_vol);
void zEntPlayer_SNDSetPitch(_tagePlayerSnd player_snd, F32 new_pitch);
void zEntPlayer_SNDStop(_tagePlayerSnd player_snd);

void zEntPlayerSpeakStop();

void zEntPlayerControlOff(zControlOwner owner);
void zEntPlayerControlOn(zControlOwner owner);

void zEntPlayer_StoreCheckPoint(xVec3* pos, F32 rot, U32 initCamID);
S32 load_talk_filter(U8* filter, xModelAssetParam* params, U32 params_size, S32 max_size);

S32 zEntPlayer_DamageNPCKnockBack(xBase* src, U32 damage, xVec3* npcPos);

S32 zEntPlayer_DamageNPCKnockBack(xBase* src, U32 damage, xVec3* npcPos);
void zEntPlayer_PredictPos(xVec3* pos, F32 timeIntoFuture, F32 leadFactor, S32 useTurn);

#endif
