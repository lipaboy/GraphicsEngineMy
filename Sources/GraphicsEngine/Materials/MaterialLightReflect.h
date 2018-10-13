#pragma once

#include "GraphicsEngine/Materials/Material.h"

namespace graphics_engine {

//TODO: make it abstract class

// It is commonality of classes Material that calculate components from each light sources
class MaterialLightReflect : public Material
{
public:
    MaterialLightReflect(float red = 1.f, float green = 1.f, float blue = 1.f) :
        ambientColor(red, green, blue) {}

//    virtual void setShaderFilename() = 0;

    virtual void Init(Object * pObject);
    virtual void Deinit();

    virtual void SetMaterial();

private:
    Vector3 ambientColor;
};

}
