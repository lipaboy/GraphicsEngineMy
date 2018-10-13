#pragma once
#include "GraphicsEngine/Rect.h"

namespace graphics_engine {

class GraphicsEngineImpl
{
public:
	virtual void Init() = 0;
	virtual void Deinit() = 0;

	virtual void Render() = 0;
    // Crutch
    virtual void RenderWithoutMainLoopEvent() = 0;   // For OpenGL ( without calling glutMainLoopEvent() )
	virtual bool IsRunning() = 0;

	virtual void SetViewport(Rect rect) = 0;
	virtual void SetResolution(int width, int height) = 0;
};

}
