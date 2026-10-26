#include "iScrFX.h"
#include "rwcore.h"
#include "rwplcore.h"

extern RwRaster* g_rast_gctapdance;
extern S32 g_alreadyTriedAlloc;
extern _iMotionBlurData sMBD;
extern U32 sMotionBlurEnabled;

void iScrFxLensFlare_Reset()
{
}

void RenderRect(RwRect* rect, F32 unknown)
{
}

S32 iScrFxCameraDestroyed(RwCamera* pCamera)
{
    if (sMBD.motionBlurFrontBuffer != NULL)
    {
        RwRasterDestroy(sMBD.motionBlurFrontBuffer);
        sMBD.motionBlurFrontBuffer = NULL;
        return 1;
    }
    return 0;
}

void iScrFxCameraEndScene(RwCamera* pCamera)
{
    if ((sMotionBlurEnabled != 0) && (sMBD.motionBlurAlpha != 0))
    {
        U8 alpha = sMBD.motionBlurAlpha;
        if (sMBD.motionBlurFrontBuffer != 0x0)
        {
            sMBD.vertex[0xc] = 0xFF;
            sMBD.vertex[0xd] = 0xFF;
            sMBD.vertex[0xe] = 0xFF;
            sMBD.vertex[0xf] = alpha;
            sMBD.vertex[0x24] = 0xFF;
            sMBD.vertex[0x25] = 0xFF;
            sMBD.vertex[0x26] = 0xFF;
            sMBD.vertex[0x27] = alpha;
            sMBD.vertex[0x3c] = 0xFF;
            sMBD.vertex[0x3d] = 0xFF;
            sMBD.vertex[0x3e] = 0xFF;
            sMBD.vertex[0x3f] = alpha;
            sMBD.vertex[0x54] = 0xFF;
            sMBD.vertex[0x55] = 0xFF;
            sMBD.vertex[0x56] = 0xFF;
            sMBD.vertex[0x57] = alpha;
            RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATETEXTUREFILTER,
                                                           (void*)rwFILTERNEAREST);
            RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEFOGENABLE,
                                                           (void*)rwFOGTYPENAFOGTYPE);
            RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)false);
            RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)false);
            RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATETEXTURERASTER,
                                                           sMBD.motionBlurFrontBuffer);
            RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,
                                                           (void*)true);
            RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATESRCBLEND,
                                                           (void*)rwBLENDSRCALPHA);
            RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEDESTBLEND,
                                                           (void*)rwBLENDINVSRCALPHA);
            RwEngineInstance->dOpenDevice.fpIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST,
                                                                       sMBD.index, 6);
            RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEFOGENABLE,
                                                           (void*)rwFOGTYPENAFOGTYPE);
            RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)true);
            RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)true);
            RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATETEXTURERASTER, NULL);
            RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,
                                                           (void*)false);
            RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATESRCBLEND,
                                                           (void*)rwBLENDSRCALPHA);
            RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEDESTBLEND,
                                                           (void*)rwBLENDINVSRCALPHA);
        }
    }
    return;
}

void iScrFxCameraCreated(RwCamera* pCamera)
{
    sMBD.motionBlurAlpha = 0x90;
    sMBD.motionBlurFrontBuffer = NULL;
    sMBD.index[0] = 0;
    sMBD.index[1] = 1;
    sMBD.index[2] = 2;
    sMBD.index[3] = 0;
    sMBD.index[4] = 2;
    sMBD.index[5] = 3;
}

void iScrFxEnd()
{
    RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEFOGENABLE,
                                                   (void*)rwFOGTYPENAFOGTYPE);
    RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)true);
    RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)true);
    RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATETEXTURERASTER, NULL);
    RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)false);
    RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDONE);
    RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDZERO);
}

void iScrFxBegin()
{
    RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATETEXTUREFILTER,
                                                   (void*)rwFILTERNEAREST);
    RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEFOGENABLE,
                                                   (void*)rwFOGTYPENAFOGTYPE);
    RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)false);
    RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)false);
    RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATETEXTURERASTER, NULL);
    RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)true);
    RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
    RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEDESTBLEND,
                                                   (void*)rwBLENDINVSRCALPHA);
    RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATECULLMODE,
                                                   (void*)rwCULLMODECULLNONE);
}

void iScrFxInit()
{
}
