#include "GL20DepthTexture.h"


void GL20DepthTexture::Init(const Rect &viewPort)
{
    glGenFramebuffers(1, &depthMapFBO);

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void GL20DepthTexture::setRenderLocation(RenderLocation location)
{
    switch (location) {

    case DEPTH_TEXTURE:
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
        // TODO: bad error catching
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cerr << "GL FrameBuffer isn't complete" << std::endl;
            return;
        }
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 1. first render to depth map
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
            glClear(GL_DEPTH_BUFFER_BIT);

    //        ConfigureShaderAndMatrices();
    //        RenderScene();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        break;

    case SCREEN:
        // 2. then render scene as normal with shadow mapping (using depth map)
        glViewport(0, 0, viewPort.w, viewPort.h);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       // ConfigureShaderAndMatrices();

        glBindTexture(GL_TEXTURE_2D, depthMap);

        //RenderScene();
        break;
    }
}





