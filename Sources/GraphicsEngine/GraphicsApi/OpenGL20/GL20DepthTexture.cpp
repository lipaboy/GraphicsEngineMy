#include "GL20DepthTexture.h"

#include "GraphicsEngine/Camera.h"

#include <iostream>
#include <QDebug>


void GL20DepthTexture::Init()
{
    //--------------------For flat shadow mapping--------------------//

    glGenFramebuffers(1, &depthMapFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_REPEAT
                    //GL_CLAMP
                    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                    GL_REPEAT
                    //GL_CLAMP
                    );

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    // TODO: bad error catching
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "GL FrameBuffer isn't complete" << std::endl;
        return;
    }
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    tempWidth = Screen::GetWidth();
    tempHeight = Screen::GetHeight();
    // doesn't work
    //tempViewport = m_scene.GetCamera().GetViewport();


    //--------------------For cude shadow mapping-------------------//


    // create depth cubemap texture
//    glGenTextures(1, &depthCubemap);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
//    for (unsigned int i = 0; i < 6; ++i)
//        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
//                     SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

//    depthCubemapFBO = 0;
//    glGenFramebuffers(1, &depthCubemapFBO);   // 1 - count of framebuffers that must be generated
//    // attach depth texture as FBO's depth buffer
//    glBindFramebuffer(GL_FRAMEBUFFER, depthCubemapFBO);

////    glEnable              ( GL_DEBUG_OUTPUT );
////    glDebugMessageCallback( (GLDEBUGPROC) MessageCallback, 0 );
//        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
//            std::cerr << "GL FrameBuffer isn't complete" << std::endl;
//            //return;
//        }
//    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);

//    glDrawBuffer(GL_NONE);
//    glReadBuffer(GL_NONE);
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GL20DepthTexture::Deinit()
{
    glDeleteTextures(1, &depthMap);
    glDeleteFramebuffers(1, &depthMapFBO);
//    glDeleteTextures(2, &depthCubemap);
   // glDeleteFramebuffers(2, &depthCubemapFBO);
}

void GL20DepthTexture::SetRenderTarget(RenderTarget location)
{
    switch (location) {

    case DEPTH_FLAT_TEXTURE:
        if (previousLocation == SCREEN) {
            tempViewport = m_scene.GetCamera().GetViewport();
            tempHeight = Screen::GetHeight();
            tempWidth = Screen::GetWidth();
        }

        // 1. first render to depth map
        m_scene.GetCamera().SetViewport(Rect(0., 0., 1., 1.));
        Screen::SetResolution(SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        previousLocation = DEPTH_FLAT_TEXTURE;
        break;

    case DEPTH_CUBEMAP_TEXTURE:
        if (previousLocation == SCREEN) {
            tempViewport = m_scene.GetCamera().GetViewport();
            tempHeight = Screen::GetHeight();
            tempWidth = Screen::GetWidth();
        }

        // 1. first render to depth map
        m_scene.GetCamera().SetViewport(Rect(0., 0., 1., 1.));
        Screen::SetResolution(SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthCubemapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        previousLocation = DEPTH_CUBEMAP_TEXTURE;
        break;

    case SCREEN:
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // 2. then render scene as normal with shadow mapping (using depth map)
        m_scene.GetCamera().SetViewport(tempViewport);
        Screen::SetResolution(tempWidth, tempHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (previousLocation == DEPTH_FLAT_TEXTURE)
            glBindTexture(GL_TEXTURE_2D, depthMap);
        else
            glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
        glClearDepth(1.0f);

        previousLocation = SCREEN;
        break;
    }
}





