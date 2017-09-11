#pragma once
#include "GraphicsEngine/GraphicsApi/PixelShaderImpl.h"


// TODO: Заменить в местах использования на MaterialImpl и удалить данный класс
class PixelShader
{
public:
	PixelShader(const char * fileName);
	PixelShader(const unsigned long * pFunction);
	virtual ~PixelShader();

	void SetShaderBegin();

	void SetShaderVector4(Vector3 vector, float w);
	void SetShaderVector4(Vector4 vector);

	void SetShaderMatrix4x4(Matrix4x4 matrix);
	void SetShaderMatrix4x3(Matrix4x4 matrix);

	void SetTexture(const Texture2D * pTexture);

	void SetShaderEnd();

private:
	PixelShaderImpl * pImpl;
};
