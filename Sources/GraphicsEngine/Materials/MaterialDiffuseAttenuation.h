#pragma once

#include "MaterialLightReflect.h"

namespace graphics_engine {

class MaterialDiffuseAttenuation : public MaterialLightReflect
{
public:
    MaterialDiffuseAttenuation();

    virtual void Init(Object * pObject) { MaterialLightReflect::Init(pObject); }
    virtual void Deinit() { MaterialLightReflect::Deinit(); }
};

}
