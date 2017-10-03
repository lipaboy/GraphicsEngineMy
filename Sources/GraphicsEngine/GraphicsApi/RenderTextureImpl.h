#ifndef RENDERTEXTUREIMPL_H
#define RENDERTEXTUREIMPL_H

enum RenderLocation {
    SCREEN,
    DEPTH_TEXTURE
};

class RenderTextureImpl
{
public:
    virtual void Init() = 0;

    virtual void setRenderLocation(RenderLocation location) = 0;
};

#endif // RENDERTEXTURE_H
