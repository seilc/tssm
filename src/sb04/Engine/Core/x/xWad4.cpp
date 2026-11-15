#include "xCommon.h"
#include "xWad4.h"
#include "rwplcore.h"
#include "xPad.h"
#include "zGame.h"
#include "zScene.h"
#include <math.h>

//                                              xRay / xScene

void xRayHitsEnt(xScene* sc, xRay3* r, xQCData* qcr, xEnt* ent, void* colldata)
{
    xCollis* coll = (xCollis*)colldata;
    xCollis c;

    if (ent->chkby == XENT_COLLTYPE_NONE)
    {
        return;
    }

    if (qcr && !xQuickCullIsects(qcr, &ent->bound.qcd))
    {
        return;
    }

    xRayHitsBound(r, &ent->bound, &c);

    if (!(c.flags & 0x1))
    {
        return;
    }

    if (c.dist < coll->dist)
    {
        coll->dist = c.dist;
        coll->oid = ent->id;
        coll->optr = ent;
        coll->mptr = ent->model;
    }
}

void xRayHitsTikiLandableEnt(xScene* sc, xRay3* r, xQCData* qcr, xEnt* ent, void* colldata)
{
    xCollis* coll = (xCollis*)colldata;
    xCollis c;

    if (ent->chkby == XENT_COLLTYPE_NONE)
    {
        return;
    }

    if (ent->collType == XENT_COLLTYPE_NPC)
    {
        return;
    }

    if (ent->baseType == eBaseTypeBoulder)
    {
        return;
    }

    if (qcr && !xQuickCullIsects(qcr, &ent->bound.qcd))
    {
        return;
    }

    xRayHitsBound(r, &ent->bound, &c);

    if (!(c.flags & 0x1))
    {
        return;
    }

    if (ent->collLev == 0x5)
    {
        iRayHitsModel(r, ent->model, &c);

        if (!(c.flags & 0x1))
        {
            return;
        }
    }

    if (c.dist < coll->dist)
    {
        coll->dist = c.dist;
        coll->oid = ent->id;
        coll->optr = ent;
        coll->mptr = ent->model;
    }
}

void xSceneForAllNPCs(xScene* sc, xSceneEntCallback func, void* data)
{
    for (U16 i = 0; i < sc->num_npcs; i++)
    {
        if (!func(sc->npcs[i], sc, data))
        {
            break;
        }
    }
}

void xSceneForAllDynamics(xScene* sc, xSceneEntCallback func, void* data)
{
    for (U16 i = 0; i < sc->num_dyns; i++)
    {
        if (!func(sc->dyns[i], sc, data))
        {
            break;
        }
    }
}

void xSceneForAllStatics(xScene* sc, xSceneEntCallback func, void* data)
{
    for (U16 i = 0; i < sc->num_stats; i++)
    {
        if (!func(sc->stats[i], sc, data))
        {
            break;
        }
    }
}

void xSceneForAllEnts(xScene* sc, xSceneEntCallback func, void* data)
{
    for (U16 i = 0; i < sc->num_act_ents; i++)
    {
        if (!func(sc->act_ents[i], sc, data))
        {
            break;
        }
    }
}

xBase* xSceneResolvID(xScene* sc, U32 id)
{
    if (sc->resolvID)
    {
        return sc->resolvID(id);
    }

    return NULL;
}

void xSceneAddEnt(xScene* sc, xEnt* ent)
{
    if (ent->collType == XENT_COLLTYPE_TRIG)
    {
        sc->trigs[sc->num_trigs++] = ent;
    }
    else if (ent->collType == XENT_COLLTYPE_STAT)
    {
        sc->stats[sc->num_stats++] = ent;
    }
    else if (ent->collType == XENT_COLLTYPE_DYN)
    {
        sc->dyns[sc->num_dyns++] = ent;
    }
    else if (ent->collType == XENT_COLLTYPE_NPC)
    {
        sc->npcs[sc->num_npcs++] = ent;
    }

    sc->act_ents[sc->num_act_ents++] = ent;
}

void xSceneSetup(xScene* sc)
{
    xEnvSetup(sc->env);
}

void xSceneLoad(xScene* sc, xSerial* s)
{
}

void xSceneSave(xScene* sc, xSerial* s)
{
}

void xSceneExit(xScene* sc)
{
}

void xSceneInit(xScene* sc, U16 num_trigs, U16 num_stats, U16 num_dyns, U16 num_npcs)
{
    sc->flags = 0;
    sc->num_trigs_allocd = num_trigs;
    sc->trigs = (xEnt**)xMEMALLOC(num_trigs * sizeof(xEnt*), 0);
    sc->num_stats_allocd = num_stats;
    sc->stats = (xEnt**)xMEMALLOC(num_stats * sizeof(xEnt*), 0);
    sc->num_dyns_allocd = num_dyns;
    sc->dyns = (xEnt**)xMEMALLOC(num_dyns * sizeof(xEnt*), 0);
    sc->num_npcs_allocd = num_npcs;
    sc->npcs = (xEnt**)xMEMALLOC(num_npcs * sizeof(xEnt*), 0);
    sc->num_ents_allocd = (U32)num_trigs + (U32)num_stats + (U32)num_dyns + (U32)num_npcs;
    sc->num_act_ents = 0;
    sc->act_ents = (xEnt**)xMEMALLOC(sc->num_ents_allocd * sizeof(xEnt*), 0);
    sc->num_trigs = 0;
    sc->num_stats = 0;
    sc->num_dyns = 0;
    sc->num_npcs = 0;

    sc->resolvID = NULL;

    xAnimInit();
    xModelInit();
    xAnimPoolInit(&sc->mempool, 50, 1, 0x1, 4);
    xModelPoolInit(49, 64);
    xModelPoolInit(74, 8);
    xModelPoolInit(324, 1);
}

