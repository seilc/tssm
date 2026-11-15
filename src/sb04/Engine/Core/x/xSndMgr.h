#ifndef XSNDMGR_H
#define XSNDMGR_H

#include "iSnd.h"
#include "xMath3.h"
#include "xSnd.h"

struct xEnt;

void xSndMgrPauseSounds(S16 eSoundCategory, bool bPaused, bool bPauseFutureSoundsOfThisType);
xSndGroupHandle xSndMgrGetSoundGroup(U32 uSoundGroupNameHash);
iSndHandle xSndMgrPlay(xSndGroupHandle hSoundToPlay, U32 uFlags, const xVec3* pPos_WS, const xVec3* pVel, xEnt* pParentEnt, F32* pfOverrideVolume, F32* pfOverridePitch);
void xSndMgrStop(iSndHandle& hInHandle);
void xSndMgrStartStereo(iSndHandle hSnd00, iSndHandle hSnd01);

template <S32 unknown>
class sound_queue
{
public:
    sound_queue() { head = 0; tail = 0; }

    void play(xSndGroupHandle hSoundToPlay, S32 uFlags, const xVec3* pPos_WS, const xVec3* pVel, xEnt* pParentEnt, F32* pfOverrideVolume, F32* pfOverridePitch)
    {
        iSndHandle handle = xSndMgrPlay(hSoundToPlay, uFlags, pPos_WS, pVel, pParentEnt, pfOverrideVolume, pfOverridePitch);
        push(handle);
    }

    void push(iSndHandle handle)
    {
        _playing[tail] = handle;

        S32 begin = head;
        S32 end = tail+1;
        if (end <= begin) end += unknown+1;

        S32 len = end - begin;
        if (len > unknown) {
            xSndMgrStop(_playing[begin]);
            begin++;
            head = begin % (unknown+1);
        }

        tail = end % (unknown+1);
    }

private:
    iSndHandle _playing[unknown+1];
    S32 head;
    S32 tail;
};

#endif
