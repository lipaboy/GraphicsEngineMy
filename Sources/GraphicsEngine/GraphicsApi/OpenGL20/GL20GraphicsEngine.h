#pragma once
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20.h"
#include "GraphicsEngine/GraphicsApi/GraphicsEngineImpl.h"
#include "GraphicsEngine/Scene.h"

#include "GraphicsEngine/GraphicsApi/RenderTextureImpl.h"
#include <memory>
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/Lights/Light.h"

namespace graphics_engine {

class GL20GraphicsEngine : public GraphicsEngineImpl
{
public:
	GL20GraphicsEngine();

	void Init();
	void Deinit();

	void Render();
    void RenderWithoutMainLoopEvent();
	bool IsRunning();

	void SetViewport(Rect rect);
	void SetResolution(int width, int height);

	// TODO: —делать private
	void Render1();
	void Reshape(int w, int h);

private:
	const char * m_pWindowTitle;
	int m_window;
	
    //std::shared_ptr<RenderTextureImpl> pRenderTextureImpl;
    //ShadowMaterial * pShadowMaterial;

	Rect m_viewportRect;
    bool isSwapBuffers = true;

	Scene & m_scene;
};

}
