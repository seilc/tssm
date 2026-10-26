#ifndef ZREWARDS_H
#define ZREWARDS_H

#include "types.h"
#include "zEnt.h"
#include "zEntPickup.h"
#include "zNPCTypes.h"

struct zRewardsQ
{
    U8 active;
    S32 numRewards;
    xVec3 spawnPos;
};

struct zRewardsMgr
{
    zRewardsQ rewardsQ[20];
    F32 comboTime;
    F32 comboTimer;
    U32 numCratesDestroyed;
    U32 numEnemiesDefeated;
    U32 lastComboManlinessPoints; // 0x1a0
    U32 lastComboIndex; // 0x1a4
    F32 spawnTimer;
    bool playerDead; // 0x1ac
    zEntPickup* enemyManlinessPoints[20][5];

    void SetPlayerDead();
    void GiveAllRewardsNow();
    void ResetLastComboIndex();
    U32 GetLastComboIndex() const;
    void ResetLastComboManlinessPoints();
    U32 GetLastComboManlinessPoints() const;
    void SpawnRewards(S32 numRewards, xVec3& fromPos);
    void Update(F32 dt);
    U32 GetComboManlinessPoints();
    void GiveReward(en_npctyp enemy, xVec3& fromPos);
    U32 GetUpgradeRangeUpper() const;
};

#endif
