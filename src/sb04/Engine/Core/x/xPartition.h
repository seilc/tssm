#ifndef XPARTITION_H
#define XPARTITION_H

#include "xMath3.h"
#include "xEnv.h"
#include "xVolume.h"

typedef struct _tagPartLink
{
    void* data;
    _tagPartLink* next;
} PartLink;

typedef struct _tagPartSpace
{
    S32 total;
    PartLink head;
} PartSpace;

typedef struct _tagPartition
{
    xVec3 min;
    xVec3 max;
    xVec3 space_dim;
    S32 total_x;
    S32 total_y;
    S32 total_z;
    PartSpace* space;
    PartSpace global;
} Partition;

void xPartitionReset();
PartLink* PartitionGetFreeLink();
void PartitionSpaceReset(PartSpace* space);
void PartitionSpaceInsert(PartSpace* space, void* data);
S32 xPartitionGetTrueIdx(Partition* part, S32 x_spaces, S32 y_spaces, S32 z_spaces);
void xPartitionWorld(Partition* part, xEnv* env, S32 x_spaces, S32 y_spaces,
                     S32 z_spaces);
void xPartitionVolume(Partition* part, xVolume* volume, S32 x_spaces, S32 y_spaces,
                      S32 z_spaces);
void xPartitionDump(Partition* part, char* string);
S32 xPartitionUpdate(Partition* part, void* data, S32 old_idx, xVec3* current_pos);
S32 xPartitionInsert(Partition* part, void* insert_data, xVec3* insert_pos);

#endif
