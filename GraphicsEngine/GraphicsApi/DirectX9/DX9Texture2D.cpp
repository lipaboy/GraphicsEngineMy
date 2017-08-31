#include "DX9Texture2D.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngineContext.h"


DX9Texture2D::DX9Texture2D(const char * filepath)
{
	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX9GraphicsEngineContext * pDX9Context = static_cast<const DX9GraphicsEngineContext *>( pContext );
	m_pDevice = pDX9Context->m_pDevice;

	D3DXCreateTextureFromFileA( m_pDevice, filepath, &m_pTexture );

	m_useMipMaps = false;
	m_useAniso = false;
	
	SetFilterMode(TEXTURE_FILTER_MODE_POINT);
	
	// TODO: Release resources at destructor
}

void DX9Texture2D::SetFilterMode(TextureFilterMode filterMode)
{
	// https://msdn.microsoft.com/en-us/library/windows/desktop/bb172615(v=vs.85).aspx
	// https://msdn.microsoft.com/en-us/library/windows/desktop/bb172264(v=vs.85).aspx
	// http://www.toymaker.info/Games/html/textures.html

	m_filterMode = filterMode;

	if (m_filterMode == TEXTURE_FILTER_MODE_POINT)
	{
		m_filterType = D3DTEXF_POINT;
		m_useMipMaps = false;
		m_useAniso = false;
	}
	else if (m_filterMode == TEXTURE_FILTER_MODE_BILINEAR)
	{
		// TODO: Task05
	}
	else if (m_filterMode == TEXTURE_FILTER_MODE_TRILINEAR)
	{
		// TODO: Task05
	}
	else if (m_filterMode == TEXTURE_FILTER_MODE_ANISOTROPIC)
	{		
		// TODO: Task05
	}	
}

void DX9Texture2D::SetTexture(int textureRegister) const
{
	m_pDevice->SetTexture( textureRegister, m_pTexture );
	
	// Set filter mode (Point, Bilinear, Trilinear, Anisotropic)
	m_pDevice->SetSamplerState( textureRegister, D3DSAMP_MINFILTER, m_filterType );
	m_pDevice->SetSamplerState( textureRegister, D3DSAMP_MAGFILTER, m_filterType );
	
	// Set degree of anisotropic filtering (aniso level)
	// TODO: Task05
		
	// Enable/Disable mip maps
	// TODO: Task05
}

#endif
