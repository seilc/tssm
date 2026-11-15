#ifndef ZUICUSTOM_H
#define ZUICUSTOM_H

#include "xBase.h"
#include "zConditional.h"

struct xGroup;
class zUI;
struct zUIMotionFrame;

class zUICustom
{
public:
    zUICustom(zUI* ui) : ui(ui) {}

    virtual void Init();
    virtual void Setup();
    virtual void Reset();
    virtual void ResetMotion();
    virtual U8 HandleEvent(xBase* from, U32 toEvent, const F32* toParam, xBase* toParamWidget, U32 toParamWidgetID);
    virtual void PreUpdate(F32 dt);
    virtual void PostUpdate(F32 dt);
    virtual U8 PreRender();
    virtual void PostRender();
    virtual void Exit();
    virtual U8 PreAutoMenu();
    virtual void PreInitMotion();
    virtual void PostInitMotion();
    virtual void PreApplyMotionFrame(zUIMotionFrame* frame);
    virtual void PostApplyMotionFrame(zUIMotionFrame* frame);
    virtual U8 IsSystem(zUI*) { return 0; }
    virtual U8 IsSignalAllowed(U32) { return 1; }

    static void* operator new(size_t size);

protected:
    zUI* ui;
};

class zUICustomConditionallyDisabled : public zUICustom
{
public:
    zConditional* m_pCondition;
    U8 m_bCondition;

    zUICustomConditionallyDisabled(zUI* ui);

    U8 PreRender();
    U8 PreAutoMenu();
    void PreUpdate(F32 dt);
};

class zUICustomImageSlideshow : public zUICustom
{
public:
    U32 m_CurrentImage;
    U32 m_NumImages;
    xGroup* m_TextureGroup;

    zUICustomImageSlideshow(zUI* ui);

    void UpdateTexture();
    void SetTextureList(xGroup* textureList);
    U8 HandleEvent(xBase* from, U32 toEvent, const F32* toParam, xBase* toParamWidget, U32 toParamWidgetID);
    void Reset();
};

#endif
