#ifndef XTEXTUREMANAGER_H
#define XTEXTUREMANAGER_H

#include "types.h"

#include <rwcore.h>

struct xInternalTextureNode;
struct xInternalMovieNode;

class xTextureHandle
{
    RwTexture* m_pTexture;
    xInternalMovieNode* m_pMovie;
    xInternalTextureNode* m_pNode;
    xInternalTextureNode* m_pPrevNode;

    friend class xTextureManager;

public:
    xTextureHandle();
    ~xTextureHandle();
    xTextureHandle& operator=(const xTextureHandle& handle);

    void Reference(U32 assetID, bool clearPrev);
    void Reference(RwTexture* pTexture);
    RwTexture* GetTexture();

    void PlayMovie(U32 assetID, U32 looping, U32 freezeframed, U32 startframe, U32 endframe);
    bool IsMoviePlaying();
};

#endif
