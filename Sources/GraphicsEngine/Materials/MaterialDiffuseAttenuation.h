#ifndef MATERIALDIFFUSEATTENUATION_H
#define MATERIALDIFFUSEATTENUATION_H

#include "MaterialLightReflect.h"

class MaterialDiffuseAttenuation : public MaterialLightReflect
{
public:
    MaterialDiffuseAttenuation(float red = 1.f, float green = 1.f, float blue = 1.f);

    virtual void Init(Object * pObject) { MaterialLightReflect::Init(pObject); }
    virtual void Deinit() { MaterialLightReflect::Deinit(); }
};

#endif // MATERIALDIFFUSEATTENUATION_H
