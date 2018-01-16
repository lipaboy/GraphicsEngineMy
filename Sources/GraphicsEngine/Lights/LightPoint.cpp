#include "LightPoint.h"

#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/MathUtils.h"

#include "GraphicsEngine/Meshes/MeshSphere.h"
#include "GraphicsEngine/Materials/MaterialDiffuseAttenuation.h"
#include "GraphicsEngine/Materials/MaterialUnlit.h"

LightPoint::LightPoint()
{
    pLightFigure = new Object();

    pLightFigure->m_pTransform	= new Transform();
    pLightFigure->m_pMesh		= new MeshSphere(20);
            //new MeshCube(3);      //why system coordinates is changing when I replace Sphere on Cube???
    pLightFigure->m_pMaterial = std::shared_ptr<Material>(//new MaterialDiffuse();
        new MaterialUnlit()
        //new MaterialDiffuseSpecular()
    );

    Scene & scene = Application::Instance().GetScene();
    scene.AddObject(pLightFigure);
}

void LightPoint::Update() {
    RecalcLightSpaceMatrix();

    Transform *pFigureTr = pLightFigure->m_pTransform;
    Transform *pLightTr = this->GetConstObjectPtr()->m_pTransform;

    *pFigureTr = *pLightTr;
}

void LightPoint::RecalcLightSpaceMatrix()
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
