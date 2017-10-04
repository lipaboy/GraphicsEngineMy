#include "GraphicsEngine.h"
#include "GraphicsEngineFabric.h"
#include "GraphicsEngine/Time.h"
#include <cstddef>


GraphicsEngine * GraphicsEngine::pEngine = NULL;

GraphicsEngine & GraphicsEngine::Instance()
{
	if (NULL == pEngine)
	{
		pEngine = new GraphicsEngine();
	}

	return *pEngine;
}

GraphicsEngine::GraphicsEngine()
{
}

void GraphicsEngine::Init()
{
	pGraphicsEngineImpl = GraphicsEngineFabric::CreateEngine();
	pGraphicsEngineImpl->Init();

    pRenderTextureImpl = GraphicsEngineFabric::CreateRenderTexture();
    pRenderTextureImpl -> Init();
}

void GraphicsEngine::Deinit()
{
	pGraphicsEngineImpl->Deinit();
}

void GraphicsEngine::Render()
{
	Time::Update();

    pRenderTextureImpl -> setRenderLocation(DEPTH_TEXTURE);

    // Set camera at light source

    Scene & m_scene = Application::Instance().GetScene();

    Camera & camera = m_scene.GetCamera();
    Transform transformTemp(*(camera.GetObjectPtr()->m_pTransform));
    const std::list<const Light *> & lights = m_scene.GetLights();
    Transform * cameraTransform = camera.GetConstObjectPtr()->m_pTransform;
    Transform * lightTransform ((lights.front() -> GetConstObjectPtr() -> m_pTransform));

    cameraTransform -> SetPosition(-20 * lightTransform->GetForward());
    cameraTransform -> SetEulerAngles(lightTransform->GetEulerAngles());
    cameraTransform -> Rotate(0, 180, 0);
   // cameraTransform -> RotateByOperator(//lightTransform->GetUp()
        //                                cameraTransform->GetUp(), PI);

    camera.isPerspective = false;

    // Render
    pGraphicsEngineImpl -> RenderWithoutMainLoopEvent();

    //camera.GetObjectPtr()->m_pTransform = transformTemp;
    cameraTransform->SetPosition(transformTemp.GetPosition());
    cameraTransform->SetEulerAngles(transformTemp.GetEulerAngles());
    // cameraTransform -> RotateByOperator(lightTransform->GetUp(), PI);
    camera.isPerspective = true;

    pRenderTextureImpl -> setRenderLocation(SCREEN);
    pGraphicsEngineImpl -> Render();
}

bool GraphicsEngine::IsRunning()
{
	return pGraphicsEngineImpl->IsRunning();
}
