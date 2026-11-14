#ifndef ZHUD_H
#define ZHUD_H

#include "xHud.h"
#include "xHudFontMeter.h"
#include "xHudModel.h"
#include "xHudText.h"
#include "xHudUnitMeter.h"
#include "xLightKit.h"
#include "zUI.h"

namespace zhud
{
    void render();
    void update(F32 dt);
    void show();
    void hide();
    void init();
    void destroy();
    void setup();
} // namespace zhud

namespace zHud
{
    extern RwCamera* HudCamera;
    extern xLightKit* HudLightKit;
} // namespace zHud

namespace xhud
{
    enum eDirection
    {
        eDIRECTION_X,
        eDIRECTION_Y
    };

    struct TextureScroller
    {
        model_widget* m_pModelWidget;
        U16* m_aMoveIndices;
        U16 m_moveCount;
        eDirection m_dir : 8;
        U8 m_pad1;
        F32 m_prevOffset;
        F32 m_finalOffset;
        F32 m_initialOffset;
    };
} // namespace xhud

struct hud_element : xBase
{
    hud_element* _next;
};

struct ModelAndFont : hud_element
{
    xhud::model_widget* modelWidget;
    xhud::font_meter_widget* fontMeter;
    U32* valueToWatch;
    U32 lastValue;
    U8 okToAutoHide;
};

struct ModelAndFontHideOnTextBox : ModelAndFont
{
    U8 delayedShow;
    U8 hidden;
};

struct BarMeter : hud_element
{
    // Added the xhud prefix to the structs, dont know whether or not all these structs need to be in the namespace
    //
    xhud::model_widget* bar;
    xhud::model_widget* barNotch;
    xhud::font_meter_widget* barMeter;
    F32 sizeOfActualBar;
    xVec3 notchLocation;
    xVec3 fontLocation;
    xhud::text_widget* minValueText;
    xhud::text_widget* maxValueText;
    xhud::TextureScroller* textureScroller;
    xhud::widget* barPartsWidgets[5];
    xLightKit* hudLightKit;
    S32 defaultMinValue;
    S32 defaultMaxValue;
    S32* valueToWatch;
    S32* minValueToWatch;
    S32* maxValueToWatch;
    S32 lastValue;
    U8 firstTimeUpdate;

    void reset();
    void hide();
    void show();
    void update();
};

struct ManlinessMeter : BarMeter
{
    xhud::model_widget* upgradeIcon;
    xhud::text_widget* manlinessPointsComboText;
    xhud::text_widget* manlinessPointsComboPointsText;
    U32 lastManlinessPoints;
    U32 minManlinessPoints;
    U32 maxManlinessPoints;
    U32 lastMaxManlinessPoints;
    U32 lastUnusedSkillPoints;
    U8 firstTimeUpdate;
    char nextUpgrade[16];
    xhud::widget* widgets[8];
    xhud::TextureScroller manlinessTextureScroller;
    iSndHandle upgradeSound;
    iSndGroupHandle upgradeSoundGroupHandle;

    void hide();
    void show(char autohide);
    void update(F32 dt);
    void SetImmediateValue(U32 value);
    void setup();
    void reset();
    //void* __ct();
};

struct KrabbyPattyMeter : hud_element
{
    xhud::unit_meter_widget* krabbyPattyMeter;
    U32 lastHealth;
    U32 lastMaxHealth;
    U8 firstTime;
};

struct TreasureChest : ModelAndFontHideOnTextBox
{
};

struct GoofyGooberMeter : ModelAndFontHideOnTextBox
{
    zUIText* autoSave;
};

struct NitroMeter : ModelAndFontHideOnTextBox
{
};

#endif
