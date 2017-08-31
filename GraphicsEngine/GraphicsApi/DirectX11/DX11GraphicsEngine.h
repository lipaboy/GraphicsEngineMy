#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX11/DX11.h"
#include "GraphicsEngine/GraphicsApi/GraphicsEngineImpl.h"
#include "GraphicsEngine/PlatformApi/Windows/WinWindow.h"
#include "GraphicsEngine/Matrix4x4.h"


class DX11GraphicsEngine : public GraphicsEngineImpl
{	
public:

	DX11GraphicsEngine();

	// Register class and create window
	void Init();
	
	// Clean up the objects we've created
	void Deinit();
		
	// Render a frame
	void Render();

	bool IsRunning();

	void SetViewport(Rect rect);
	void SetResolution(int width, int height);

private:
	// Create Direct3D device and swap chain
	HRESULT InitDevice();

	WinWindow	m_window;

	const TCHAR * m_pWindowTitle;

	int m_width;
	int m_height;

	ID3D11Device *				m_pDevice;
	ID3D11DeviceContext *		m_pImmediateContext;
	IDXGISwapChain *			m_pSwapChain;
	ID3D11RenderTargetView *	m_pRenderTargetView;
	ID3D11Texture2D *			m_pDepthStencil;
	ID3D11DepthStencilView *	m_pDepthStencilView;
	ID3D11RasterizerState *		m_pRasterizerState;
	
	Rect	m_viewportRect;	
};

#endif
