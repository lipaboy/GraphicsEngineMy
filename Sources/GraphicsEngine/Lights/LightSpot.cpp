#include "LightSpot.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/MathUtils.h"

#include "GraphicsEngine/Meshes/MeshCylinder.h"
#include "GraphicsEngine/Materials/MaterialDiffuseAttenuation.h"
#include "GraphicsEngine/Materials/MaterialUnlit.h"

#ifdef QT_H
#include <QDebug>
#endif

namespace graphics_engine {

LightSpot::LightSpot() : AbstractLight() {
    pLightFigure = new Object();

    pLightFigure->m_pTransform	= new Transform();
    pLightFigure->m_pMesh		= new MeshCylinder(20);
            //new MeshCube(3);      //why system coordinates is changing when I replace Sphere on Cube???
    pLightFigure->m_pMaterial = std::shared_ptr<Material>(//new MaterialDiffuse();
        new MaterialUnlit()
        //new MaterialDiffuseSpecular()
    );

    Scene & scene = Application::Instance().GetScene();
    scene.AddObject(pLightFigure);
}

void LightSpot::Update() {
    static Matrix4x4 saveMat;

    saveMat = m_spaceMatrix;
    RecalcLightSpaceMatrix();

    Transform *pFigureTr = pLightFigure->m_pTransform;
    Transform *pLightTr = this->GetConstObjectPtr()->m_pTransform;

    *pFigureTr = *pLightTr;
    pFigureTr->RotateByOperator(Vector3(0, 0, 1), PI / 2.);
    pFigureTr->RotateByOperator(Vector3(1, 0, 0), PI / 2.);
}

void LightSpot::RecalcLightSpaceMatrix()
{
    Camera & camera = Application::Instance().GetScene().GetCamera();

    auto temp = camera.GetLightSide();
    camera.SetLightSide(this);
    const Matrix4x4 & matView = //SceneUtils::GetMatrixView();
            this->GetConstObjectPtr()->m_pTransform->GetMatView();
    const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();
    m_spaceMatrix = MathUtils::GetMatrixWorldViewProjT(Matrix4x4::Identity(),
                                            // We don't need matWorld because it flows up from each object
                                                       matView, matProj);
    camera.SetLightSide(temp);
    m_spaceMatrix = m_spaceMatrix;
}

}
