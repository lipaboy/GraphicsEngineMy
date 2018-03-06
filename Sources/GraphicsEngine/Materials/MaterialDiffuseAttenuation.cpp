#include "MaterialDiffuseAttenuation.h"

MaterialDiffuseAttenuation::MaterialDiffuseAttenuation(float red, float green, float blue)
    : MaterialLightReflect(red, green, blue)
{
    m_vsFileName = "ShaderDiffuseAttenuation";
    m_psFileName = "ShaderDiffuseAttenuation";
}
