#include "xCommon.h"
#include "zUIMgr.h"

#include "iDraw.h"
#include "xRenderState.h"
#include "xTRC.h"
#include "xutil.h"
#include "zGlobals.h"
#include "zHashes.h"
#include "zRenderState.h"
#include "zScene.h"
#include "zUI.h"
#include "zUIBox.h"
#include "zUIController.h"
#include "zUIImage.h"
#include "zUIModel.h"

#include <rwcore.h>

namespace
{
    zUI* uiElements[1024];
    U32 uiElementCount;
    bool uiHDREnabled;
    bool uiAnyActive = true;
    F32 buttonTimer;
    U32 buttonsPressedQueue;
    U32 buttonsPressed;
} // namespace

void zUIMgrInit(zScene* s)
{
    uiElementCount = 0;
    zUITextInitSystem();

    zUIText* ui1 = (zUIText*)s->baseList[eBaseTypeUIText];
    for (S32 i = 0; i < s->baseCount[eBaseTypeUIText]; i++) {
        uiElements[uiElementCount++] = &ui1[i];
    }

    zUIImage* ui2 = (zUIImage*)s->baseList[eBaseTypeUIImage];
    for (S32 i = 0; i < s->baseCount[eBaseTypeUIImage]; i++) {
        uiElements[uiElementCount++] = &ui2[i];
    }

    zUIModel* ui3 = (zUIModel*)s->baseList[eBaseTypeUIModel];
    for (S32 i = 0; i < s->baseCount[eBaseTypeUIModel]; i++) {
        uiElements[uiElementCount++] = &ui3[i];
    }

    zUIBox* ui4 = (zUIBox*)s->baseList[eBaseTypeUIBox];
    for (S32 i = 0; i < s->baseCount[eBaseTypeUIBox]; i++) {
        uiElements[uiElementCount++] = &ui4[i];
    }

    zUIUserString* ui5 = (zUIUserString*)s->baseList[eBaseTypeUIUserString];
    for (S32 i = 0; i < s->baseCount[eBaseTypeUIUserString]; i++) {
        uiElements[uiElementCount++] = &ui5[i];
    }

    zUIController* ui7 = (zUIController*)s->baseList[eBaseTypeUIController];
    for (S32 i = 0; i < s->baseCount[eBaseTypeUIController]; i++) {
        uiElements[uiElementCount++] = &ui7[i];
    }

    zUIMgrUpdateOrder();

    for (U32 i = 0; i < uiElementCount; i++) {
        uiElements[i]->Setup();
    }

    zUIMgrReset();
}

void zUIMgrReset()
{
    for (U32 i = 0; i < uiElementCount; i++) {
        uiElements[i]->Reset();
    }

    uiAnyActive = true;
}

void zUIMgrUpdate(F32 dt)
{
    if (globals.pad0->pressed & (XPAD_BUTTON_START | XPAD_BUTTON_Z)) {
        uiAnyActive = true;
    }

    buttonTimer -= dt;

    if (gTrcPad[0].state == TRC_PadInserted) {
        buttonsPressedQueue |= globals.pad0->pressed;
    } else {
        buttonsPressedQueue = 0;
    }

    if (!uiAnyActive) {
        return;
    }

    for (U32 i = 0; i < uiElementCount; i++) {
        uiElements[i]->lastFocus = uiElements[i]->focus;
    }

    if (buttonTimer <= 0.0f && buttonsPressedQueue) {
        buttonsPressed = buttonsPressedQueue;
        buttonsPressedQueue = 0;
        buttonTimer = 0.1f;
    } else {
        buttonsPressed = 0;
    }

    uiAnyActive = false;

    for (U32 i = 0; i < uiElementCount; i++) {
        if (xBaseIsEnabled(uiElements[i]) &&
            (uiElements[i]->focus ||
             (uiElements[i]->visible && (uiElements[i]->current.color.a || uiElements[i]->GetMotion())))) {
            uiElements[i]->Update(dt, buttonsPressed);

            // BUG: always true, || instead of &&
            if (uiElements[i]->id != HASH___PAUSE_STATE_PAUSE_MGR ||
                uiElements[i]->id != HASH_UPGRADE_TUTORIAL_CONTROLLER) {
                uiAnyActive = true;
            }
        }
    }
}

