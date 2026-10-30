#include "xTRC.h"

#include "xFont.h"
#include "xTextAsset.h"
#include "iCamera.h"
#include "zEntPlayerOOBState.h"
#include "zGame.h"
#include "zGameState.h"
#include "zGlobals.h"
#include "zMenu.h"
#include "zVar.h"

#include <string.h>

_tagTRCPadInfo gTrcPad[k_MAX_TRC_PADS];
_tagTRCDiskInfo gTrcDisk;
static const char* k_CONTROLLER_MISSING_MESSAGE;
static const char* k_CONTROLLER_INVALID_MESSAGE;
static const xColor yellow = { 0xFF, 0xE6, 0x00, 0xFF };

void xTRCInit()
{
    memset(gTrcPad, 0, sizeof(gTrcPad));
    for (S32 i = 0; i < k_MAX_TRC_PADS; i++) {
        gTrcPad[i].id = i;
        gTrcPad[i].state = TRC_PadMissing;
    }
    memset(&gTrcDisk, 0, sizeof(gTrcDisk));
}

void xTRCInitMessages()
{
    k_CONTROLLER_MISSING_MESSAGE = xTextFindString("TRC_CONTROLLER_MISSING", NULL);
    k_CONTROLLER_INVALID_MESSAGE = xTextFindString("TRC_CONTROLLER_INVALID", NULL);
}

static U32 pad_message_valid()
{
    if (gGameMode == eGameMode_Boot || gGameMode == eGameMode_Intro) {
        return FALSE;
    } else if (zMenuRunning()) {
        return FALSE;
    } else if (zGameModeGet() == eGameMode_Save || zGameModeGet() == eGameMode_Load) {
        return TRUE;
    } else if (gBusStopIsRunning) {
        globals.dontShowPadMessageDuringLoadingOrCutScene = false;
        return FALSE;
    } else if (zGameGetOstrich() != eGameOstrich_InScene) {
        return FALSE;
    } else if (!oob_state::IsPlayerInControl()) {
        return FALSE;
    } else if (globals.sceneCur->sceneID == 'B402') {
        zGameStall();
        return TRUE;
    } else if (globals.player.ControlOff) {
        if (!(globals.player.ControlOff & CONTROL_OWNER_EVENT && globals.cmgr) && !(globals.player.ControlOff & CONTROL_OWNER_CUTSCENE)) {
            zGameStall();
            return TRUE;
        } else {
            globals.dontShowPadMessageDuringLoadingOrCutScene = false;
            return FALSE;
        }
    }
    return TRUE;
}

static void render_message(const char* s)
{
    static xtextbox tb = xtextbox::create(xfont::create(1, NSCREENX(19.0f), NSCREENY(22.0f), 0.0f, yellow, screen_bounds), screen_bounds);
    tb.set_text(s);
    tb.bounds = screen_bounds;
    tb.bounds.contract(0.1f);
    tb.bounds.h = tb.yextent(true);
    tb.bounds.y = 0.5f - 0.5f * tb.bounds.h;
    xColor c = { 0x00, 0x00, 0x00, 0xF5 };
    render_fill_rect(tb.font.clip, c);
    tb.render(true);
}

static char composed_message_text[256];
static const char* message_text;
static U32 standalone;

void xTRCClearPadMsg()
{
    message_text = NULL;
    composed_message_text[0] = '\0';
}

void xTRCRender()
{
    if (composed_message_text[0] != '\0')
        render_message(composed_message_text);
    else if (message_text)
        render_message(message_text);
}

void xTRCReset()
{
    xTRCClearPadMsg();
    xglobals->dontShowPadMessageDuringLoadingOrCutScene = false;
    if (gGameMode == eGameMode_Stall) {
        zGameModeSwitch(eGameMode_Game);
        zGameStatePauseUnpauseSnd(false);
    }
}

