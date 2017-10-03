#pragma once
#include "GraphicsEngine/GraphicsApi/GraphicsEngineContext.h"
#include "GraphicsEngine/GraphicsApi/GraphicsEngineImpl.h"

#include "GraphicsEngine/GraphicsApi/RenderTextureImpl.h"
#include <memory>

class GraphicsEngine
{
public:
	static GraphicsEngine & Instance();

	void Init();
	void Deinit();

	void Render();
	bool IsRunning();
	
private:
	// TODO: Сделать по всему проекту префикс m_ (почитать С++ code style)
	GraphicsEngineImpl * pGraphicsEngineImpl;
    std::shared_ptr<RenderTextureImpl> pRenderTextureImpl;

	GraphicsEngine();
	GraphicsEngine( const GraphicsEngine & );
	static GraphicsEngine * pEngine;
};
