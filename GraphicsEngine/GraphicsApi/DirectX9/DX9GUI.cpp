#include "DX9GUI.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngineContext.h"
#include "GraphicsEngine/Application.h"

LPDIRECT3DDEVICE9	DX9GUI::m_pDevice	= NULL;
ID3DXFont *			DX9GUI::m_pFont		= NULL;

void DX9GUI::Init()
{
	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX9GraphicsEngineContext * pDX9Context = static_cast<const DX9GraphicsEngineContext *>( pContext );
	m_pDevice = pDX9Context->m_pDevice;
}

void DX9GUI::Label(int x, int y, int w, int h, const char * pText)
{

}

#endif
