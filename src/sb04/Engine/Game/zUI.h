#ifndef ZUI_H
#define ZUI_H

#include "xGroup.h"
#include "xIni.h"
#include "xMgr.h"
#include "zConditional.h"
#include "zEnt.h"
#include "zTextbox.h"
#include "zWadUI.h"
#include "zUIAsset.h"

struct zUIMotionAsset : xBaseAsset
{
    U8 cmdCount;
    U8 in;
    U8 pad[2];
    U32 cmdSize;
    F32 totalTime;
    F32 loopTime;
};

class zUI;

struct zUIMotionFrame
{
    F32 offsetX;
    F32 offsetY;
    F32 scaleX;
    F32 scaleY;
    F32 centerScaleX;
    F32 centerScaleY;
    F32 textScaleX;
    F32 textScaleY;
    F32 rotation;
    F32 offsetU;
    F32 offsetV;
    xColor color;
    U8 brightness;
};

struct zUICustom
{
    zUI* ui;

    void* __nw(U32 size);
    void PostApplyMotionFrame(zUIMotionFrame*);
    void PreApplyMotionFrame(zUIMotionFrame*);
    void PostInitMotion();
    void PreInitMotion();
    void Exit();
    void PostRender();
    U8 PreAutoMenu();
    U8 PreRender();
    void PostUpdate(float);
    void PreUpdate(float);
    U8 HandleEvent(xBase*, unsigned int, const float*, xBase*, unsigned int);
    void ResetMotion();
    void Reset();
    void Setup();
    void Init();
    U8 IsSystem();
    U8 IsSignalAllowed();
};

struct zUICustomConditionallyDisabled : zUICustom
{
    S32 padding; // aligns 2 functions
    zConditional* m_pCondition;
    U8 m_bCondition;

    U8 PreRender();
    U8 PreAutoMenu();
    void PreUpdate();
};

class zUI : public xBase
{
public:
    struct State
    {
        F32 x;
        F32 y;
        F32 width;
        F32 height;
        xColor color;
        U8 brightness;
        U8 pad[3];
    };

    const zUIAsset* asset;
    State current;
    State startMovement;
    F32 z;
    zUIMotionAsset* selectedMotion;
    zUIMotionAsset* unselectedMotion;
    zUICustom* custom;
    bool visible;
    bool focus;
    bool lastFocus;
    bool selected;
    bool brighten;
    bool hdrPass;
    bool locked;

    zUIAsset* GetAsset() const { return (zUIAsset*)asset; }

    virtual U32 GetSortKey() const = 0;
    virtual bool Blends() const;
    virtual bool IsUIText() { return false; }
    virtual void DoInit();
    virtual void DoSetup();
    virtual void DoReset();
    virtual void DoResetMotion();
    virtual void DoHandleEvent(xBase* from, U32 toEvent, const F32* toParam, xBase* toParamWidget, U32 toParamWidgetID);
    virtual void DoRender() const = 0;
    virtual void DoUpdate(F32 dt, U32 buttonsPressed);
    virtual void DoExit();
    virtual void DoInitMotion();
    virtual void DoApplyMotionFrame(const zUIMotionFrame* frame);
    virtual void FocusOn();
    virtual void FocusOff();
    virtual void Select();
    virtual void Unselect();
    virtual void Visible();
    virtual void Invisible();

    void AutoMenu(U32 zUIAsset::*item, U32 event);
    void ApplyMotion();
    F32 CalcAcceleratedDistance(F32 totalDistance, F32 startTime, F32 endTime, F32 accelTime,
                                F32 decelTime);
    void RunMotion(zUIMotionAsset* asset, bool loop, bool reset);
    void Signal(U32 event);

private:
    zUIMotionAsset* motion;
    F32 motionTime;
    bool motionFiredEvent;
    bool motionLoop;
};

struct zUICustomImageSlideshow : zUICustom
{
    U32 m_CurrentImage;
    U32 m_NumImages;
    xGroup* m_TextureGroup;

