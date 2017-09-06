#ifndef MATERIALDIFFUSEATTENUATION_H
#define MATERIALDIFFUSEATTENUATION_H

#include "MaterialLightReflect.h"

class MaterialDiffuseAttenuation : public MaterialLightReflect
{
public:
    MaterialDiffuseAttenuation();

    virtual void Init(Object * pObject) { MaterialLightReflect::Init(pObject); }
    virtual void Deinit() { MaterialLightReflect::Deinit(); }
};

#endif // MATERIALDIFFUSEATTENUATION_H
