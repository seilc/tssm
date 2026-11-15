#include "xCommon.h"
#include "zUICustom.h"

#include "xEvent.h"
#include "xGroup.h"
#include "zScene.h"
#include "zUI.h"

zUICustomConditionallyDisabled::zUICustomConditionallyDisabled(zUI* ui) : zUICustom(ui), m_pCondition(NULL)
{
    xBase* pCond = zSceneFindObject(ui->GetAsset()->customWidget);
    if (pCond) {
        if (pCond && pCond->baseType == eBaseTypeCond) {
            m_pCondition = (zConditional*)pCond;
        }
    }
}

zUICustomImageSlideshow::zUICustomImageSlideshow(zUI* ui) : zUICustom(ui), m_CurrentImage(0), m_NumImages(0), m_TextureGroup(NULL)
{
    U32 widgetID = ui->GetAsset()->customWidget;
    if (widgetID) {
        SetTextureList((xGroup*)zSceneFindObject(widgetID));
    }
}

void zUICustom::Init()
{
}

void zUICustom::Setup()
{
}

void zUICustom::Reset()
{
}

void zUICustom::ResetMotion()
{
}

U8 zUICustom::HandleEvent(xBase*, U32, const F32*, xBase*, U32)
{
    return 1;
}

void zUICustom::PreUpdate(F32)
{
}

void zUICustom::PostUpdate(F32)
{
}

U8 zUICustom::PreRender()
{
    return 1;
}

U8 zUICustom::PreAutoMenu()
{
    return 1;
}

void zUICustom::PostRender()
{
}

void zUICustom::Exit()
{
}

void zUICustom::PreInitMotion()
{
}

void zUICustom::PostInitMotion()
{
}

void zUICustom::PreApplyMotionFrame(zUIMotionFrame*)
{
}

void zUICustom::PostApplyMotionFrame(zUIMotionFrame*)
{
}

void* zUICustom::operator new(size_t size)
{
    return zUIAllocStaticMemory(size);
}

void zUICustomImageSlideshow::Reset()
{
    m_CurrentImage = 0;
    if (m_TextureGroup) {
        UpdateTexture();
    }
}

U8 zUICustomImageSlideshow::HandleEvent(xBase* from, U32 toEvent, const F32* toParam, xBase* toParamWidget, U32 toParamWidgetID)
{
    switch (toEvent) {
    case eEventUISignalUp:
        m_CurrentImage = m_CurrentImage < m_NumImages - 1 ? m_CurrentImage + 1 : 0;
        return 1;
    case eEventUISignalDown:
        m_CurrentImage = m_CurrentImage ? m_CurrentImage - 1 : m_NumImages - 1;
        return 1;
    case eEventUIChangeTexture:
        UpdateTexture();
        return 0;
    }
    return 1;
}

void zUICustomImageSlideshow::SetTextureList(xGroup* textureList)
{
    xASSERT(textureList);
    m_TextureGroup = textureList;
    m_CurrentImage = 0;
    m_NumImages = xGroupGetCount(m_TextureGroup);
    xASSERT(m_NumImages);
}

void zUICustomConditionallyDisabled::PreUpdate(F32)
{
    if (m_pCondition) {
        m_bCondition = zConditional_Evaluate(m_pCondition) != 0;
    } else {
        m_bCondition = 1;
    }
}

U8 zUICustomConditionallyDisabled::PreAutoMenu()
{
    return m_bCondition;
}

U8 zUICustomConditionallyDisabled::PreRender()
{
    return m_bCondition;
}
