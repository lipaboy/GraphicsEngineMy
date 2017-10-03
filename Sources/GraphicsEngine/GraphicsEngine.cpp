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

    // Set camera at light source

    pRenderTextureImpl -> setRenderLocation(DEPTH_TEXTURE);
	pGraphicsEngineImpl->Render();
    pRenderTextureImpl -> setRenderLocation(SCREEN);
    pGraphicsEngineImpl->Render();
}

bool GraphicsEngine::IsRunning()
{
	return pGraphicsEngineImpl->IsRunning();
}