//                                      xQuickCull WEAK

//                                              xSG

#include "xsavegame.cpp"

//                                              xRumble

#include "xRMemData.cpp"

//                                                xRender

//                                                xRenderState

#include "xRenderState.cpp"

//                                                xRenderBuffer

void xRenderBufferInit()
{
    gRenderBuffer.m_mode = 0;
    gRenderBuffer.m_indexCount = 0;
    gRenderBuffer.m_vertexCount = 0;
    gRenderBuffer.m_vertexTypeSize = 36;
    gRenderBuffer.m_index = gRenderArr.m_index;
    gRenderBuffer.m_vertex = gRenderArr.m_vertex;
    gRenderBuffer.m_vertexTZ = gRenderArr.m_vertexTZ;
}

//                                              xQuickCull cont.

//                                                  xPTank

//                                                  PKR

#include "xpkrsvc.cpp"

#include "xPartition.cpp"

//                                                  xParticle

//                                                  xPar

volatile static U32 sFrameCount;
static S32 sParMgrInit;

#define REG_TABLE_SIZE 255

extern F32 _708;
extern F32 _709;

S32 sParGroupRegTableInit = 0;
S32 sParGroupRegTableCount = 0;
extern xParGroup* sParGroupRegTable[REG_TABLE_SIZE]; // todo: move from bss.s

void xParMgrRender()
{
    iParMgrRender();
}

void xParMgrUpdate(F32 elapsedTime)
{
    iParMgrUpdate(elapsedTime);

    sFrameCount++;

    if (sFrameCount > 10)
    {
        sFrameCount = 1;
    }

    U32 i;
    for (i = sFrameCount; i >= 1; i--)
        ;
    sFrameCount = i;
}

void xParMgrInit()
{
    if (sParMgrInit == 0)
    {
        xParMemInit();
        iParMgrInit();
        sParMgrInit = 1;
    }
    else
    {
        xParMgrKillAllParticles();
        iParMgrInit();
    }
}

void xParGroupKillPar(xParGroup* ps, xPar* p)
{
    if (p == ps->m_root)
    {
        ps->m_root = p->m_next;

        if (ps->m_root)
        {
            ps->m_root->m_prev = NULL;
        }

        p->m_next = NULL;
        p->m_prev = NULL;
    }
    else
    {
        if (p->m_next)
        {
            p->m_next->m_prev = p->m_prev;
        }

        if (p->m_prev)
        {
            p->m_prev->m_next = p->m_next;
        }

        p->m_prev = NULL;
        p->m_next = NULL;
    }

    ps->m_num_of_particles--;

    if (ps->m_flags & XPARGROUP_ALLOCPARS)
    {
        xParFree(p);
    }
    else
    {
        xParGroupAddParToDeadList(ps, p);
    }
}

xPar* xParGroupAddPar(xParGroup* ps)
{
    xPar* p;

    if (ps->m_flags & XPARGROUP_ALLOCPARS)
    {
        p = xParAlloc();

        if (!p)
        {
            S32 myPriority = ps->m_priority;

            for (U8 i = 0; i < REG_TABLE_SIZE; i++)
            {
                if (sParGroupRegTable[i] && sParGroupRegTable[i] != ps &&
                    (sParGroupRegTable[i]->m_flags & XPARGROUP_ALLOCPARS) &&
                    !(sParGroupRegTable[i]->m_flags & XPARGROUP_UNK10) &&
                    sParGroupRegTable[i]->m_priority < myPriority && sParGroupRegTable[i]->m_root)
                {
                    xParGroupKillPar(sParGroupRegTable[i], sParGroupRegTable[i]->m_root);

                    p = xParAlloc();

                    break;
                }
            }
        }
    }
    else if (ps->m_dead)
    {
        p = ps->m_dead;
        ps->m_dead = p->m_next;

        if (ps->m_dead)
        {
            ps->m_dead->m_prev = NULL;
        }
    }
    else
    {
        p = NULL;
    }

    if (p)
    {
        xParInit(p);
        xParGroupAddParP(ps, p);
    }

    return p;
}

#define CLAMP_COLOR(x,a,b) ((x) < (a) ? (a) : ((x) > (b) ? (b) : (x)))

