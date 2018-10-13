#include "MaterialShadowMappingDepth.h"

namespace graphics_engine {

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

//    const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);

    const std::list<const AbstractLight *> & lights = SceneUtils::GetLights();
    Matrix4x4 lightSpaceMatrix;
    if (lights.size() > 0) {
        lightSpaceMatrix = lights.front()->GetLightSpaceMatrix();
        lightSpaceMatrix = lightSpaceMatrix * matWorld.Transpose();
        //lights.front()->SetLightSpaceMatrix(matWorldViewProjT);
    }

    Camera & camera = Application::Instance().GetScene().GetCamera();

    SetMaterialBegin();
    {
        if (lights.size() > 0) {
            SetVertexShaderBegin();
            SetVertexShaderMatrix4x4("lightSpaceMatrix", lightSpaceMatrix);
            SetVertexShaderEnd();
        }

        // Empty
        SetPixelShaderBegin();      // == fragment shader
        SetPixelShaderVector4("farPlane", Vector4(camera.getFarPlane(), 0., 0., 0.));
        SetPixelShaderVector4("nearPlane", Vector4(camera.getNearPlane(), 0., 0., 0.));
        SetPixelShaderEnd();
    }
    SetMaterialEnd();
}

}
