#ifndef GL20DEPTHTEXTURE_H
#define GL20DEPTHTEXTURE_H

#include <iostream>

#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20.h"
#include "GraphicsEngine/Rect.h"

enum RenderLocation {
    SCREEN,
    DEPTH_TEXTURE
};

class GL20DepthTexture
{
public:

    void Init();
    //void Deinit();

    void setRenderLocation(RenderLocation location);

private:
    GLuint depthMapFBO;
    GLuint depthMap;

    const unsigned int SHADOW_WIDTH = 1024;
    const unsigned int SHADOW_HEIGHT = 1024;
};


#endif // GL20DEPTHTEXTURE_H
