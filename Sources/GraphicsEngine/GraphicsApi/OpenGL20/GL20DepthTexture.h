#ifndef GL20DEPTHTEXTURE_H
#define GL20DEPTHTEXTURE_H

#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20.h"
#include "GraphicsEngine/Rect.h"

#include "GraphicsEngine/GraphicsApi/RenderTextureImpl.h"
#include "GraphicsEngine/Screen.h"
#include "GraphicsEngine/Application.h"

class GL20DepthTexture : public RenderTextureImpl
{
public:
    GL20DepthTexture() : m_scene(Application::Instance().GetScene()) {}

    void Init();
    void Deinit();

    void SetRenderTarget(RenderTarget location);
    RenderTarget GetRenderTarget() const { return previousLocation; }

public:
    GLuint depthMapFBO; // depth map of framebuffer object
    GLuint depthMap;

    GLuint depthCubemapFBO;
    GLuint depthCubemap;

    const unsigned int SHADOW_WIDTH = 1024;
    const unsigned int SHADOW_HEIGHT = 1024;

    Scene & m_scene;
    Rect tempViewport;
    int tempWidth;
    int tempHeight;
    RenderTarget previousLocation = SCREEN;
};


#endif // GL20DEPTHTEXTURE_H
