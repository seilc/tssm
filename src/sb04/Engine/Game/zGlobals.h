#ifndef ZGLOBALS_H
#define ZGLOBALS_H

#include "xGlobals.h"
#include "xShadowSimple.h"
#include "xEntDrive.h"

#include "zEnt.h"
#include "zEntPlayer.h"
#include "zScene.h"

enum zGlobalDemoType
{
    zDT_NONE,
    zDT_E3,
    zDT_PUBLICITY,
    zDT_OPM,
    zDT_LAST
};

struct zGlobalSettings
{
    U16 AnalogMin;
    U16 AnalogMax;
    F32 SundaeTime;
    F32 SundaeMult;
    U32 InitialShinyCount;
    U32 InitialSpatulaCount;
    S32 ShinyValuePurple;
    S32 ShinyValueBlue;
    S32 ShinyValueGreen;
    S32 ShinyValueYellow;
    S32 ShinyValueRed;
    S32 ShinyValueCombo0;
    S32 ShinyValueCombo1;
    S32 ShinyValueCombo2;
    S32 ShinyValueCombo3;
    S32 ShinyValueCombo4;
    S32 ShinyValueCombo5;
    S32 ShinyValueCombo6;
    S32 ShinyValueCombo7;
    S32 ShinyValueCombo8;
    S32 ShinyValueCombo9;
    S32 ShinyValueCombo10;
    S32 ShinyValueCombo11;
    S32 ShinyValueCombo12;
    S32 ShinyValueCombo13;
    S32 ShinyValueCombo14;
    S32 ShinyValueCombo15;
    F32 ComboTimer;
    U32 Initial_Specials;
    U32 TakeDamage;
    F32 DamageTimeHit;
    F32 DamageTimeSurface;
    F32 DamageTimeEGen;
    F32 DamageSurfKnock;
    F32 DamageGiveHealthKnock;
    U32 CheatSpongeball;
    U32 CheatPlayerSwitch;
    U32 CheatAlwaysPortal;
    U32 CheatFlyToggle;
    U32 FriendlySelectMode;
    F32 RotMatchMaxAngle;
    F32 RotMatchMatchTime;
    F32 RotMatchRelaxTime;
    F32 Gravity;
    F32 BBashTime;
    F32 BBashHeight;
    F32 BBashDelay;
    F32 BBashCVTime;
    F32 BBounceSpeed;
    F32 BBashGauntletDelay;
    F32 BBashGauntletBlastRadius;
    F32 BSpinMinFrame;
    F32 BSpinMaxFrame;
    F32 BSpinRadius;
    F32 BSpinReach;
    F32 BSpinReachUpgrade;
    F32 CartwheelDamageSize;
    F32 BubbleBowlTimeDelay;
    F32 BubbleBowlLaunchPosLeft;
    F32 BubbleBowlLaunchPosUp;
    F32 BubbleBowlLaunchPosAt;
    F32 BubbleBowlLaunchVelLeft;
    F32 BubbleBowlLaunchVelUp;
    F32 BubbleBowlLaunchVelAt;
    F32 BubbleBowlPercentIncrease;
    F32 BubbleBowlMinSpeed;
    F32 BubbleBowlMinRecoverTime;
    F32 SlideAccelVelMin;
    F32 SlideAccelVelMax;
    F32 SlideAccelStart;
    F32 SlideAccelEnd;
    F32 SlideAccelPlayerFwd;
    F32 SlideAccelPlayerBack;
    F32 SlideAccelPlayerSide;
    F32 SlideVelMaxStart;
    F32 SlideVelMaxEnd;
    F32 SlideVelMaxIncTime;
    F32 SlideVelMaxIncAccel;
    F32 SlideAirHoldTime;
    F32 SlideAirSlowTime;
    F32 SlideAirDblHoldTime;
    F32 SlideAirDblSlowTime;
    F32 SlideVelDblBoost;
    U8 SlideApplyPhysics;
    U8 PowerUp[10];
    U8 InitialPowerUp[10];
    U8 AttractModeDuringGameplay;
};

struct xEntBoulder;
struct zEntHangable;
struct zPlatform;
struct xSurface;
struct zAssetPickupTable;
struct zCutsceneMgr;

struct zCheckPoint
{
    xVec3 pos;
    F32 rot;
    U32 initCamID;
};

#define LEVEL_COUNT 15

struct zRewardsMgr;

