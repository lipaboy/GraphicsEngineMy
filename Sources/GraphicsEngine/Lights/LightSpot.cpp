#include "LightSpot.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/MathUtils.h"

#include "GraphicsEngine/Meshes/MeshCylinder.h"
#include "GraphicsEngine/Materials/MaterialDiffuseAttenuation.h"
#include "GraphicsEngine/Materials/MaterialUnlit.h"

#include <QDebug>

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
    RecalcLightSpaceMatrix();

    Transform *p1 = pLightFigure->m_pTransform;
    Transform *p2 = this->GetConstObjectPtr()->m_pTransform;

    if ((p1->GetEulerAngles() - p2->GetEulerAngles()).Length() > 1e-4 ) {
        qDebug() << "oops";
    }

    *(pLightFigure->m_pTransform) = *(this->GetConstObjectPtr()->m_pTransform);
    pLightFigure->m_pTransform->RotateByOperator(Vector3(0, 0, 1), PI / 2.);
}

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
