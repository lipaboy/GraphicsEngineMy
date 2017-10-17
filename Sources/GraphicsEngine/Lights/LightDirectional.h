#ifndef LIGHTDIRECTIONAL_H
#define LIGHTDIRECTIONAL_H

#include "Light.h"

class LightDirectional : public AbstractLight
{
public:
    LightDirectional() : AbstractLight() {}

    virtual Matrix4x4 const & GetProjectionMatrix() const;

    virtual Vector4 GetType() const { return Vector4(LIGHT_DIRECTIONAL, 0, 0, 0); }

private:
    Matrix4x4 m_spaceMatrix;
};

#endif // LIGHTDIRECTIONAL_H
