#include "GL20DepthTexture.h"
#include "GraphicsEngine/Screen.h"

void GL20DepthTexture::Init()
{
    glGenFramebuffers(1, &depthMapFBO);

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

}

void GL20DepthTexture::setRenderLocation(RenderLocation location)
{
    switch (location) {

    case DEPTH_TEXTURE:

        if (previousLocation == SCREEN) {
            tempViewport = m_scene.GetCamera().GetViewport();
            tempHeight = Screen::GetHeight();
            tempWidth = Screen::GetWidth();
        }

        // 1. first render to depth map
        m_scene.GetCamera().SetViewport(Rect(0., 0., 1., 1.));
        Screen::SetResolution(SHADOW_WIDTH, SHADOW_HEIGHT);
        //glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        previousLocation = DEPTH_TEXTURE;
        break;

    case SCREEN:
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // 2. then render scene as normal with shadow mapping (using depth map)
        m_scene.GetCamera().SetViewport(tempViewport);
        Screen::SetResolution(tempWidth, tempHeight);
        //glViewport(0, 0, Screen::GetWidth(), Screen::GetHeight());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glClearDepth(1.0f);

        previousLocation = SCREEN;
        break;
    }
}





