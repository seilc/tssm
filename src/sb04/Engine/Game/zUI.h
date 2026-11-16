#ifndef ZUI_H
#define ZUI_H

#include "xBase.h"
#include "xColor.h"
#include "xIni.h"
#include "xMgr.h"
#include "zEnt.h"
#include "zTextbox.h"
#include "zUIAsset.h"
#include "zUICustom.h"
#include "zUIMotion.h"

struct zUIMotionAsset;

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

    static U8 bAllowInput;

    zUIAsset* GetAsset() const { return (zUIAsset*)asset; }
    zUIMotionAsset* GetMotion() const { return motion; }

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

    void Init()
    {
        DoInit();
        if (custom) {
            custom->Init();
        }
    }

    void Setup()
    {
        DoSetup();
        if (custom) {
            custom->Setup();
        }
    }

    void Reset()
    {
        DoReset();
        if (custom) {
            custom->Reset();
        }
    }

    void ResetMotion()
    {
        DoResetMotion();
        if (custom) {
            custom->ResetMotion();
        }
    }

    void HandleEvent(xBase* from, U32 toEvent, const F32* toParam, xBase* toParamWidget, U32 toParamWidgetID)
    {
        if (custom && !custom->HandleEvent(from, toEvent, toParam, toParamWidget, toParamWidgetID)) {
            return;
        }
        DoHandleEvent(from, toEvent, toParam, toParamWidget, toParamWidgetID);
    }

    void Render() const
    {
        if (custom && !custom->PreRender()) {
            return;
        }
        DoRender();
        if (custom) {
            custom->PostRender();
        }
    }

    void Update(F32 dt, U32 buttonsPressed)
    {
        if (custom) {
            custom->PreUpdate(dt);
        }
        DoUpdate(dt, buttonsPressed);
        if (custom) {
            custom->PostUpdate(dt);
        }
    }

    void Exit()
    {
        if (custom) {
            custom->Exit();
        }
        DoExit();
    }

    void AutoMenu(U32 zUIAsset::*item, U32 event);
    void ApplyMotion();
    F32 CalcAcceleratedDistance(F32 totalDistance, F32 startTime, F32 endTime, F32 accelTime, F32 decelTime);
    void StopMotion();
    void RunMotion(zUIMotionAsset* asset, bool loop, bool reset);
    void Signal(xBase* from, U32 event);

    void Signal(U32 event)
    {
        Signal(this, event);
    }

    void InitMotion()
    {
        if (custom) {
            custom->PreInitMotion();
        }
        DoInitMotion();
        if (custom) {
            custom->PostInitMotion();
        }
    }

    void ApplyMotionFrame(const zUIMotionFrame* frame)
    {
        if (custom) {
            zUIMotionFrame newFrame = *frame;
            custom->PreApplyMotionFrame(&newFrame);
            DoApplyMotionFrame(&newFrame);
            custom->PostApplyMotionFrame(&newFrame);
        } else {
            DoApplyMotionFrame(frame);
        }
    }

private:
    zUIMotionAsset* motion;
    F32 motionTime;
    bool motionFiredEvent;
    bool motionLoop;
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
void* zUIAllocStaticMemory(U32 size);
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
