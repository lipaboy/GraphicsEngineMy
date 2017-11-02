#include "LightDirectional.h"

#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"

#ifdef CAN_USE_OPEN_GL
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#endif

void LightDirectional::RecalcLightSpaceMatrix()
{
//    Matrix4x4 biasMatrix = {
//        0.5, 0.0, 0.0, 0.0,
//        0.0, 0.5, 0.0, 0.0,
//        0.0, 0.0, 0.5, 0.0,
//        0.5, 0.5, 0.5, 1.0
//    };
//    Matrix4x4 reflectMat = {
//        1., 0., 0., 0.,
//        0., 1., 0., 0.,
//        0., 0.,-1., 0.,
//        0., 0., 0., 1.
//    };

    Camera & camera = Application::Instance().GetScene().GetCamera();

    auto temp = camera.GetLightSide();
    camera.SetLightSide(this);
    const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
    const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();
    m_spaceMatrix = MathUtils::GetMatrixWorldViewProjT(Matrix4x4::Identity(), matView,
                                                                        matProj);
    camera.SetLightSide(temp);
    m_spaceMatrix = m_spaceMatrix;

}
