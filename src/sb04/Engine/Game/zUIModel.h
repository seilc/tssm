#ifndef ZUIMODEL_H
#define ZUIMODEL_H

#include "zUI.h"

struct xAnimTable;
struct xModelInstance;
struct xSurface;

class zUIModel : public zUI
{
public:
    xModelInstance* model;
    xAnimTable* atbl;
    xSurface* surf;
};

#endif
