#include "GL20DepthTexture.h"
#include "GraphicsEngine/Screen.h"

void GL20DepthTexture::Init()
{
    glGenFramebuffers(MAX_LIGHT_COUNT, depthMapFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO[0]);

    glGenTextures(MAX_LIGHT_COUNT, depthMap);
    for (int i = 0; i < 2; i++) {
        glBindTexture(GL_TEXTURE_2D, depthMap[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap[i], 0);
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
    }



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
    // tempViewport = m_scene.GetCamera().GetViewport();
}

void GL20DepthTexture::Deinit()
{
    glDeleteTextures(MAX_LIGHT_COUNT, depthMap);
    glDeleteFramebuffers(MAX_LIGHT_COUNT, depthMapFBO);
}

void GL20DepthTexture::SetRenderTarget(RenderTarget location)
{
    static int currTexture = 0;

    switch (location) {

    case DEPTH_TEXTURE:

        if (previousLocation == SCREEN) {
            currTexture = 0;
            if (previousLocation == SCREEN) {
                tempViewport = m_scene.GetCamera().GetViewport();
                tempHeight = Screen::GetHeight();
                tempWidth = Screen::GetWidth();
            }

            // 1. first render to depth map
            m_scene.GetCamera().SetViewport(Rect(0., 0., 1., 1.));
            Screen::SetResolution(SHADOW_WIDTH, SHADOW_HEIGHT);
            //glActiveTexture(GL_TEXTURE0);
            glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO[currTexture]);
            glClear(GL_DEPTH_BUFFER_BIT);
        }
        else {
            glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO[++currTexture]);
            glClear(GL_DEPTH_BUFFER_BIT);
        }

        previousLocation = DEPTH_TEXTURE;
        break;

    case SCREEN:
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // 2. then render scene as normal with shadow mapping (using depth map)
        m_scene.GetCamera().SetViewport(tempViewport);
        Screen::SetResolution(tempWidth, tempHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap[1]);
        glClearDepth(1.0f);

        previousLocation = SCREEN;
        break;
    }
}





