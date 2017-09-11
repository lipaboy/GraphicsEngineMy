#include "PixelShader.h"
#include "GraphicsEngine/GraphicsEngineFabric.h"


PixelShader::PixelShader(const char * fileName)
{
	pImpl = GraphicsEngineFabric::CreatePixelShader(fileName);
}

PixelShader::PixelShader(const unsigned long * pFunction)
{
	pImpl = GraphicsEngineFabric::CreatePixelShader(pFunction);
}

PixelShader::~PixelShader()
{
	delete pImpl;
	pImpl = NULL;
}

void PixelShader::SetShaderBegin()
{
	pImpl->SetShaderBegin();
}

void PixelShader::SetShaderVector4(Vector3 vector, float w)
{
	pImpl->SetShaderVector4(vector, w);
}

void PixelShader::SetShaderVector4(Vector4 vector)
{
	pImpl->SetShaderVector4(vector);
}

void PixelShader::SetShaderMatrix4x4(Matrix4x4 matrix)
{
	pImpl->SetShaderMatrix4x4(matrix);
}

void PixelShader::SetShaderMatrix4x3(Matrix4x4 matrix)
{
	pImpl->SetShaderMatrix4x3(matrix);
}

// Передача на видеокарту Текстуры и Способа фильтрации (билинейная, анизотропная)
void PixelShader::SetTexture(const Texture2D * pTexture)
{
	pImpl->SetTexture(pTexture);
}

void PixelShader::SetShaderEnd()
{
	pImpl->SetShaderEnd();
}
