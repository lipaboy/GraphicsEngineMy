#pragma once
#include "GraphicsEngine/GraphicsApi/GraphicsEngineContext.h"
#include "GraphicsEngine/GraphicsApi/GraphicsEngineImpl.h"

#include "GraphicsEngine/Camera.h"
#include "Application.h"
#include "Transform.h"
#include "Light.h"

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

	GraphicsEngine();
	GraphicsEngine( const GraphicsEngine & );
	static GraphicsEngine * pEngine;
};
