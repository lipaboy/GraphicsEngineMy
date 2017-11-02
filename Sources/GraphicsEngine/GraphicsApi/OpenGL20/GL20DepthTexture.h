#ifndef GL20DEPTHTEXTURE_H
#define GL20DEPTHTEXTURE_H

#include <iostream>

#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20.h"
#include "GraphicsEngine/Rect.h"
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/SceneUtils.h"

#include "GraphicsEngine/GraphicsApi/RenderTextureImpl.h"

class GL20DepthTexture : public RenderTextureImpl
{
public:
    GL20DepthTexture() : m_scene(Application::Instance().GetScene()) {}

    void Init();
    void Deinit();

    void SetRenderTarget(RenderTarget location);
    RenderTarget GetRenderTarget() const { return previousLocation; }

public:
    static constexpr uint32_t MAX_LIGHT_COUNT = SceneUtils::MAX_LIGHT_COUNT;
    GLuint depthMapFBO[MAX_LIGHT_COUNT];
    GLuint depthMap[MAX_LIGHT_COUNT];

    const unsigned int SHADOW_WIDTH = 1024;
    const unsigned int SHADOW_HEIGHT = 1024;

    Scene & m_scene;
    Rect tempViewport;
    int tempWidth;
    int tempHeight;
    RenderTarget previousLocation = SCREEN;
};


#endif // GL20DEPTHTEXTURE_H
