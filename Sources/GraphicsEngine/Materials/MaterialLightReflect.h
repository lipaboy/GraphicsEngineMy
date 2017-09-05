#ifndef MATERIALLIGHTREFLECT_H
#define MATERIALLIGHTREFLECT_H

#include "GraphicsEngine/Materials/Material.h"

//TODO: make it abstract class

// It is commonality of classes Material that calculate components from each light sources
class MaterialLightReflect : public Material
{
public:
//    MaterialLightReflect();

//    virtual void setShaderFilename() = 0;

    virtual void Init(Object * pObject);
    virtual void Deinit();

    virtual void SetMaterial();
};

#endif // MATERIALLIGHTREFLECT_H
