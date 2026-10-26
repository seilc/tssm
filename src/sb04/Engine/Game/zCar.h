#ifndef ZCAR_H
#define ZCAR_H

#include "types.h"
#include "xAnim.h"
#include "xBase.h"
#include "xEnt.h"
#include "zEnt.h"
#include "xModel.h"
#include "iSnd.h"
#include "xParEmitter.h"
#include "xModelBlur.h"
#include "xCounter.h"
#include "zStreamedSound.h"
#include "zEntPlayerCar.h"

// Remember:
// U8 is commonly a bool

enum eDamage
{
    eDamageNone,
    eDamage1,
    eDamage2,
    eDamage3,
    eDamageMax
};

enum eCollisionType
{
    eCollisionTypeHeadOn,
    eCollisionTypeSideKnock,
    eCollisionTypeJumpLand,
    eCollisionTypeDamage
};

enum zDrivingSurf
{
    ezDRIVINGSURF_Default,
    ezDRIVINGSURF_Tarmac,
    ezDRIVINGSURF_Cement,
    ezDRIVINGSURF_HardDirt,
    ezDRIVINGSURF_Railroad,
    ezDRIVINGSURF_Grass,
    ezDRIVINGSURF_SoftDirt,
    ezDRIVINGSURF_SideWalk,
    ezDRIVINGSURF_Sand,
    ezDRIVINGSURF_SurfaceWater,
    ezDRIVINGSURF_ThickOil,
    ezDRIVINGSURF_HotSauce,
    ezDRIVINGSURF_NumNormalDrivableSurfaces,
    ezDRIVINGSURF_Wall,
    ezDRIVINGSURF_SlideTubWood,
    ezDRIVINGSURF_SlideTubSand,
    ezDRIVINGSURF_SlideTubHardRock,
    ezDRIVINGSURF_SlideShellHardRock,
    ezDRIVINGSURF_SlideShellTongue,
    ezDRIVINGSURF_SlideCrownRubberHose,
    ezDRIVINGSURF_SlideCrownRubberCable,
    ezDRIVINGSURF_SlideCrownMetalLamp,
    ezDRIVINGSURF_MaxTypes
};

enum animState
{
    eANIMSTATE_Idle,
    eANIMSTATE_Drive,
    eANIMSTATE_DriveSlippy,
    eANIMSTATE_Boosting,
    eANIMSTATE_Reversing,
    eANIMSTATE_Jump,
    eANIMSTATE_JumpLandSquash,
    eANIMSTATE_Crash,
    eANIMSTATE_SpinLeft,
    eANIMSTATE_SpinRight,
    eANIMSTATE_Success,
    eANIMSTATE_Failed,
    eANIMSTATE_Death
};

struct effectAsset : xDynAsset
{
    F32 time;
    F32 intensity;
    U32 id;
    U8 priority;
    U8 type;
    U8 rumbleInPause;
    U8 pad;
    F32 param1;
    F32 param2;
    F32 shakeMagnitude;
    F32 shakeCycleMax;
    F32 shakeRotationalMagnitude;
    U8 shakeY;
};

struct emitterBase : xBase
{
    effectAsset* pEffectAsset;

    void SetIntensity(F32 intensity);
};

struct effect : emitterBase
{
};

struct driveSurfaceDescriptor
{
    F32 staticTraction;
    F32 slidingTraction;
    F32 slideThreshold;
    U8 useSlideAnimation;
    F32 topSpeedFactor;
    iSndGroupHandle soundGroupDrive;
    iSndGroupHandle soundGroupSkid;
};

// Im thinking that this struct is fucked because of
// the mismatching offsets
struct zCar
{
    xEnt* pEnt;
    xMat4x3 lastMat;
    xMat4x3 mat;
    F32 boundYShift;
    F32 boundRadius;
    F32 shockHalfRange;
    U8 engineRunning;
    U8 playShutDownSound;
    iSndHandle soundBoostStartHandle;
    F32 modelYaw;
    xVec3 velocity;
    U8 inGroundContact;
    F32 timeOffGround;
    F32 shockExtension;
    F32 steeringPosition;
    U8 isSliding;
    U8 isInDamageSpin;
    F32 oilPenaltyTimer;
    driveSurfaceDescriptor* pCurrentSurface;
    zDrivingSurf currentSurfaceType;
    S32 numCollisions;
    xCollis collisions[12];
    U32 collisionUserFlags[12];
    xBound bound;
    char collisionTypes[22];
    S32 numNitros;
    F32 boostTimeRemaining;
    xModelBlur nitroBlur;
    animState currentAnimState;
    animState idealDrivingAnimState;
    U8 animReversing;
    U8 animBrakeLightsOn;
    S32 animPropellorAngle;
    F32 animLean;
    xVec3 animVirtualBunTopPos;
    xVec3 animVirtualBunTopVel;
    F32 animVirtualBunTopHeight;
    F32 animVirtualBunTopVerticalVel;
    F32 animJumpOpeness;
    U8 animCrash;
    U8 animStartSpinLeft;
    U8 animStartSpinRight;
    U8 animHeavyLanding;
    U8 animInJumpAnimation;
    U8 animSuccessMode;
    U8 animFailedMode;
    F32 skidFXIntensity;
    xVec3 lastPositionPar[4];
    xVec3 lastVelocityPar[4];
    xVec3 lastPositionSeed;
    xVec3 lastPositionKetchup;
    xVec3 lastVelocityKetchup;
    xVec3 lastPositionMustard;
    xVec3 lastVelocityMustard;
    eDamage damageLevel;
    F32 soundEnginePitch;
    iSndHandle soundEngineHandle;
    eDamage soundCurrentEngineType;
    iSndHandle soundBoostLoopHandle;
    S64 soundReverseActivationTime;
    iSndHandle soundReverseBeepHandle;
    driveSurfaceDescriptor* pSoundCurrentSurface;
    iSndHandle soundDriveLoopHandle;
    iSndHandle soundSkidLoopHandle;
    iSndHandle soundSkidLoopHandles[22];
    U8 soundGearCrunchReady;
    _xCounter* nitroUsedCounter;
    U8 oilOneLinerPlayed;
    zStreamedSoundList carOneLiners;
    effect* mpRumbleCollision;
    effect* mpRumbleDamage;
    effect* mpRumbleBoostStart;
    effect* mpRumbleBoost;