void xParGroupAnimate(xParGroup* ps, F32 dt)
{
    xPar* i = ps->m_root;
    xPar* tmp;
    F32 age = dt;

    if (ps->m_flags & XPARGROUP_NOAGING)
    {
        age = _708;
    }

    if (!ps->m_root)
    {
        ps->m_alive = 0;
    }

    while (i)
    {
        if (i->m_lifetime < _708)
        {
            tmp = i;

            i = i->m_next;

            xParGroupKillPar(ps, tmp);
        }
        else
        {
            // non-matching: stack isn't resizing for each float-to-U8 conversion
            i->m_c[0] = i->m_cfl[0] = CLAMP_COLOR(i->m_cvel[0] * dt + i->m_cfl[0], _708, _709);
            i->m_c[1] = i->m_cfl[1] = CLAMP_COLOR(i->m_cvel[1] * dt + i->m_cfl[1], _708, _709);
            i->m_c[2] = i->m_cfl[2] = CLAMP_COLOR(i->m_cvel[2] * dt + i->m_cfl[2], _708, _709);
            i->m_c[3] = i->m_cfl[3] = CLAMP_COLOR(i->m_cvel[3] * dt + i->m_cfl[3], _708, _709);
            i->m_size += i->m_sizeVel * dt;
            i->m_lifetime -= age;

            i = i->m_next;
        }
    }
}

struct xCmdInfo
{
    U32 type;
    U32 size;
    xParCmdUpdateFunc func;
};

static xCmdInfo sCmdInfo[XPARCMD_TYPE_COUNT] = {};

extern F32 _658_0;
extern F32 _691;
extern F32 _760;
extern F32 _772;
extern F32 _812;
extern F32 _830_1;
extern F32 _831_0; // TO-DO - WRONG - CHANGE LATER
extern F32 _857_0;
extern F32 _858;
extern F32 _1075;
extern F32 _1076;
extern F32 _1077;

void xParCmd_SizeInOut_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    xPar* p;
    xParCmdSizeInOutData* cmd = (xParCmdSizeInOutData*)c->tasset;

    if (cmd->enabled)
    {
        p = ps->m_root;

        S32 i, seg;
        F32 slope_size[3];

        slope_size[0] = _1075 * (cmd->custSize[1] - cmd->custSize[0]);
        slope_size[1] = _1075 * (cmd->custSize[2] - cmd->custSize[1]);
        slope_size[2] = _1075 * (cmd->custSize[3] - cmd->custSize[2]);

        while (p)
        {
            // non-matching: there is definitely a clamp happening here, but it isn't using the CLAMP macro.
            F32 frac = CLAMP(_812 - p->m_lifetime / p->totalLifespan, _691, _812);

            if (frac < _1076)
            {
                seg = 0;
            }
            else if (frac < _1077)
            {
                seg = 1;
            }
            else
            {
                seg = 2;
            }

            for (S32 i = seg; i > 0; i--)
            {
                // non-matching: _1076 is cached before loop
                frac -= _1076;
            }

            p->m_size = frac * slope_size[seg] + cmd->custSize[seg];

            p = p->m_next;
        }
    }
}

void xParCmd_DampenSpeed_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    xPar* p;
    xParCmdDampenData* cmd = (xParCmdDampenData*)c->tasset;

    if (cmd->enabled)
    {
        p = ps->m_root;

        F32 damp = dt * cmd->dampSpeed;

        while (p)
        {
            xVec3AddScaled(&p->m_vel, &p->m_vel, damp);

            p = p->m_next;
        }
    }
}

void xParCmdCollideFallSticky_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    xParCmdCollideFallSticky& cmd = *(xParCmdCollideFallSticky*)c->tasset;
    F32 xzdamp = _812 - cmd.sticky;
    xPar* p = ps->m_root;

    while (p)
    {
        F32& loc = p->m_pos.y;
        F32& vel = p->m_vel.y;
        F32 dloc = cmd.y - loc;

        if (dloc < _691)
        {
            // lol
        }
        else
        {
            loc = dloc * cmd.bounce + cmd.y;

            if (vel < _691)
            {
                vel = -vel * cmd.bounce;
            }

            p->m_vel.x *= xzdamp;
            p->m_vel.z *= xzdamp;
        }

        p = p->m_next;
    }
}

void xParCmdCollideFall_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    xParCmdCollideFall& cmd = *(xParCmdCollideFall*)c->tasset;
    xPar* p = ps->m_root;

    while (p)
    {
        F32& loc = p->m_pos.y;
        F32& vel = p->m_vel.y;
        F32 dloc = cmd.y - loc;

        if (dloc < _691)
        {
            // lol
        }
        else
        {
            loc = dloc * cmd.bounce + cmd.y;

            if (vel < _691)
            {
                vel = -vel * cmd.bounce;
            }
        }

        p = p->m_next;
    }
}

