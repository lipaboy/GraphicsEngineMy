#include "MaterialShadowMappingDepth.h"

MaterialShadowMappingDepth::MaterialShadowMappingDepth()
{
    m_vsFileName = "ShaderShadowMap";
    m_psFileName = "ShaderShadowMap";
}

void MaterialShadowMappingDepth::Init(Object *pObject)
{
     Material::Init(pObject);
}

void MaterialShadowMappingDepth::Deinit()
{
     Material::Deinit();
}

#ifdef CAN_USE_OPEN_GL
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#endif

void MaterialShadowMappingDepth::SetMaterial()
{
    // Заполняем матрицы World, View, Proj
    const Matrix4x4 & matWorld	= SceneUtils::GetMatrixWorld(m_pObject);
    const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
    const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();

    const Matrix4x4 matWorldViewProjT	= MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);

    const std::list<const AbstractLight *> & lights = SceneUtils::GetLights();
    const Matrix4x4 lightSpaceMatrix = lights.front()->GetLightSpaceMatrix();

    SetMaterialBegin();
    {
        SetVertexShaderBegin();
        SetVertexShaderMatrix4x4("lightSpaceMatrix", lightSpaceMatrix);
        SetVertexShaderEnd();

        // Empty
//        SetPixelShaderBegin();      // == fragment shader
//        SetPixelShaderEnd();
    }
    SetMaterialEnd();
}
