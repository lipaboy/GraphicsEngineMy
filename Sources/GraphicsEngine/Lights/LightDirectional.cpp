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
    // Transform from LH to RH or may be opposite
//    Matrix4x4 reflectMat = {
//        1., 0., 0., 0.,
//        0., 1., 0., 0.,
//        0., 0.,-1., 0.,
//        0., 0., 0., 1.
//    };

     Camera & camera = Application::Instance().GetScene().GetCamera();

    auto temp = camera.GetLightSide();
    camera.SetLightSide(this);
    //const Matrix4x4 & matWorld = this->GetConstObjectPtr()->m_pTransform->GetMatWorld();
    const Matrix4x4 & matView = //SceneUtils::GetMatrixView();
            this->GetConstObjectPtr()->m_pTransform->GetMatView();
    const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();
    m_spaceMatrix = MathUtils::GetMatrixWorldViewProjT(Matrix4x4::Identity(),
                                            // We don't need matWorld because it flows up from each object
                                                       matView, matProj);
    camera.SetLightSide(temp);
    m_spaceMatrix = m_spaceMatrix;

}
