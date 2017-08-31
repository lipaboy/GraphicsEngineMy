#include "DX9GraphicsEngine.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GUI.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngineContext.h"
#include "GraphicsEngine/Time.h"


DX9GraphicsEngine * pDX9Engine = NULL;


DX9GraphicsEngine::DX9GraphicsEngine()
	:	m_scene( Application::Instance().GetScene() ),
		m_window( TEXT("Graphics Engine (DirectX 9)") )
{

}

void DX9GraphicsEngine::Init()
{
	m_window.Init(this);

    // Initialize Direct3D
    if( SUCCEEDED( InitDevice() ) )
    {
		m_window.Show();
    }

	m_scene.Init();

	pDX9Engine = this;
}

void DX9GraphicsEngine::Deinit()
{
	pDX9Engine = NULL;

	m_scene.Deinit();

	if( m_pDevice != NULL )
        m_pDevice->Release();

	m_window.Deinit();
}

void DX9GraphicsEngine::Render()
{
	m_window.DispatchMessages();
    
	if (IsRunning())
	{
		// Clear the backbuffer to a dark blue color
		m_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 32, 80 ), 1.0f, 0 );
				
		// Clear the z-buffer
		m_pDevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0 );

		// Begin the scene
		if( SUCCEEDED( m_pDevice->BeginScene() ) )
		{
			m_scene.Update();
			m_scene.Render();

			GUI::Update();

			// End the scene
			m_pDevice->EndScene();
		}

		// Present the backbuffer contents to the display
		m_pDevice->Present( NULL, NULL, NULL, NULL );
	}
}

bool DX9GraphicsEngine::IsRunning()
{
	return m_window.IsRunning();
}

void DX9GraphicsEngine::SetViewport(Rect rect)
{
	// https://msdn.microsoft.com/en-us/library/windows/desktop/bb174469(v=vs.85).aspx

	D3DVIEWPORT9 vp;
	{
		vp.X      = static_cast<DWORD>( rect.x * m_width  );
		vp.Y      = static_cast<DWORD>( rect.y * m_height );
		vp.Width  = static_cast<DWORD>( rect.w * m_width  );
		vp.Height = static_cast<DWORD>( rect.h * m_height );
		vp.MinZ   = 0.0f;
		vp.MaxZ   = 1.0f;
	}

	m_pDevice->SetViewport( &vp );
}


HRESULT DX9GraphicsEngine::InitDevice()
{
	m_window.GetResolution(m_width, m_height);	

    // Create the D3D object.
    if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice
    {
		ZeroMemory( &m_d3dpp, sizeof( m_d3dpp ) );
		m_d3dpp.Windowed				= TRUE;
		m_d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
		// Set z-buffer parameters
		m_d3dpp.BackBufferFormat		= D3DFMT_UNKNOWN;
		m_d3dpp.EnableAutoDepthStencil	= TRUE;
		m_d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;
	}

    // Create the D3DDevice
    if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_window.GetHWND(),
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &m_d3dpp, &m_pDevice ) ) )
    {
        return E_FAIL;
    }

	Application::Instance().SetContext( new DX9GraphicsEngineContext(m_pDevice, this) );
	
	// Set primitive type to draw
	{
		// Draw polygons only (is used usual)
		m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

		// Draw edges only (is used for debug)
		//m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	
	// Set culling mode
	{
		// Draw only front polygons (CW) == Cull back polygons (CCW)
		// CCW = Conter Clock Wise
		// CW = Clock Wise
		m_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	
		// Draw front and back polygons == Turn off culling
		//m_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	}
	
    // Turn off D3D lighting, since we are providing our own vertex colors
    m_pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// Turn on the z-buffer
	m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	
    return S_OK;
}

void DX9GraphicsEngine::SetResolution(int width, int height)
{
	if (m_width == width && m_height == height)
	{
		return;
	}

	m_width	= width;
	m_height = height;

	m_d3dpp.BackBufferCount  = 1;
	m_d3dpp.BackBufferWidth  = m_width;
	m_d3dpp.BackBufferHeight = m_height;

	HRESULT hr = m_pDevice->Reset(&m_d3dpp);
		
	if (D3DERR_INVALIDCALL == hr)
	{
		int i = 0;
	}
}

#endif
