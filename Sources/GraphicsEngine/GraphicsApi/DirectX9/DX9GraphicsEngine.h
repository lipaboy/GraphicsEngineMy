#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX9/DX9.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/GraphicsApi/GraphicsEngineImpl.h"
#include "GraphicsEngine/PlatformApi/Windows/WinWindow.h"


class DX9GraphicsEngine : public GraphicsEngineImpl
{
public:
	DX9GraphicsEngine();

	void Init();
	void Deinit();

	void Render();
	bool IsRunning();

	void SetViewport(Rect rect);
	void SetResolution(int width, int height);

private:
	HRESULT InitDevice();
	

	LPDIRECT3D9				m_pD3D;
	LPDIRECT3DDEVICE9		m_pDevice;
	D3DPRESENT_PARAMETERS	m_d3dpp;

	WinWindow	m_window;

	int m_width;
	int m_height;

	Scene & m_scene;
};

#endif
