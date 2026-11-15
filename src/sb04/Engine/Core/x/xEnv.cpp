#include "xCommon.h"
#include "xEnv.h"

#include "xstransvc.h"
#include "zJSPExtraData.h"

xEnv* gCurXEnv;

void xEnvLoadJSPList(xEnv* env, S32 dataType)
{
    if (dataType == 0) {
        U32 bufsize;
        void* buf;

        env->geom = &env->ienv;

        S32 jsp_count = xSTAssetCountByType('JSP ');
        xASSERT_FMT((jsp_count > 0), "No JSP's found in scene!");

        iEnvLoadBegin(env->geom, dataType, jsp_count / 2);

        S32 index = 0;
        for (S32 i = 0; i < jsp_count; i++) {
            PKRAssetTOCInfo info;
            buf = xSTFindAssetByType('JSP ', i, &bufsize);

            xSTGetAssetInfoByType('JSP ', i, &info);

            S32 rc = iEnvLoadJSP(env->geom, info.aid, buf, bufsize, dataType, index);
            if (rc) {
                index++;
            }
        }

        env->geom->jsp_count = index;
        iEnvLoadEnd(env->geom, dataType);
    }

    xASSERT(env->geom);

    gCurXEnv = env;
}

void xEnvSetup(xEnv* env)
{
    xASSERT(env->geom);

    iEnvSetup(env->geom);
    iEnvDefaultLighting(env->geom);

    env->lightKit = NULL;
    gCurXEnv = env;
}

void xEnvFree(xEnv* env)
{
    xASSERT(env);

    if (env->geom) {
        xASSERT(env->geom == &env->ienv);
        iEnvFree(env->geom);
        env->geom = NULL;
    }
}

void xEnvRender(xEnv* env, bool alpha)
{
    xASSERT(env);

    if (env->geom) {
        iEnvRender(env->geom, alpha);
    }

    if (env->geom->jsp_count > 0) {
        U32 jspRenderCount = 0;

        for (S32 i = 0; i < env->geom->jsp_count; i++) {
            if (env->geom->jsp_visibilityCount[i] > 0) {
                jspRenderCount++;
            }
        }

        if (env->geom->jsp_count == 1) {
            env->geom->jsp_visibilityCount[0] = 1;
        }
    }
}

void xEnvSceneReset(xEnv* env)
{
    for (S32 i = 0; i < env->geom->jsp_count; i++) {
        env->geom->jsp_visibilityCount[i] = 0;
    }

    zJSPExtraData::ShowAllAssociatedGroups(false);
}