void zUIMgrRender()
{
    zUIMgrHDRContext context;

    if (!uiAnyActive) {
        return;
    }

    if (uiHDREnabled) {
        zUIMgrSetHDR(context);
    }

    zRenderState(SDRS_UI);

    for (S32 i = uiElementCount - 1; i >= 0; i--) {
        zUI* ui = uiElements[i];
        if (ui->visible && uiElements[i]->current.color.a) {
            if (uiHDREnabled) {
                zUIMgrRenderElementHDR(context, ui);
            } else {
                ui->Render();
            }
        }
    }

    if (uiHDREnabled) {
        zUIMgrFinishHDR(context);
    }
}

void zUIMgrExit(zScene*)
{
    for (U32 i = 0; i < uiElementCount; i++) {
        uiElements[i]->Exit();
    }
}

namespace
{
    class ElementCompare
    {
    public:
        S32 operator()(const void* A, const void* B) const
        {
            const zUI* a = *(const zUI* const*)A;
            const zUI* b = *(const zUI* const*)B;

            if (a->z != b->z) {
                return a->z > b->z ? 1 : -1;
            }

            U32 akey = a->GetSortKey();
            U32 bkey = b->GetSortKey();
            return bkey - akey;
        }
    };
} // namespace

void zUIMgrUpdateOrder()
{
    quicksort(uiElements, uiElementCount, sizeof(zUI*), ElementCompare());
}

void zUIMgrEnableHDR(bool enabled)
{
}

void zUIMgrSortList(zUI** list, S32 count)
{
    quicksort(list, count, sizeof(zUI*), ElementCompare());
}

void zUIMgrSetHDR(zUIMgrHDRContext& context)
{
    context.renderedHDR = false;
    xFXHighDynamicRangeGetConfiguration(context.oldConfiguration);

    xFXHighDynamicRangeConfiguration newConfiguration = context.oldConfiguration;
    newConfiguration.glow = 0;
    newConfiguration.darken = 0;
    newConfiguration.downsamples = 3;
    newConfiguration.overbrighten = 1.0f;
    newConfiguration.blur_faster = false;
    xFXHighDynamicRangeSetConfiguration(newConfiguration);

    xFXHighDynamicRangeStartRender();
    xRenderFixIMBegin();
}

void zUIMgrFinishHDR(zUIMgrHDRContext& context)
{
    if (context.renderedHDR) {
        RwCamera* currentCamera = RwCameraGetCurrentCamera();
        xFXHighDynamicRangeRender(currentCamera);
    }

    xRenderFixIMEnd();
    HDR_brightening = false;
    iDrawSetFBMSK(0xFF000000, 0xFFFFFFFF, true);
    xFXHighDynamicRangeSetConfiguration(context.oldConfiguration);
}

void zUIMgrRenderElementHDR(zUIMgrHDRContext& context, zUI* ui)
{
    if (ui->brighten) {
        bool blends = ui->Blends();
        iDrawSetFBMSK(blends ? 0x00FFFFFF : 0, 0xFFFFFFFF, true);

        xColor save = ui->current.color;
        ui->current.color.a = ui->current.color.a * ui->current.brightness / 255;

        void *oldAlphaTest, *oldAlphaTestValue;
        RwRenderStateGet(rwRENDERSTATEALPHATESTFUNCTION, &oldAlphaTest);
        RwRenderStateGet(rwRENDERSTATEALPHATESTFUNCTIONREF, &oldAlphaTestValue);
        RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, (void*)rwALPHATESTFUNCTIONALWAYS);

        ui->hdrPass = true;
        ui->Render();
        ui->hdrPass = false;

        ui->current.color = save;
        iDrawSetFBMSK(0xFF000000, 0xFFFFFFFF, true);
        context.renderedHDR = true;

        if ((S32)oldAlphaTest >= rwALPHATESTFUNCTIONNEVER) {
            RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, oldAlphaTest);
        } else {
            RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, (void*)rwALPHATESTFUNCTIONGREATEREQUAL);
        }
        RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, oldAlphaTestValue);

        if (!blends) {
            return;
        }
    }

    ui->Render();
}

void zUIMgrSignalActive()
{
    uiAnyActive = true;
}
