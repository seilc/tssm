#ifndef ZUIBOX_H
#define ZUIBOX_H

#include "zUI.h"
#include "xTextureManager.h"

class zUIBox : public zUI
{
public:
    xTextureHandle textures[9];
    F32 curRotation;
};

#endif