    void SoundInitAssetTable();
    xAnimTable* CreateAnimTable();
    U32 JumpEndedCB(xAnimTransition*, xAnimSingle* anim, void*);
    U32 JumpStartedCB();
    U32 AnimDefaultCB(xAnimTransition*, xAnimSingle* anim, void*);
    U32 DamageSpinCompleteCB(xAnimSingle* anim);
    U32 DeathCheck();
    U32 FailedCheck();
    U32 SuccessCheck();
    U32 SpinRightCheck();
    U32 SpinLeftCheck();
    U32 CrashCheck();
    U32 JumpEndCheck();
    U32 JumpCheck();
    U32 ReverseCheck();
    U32 StartBoostingCheck();
    U32 StartDrivingSlippyCheck();
    U32 StartDrivingCheck();
    U32 IdleCheck();
    void PreventPoppingThroughWorld(xVec3* pStartPosition, xVec3* pEndPosition, xVec3* pVelocity);
    void Exit();
};

void SoundUpdate();
void SoundPlayCollision(eCollisionType type, F32 strength);
void SoundPlayHorn();
void SoundInitAssetTable();
void ModelSwap(eDamage newDamageLevel, U8 swapEffects);
void StreakFX(xEnt* ent, F32 dt);
void DriveSurfaceFXInternal(xModelInstance* pModel, F32 dt, zDrivingSurf collisionType);
void RenderBrakeLights(xModelInstance* pModel);
void zCarRenderOneBrakeLight(xMat4x3* pMat);
void UpdateEffects(F32 dt);
void UpdateVirtualBunTop(F32 dt);
xAnimTable* CreateAnimTable();
U32 JumpEndedCB();
U32 JumpStartedCB();
U32 AnimDefaultCB(xAnimSingle* anim);
U32 DamageSpinCompleteCB(xAnimSingle* anim);
U32 DeathCheck();
U32 FailedCheck();
U32 SuccessCheck();
U32 SpinRightCheck();
U32 SpinLeftCheck();
U32 CrashCheck();
U32 JumpEndCheck();
U32 JumpCheck();
U32 ReverseCheck();
U32 StartBoostingCheck();
U32 StartDrivingSlippyCheck();
U32 StartDrivingCheck();
U32 IdleCheck();
void UpdateAnimState(xEnt* pEnt);
void ApplyCollisionRebounds(xVec3* pVelocity);
void DepenetrateCollisionList(xVec3* pPosition);
void PreventPoppingThroughWorld(xVec3* pStartPosition, xVec3* pEndPosition, xVec3* pVelocity);
void SphereCollision(xVec3* pNewCarPosition, xVec3* pVelocity, U8* pInGroundContact,
                     F32* pShockExtension, xVec3* pGroundNormal);
U8 __cl(xEnt& ent);
void UpdateGroundCharacteristics();
void CalculateIdealOrientation(F32 yaw, xMat3x3* pIdealOrientation, xVec3* pGroundNormal);
void CarUpdate(F32 dt, F32 steer, U8 accelOn, U8 brakeOn, U8 boostOn);
void StartBoost();
U32* GetVarNitros();
U8 CanPickupNitros();
void AddNitros(S32 nitros);
xMat4x3* GetMatrix();
void SetMatrix(xMat4x3* pSource);
void GiveHealth(S32 health);
void SetFullHealth();
void TakeDamage(U8 spinClockwise);
void HandleEvent(xBase* from, xBase* to, U32 toEvent, F32* toParam, xBase* toParamWidget,
                 U32 UNUSEDtoParamWidgetID);
void Exit();
void Reset(xEnt* pCarEnt, F32 initialYaw, xVec3* pPosition);
void Initialize(xEnt* pCarEnt);
void SceneInit();
zCar* zEntPlayerCarGetCar();

#endif
