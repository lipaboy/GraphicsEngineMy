#include "DX9GraphicsEngineFabric.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngine.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GUI.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9Material.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9Mesh.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9VertexShader.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9PixelShader.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9Texture2D.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9FixedFunctionPipeline.h"


GraphicsEngineImpl * DX9GraphicsEngineFabric::CreateEngine()
{
	return new DX9GraphicsEngine();
}

GUIImpl * DX9GraphicsEngineFabric::CreateGUI()
{
	return new DX9GUI();
}

MeshImpl * DX9GraphicsEngineFabric::CreateMesh()
{
	return new DX9Mesh();
}

Texture2DImpl * DX9GraphicsEngineFabric::CreateTexture2D(const char * filepath)
{
	return new DX9Texture2D(filepath);
}

MaterialImpl * DX9GraphicsEngineFabric::CreateMaterial(const char * vertexShaderFilePath, const char * fragmentShaderFilePath)
{
	return new DX9Material(vertexShaderFilePath, fragmentShaderFilePath);
}

VertexShaderImpl * DX9GraphicsEngineFabric::CreateVertexShader(const char * filepath)
{
	return new DX9VertexShader(filepath);
}

VertexShaderImpl * DX9GraphicsEngineFabric::CreateVertexShader(const unsigned long * pFunction)
{
	return new DX9VertexShader(pFunction);
}

PixelShaderImpl * DX9GraphicsEngineFabric::CreatePixelShader(const char * filepath)
{
	return new DX9PixelShader(filepath);
}

PixelShaderImpl * DX9GraphicsEngineFabric::CreatePixelShader(const unsigned long * pFunction)
{
	return new DX9PixelShader(pFunction);
}

FixedFunctionPipelineImpl * DX9GraphicsEngineFabric::CreateFixedFunctionPipeline()
{
	return new DX9FixedFunctionPipeline();
}

#endif
