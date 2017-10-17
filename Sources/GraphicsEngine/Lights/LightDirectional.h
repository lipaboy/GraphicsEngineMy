#ifndef LIGHTDIRECTIONAL_H
#define LIGHTDIRECTIONAL_H

#include "Light.h"

class LightDirectional : public ILight
{
public:
    LightDirectional() : ILight(LIGHT_DIRECTIONAL) {}

    virtual Matrix4x4 const & GetLightSpaceMatrix() const;
};

#endif // LIGHTDIRECTIONAL_H
