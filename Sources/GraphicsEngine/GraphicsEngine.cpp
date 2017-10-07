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
}

void GraphicsEngine::Deinit()
{
	pGraphicsEngineImpl->Deinit();
}

void GraphicsEngine::Render()
{
    Time::Update();

    // Set viewport of current camera
//    {
//        Rect viewport = m_pCamera->GetViewport();
//        pGraphicsEngineImpl->SetViewport(viewport);
//    }

    pGraphicsEngineImpl -> Render();
}

bool GraphicsEngine::IsRunning()
{
	return pGraphicsEngineImpl->IsRunning();
}
