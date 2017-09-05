#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX9/DX9.h"
#include "GraphicsEngine/GraphicsApi/Texture2DImpl.h"
#include <Windows.h>


class DX9Texture2D : public Texture2DImpl
{
public:
	DX9Texture2D(const char * filepath);

	void SetFilterMode(TextureFilterMode filterMode);
	void SetTexture(int textureRegister) const;

private:
	LPDIRECT3DDEVICE9		m_pDevice;
	LPDIRECT3DTEXTURE9		m_pTexture;
	D3DTEXTUREFILTERTYPE	m_filterType;

	TextureFilterMode		m_filterMode;
	bool					m_useMipMaps;
	bool					m_useAniso;
};

#endif