void xParCmdTexAnim_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    xPar* p;
    xParCmdTexAnim* cmd = (xParCmdTexAnim*)c->tasset;
    xParCmdTex* tex = ps->m_cmdTex;

    if (!tex)
    {
        return;
    }

    if (cmd->throttle_time > _691)
    {
        cmd->throttle_time_elapsed -= dt;

        if (cmd->throttle_time_elapsed > _691)
        {
            return;
        }

        cmd->throttle_time_elapsed = cmd->throttle_time;
    }

    p = ps->m_root;

    if (cmd->anim_mode == 0)
    {
        while (p)
        {
            p->m_texIdx[0] = xrand() % tex->cols;
            p->m_texIdx[1] = xrand() % tex->rows;

            p = p->m_next;
        }
    }
    else if (cmd->anim_mode == 1)
    {
        if (tex->cols > 1)
        {
            while (p)
            {
                p->m_texIdx[0]++;

                if (p->m_texIdx[0] >= tex->cols)
                {
                    p->m_texIdx[0] = 0;

                    if (cmd->anim_wrap_mode == 1)
                    {
                        p->m_texIdx[1]++;

                        if (p->m_texIdx[1] >= tex->rows)
                        {
                            p->m_texIdx[1] = 0;
                        }
                    }
                    else if (cmd->anim_wrap_mode == 2)
                    {
                        if (p->m_texIdx[1] == 0)
                        {
                            p->m_texIdx[1] = tex->rows - 1;
                        }
                        else
                        {
                            p->m_texIdx[1]--;
                        }
                    }
                    else if (cmd->anim_wrap_mode == 3)
                    {
                        p->m_texIdx[1]++;

                        if (p->m_texIdx[1] >= tex->rows)
                        {
                            p->m_texIdx[1] = tex->rows - 1;
                            p->m_texIdx[0] = tex->cols - 1;
                        }
                    }
                }

                p = p->m_next;
            }
        }
    }
    else if (cmd->anim_mode == 2)
    {
        if (tex->cols > 1)
        {
            while (p)
            {
                if (p->m_texIdx[0] == 0)
                {
                    p->m_texIdx[0] = tex->cols - 1;

                    if (cmd->anim_wrap_mode == 1)
                    {
                        p->m_texIdx[1]++;

                        if (p->m_texIdx[1] >= tex->rows)
                        {
                            p->m_texIdx[1] = 0;
                        }
                    }
                    else if (cmd->anim_wrap_mode == 2)
                    {
                        if (p->m_texIdx[1] == 0)
                        {
                            p->m_texIdx[1] = tex->rows - 1;
                        }
                        else
                        {
                            p->m_texIdx[1]--;
                        }
                    }
                }
                else
                {
                    p->m_texIdx[0]--;
                }

                p = p->m_next;
            }
        }
    }
    else if (cmd->anim_mode == 3)
    {
        if (tex->rows > 1)
        {
            while (p)
            {
                if (p->m_texIdx[1] == 0)
                {
                    p->m_texIdx[1] = tex->rows - 1;

                    if (cmd->anim_wrap_mode == 1)
                    {
                        p->m_texIdx[0]++;

                        if (p->m_texIdx[0] >= tex->cols)
                        {
                            p->m_texIdx[0] = 0;
                        }
                    }
                    else if (cmd->anim_wrap_mode == 2)
                    {
                        if (p->m_texIdx[0] == 0)
                        {
                            p->m_texIdx[0] = tex->cols - 1;
                        }
                        else
                        {
                            p->m_texIdx[0]--;
                        }
                    }
                }
                else
                {
                    p->m_texIdx[1]--;
                }

                p = p->m_next;
            }
        }
    }
    else if (cmd->anim_mode == 4)
    {
        if (tex->rows > 1)
        {
            while (p)
            {
                p->m_texIdx[1]++;

                if (p->m_texIdx[1] >= tex->rows)
                {
                    p->m_texIdx[1] = 0;

                    if (cmd->anim_wrap_mode == 1)
                    {
                        p->m_texIdx[0]++;

                        if (p->m_texIdx[0] >= tex->cols)
                        {
                            p->m_texIdx[0] = 0;
                        }
                    }
                    else if (cmd->anim_wrap_mode == 2)
                    {
                        if (p->m_texIdx[0] == 0)
                        {
                            p->m_texIdx[0] = tex->cols - 1;
                        }
                        else
                        {
                            p->m_texIdx[0]--;
                        }
                    }
                }

                p = p->m_next;
            }
        }
    }
}

void xParCmdTex_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
}

void xParCmdRotateAround_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    xPar* p = ps->m_root;
    xParCmdRotateAround* cmd = (xParCmdRotateAround*)c->tasset;

    F32 yaw = _857_0 * (dt * cmd->yaw) / _858;
    F32 radius_growth = dt * cmd->radius_growth;

    while (p)
    {
        xVec3 at;
        xVec3Sub(&at, &cmd->pos, &p->m_pos);

        at.y = _691;

        xMat3x3 lookmat;

        F32 radius = xMat3x3LookVec(&lookmat, &at);

        xVec3 angles;
        xMat3x3GetEuler(&lookmat, &angles);

        angles.x += yaw;

        xMat3x3 rotmat;
        xMat3x3Euler(&rotmat, angles.x, angles.y, angles.z);

        xVec3 var_BC, var_C8;

        // non-matching: f0 and f1 swapped

        var_BC.x = _691;
        var_BC.y = _691;
        var_BC.z = radius + radius_growth;

        xMat3x3RMulVec(&var_C8, &rotmat, &var_BC);

        p->m_pos.x = var_C8.x + cmd->pos.x;
        p->m_pos.z = var_C8.z + cmd->pos.z;

        p = p->m_next;
    }
}

void xParCmdVelocityApply_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    xPar* p = ps->m_root;

    while (p)
    {
        xVec3Add(&p->m_pos, &p->m_pos, &p->m_vel);

        p = p->m_next;
    }
}

