#include "VertexShader.h"
#include "GraphicsEngine/GraphicsEngineFabric.h"


VertexShader::VertexShader(const char * fileName)
{
	pImpl = GraphicsEngineFabric::CreateVertexShader(fileName);
}

VertexShader::VertexShader(const unsigned long * pFunction)
{
	pImpl = GraphicsEngineFabric::CreateVertexShader(pFunction);
}

void VertexShader::SetShaderBegin()
{
	pImpl->SetShaderBegin();
}

void VertexShader::SetShaderVector4(Vector3 vector, float w)
{
	pImpl->SetShaderVector4(vector, w);
}

void VertexShader::SetShaderVector4(Vector4 vector)
{
	pImpl->SetShaderVector4(vector);
}

void VertexShader::SetShaderMatrix4x4(Matrix4x4 matrix)
{
	pImpl->SetShaderMatrix4x4(matrix);
}

void VertexShader::SetShaderMatrix4x3(Matrix4x4 matrix)
{
	pImpl->SetShaderMatrix4x3(matrix);
}

void VertexShader::SetShaderEnd()
{
	pImpl->SetShaderEnd();
}