struct zPlayerGlobals
{
    xEntShadow entShadow_embedded;
    xShadowSimpleCache simpShadow_embedded;
    zGlobalSettings g;
    zPlayerSettings* s;
    zPlayerSettings sb;
    zPlayerSettings patrick;
    zPlayerSettings spongepat;
    xLightKit* pPlayerLightKit;
    xModelInstance* model_spongebob;
    xModelInstance* model_patrick;
    xModelInstance* model_spongepat;
    xModelInstance* model_car;
    U32 Visible;
    S32 Speed;
    F32 SpeedMult;
    S32 Sneak;
    S32 Teeter;
    F32 SlipFadeTimer;
    S32 Slide;
    F32 SlideTimer;
    S32 Stepping;
    S32 JumpState;
    S32 LastJumpState;
    F32 JumpTimer;
    F32 LookAroundTimer;
    U32 LookAroundRand;
    U32 LastProjectile;
    F32 DecelRun;
    F32 DecelRunSpeed;
    F32 HotsauceTimer;
    F32 LeanLerp;
    F32 ScareTimer;
    xBase* ScareSource;
    F32 CowerTimer;
    F32 DamageTimer;
    F32 SundaeTimer;
    F32 ControlOffTimer;
    F32 HelmetTimer;
    U32 WorldDisguise;
    U32 Bounced;
    F32 FallDeathTimer;
    F32 HeadbuttVel;
    F32 HeadbuttTimer;
    U32 DoMeleeCheck;
    F32 ForceSlipperyTimer;
    F32 ForceSlipperyFriction;
    F32 ShockRadius;
    F32 ShockRadiusOld;
    F32 Face_ScareTimer;
    U32 Face_ScareRandom;
    U32 Face_Event;
    F32 Face_EventTimer;
    F32 Face_PantTimer;
    U32 Face_AnimSpecific;
    U32 IdleRand;
    F32 IdleMinorTimer;
    F32 IdleMajorTimer;
    F32 IdleSitTimer;
    S32 Transparent;
    zEnt* FireTarget;
    U32 PlayerIsFrozen;
    U32 ControlOff;
    U32 ControlOnEvent;
    U32 AutoMoveSpeed;
    F32 AutoMoveDist;
    xVec3 AutoMoveTarget;
    xBase* AutoMoveObject;
    zEnt* Diggable;
    F32 DigTimer;
    zPlayerCarryInfo carry;
    zPlayerLassoInfo lassoInfo;
    xModelTag BubbleWandTag[2];
    xModelInstance* model_wand;
    xEntBoulder* bubblebowl[2];
    F32 bbowlInitVel;
    zEntHangable* HangFound;
    zEntHangable* HangEnt;
    zEntHangable* HangEntLast;
    xVec3 HangPivot;
    xVec3 HangVel;
    F32 HangLength;
    xVec3 HangStartPos;
    F32 HangStartLerp;
    xModelTag HangPawTag[4];
    F32 HangPawOffset;
    F32 HangElapsed;
    F32 Jump_CurrGravity;
    F32 Jump_HoldTimer;
    F32 Jump_ChangeTimer;
    S32 Jump_CanDouble;
    S32 Jump_CanFloat;
    S32 Jump_SpringboardStart;
    zPlatform* Jump_Springboard;
    S32 CanJump;
    S32 CanBubbleSpin;
    S32 CanBubbleBounce;
    S32 CanBubbleBash;
    S32 IsJumping;
    S32 IsDJumping;
    S32 IsBubbleSpinning;
    S32 IsBubbleBouncing;
    S32 IsBubbleBashing;
    S32 IsBubbleBowling;
    S32 WasDJumping;
    _zPlayerWallJumpState WallJumpState;
    S32 cheat_mode;
    zRewardsMgr* rewardsMgr;
    U32 ManlinessPointsCurrentRange;
    U32 InvManlinessPoints;
    U32 InvManlinessPointsMultiplier;
    U32 InvGoofyGoober;
    U32 InvTreasureChest[20];
    U32 InvTreasureChestMax[20];
    U32 InvTreasureChestCurrentLevel;
    U32 InvLevelPickups[20];
    U32 InvLevelPickupsCurrentLevel;
    U32 InvTreasureChestTotal;
    U32 InvTreasureChestOpened;
    U32 CurrentSkillLevel;
    U32 InitialUnusedSkillPoints;
    S16 CurrentUnusedSkillPoints;
    S16 CurrentSpentSkillPoints;
    xModelTag BubbleTag;
    xEntDrive drv;
    xSurface* floor_surf;
    xVec3 floor_norm;
    S32 slope;
    xCollis earc_coll;
    xSphere head_sph;
    xModelTag center_tag;
    xModelTag head_tag;
    U32 TongueFlags[2];
    xVec3 RootUp;
    xVec3 RootUpTarget;
    zCheckPoint checkpoint;
    U32 SlideTrackSliding;
    U32 SlideTrackCount;
    xEnt* SlideTrackEnt[161];
    U32 SlideNotGroundedSinceSlide;
    xVec3 SlideTrackDir;
    xVec3 SlideTrackVel;
    F32 SlideTrackDecay;
    F32 SlideTrackLean;
    F32 SlideTrackLand;
    char* sb_model_indices;
    xModelInstance* sb_models[11];
    U32 currentPlayer;
    xVec3 PredictRotate;
    xVec3 PredictTranslate;
    F32 PredictAngV;
    xVec3 PredictCurrDir;
    F32 PredictCurrVel;
    F32 KnockBackTimer;
    F32 KnockIntoAirTimer;
};

struct zGlobals : xGlobals
{
    U32 playerTag;
    U32 playerLoaded; //0x884
    U32 playerLoadOrder[8];
    U8 invertJoystick;
    zPlayerGlobals player;
    zAssetPickupTable* pickupTable;
    zCutsceneMgr* cmgr;
    zCutsceneMgr* DisabledCutsceneDoneMgr;
    char startDebugMode[32];
    U32 noMovies; // 0x2200?
    U32 boundUpdateTime;
    U8 draw_player_after_fx;
    zGlobalDemoType demoType;
};

extern zGlobals globals;
extern xGlobals* xglobals;

#endif
