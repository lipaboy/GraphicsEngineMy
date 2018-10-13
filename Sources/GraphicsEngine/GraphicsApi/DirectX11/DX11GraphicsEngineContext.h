#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11.h"
#include "GraphicsEngine/GraphicsApi/GraphicsEngineContext.h"

namespace graphics_engine {

#ifdef CAN_USE_DIRECT_X

class DX11GraphicsEngineContext : public GraphicsEngineContext
{
public:
	ID3D11Device *			m_pDevice;
	ID3D11DeviceContext *	m_pImmediateContext;

	DX11GraphicsEngineContext(ID3D11Device * pDevice, ID3D11DeviceContext * pImmediateContext, GraphicsEngineImpl * pImpl)
		: GraphicsEngineContext(pImpl)
	{
		m_pDevice = pDevice;
		m_pImmediateContext = pImmediateContext;
	}
};

#endif

}
