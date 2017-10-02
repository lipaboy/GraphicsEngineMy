#ifndef MATERIALSPECULAR_H
#define MATERIALSPECULAR_H

#include "MaterialLightReflect.h"

class MaterialDiffuseSpecular : public MaterialLightReflect
{
public:
    MaterialDiffuseSpecular(float red = 1.f, float green = 1.f, float blue = 1.f);

    virtual void Init(Object * pObject) { MaterialLightReflect::Init(pObject); }
    virtual void Deinit() { MaterialLightReflect::Deinit(); }
};

#endif // MATERIALSPECULAR_H