void xParCmdRotPar_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    // Removed ported code cus it wasnt even close to correct (2%)
}

void xParCmdApplyWind_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    xPar* p = ps->m_root;

    // non-matching: f2 and f3 are combined into one register
    F32 f2 = _812 * (((xParCmdApplyWind*)c->tasset)->unknown * dt);
    F32 f3 = _812 * (((xParCmdApplyWind*)c->tasset)->unknown * dt);

    while (p)
    {
        p->m_vel.x += f2;
        p->m_vel.z += f3;

        p = p->m_next;
    }
}

void xParCmdRandomVelocityPar_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    xPar* p = ps->m_root;
    xParCmdRandomVelocityPar* cmd = (xParCmdRandomVelocityPar*)c->tasset;
    F32 f31 = cmd->x * dt;
    F32 f30 = cmd->y * dt;
    F32 f29 = cmd->z * dt;

    while (p)
    {
        xMat3x3 var_88;

        F32 y = _760 * (f31 * xurand()) - f31;
        F32 x = _760 * (f30 * xurand()) - f30;
        F32 z = _760 * (f29 * xurand()) - f29;

        xMat3x3Euler(&var_88, x, y, z);
        xMat3x3LMulVec(&p->m_vel, &var_88, &p->m_vel);

        p = p->m_next;
    }
}

void xParCmdAlpha3rdPolyReg_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
}

void xParCmdScale_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
}

void xParCmdSmokeAlpha_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
}

void xParCmdScale3rdPolyReg_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
}

void xParCmdMoveRandomPar_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    // Not even close. (5%)
    xPar* p = ps->m_root;
    xParCmdMoveRandomPar* cmd = (xParCmdMoveRandomPar*)c->tasset;
    F32 f31 = cmd->dim.x * (dt * _772);
    F32 f30 = cmd->dim.z * (dt * _772);

    while (p)
    {
        p->m_pos.x += f31 * (xurand() - _772);
        p->m_pos.z += f30 * (xurand() - _772);

        p = p->m_next;
    }
}

void xParCmdMoveRandom_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    xPar* p;
    xParCmdMove* cmd = (xParCmdMove*)c->tasset;

    xVec3 var_28;
    var_28 = cmd->dir;

    var_28.x *= _760 * xurand();
    var_28.y *= _760 * xurand();
    var_28.z *= _760 * xurand();

    xVec3Sub(&var_28, &var_28, &cmd->dir);
    xVec3SMulBy(&var_28, dt);

    p = ps->m_root;

    while (p)
    {
        xVec3Add(&p->m_pos, &p->m_pos, &var_28);

        p = p->m_next;
    }
}

void xParCmdMove_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    xPar* p;
    xParCmdMove* cmd = (xParCmdMove*)c->tasset;

    xVec3 var_28;
    var_28 = cmd->dir;

    xVec3SMulBy(&var_28, dt);

    p = ps->m_root;

    while (p)
    {
        xVec3Add(&p->m_pos, &p->m_pos, &var_28);

        p = p->m_next;
    }
}

void xParCmdAccelerate_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    xPar* p;
    xParCmdAccelerate* cmd = (xParCmdAccelerate*)c->tasset;

    xVec3 var_28;
    var_28 = cmd->acc;

    xVec3SMulBy(&var_28, dt);

    p = ps->m_root;

    while (p)
    {
        p->m_vel.x += var_28.x;
        p->m_vel.y += var_28.y;
        p->m_vel.z += var_28.z;

        p = p->m_next;
    }
}

void xParCmdOrbitLine_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    xPar* p = ps->m_root;
    xParCmdOrbitLine* cmd = (xParCmdOrbitLine*)c->tasset;
    F32 mdt = cmd->gravity * dt;

    while (p)
    {
        xVec3 var_34, var_40, var_4C, var_58;

        xVec3Sub(&var_34, &p->m_pos, &cmd->p);
        xVec3Cross(&var_4C, &var_34, &cmd->axis);
        xVec3Cross(&var_40, &cmd->axis, &var_4C);
        xVec3Sub(&var_58, &var_40, &var_34);

        F32 f31 = xVec3Length2(&var_58);

        if (f31 < cmd->maxRadiusSqr)
        {
            F32 f1 = xVec3LengthFast(var_58.x, var_58.y, var_58.z);

            F32 force = mdt / (f1 + (f31 + cmd->epsilon));

            p->m_vel.x += var_58.x * force;
            p->m_vel.y += var_58.y * force;
            p->m_vel.z += var_58.z * force;
        }

        p = p->m_next;
    }
}

void xParCmdOrbitPoint_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    xPar* p = ps->m_root;
    xParCmdOrbitPoint* cmd = (xParCmdOrbitPoint*)c->tasset;
    F32 mdt = cmd->gravity * dt;

    while (p)
    {
        xVec3 var_38;

        xVec3Sub(&var_38, &cmd->center, &p->m_pos);

        F32 f31 = xVec3Length2(&var_38);

        if (f31 < cmd->maxRadiusSqr)
        {
            F32 f1 = xVec3LengthFast(var_38.x, var_38.y, var_38.z);

            F32 force = mdt / (f1 + (f31 + cmd->epsilon));

            p->m_vel.x += var_38.x * force;
            p->m_vel.y += var_38.y * force;
            p->m_vel.z += var_38.z * force;
        }

        p = p->m_next;
    }
}

