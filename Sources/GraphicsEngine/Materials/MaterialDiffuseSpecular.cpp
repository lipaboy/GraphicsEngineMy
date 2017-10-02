#include "MaterialDiffuseSpecular.h"

MaterialDiffuseSpecular::MaterialDiffuseSpecular(float red, float green, float blue)
    : MaterialLightReflect(red, green, blue)
{
    m_vsFileName = "ShaderDiffuseSpecular";
    m_psFileName = "ShaderDiffuseSpecular";
}
