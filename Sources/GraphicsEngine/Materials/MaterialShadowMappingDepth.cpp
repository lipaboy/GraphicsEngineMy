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
    Camera & camera = Application::Instance().GetScene().GetCamera();
    // Заполняем матрицы World, View, Proj
    const Matrix4x4 & matWorld	= SceneUtils::GetMatrixWorld(m_pObject);
    const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
    const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();

    const Matrix4x4 matWorldViewProjT	= MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);

    Matrix4x4 biasMatrix = {
        0.5, 0.0, 0.0, 0.0,
        0.0, 0.5, 0.0, 0.0,
        0.0, 0.0, 0.5, 0.0,
        0.5, 0.5, 0.5, 1.0
    };

    bool temp = camera.isPerspective;
    camera.isPerspective = false;
    // Compute the MVP matrix from the light's point of view
    Matrix4x4 depthViewMatrix;
    depthViewMatrix = glm::lookAt(
                glm::vec3(20, 0, 0),
                                glm::vec3(0,0,0), glm::vec3(0,1,0));
    depthViewMatrix = depthViewMatrix.Transpose();
    Matrix4x4 lightSpaceMatrix = MathUtils::GetMatrixWorldViewProjT(Matrix4x4::Identity(), depthViewMatrix,
                                                                        SceneUtils::GetMatrixProj());
    lightSpaceMatrix = lightSpaceMatrix
            //* biasMatrix.Transpose()
            ;
    //lightSpaceMatrix = matWorldViewProjT;
    camera.isPerspective = temp;
    //Matrix4x4 lightSpaceMatrix = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);
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