void xParCmdFollow_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    xPar* p = ps->m_root;
    xParCmdFollow* cmd = (xParCmdFollow*)c->tasset;
    F32 mdt = cmd->gravity * dt;

    while (p && p->m_next)
    {
        xVec3 var_38;

        xVec3Sub(&var_38, &p->m_next->m_pos, &p->m_pos);

        F32 f31 = xVec3Length2(&var_38);
        F32 f1 = xVec3LengthFast(var_38.x, var_38.y, var_38.z);

        F32 force = mdt / (f1 * (f31 + cmd->epsilon));

        p->m_vel.x += var_38.x * force;
        p->m_vel.y += var_38.y * force;
        p->m_vel.z += var_38.z * force;

        p = p->m_next;
    }
}

void xParCmdAge_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    xPar* p = ps->m_root;
    F32 age_rate = ((xParCmdAge*)c->tasset)->unknown * dt;

    while (p)
    {
        p->m_lifetime -= age_rate;
        p = p->m_next;
    }
}

void xParCmdKillSlow_Update(xParCmd* c, xParGroup* ps, F32 dt)
{
    xPar* p = ps->m_root;
    xParCmdKillSlow* cmd = (xParCmdKillSlow*)c->tasset;
    F32 speedLimit = cmd->speedLimitSqr * dt;

    if (cmd->kill_less_than)
    {
        while (p)
        {
            if (xVec3Length2(&p->m_vel) < speedLimit)
            {
                p->m_lifetime = _658_0;
            }

            p = p->m_next;
        }
    }
    else
    {
        while (p)
        {
            if (xVec3Length2(&p->m_vel) > speedLimit)
            {
                p->m_lifetime = _658_0;
            }

            p = p->m_next;
        }
    }
}

xParCmdUpdateFunc xParCmdGetUpdateFunc(U32 parType)
{
    for (S32 i = 0; i < XPARCMD_TYPE_COUNT; i++)
    {
        if (sCmdInfo[i].type == parType)
        {
            return sCmdInfo[i].func;
        }
    }

    return NULL;
}

void xParCmdRegister(U32 parType, U32 size, xParCmdUpdateFunc func)
{
    sCmdInfo[parType].type = parType;
    sCmdInfo[parType].size = size;
    sCmdInfo[parType].func = func;
}

void xParCmdInit()
{
    xParCmdRegister(XPARCMD_TYPE_MOVE, sizeof(xParCmdMove), xParCmdMove_Update);
    xParCmdRegister(XPARCMD_TYPE_MOVERANDOM, sizeof(xParCmdMove), xParCmdMoveRandom_Update);
    xParCmdRegister(XPARCMD_TYPE_ACCELERATE, sizeof(xParCmdAccelerate), xParCmdAccelerate_Update);
    xParCmdRegister(XPARCMD_TYPE_VELOCITYAPPLY, sizeof(xParCmdAsset), xParCmdVelocityApply_Update);
    xParCmdRegister(XPARCMD_TYPE_UNK5, sizeof(xParCmdUnk5), NULL);
    xParCmdRegister(XPARCMD_TYPE_KILLSLOW, sizeof(xParCmdKillSlow), xParCmdKillSlow_Update);
    xParCmdRegister(XPARCMD_TYPE_FOLLOW, sizeof(xParCmdFollow), xParCmdFollow_Update);
    xParCmdRegister(XPARCMD_TYPE_ORBITPOINT, sizeof(xParCmdOrbitPoint), xParCmdOrbitPoint_Update);
    xParCmdRegister(XPARCMD_TYPE_ORBITLINE, sizeof(xParCmdOrbitLine), xParCmdOrbitLine_Update);
    xParCmdRegister(XPARCMD_TYPE_MOVERANDOMPAR, sizeof(xParCmdMoveRandomPar),
                    xParCmdMoveRandomPar_Update);
    xParCmdRegister(XPARCMD_TYPE_SCALE3RDPOLYREG, sizeof(xParCmdScale3rdPolyReg),
                    xParCmdScale3rdPolyReg_Update);
    xParCmdRegister(XPARCMD_TYPE_TEX, sizeof(xParCmdTex), xParCmdTex_Update);
    xParCmdRegister(XPARCMD_TYPE_TEXANIM, sizeof(xParCmdTexAnim), xParCmdTexAnim_Update);
    xParCmdRegister(XPARCMD_TYPE_RANDOMVELOCITYPAR, sizeof(xParCmdRandomVelocityPar),
                    xParCmdRandomVelocityPar_Update);
    xParCmdRegister(XPARCMD_TYPE_AGE, sizeof(xParCmdAge), xParCmdAge_Update);
    xParCmdRegister(XPARCMD_TYPE_ALPHA3RDPOLYREG, sizeof(xParCmdAlpha3rdPolyReg),
                    xParCmdAlpha3rdPolyReg_Update);
    xParCmdRegister(XPARCMD_TYPE_APPLYWIND, sizeof(xParCmdApplyWind), xParCmdApplyWind_Update);
    xParCmdRegister(XPARCMD_TYPE_ROTPAR, sizeof(xParCmdRotPar), xParCmdRotPar_Update);
    xParCmdRegister(XPARCMD_TYPE_ROTATEAROUND, sizeof(xParCmdRotateAround),
                    xParCmdRotateAround_Update);
    xParCmdRegister(XPARCMD_TYPE_SMOKEALPHA, sizeof(xParCmdSmokeAlpha), xParCmdSmokeAlpha_Update);
    xParCmdRegister(XPARCMD_TYPE_SCALE, sizeof(xParCmdScale), xParCmdScale_Update);
    xParCmdRegister(XPARCMD_TYPE_COLLIDEFALL, sizeof(xParCmdCollideFall),
                    xParCmdCollideFall_Update);
    xParCmdRegister(XPARCMD_TYPE_COLLIDEFALLSTICKY, sizeof(xParCmdCollideFallSticky),
                    xParCmdCollideFallSticky_Update);
    xParCmdRegister(XPARCMD_TYPE_SHAPER, sizeof(xParCmdShaperData), xParCmd_Shaper_Update);
    xParCmdRegister(XPARCMD_TYPE_ALPHAINOUT, sizeof(xParCmdAlphaInOutData),
                    xParCmd_AlphaInOut_Update);
    xParCmdRegister(XPARCMD_TYPE_SIZEINOUT, sizeof(xParCmdSizeInOutData), xParCmd_SizeInOut_Update);
    xParCmdRegister(XPARCMD_TYPE_DAMPENSPEED, sizeof(xParCmdDampenData),
                    xParCmd_DampenSpeed_Update);
}