    void UpdateTexture();
    void SetTextureList(xGroup* textureList);
    U8 HandleEvent(U32 toEvent);
    void Reset();
};

struct zUITextAsset : zUIAsset
{
    U32 textID;
    U8 font;
    U8 fontSizeW;
    U8 fontSizeH;
    U8 fontSpacingX;
    U8 fontSpacingY;
    U8 textBoxInsetTop;
    U8 textBoxInsetLeft;
    U8 textBoxInsetRight;
    U8 textBoxInsetBottom;
    U8 justifyX;
    U8 justifyY;
    U8 textFlags;
    xColor shadowColor;
    F32 shadowOffsetX;
    F32 shadowOffsetY;
    F32 textScaleX;
    F32 textScaleY;
};

struct zUIUserStringAsset : zUITextAsset
{
    U8 hardMaxChars;
    U8 softMaxChars;
};

struct zUIText : zUI
{
    xColor shadowColor;
    char* text;

    void DoApplyMotionFrame(zUIMotionFrame* frame);
    void DoHandleEvent(xBase* from, U32 toEvent, F32* toParam, xBase* toParamWidget,
                       U32 toParamWidgetID);
    void DoRender();
    void setup_textbox(xtextbox& tb, zUITextAsset* asset);
    void DoReset();
    void DoInit();
    bool IsUIText();
    U32 GetSortKey();
};

struct zUIUserString : zUIText
{
    char* textBuffer;
    S32 length;
    S32 maxLength;

    U32 GetSortKey() const;
    void DoHandleEvent(xBase* from, U32 toEvent, F32* toParam, xBase* toParamWidget,
                       U32 toParamWidgetID);
    void DoReset();
    void DoInit();
};

struct _zUI : zEnt
{
    zUIAsset* sasset;
    U32 uiFlags;
    U32 uiButton;
    U16 preUpdateIndex;
    U16 updateIndex;
};

struct zUIMgr : xMgr
{
    S32 m_preUpdateStart;
    S32 m_preUpdateEnd;
    U32 m_preUpdateMax;
    _zUI** m_preUpdate;
    S32 m_updateStart;
    S32 m_updateEnd;
    U32 m_updateMax;
    _zUI** m_update;

    void PreUpdate(zScene* s, F32 dt);
    void Update(zScene* s, F32 dt);
    void Setup(zScene* s);
    void Touch(_zUI* ui);
    void Remove(_zUI* ui);
    void Remove_PreUpdate(_zUI* ui);
    void Remove_Update(_zUI* ui);
    void Add(_zUI* ui);
    void Add_PreUpdate(_zUI* ui);
    void Add_Update(_zUI* ui);
};

extern S32 bad_card_available;
// Another .comm symbol is here ("uknown_common_bss_symbol").
// Maybe some unused variable that was still linked in?
_zUI* sSorted[768];
zUIMgr gUIMgr;

void zUI_Init(zUI* text, zUIAsset* asset);
void zUI_Init();
void zUI_Init(void* ent, void* asset);
void zUI_Init(_zUI* ent, xEntAsset* asset);
void zUI_Save(_zUI* ent, xSerial* s);
void zUI_Load(_zUI* ent, xSerial* s);
void zUI_Reset(_zUI* ent);
void zUI_PreUpdate(_zUI* ent, xScene*, F32);
void zUI_Update(_zUI* ent, xScene*, F32 dt);
void zUIRenderAll();
void zUI_Render(xEnt* ent);
S32 zUIEventCB(xBase*, xBase* to, U32 toEvent, const F32* toParam, xBase*);
void zUI_ParseINI(xIniFile* ini);
S32 zUIPortalEventCB(xBase* from, xBase* to, U32 toEvent, const F32* toParam, xBase* toParamWidget);
void zUI_ScenePortalSetToCurrentLevel(zScene* zsc);
void zUI_ScenePortalInit(zScene* zsc);
void zUI_PortalToKrabs(U32 taskNum);
void zUI_ScenePortalUpdate();
void zUI_ScenePortalSave(xSerial* s);
void zUI_ScenePortalLoad(xSerial* s);

#endif
