#pragma once
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/GraphicsApi/FixedFunctionPipelineImpl.h"

namespace graphics_engine {

class MaterialTask01 : public Material
{
public:
	virtual void Init(Object * pObject);
	virtual void Deinit();
	virtual void SetMaterial();

private:
	FixedFunctionPipelineImpl * pImpl;
};

}
