#include "DX11Texture2D.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11GraphicsEngineContext.h"


DX11Texture2D::DX11Texture2D(const char * filepath)
{
	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX11GraphicsEngineContext * pDX11Context = static_cast<const DX11GraphicsEngineContext *>( pContext );
	m_pDevice = pDX11Context->m_pDevice;
	// TODO: Rename m_pImmediateContext to m_pDeviceContext
	m_pDeviceContext = pDX11Context->m_pImmediateContext;

	// Load the Texture
	HRESULT hr = D3DX11CreateShaderResourceViewFromFileA( m_pDevice, filepath, NULL, NULL, &m_pTexture, NULL );
    if( FAILED( hr ) )
        return;

	m_pSamplerState = NULL;
	SetFilterMode(TEXTURE_FILTER_MODE_POINT);

	// TODO: Release resources at destructor
}

void DX11Texture2D::SetFilterMode(TextureFilterMode filterMode)
{
	// http://www.3dgep.com/texturing-lighting-directx-11/
	// https://msdn.microsoft.com/en-us/library/dn642451.aspx
	// http://gamedev.stackexchange.com/questions/66231/set-sampler-states-linear-bilinear-trilinear-filtering-interpolation

	if (NULL != m_pSamplerState)
	{
		m_pSamplerState->Release();
		m_pSamplerState = NULL;
	}

	D3D11_FILTER filter;

	if (filterMode == TEXTURE_FILTER_MODE_POINT)
	{
		filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	}
	else if (filterMode == TEXTURE_FILTER_MODE_BILINEAR)
	{
		// TODO: Task05
	}
	else if (filterMode == TEXTURE_FILTER_MODE_TRILINEAR)
	{
		// TODO: Task05
	}
	else if (filterMode == TEXTURE_FILTER_MODE_ANISOTROPIC)
	{
		// TODO: Task05
	}
	
	// Create the sample state
    D3D11_SAMPLER_DESC sampDesc;
	{
		ZeroMemory( &sampDesc, sizeof(sampDesc) );
		sampDesc.Filter			= filter;
		sampDesc.AddressU		= D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV		= D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW		= D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc	= D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD			= 0;
		sampDesc.MaxLOD			= 0;
		sampDesc.MaxAnisotropy	= 0;
	}
    HRESULT hr = m_pDevice->CreateSamplerState( &sampDesc, &m_pSamplerState );
	if( FAILED( hr ) )
	{
		m_pSamplerState = NULL;   
	}
}

void DX11Texture2D::SetTexture(int textureRegister) const
{
	m_pDeviceContext->PSSetShaderResources( textureRegister, 1, &m_pTexture );
    m_pDeviceContext->PSSetSamplers( textureRegister, 1, &m_pSamplerState );
}

#endif
