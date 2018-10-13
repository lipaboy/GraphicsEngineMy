#pragma once
#include "GraphicsEngine/Materials/MaterialLightReflect.h"

namespace graphics_engine {

// Рассчитывает только компоненту diffuse от всех источников света
class MaterialDiffuse : public MaterialLightReflect
{
public:
    MaterialDiffuse();

   // virtual void setShaderFilename();

	virtual void Init(Object * pObject);
	virtual void Deinit();
	
    //virtual void SetMaterial() {
};

}
