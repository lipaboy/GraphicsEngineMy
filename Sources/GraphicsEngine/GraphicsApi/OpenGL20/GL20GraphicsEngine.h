﻿#pragma once
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20.h"
#include "GraphicsEngine/GraphicsApi/GraphicsEngineImpl.h"
#include "GraphicsEngine/Scene.h"

#include "GL20DepthTexture.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/gl20shadowmaterial.h"


class GL20GraphicsEngine : public GraphicsEngineImpl
{
public:
	GL20GraphicsEngine();

	void Init();
	void Deinit();

	void Render();
	bool IsRunning();

	void SetViewport(Rect rect);
	void SetResolution(int width, int height);

	// TODO: —делать private
	void Render1();
	void Reshape(int w, int h);

private:
	const char * m_pWindowTitle;
	int m_window;
	
    ShadowMaterial shadowMaterial;
    GL20DepthTexture depthTexture;
	Rect m_viewportRect;

	Scene & m_scene;
};