//                                      xPad

void xPadKill()
{
    iPadKill();
}

void xPadRumbleEnable(S32 idx, S32 enable)
{
    xPad* p = &mPad[idx];
    if (p->state != ePad_Enabled)
    {
        enable = 0;
    }
    if (enable)
    {
        if (p->flags & ePadInit_EnableRumble4)
        {
            p->flags |= ePadInit_Complete8a;
        }
    }
    else
    {
        if (p->flags & ePadInit_Complete8a)
        {
            p->flags ^= ePadInit_Complete8a;
            //xPadDestroyRumbleChain(mPad + idx);
        }
    }
}

// WIP.
xPad* xPadEnable(S32 idx)
{
    xPad* p = &mPad[idx];
    if (p->state == ePad_Disabled && idx == 0)
    {
        p = iPadEnable(&mPad[0], 0);
        if (p->state == ePad_Enabled || p->state != ePad_Disabled)
        {
            if (p->flags & ePadInit_EnableRumble4)
            {
                p->flags |= ePadInit_Complete8a;
            }
            else if (p->flags & ePadInit_Complete8a)
            {
                p->flags ^= ePadInit_Complete8a;
            }
        }
    }
    return p;
}

S32 xPadInit()
{
    memset(mPad, 0, sizeof(mPad));
    //memset(mRumbleList, 0, sizeof(mRumbleList));
    S32 code = iPadInit();
    if (!code)
    {
        return 0;
    }
    //gPlayerPad = mPad;
    return 1;
}

