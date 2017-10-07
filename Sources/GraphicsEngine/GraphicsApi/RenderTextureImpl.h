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

    virtual void SetRenderLocation(RenderLocation location) = 0;

    virtual RenderLocation GetRenderLocation() const = 0;
};

#endif // RENDERTEXTURE_H
