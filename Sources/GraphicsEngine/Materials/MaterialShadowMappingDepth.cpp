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

void MaterialShadowMappingDepth::SetMaterial()
{
    // Заполняем матрицы World, View, Proj
    const Matrix4x4 & matWorld	= SceneUtils::GetMatrixWorld(m_pObject);
    const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
    const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();

    Matrix4x4 biasMatrix = {
        0.5, 0.0, 0.0, 0.0,
        0.0, 0.5, 0.0, 0.0,
        0.0, 0.0, 0.5, 0.0,
        0.5, 0.5, 0.5, 1.0
    };

    Matrix4x4 lightSpaceMatrix = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);
    //lightSpaceMatrix = lightSpaceMatrix * biasMatrix.Transpose();

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