static S32 DisplayMessage(TRCState state)
{
    switch (state) {
    case TRC_Unknown:
        message_text = NULL;
        break;
    case TRC_PadMissing:
        if (!pad_message_valid()) {
            return FALSE;
        }
        message_text = k_CONTROLLER_MISSING_MESSAGE;
        U32 len_message_text = strlen(message_text);
        if (len_message_text < 256) {
            const char* msg = message_text;
            char c;
            while ((c = *msg++) != '\0' && c != '<') {}
            if (c == '\0') {
                break;
            }
            U32 sub_len = msg - message_text;
            memcpy(composed_message_text, message_text, sub_len);
            composed_message_text[sub_len - 1] = '1' + globals.pad0->port;
            memcpy(composed_message_text + sub_len, &message_text[sub_len + 2], len_message_text - sub_len - 1);
            composed_message_text[len_message_text - 2] = '\0';
        }
        break;
    case TRC_PadInvalidType:
        message_text = k_CONTROLLER_INVALID_MESSAGE;
        break;
    case TRC_DiskNotIdentified:
        message_text = "Please wait... Checking for the 'The SpongeBob SquarePants Movie' Game Disc.";
        break;
    case TRC_DiskTrayOpen:
        message_text = "The Disc Cover is open. If you want to continue the game, please close the Disc Cover.";
        break;
    case TRC_DiskNoDisk:
        message_text = "Please insert the 'The SpongeBob SquarePants Movie' Game Disc.";
        break;
    case TRC_DiskInvalid:
        message_text = "This is not the 'The SpongeBob SquarePants Movie' Game Disc. Please insert the 'The SpongeBob SquarePants Movie' Game Disc.";
        break;
    case TRC_DiskRetry:
        message_text = "The Game Disc could not be read. Please read the Nintendo GameCube\x99 Instruction Booklet for more information.";
        break;
    case TRC_DiskFatal:
        message_text = "An error has occurred. Turn the power off and refer to the Nintendo GameCube\x99 Instruction Booklet for further instructions.";
        break;
    default:
        return FALSE;
    }
    if (standalone || RwCameraGetCurrentCamera()) {
        RwCamera* cam = NULL;
        if (standalone) {
            cam = iCameraCreate(FB_XRES, FB_YRES, 0);
            RwRGBA bg = { 0, 0, 0, 0 };
            RwCameraClear(cam, &bg, rwCAMERACLEARIMAGE | rwCAMERACLEARZ);
            RwCameraBeginUpdateWrapper(cam);
        }
        render_message(message_text);
        if (standalone) {
            RwCameraEndUpdate(cam);
            RwCameraShowRaster(cam, NULL, rwRASTERFLIPWAITVSYNC);
            iCameraDestroy(cam);
        }
    }
    return TRUE;
}

void xTRCPad(S32 pad_id, TRCState state)
{
}

void xTRCDisk(TRCState state)
{
    if (state != TRC_DiskNotIdentified) {
        gTrcDisk.state = state;
        gTrcDisk.id = TRC_DiskIdentified;
    } else {
        gTrcDisk.id = TRC_DiskNotIdentified;
    }
}

void render_mem_card_no_space(S32 needed, S32 available, S32 neededFiles, bool enabled)
{
    if (available < 0 && neededFiles != -1 && needed != -1) {
        available = 0;
    }
    bad_card_needed = needed;
    bad_card_available = available;
    const char* error_text = "{i:text_mem_card_no_space}";
    if (neededFiles == 0 && needed > available) {
        error_text = "{i:text_mem_card_no_space_overwrite}";
    }
    else if (neededFiles > 0 && needed > available) {
        error_text = "{i:text_mem_card_no_space_no_save}";
    }
    RenderText(error_text, enabled);
}

void RenderText(const char* text, bool enabled)
{
    xColor c1 = { 0xFF, 0xE6, 0x00, 0xFF };
    static xtextbox tb = xtextbox::create(xfont::create(1, NSCREENX(19.0f), NSCREENY(22.0f), 0.0f, c1, screen_bounds), screen_bounds);
    tb.set_text(enabled ? text : "");
    tb.bounds = screen_bounds;
    tb.bounds.contract(0.1f);
    tb.bounds.h = tb.yextent(true);
    tb.bounds.y = 0.5f - 0.5f * tb.bounds.h;
    tb.render(true);
    xColor c2 = { 0x00, 0x00, 0x00, 0x96 };
    if (!enabled) {
        render_fill_rect(tb.font.clip, c2);
    }
}