// WIP.
S32 xPadUpdate(S32 idx, F32 time_passed)
{
    U32 new_on;
    xPad* p = &mPad[idx];
    S32 ret;
    U32 fake_dpad;
    S32 i;

    if (idx == 0)
    {
        if (zScene_ScreenAdjustMode() == 0)
        {
            // not yet implemented
            if (/*!zMenuRunning() &&*/ !zGameIsPaused())
            {
                p->flags &= ~0x10; // unknown flag 0x10
            }
            else
            {
                p->flags |= 0x10;
            }
        }
        else
        {
            p->flags &= ~0x10;
        }

        if (p->al2d_timer >= 0.35f)
            p->al2d_timer = 0.35f;
        if (p->ar2d_timer >= 0.35f)
            p->ar2d_timer = 0.35f;
        if (p->d_timer >= 0.35f)
            p->d_timer = 0.35f;

        fake_dpad = 0;
        ret = iPadUpdate(&mPad[idx], &new_on);

        if (!ret)
        {
            p->pressed = 0;
            p->released = 0;
            return 1;
        }

        if (p->flags & 0x10)
        {
            if (p->flags & ePadInit_WaitStable2)
            {
                if (p->analog1.x < 50)
                    fake_dpad |= XPAD_BUTTON_LEFT;
                else if (p->analog1.x > 49)
                    fake_dpad |= XPAD_BUTTON_RIGHT;

                if (p->analog1.y < 50)
                    fake_dpad |= XPAD_BUTTON_UP;
                else if (p->analog1.y > 49)
                    fake_dpad |= XPAD_BUTTON_DOWN;

                if (fake_dpad == 0)
                {
                    p->al2d_timer = 0.0f;
                }
                else
                {
                    p->al2d_timer -= time_passed;
                    if (p->al2d_timer <= 0.0f)
                    {
                        new_on |= fake_dpad;
                        p->al2d_timer = 0.35f;
                    }
                }
            }

            if (p->flags & ePadInit_EnableAnalog3)
            {
                S32 a2x = p->analog2.x;
                S32 a2y = p->analog2.y;
                if (a2x <= 50 || a2x >= 207 || a2y <= 50 || a2y >= 207)
                {
                    p->ar2d_timer -= time_passed;
                    if (p->ar2d_timer <= 0.0f)
                    {
                        p->ar2d_timer = 0.35f;

                        if (a2x < 50)
                            new_on |= XPAD_BUTTON_LEFT;
                        else if (a2x > 49)
                            new_on |= XPAD_BUTTON_RIGHT;

                        if (a2y < 50)
                            new_on |= XPAD_BUTTON_UP;
                        else if (a2y > 49)
                            new_on |= XPAD_BUTTON_DOWN;
                    }
                }
                else
                {
                    p->ar2d_timer = 0.0f;
                }
            }
        }

        p->pressed = new_on & ~p->on;
        p->released = p->on & ~new_on;
        p->on = new_on;

        for (i = 0; i < 22; i += 2)
        {
            U32 mask0 = 1 << i;
            U32 mask1 = 1 << (i + 1);

            if (p->pressed & mask0)
                p->down_tmr[0] = 0.0f;
            else if (p->released & mask0)
                p->up_tmr[0] = 0.0f;

            if (p->on & mask0)
                p->down_tmr[0] += time_passed;
            else
                p->up_tmr[0] += time_passed;

            if (p->pressed & mask1)
                p->down_tmr[1] = 0.0f;
            else if (p->released & mask1)
                p->up_tmr[1] = 0.0f;

            if (p->on & mask1)
                p->down_tmr[1] += time_passed;
            else
                p->up_tmr[1] += time_passed;

            p = (xPad*)(p->value + 8);
        }

        if (p->flags & 0x10)
        {
            if (!(p->on &
                  (XPAD_BUTTON_UP | XPAD_BUTTON_DOWN | XPAD_BUTTON_LEFT | XPAD_BUTTON_RIGHT)))
            {
                p->d_timer = 0.0f;
            }
            else
            {
                p->d_timer -= time_passed;
                if (p->d_timer <= 0.0f)
                {
                    p->d_timer = 0.35f;

                    if (p->on & XPAD_BUTTON_UP)
                        p->pressed |= XPAD_BUTTON_UP;
                    else if (p->on & XPAD_BUTTON_DOWN)
                        p->pressed |= XPAD_BUTTON_DOWN;

                    if (p->on & XPAD_BUTTON_LEFT)
                        p->pressed |= XPAD_BUTTON_LEFT;
                    else if (p->on & XPAD_BUTTON_RIGHT)
                        p->pressed |= XPAD_BUTTON_RIGHT;
                }
            }
        }

        return 1;
    }

    return 0;
}

void xPadNormalizeAnalog(xPad& pad, S32 inner_zone, S32 outer_zone)
{
    PadAnalog* src = &pad.analog1;

    for (S32 i = 0; i < 2; i++, src++)
    {
        analog_data* data = &pad.analog[i];
        S8 x = src->x;
        F32 normX = 0.0f;

        if (x <= 1)
        {
            if ((x <= -inner_zone) && (-outer_zone <= x))
            {
                normX = F32(x + inner_zone) / F32(outer_zone - inner_zone);
            }
        }
        else if ((inner_zone <= x) && (x <= outer_zone))
        {
            normX = F32(x - inner_zone) / F32(outer_zone - inner_zone);
        }
        data->offset.x = normX;

        S8 y = src->y;
        F32 normY = 0.0f;
        if (y <= 1)
        {
            if ((y <= -inner_zone) && (-outer_zone <= y))
            {
                normY = F32(y + inner_zone) / F32(outer_zone - inner_zone);
            }
        }
        else if ((inner_zone <= y) && (y <= outer_zone))
        {
            normY = F32(y - inner_zone) / F32(outer_zone - inner_zone);
        }
        data->offset.y = normY;

        if ((data->offset.x == 0.0f) && (data->offset.y == 0.0f))
        {
            data->mag = 0.0f;
            data->dir.x = 1.0f;
            data->dir.y = 0.0f;
            data->ang = 0.0f;
        }
        else
        {
            if (data->offset.x > 1.0f)
                data->offset.x = 1.0f;
            else if (data->offset.x < -1.0f)
                data->offset.x = -1.0f;

            if (data->offset.y > 1.0f)
                data->offset.y = 1.0f;
            else if (data->offset.y < -1.0f)
                data->offset.y = -1.0f;

            F32 mag = data->offset.x * data->offset.x + data->offset.y * data->offset.y;

            if (mag >= 0.0f)
            {
                if (!isinf(mag))
                {
                    F32 inv_sqrt = 1.0 / sqrt(mag);
                    F32 val = -(inv_sqrt * inv_sqrt * mag - 3.0f) * inv_sqrt * 0.5f;
                    mag = 100000.0f;
                    if (val > 0.0000099999997f)
                    {
                        mag = 1.0f / val;
                    }
                }
            }

            data->mag = mag;

            F32 inv_mag = 1.0f / data->mag;
            data->dir.x = data->offset.x * inv_mag;
            data->dir.y = data->offset.y * inv_mag;

            data->ang = xAngleClampFast(atan2(data->dir.y, data->dir.x));
        }
    }
}
