#pragma once

#include "Material.h"

#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/MathUtils.h"

namespace graphics_engine {

class MaterialShadowMappingDepth : public Material
{
public:
    MaterialShadowMappingDepth();

    virtual void Init(Object * pObject);
    virtual void Deinit();

    virtual void SetMaterial();
};

}
