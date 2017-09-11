#pragma once
#include "GraphicsEngine/GraphicsApi/VertexShaderImpl.h"


// TODO: Заменить в местах использования на MaterialImpl и удалить данный класс
class VertexShader
{
public:
	VertexShader(const char * fileName);
	VertexShader(const unsigned long * pFunction);

	void SetShaderBegin();
	
	void SetShaderVector4(Vector3 vector, float w);
	void SetShaderVector4(Vector4 vector);

	void SetShaderMatrix4x4(Matrix4x4 matrix);
	void SetShaderMatrix4x3(Matrix4x4 matrix);
	
	void SetShaderEnd();

private:
	VertexShaderImpl * pImpl;
};
