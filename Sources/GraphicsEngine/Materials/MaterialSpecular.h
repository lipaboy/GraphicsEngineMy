#ifndef MATERIALSPECULAR_H
#define MATERIALSPECULAR_H

#include "MaterialLightReflect.h"

class MaterialSpecular : public MaterialLightReflect
{
public:
    MaterialSpecular();

    virtual void Init(Object * pObject) { MaterialLightReflect::Init(pObject); }
    virtual void Deinit() { MaterialLightReflect::Deinit(); }
};

#endif // MATERIALSPECULAR_H
