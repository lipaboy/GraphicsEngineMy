#ifndef LIGHTSPOT_H
#define LIGHTSPOT_H

#include "Light.h"

class LightSpot : public AbstractLight
{
public:
    LightSpot() : AbstractLight() {}

    virtual Matrix4x4 const & GetLightSpaceMatrix() const { return m_spaceMatrix; }

    virtual Vector4 GetType() const { return Vector4(LIGHT_SPOT, 0, 0, 0); }

    void Update() { RecalcLightSpaceMatrix(); }

protected:
    void RecalcLightSpaceMatrix();

private:
    Matrix4x4 m_spaceMatrix;
};

#endif // LIGHTSPOT_H
