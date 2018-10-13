#pragma once
#include "GraphicsEngine/GraphicsApi/GraphicsEngineFabricImpl.h"

#include "GraphicsEngine/GraphicsApi/RenderTextureImpl.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20DepthTexture.h"
#include <memory>

namespace graphics_engine {

// Class implements an interface GraphicsEngineFabricImpl in OpenGL20.
// Class creates objects listed below if OpenGL20 is chosen as Graphics API
// Design Patterns: Abstract Factory (role - Concrete Factory).
class GL20GraphicsEngineFabric : public GraphicsEngineFabricImpl
{
public:
	GraphicsEngineImpl *	CreateEngine();

	GUIImpl *				CreateGUI();

	MeshImpl *				CreateMesh();
	
	Texture2DImpl *			CreateTexture2D(const char * filepath);
    std::shared_ptr<RenderTextureImpl>
                            CreateRenderTexture();

	MaterialImpl *			CreateMaterial(const char * vertexShaderFilePath, const char * fragmentShaderFilePath);
	
	VertexShaderImpl *		CreateVertexShader(const char * filepath);
	VertexShaderImpl *		CreateVertexShader(const unsigned long * pFunction);
	
	PixelShaderImpl *		CreatePixelShader(const char * filepath);
	PixelShaderImpl *		CreatePixelShader(const unsigned long * pFunction);
	
	FixedFunctionPipelineImpl * CreateFixedFunctionPipeline();
};

}
