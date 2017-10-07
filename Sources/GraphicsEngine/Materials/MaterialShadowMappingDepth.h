#ifndef MATERIALSHADOWMAPPINGDEPTH_H
#define MATERIALSHADOWMAPPINGDEPTH_H

#include "Material.h"

#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/MathUtils.h"

class MaterialShadowMappingDepth : public Material
{
public:
    MaterialShadowMappingDepth();

    virtual void Init(Object * pObject);
    virtual void Deinit();

    virtual void SetMaterial();
};

#endif // MATERIALSHADOWMAPPINGDEPTH_H
