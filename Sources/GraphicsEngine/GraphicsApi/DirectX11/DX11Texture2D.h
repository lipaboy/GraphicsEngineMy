#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX11/DX11.h"
#include "GraphicsEngine/GraphicsApi/Texture2DImpl.h"
#include <Windows.h>


class DX11Texture2D : public Texture2DImpl
{
public:
	DX11Texture2D(const char * filepath);

	void SetFilterMode(TextureFilterMode filterMode);
	void SetTexture(int textureRegister) const;

private:
	ID3D11Device *				m_pDevice;
	ID3D11DeviceContext *		m_pDeviceContext;
	ID3D11ShaderResourceView *	m_pTexture;
	ID3D11SamplerState *		m_pSamplerState;
};

#endif
