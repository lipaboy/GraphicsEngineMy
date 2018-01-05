#ifndef LIGHTSPOT_H
#define LIGHTSPOT_H

#include "Light.h"

class LightSpot : public AbstractLight
{
    Object * pLightFigure;
public:
    LightSpot();

    virtual Matrix4x4 const & GetLightSpaceMatrix() const { return m_spaceMatrix; }

    virtual Vector4 GetType() const { return Vector4(LIGHT_SPOT, 0, 0, 0); }

    void Update();

protected:
    void RecalcLightSpaceMatrix();

private:
    Matrix4x4 m_spaceMatrix;
    double innerCone = 0.7;
    double outerCone = 0.9;
};

#endif // LIGHTSPOT_H
