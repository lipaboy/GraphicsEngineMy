#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX9/DX9.h"
#include "GraphicsEngine/GraphicsApi/PixelShaderImpl.h"


class DX9PixelShader : public PixelShaderImpl
{
public:
	// TODO: Заменить в проекте LPCWSTR на LPCTSTR
	DX9PixelShader(const char * fileName);
	DX9PixelShader(const unsigned long * pFunction);

	bool IsInited();

	void SetShaderBegin();

	void SetShaderVector4(Vector3 vector, float w);
	void SetShaderVector4(Vector4 vector);

	void SetShaderMatrix4x4(Matrix4x4 matrix);
	void SetShaderMatrix4x3(Matrix4x4 matrix);

	void SetTexture(const Texture2D * pTexture);

	void SetShaderEnd();

private:
	bool m_isInited;

	LPDIRECT3DDEVICE9				m_pDevice;
	LPDIRECT3DPIXELSHADER9			m_pPShader;

	int m_startRegister;
	int m_textureRegister;
};

#endif
