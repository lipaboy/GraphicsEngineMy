#ifndef MATERIALSPECULAR_H
#define MATERIALSPECULAR_H

#include "MaterialLightReflect.h"

class MaterialDiffuseSpecular : public MaterialLightReflect
{
public:
    MaterialDiffuseSpecular();

    virtual void Init(Object * pObject) { MaterialLightReflect::Init(pObject); }
    virtual void Deinit() { MaterialLightReflect::Deinit(); }
};

#endif // MATERIALSPECULAR_H
