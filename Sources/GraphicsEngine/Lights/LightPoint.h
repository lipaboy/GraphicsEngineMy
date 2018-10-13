#pragma once

#include "Light.h"

namespace graphics_engine {

class LightPoint : public AbstractLight
{
    Object * pLightFigure;
public:
    LightPoint();

    virtual Matrix4x4 const & GetLightSpaceMatrix() const { return m_spaceMatrix; }

    virtual Vector4 GetType() const { return Vector4(LIGHT_POINT, 0, 0, 0); }

    void Update();

protected:
    void RecalcLightSpaceMatrix();

private:
    Matrix4x4 m_spaceMatrix;
};

}
