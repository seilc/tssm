#ifndef ZMENUSB_H
#define ZMENUSB_H

#include "zUICustom.h"

struct xAnimTable;
struct xModelInstance;
struct xSoundFX;
struct ztalkbox;
struct zUIText;

class zUICustomDialogPlayer : public zUICustom
{
public:
    zUICustomDialogPlayer(zUI* ui);

    U8 HandleEvent(xBase* from, U32 toEvent, const F32* toParam, xBase* toParamWidget, U32 toParamWidgetID);
};

class zUICustomUpgradeTutorialContoller : public zUICustom
{
public:
    ztalkbox* upgradeTutorialTalkBox;
    zUIText* autoSave;
    U32 upgradeTutorialID;

    zUICustomUpgradeTutorialContoller(zUI* ui);

    void Reset();
    void PreUpdate(F32 dt);
    U8 HandleEvent(xBase* from, U32 toEvent, const F32* toParam, xBase* toParamWidget, U32 toParamWidgetID);
};

class zUICustomPalRedirector : public zUICustom
{
public:
    zUICustomPalRedirector(zUI* ui);

    U8 HandleEvent(xBase* from, U32 toEvent, const F32* toParam, xBase* toParamWidget, U32 toParamWidgetID);
};

class zUICustomExtrasIcon : public zUICustom
{
public:
    F32 mOffsetX;
    F32 mOffsetY;
    F32 mWidth;
    F32 mHeight;
    U8 mbFullReset;
    U8 misUnlocked;
    U8 mbIsHidden;
    xModelInstance* munlockedModel;
    xAnimTable* munlockedAtbl;
    F32 munlockedOffsetX;
    F32 munlockedOffsetY;
    F32 munlockedWidth;
    F32 munlockedHeight;

    zUICustomExtrasIcon(zUI* ui);

    void ResetMotion();
    void PostInitMotion();
    void PreUpdate(F32 dt);
    void PostUpdate(F32 dt);
    U8 HandleEvent(xBase* from, U32 toEvent, const F32* toParam, xBase* toParamWidget, U32 toParamWidgetID);
};

class zUICustomExtrasManager : public zUICustom
{
public:
    U8 mCurRow;
    U8 mCurColumn;
    U8 mNumRows;
    U8 mNumColumns;
    F32 mOffsetX;
    F32 mOffsetY;
    U8 mbInSubScreen;
    zUI** mGrid;
    zUI** mIconTypes;
    xGroup* mAuraGroup;
    zUIText* mDescription;
    zUIText* mActionText;
    zUIText* mNextExtraText;
    xGroup* mNextExtraGroup;
    xSoundFX* mSoundMove;
    xSoundFX* mSoundDeny;
    xSoundFX* mSoundConfirm;
    zUICustom** mSubScreens;

    zUICustomExtrasManager(zUI* ui);

    U8 HandleEvent(xBase* from, U32 toEvent, const F32* toParam, xBase* toParamWidget, U32 toParamWidgetID);
    void PostUpdate(F32 dt);
};

class zUICustomLoadingText : public zUICustom
{
public:
    zUICustomLoadingText(zUI* ui);

    U8 HandleEvent(xBase* from, U32 toEvent, const F32* toParam, xBase* toParamWidget, U32 toParamWidgetID);
};

#endif
