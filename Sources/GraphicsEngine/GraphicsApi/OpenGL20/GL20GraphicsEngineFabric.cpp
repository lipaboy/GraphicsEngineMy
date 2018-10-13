#include "GL20GraphicsEngineFabric.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20GraphicsEngine.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20GUI.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20Material.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20Mesh.h"
//#include "GraphicsEngine/GraphicsApi/DirectX11/DX11VertexShader.h"
//#include "GraphicsEngine/GraphicsApi/DirectX11/DX11PixelShader.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20Texture2D.h"
//#include "GraphicsEngine/GraphicsApi/DirectX9/FixedFunctionPipelineDX9.h"

namespace graphics_engine {

GraphicsEngineImpl * GL20GraphicsEngineFabric::CreateEngine()
{
	return new GL20GraphicsEngine();
}

GUIImpl * GL20GraphicsEngineFabric::CreateGUI()
{
	return new GL20GUI();
}

MeshImpl * GL20GraphicsEngineFabric::CreateMesh()
{
	return new GL20Mesh();
}

Texture2DImpl * GL20GraphicsEngineFabric::CreateTexture2D(const char * filepath)
{
    return new GL20Texture2D(filepath);
}

std::shared_ptr<RenderTextureImpl> GL20GraphicsEngineFabric::CreateRenderTexture()
{
    return std::shared_ptr<RenderTextureImpl>(new GL20DepthTexture());
}

MaterialImpl * GL20GraphicsEngineFabric::CreateMaterial(const char * vertexShaderFilePath, const char * fragmentShaderFilePath)
{
	return new GL20Material(vertexShaderFilePath, fragmentShaderFilePath);
}

VertexShaderImpl * GL20GraphicsEngineFabric::CreateVertexShader(const char *)
{
    return nullptr;
}

VertexShaderImpl * GL20GraphicsEngineFabric::CreateVertexShader(const unsigned long *)
{
    return nullptr;
}

PixelShaderImpl * GL20GraphicsEngineFabric::CreatePixelShader(const char *)
{
    return nullptr;
}

PixelShaderImpl * GL20GraphicsEngineFabric::CreatePixelShader(const unsigned long *)
{
    return nullptr;
}

FixedFunctionPipelineImpl * GL20GraphicsEngineFabric::CreateFixedFunctionPipeline()
{
    return nullptr;
}

}
