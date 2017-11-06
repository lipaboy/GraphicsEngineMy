#ifndef LIGHTDIRECTIONAL_H
#define LIGHTDIRECTIONAL_H

#include "Light.h"
#include "GraphicsEngine/Matrix4x4.h"

class LightDirectional : public AbstractLight
{
public:
    LightDirectional() : AbstractLight() {}

    virtual Matrix4x4 const & GetLightSpaceMatrix() const { return m_spaceMatrix; }

    virtual Vector4 GetType() const { return Vector4(LIGHT_DIRECTIONAL, 0, 0, 0); }

    void Update() { RecalcLightSpaceMatrix(); }

protected:
    void RecalcLightSpaceMatrix();

private:
    Matrix4x4 m_spaceMatrix;

};

#endif // LIGHTDIRECTIONAL_H
