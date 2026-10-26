#ifndef XHUDMETER_H
#define XHUDMETER_H

#include "xHud.h"
#include "xSnd.h"
#include "xHudModel.h"
#include "zUI.h"
#include "xHudText.h"

namespace xhud
{

    enum eDirection
    {
        eDIRECTION_X,
        eDIRECTION_Y
    };

    struct meter_asset : asset
    {
        F32 start_value;
        F32 min_value;
        F32 max_value;
        F32 increment_time;
        F32 decrement_time;
        struct _class_0
        {
            U32 start_increment;
            U32 increment;
            U32 start_decrement;
            U32 decrement;
        } sound;
    };

    struct meter_widget : widget
    {
        meter_asset& res;
        F32 value;
        F32 min_value;
        F32 max_value;
        F32 end_value;
        F32 value_vel;
        F32 value_accel;
        F32 ping_delay;
        F32 pitch;
        sound_queue<4> pings;
    };

    struct font_context
    {
        U32 id;
        S32 justify;
        F32 w;
        F32 h;
        F32 space;
        F32 drop_x;
        F32 drop_y;
        xColor_tag c;
        xColor_tag drop_c;
    };

    struct font_meter_widget : meter_widget
    {
        font_context font;
        font_context start_font;
        S32 precision;
        char buffer[12];
        S32 last_value;
        xfont xf;
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

    struct model_info
    {
        U32 id;
        xVec3 loc;
        xVec3 size;
    };

    struct unit_meter_asset : meter_asset
    {
        model_info model[2];
        xVec3 offset;
        U32 fill_forward;
    };

    struct unit_meter_widget : meter_widget
    {
        unit_meter_asset res;
        xModelInstance* model[2][6];
        F32 anim_time;

        static void load(xBase& data, xDynAsset& asset, size_t);
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
    widget* barPartsWidgets[5];
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
    widget* widgets[8];
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
