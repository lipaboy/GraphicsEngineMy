#include "LightSpot.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/MathUtils.h"

void LightSpot::RecalcLightSpaceMatrix()
{
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
