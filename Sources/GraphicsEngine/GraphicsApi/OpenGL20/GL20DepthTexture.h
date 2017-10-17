#ifndef GL20DEPTHTEXTURE_H
#define GL20DEPTHTEXTURE_H

#include <iostream>

#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20.h"
#include "GraphicsEngine/Rect.h"
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Camera.h"

#include "GraphicsEngine/GraphicsApi/RenderTextureImpl.h"



class GL20DepthTexture : public RenderTextureImpl
{
public:
    GL20DepthTexture() : m_scene(Application::Instance().GetScene()) {}

    void Init();
    // TODO: add glDeleteFramebuffer
    //void Deinit();

    void SetRenderTarget(RenderTarget location);
    RenderTarget GetRenderTarget() const { return previousLocation; }

public:
    GLuint depthMapFBO;
    GLuint depthMap;

    const unsigned int SHADOW_WIDTH = 1024;
    const unsigned int SHADOW_HEIGHT = 1024;

    Scene & m_scene;
    Rect tempViewport;
    int tempWidth;
    int tempHeight;
    RenderTarget previousLocation = SCREEN;
};


#endif // GL20DEPTHTEXTURE_H
