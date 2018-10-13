#pragma once

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Lights/Light.h"
#include "GraphicsEngine/Lights/LightDirectional.h"
#include "GraphicsEngine/Lights/LightSpot.h"
#include "GraphicsEngine/Lights/LightPoint.h"

#include "GraphicsEngine/Materials/MaterialTask01.h"
#include "GraphicsEngine/Materials/MaterialUnlit.h"
#include "GraphicsEngine/Materials/MaterialDiffuse.h"
#include "GraphicsEngine/Materials/MaterialDiffuseSpecular.h"
#include "GraphicsEngine/Materials/MaterialDiffuseAttenuation.h"
#include "GraphicsEngine/Materials/MaterialSand.h"

#include "GraphicsEngine/Meshes/MeshTriangle.h"
#include "GraphicsEngine/Meshes/MeshQuad.h"
#include "GraphicsEngine/Meshes/MeshSphere.h"
#include "GraphicsEngine/Meshes/MeshCube.h"
#include "GraphicsEngine/Meshes/MeshCylinder.h"

#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Transform.h"
#include "Tasks/Task.h"
#include "Tasks/ObjectRotator.h"

#include "CameraController.h"

#include <cmath>

#include "domino/domino_falling.h"

namespace graphics_engine {

class Domino: public Task
{
private:
    //Object * m_pCameraObj;
   // Object * m_pSphereObj;
public:
    virtual ~Domino() { }

    virtual void Init()
    {
        Scene & scene = Application::Instance().GetScene();
        Vector3 defaultDirection(1, 0, 0);

        Vector3 floorPosition(-3, -8, 0);
        Vector3 floorNormal(0, 1, 0);
        // width, height, length
        Vector3 dominoSize(4, 4, 2);
        Vector3 dominoPosition = floorPosition + Vector3(0, dominoSize.y / 2., 0)
                + Vector3(0, dominoSize.y, 0);
        Vector3 dominoDirection(2, 0, -2);

        // Calculation the angle of domino rotation

        auto crossVec = Vector3::Cross(defaultDirection, dominoDirection);
        // #crutch: calculating the direction of rotating
        double dominoRotationAngle = (crossVec.y > 0) * std::asin(crossVec.Length()
                / dominoDirection.Length()
                / defaultDirection.Length());

        // Camera
        {
            Object * pCameraObj = new Object();
            pCameraObj->m_pTransform = new Transform( Vector3(0.0f, 0, -20), Vector3(20, 0, 0));
            Camera * pCamera = new Camera();
            pCameraObj->AddComponent( pCamera );
            pCameraObj->AddComponent(new CameraController());

            scene.SetCamera( pCamera );
        }

        // object #2 - Quad
        {
            Object * pObject1 = new Object();
            pObject1->m_pTransform	= new Transform(floorPosition, Vector3(0,90,0), Vector3(16,16,16));
            pObject1->m_pTransform -> RotateByOperator(Vector3(0, 0, 1), -PI / 2);
            pObject1->m_pMesh		=
                    new MeshQuad();      //why system coordinates is changing when I replace Sphere on Cube???
            pObject1->m_pMaterial = std::shared_ptr<Material>(
//                        new MaterialUnlit()
//                        new MaterialDiffuseAttenuation()
                        new MaterialTexture("sand.jpg", TEXTURE_FILTER_MODE_POINT)
//                        new MaterialDiffuseSpecular(1,.5,1)
                        );
            scene.AddObject( pObject1 );
        }

        // object #4 - Domino
        {
            Object * pDomino = new Object();
            pDomino->m_pTransform = new Transform(dominoPosition, Vector3(0,0,0), dominoSize);
            pDomino->m_pTransform -> RotateByOperator(floorNormal, dominoRotationAngle);

            pDomino->m_pMesh		= //new MeshSphere(20);
                   new MeshCube(3);      //why system coordinates is changing when I replace Sphere on Cube???
            pDomino->m_pMaterial = std::shared_ptr<Material>(
                       new MaterialUnlit()
            //                       new MaterialTexture("Earth_NormalMap.jpg", TEXTURE_FILTER_MODE_POINT)
            //                       new MaterialDiffuseAttenuation()
            //                        new MaterialDiffuseSpecular(1,1,1)
                       );

            pDomino->m_pTransform -> preliminaryTranslation = Vector3(-dominoSize.x / 2, dominoSize.y / 2, 0);
            double angularSpeed
                    = 0;
//                      = PI / 10 / 1; // (PI / 20) radian per 1 second
            pDomino->AddComponent(new DominoFalling(dominoDirection, floorNormal,
                                                    angularSpeed, dominoSize.y, dominoSize.x));

            scene.AddObject( pDomino );
        }

        // axis of rotation
        {
            using lipaboy_lib::RotateOperator;
            using lipaboy_lib::Vector3D;
            using lipaboy_lib::createVector3D;

            Object * pRotAsix   = new Object();

            Vector3D asixRotBase(dominoSize.x / 2, -dominoSize.y / 2, 0);
            Vector3 asixRotVect(
                        RotateOperator(createVector3D<Vector3>(floorNormal),
                                       dominoRotationAngle).rotate(asixRotBase)
                        );
            pRotAsix->m_pTransform	= new Transform(dominoPosition + asixRotVect,
                                                    Vector3(0,0,0), Vector3(.2,dominoSize.z,.2));
            pRotAsix->m_pTransform -> RotateByOperator(dominoDirection, PI / 2);
            pRotAsix->m_pMesh = new MeshCylinder(20);
            pRotAsix->m_pMaterial = std::shared_ptr<Material>(new MaterialDiffuseSpecular(1,0,0));
            scene.AddObject(pRotAsix);

            // vertical asix

            Object * pRotVerticalAsix   = new Object();
            pRotVerticalAsix->m_pTransform	= new Transform(*pRotAsix->m_pTransform);
            pRotVerticalAsix->m_pTransform -> RotateByOperator(dominoDirection, PI / 2);
            pRotVerticalAsix->m_pTransform -> SetScale(Vector3(.05, dominoSize.z * 1.3, .05));
            pRotVerticalAsix->m_pTransform -> Translate(Vector3(0, dominoSize.y / 2, 0));
            pRotVerticalAsix->m_pMesh = new MeshCylinder(20);
            pRotVerticalAsix->m_pMaterial = std::shared_ptr<Material>(new MaterialDiffuseSpecular(1,0,0));
            scene.AddObject(pRotVerticalAsix);
        }

        //---------------------------------------------------//
        //--------------------"Background"-------------------//
        //---------------------------------------------------//

        // object #5 - Quad
        {
            Object * pObject1 = new Object();
            pObject1->m_pTransform	= new Transform(18,0,18, 0,10,0, 16,16,16);
            pObject1->m_pMesh		=
                   new MeshQuad();      //why system coordinates is changing when I replace Sphere on Cube???
            pObject1->m_pMaterial = std::shared_ptr<Material>(
            //                       new MaterialUnlit()
                       new MaterialDiffuseAttenuation()
                       );
            scene.AddObject( pObject1 );
        }

        // sun
        {
            AbstractLight * pLight = new LightDirectional();
            pLight->SetColor(1,1,0);
            pLight->SetIntensity(1);

            Object * pLightObject = new Object();
            pLightObject->m_pTransform	= new Transform(16,16,16, 0,0,0, 1,1,1);
//            pLightObject->m_pTransform -> RotateByOperator(Vector3(0, 0, 1), PI / 2);
            pLightObject->AddComponent(pLight);

            scene.AddLight(pLight);
        }




//------------------------------------------------------------------//
//------------------------------------------------------------------//
//------------------------------------------------------------------//
//------------------------------------------------------------------//

        // Ox
        {
            Object * pTriangle   = new Object();
            pTriangle->m_pTransform	= new Transform(0,0,0,
                                                        0,0,-90, .2,2,2);
            //pTriangle->m_pTransform->RotateByOperator(Vector3(0,0,1), -PI / 2);
            pTriangle->m_pMesh = new MeshTriangle();
            pTriangle->m_pMaterial = std::shared_ptr<Material>(new MaterialDiffuseSpecular(1,0,0));
            scene.AddObject(pTriangle);

            pTriangle   = new Object();
            pTriangle->m_pTransform	= new Transform(0,0,0,
                                                        0,180,-90, .2,2,2);
            pTriangle->m_pMesh = new MeshTriangle();
            pTriangle->m_pMaterial = std::shared_ptr<Material>(new MaterialDiffuseSpecular(1,0,0));
            scene.AddObject(pTriangle);
        }
        // Oy
        {
            Object * pTriangle   = new Object();
            pTriangle->m_pTransform	= new Transform(0,0,0,
                                                        0,0,0, .2,2,2);
            pTriangle->m_pMesh = new MeshTriangle();
            pTriangle->m_pMaterial = std::shared_ptr<Material>(new MaterialDiffuseSpecular(0,1,0));
            scene.AddObject(pTriangle);

            pTriangle   = new Object();
            pTriangle->m_pTransform	= new Transform(0,0,0,
                                                        0,180,0, .2,2,2);
            pTriangle->m_pMesh = new MeshTriangle();
            pTriangle->m_pMaterial = std::shared_ptr<Material>(new MaterialDiffuseSpecular(0,1,0));
            scene.AddObject(pTriangle);
        }
        // Oz
        {
            Object * pTriangle   = new Object();
            pTriangle->m_pTransform	= new Transform(0,0,0,
                                                        90,0,0, .2,2,2);
            pTriangle->m_pMesh = new MeshTriangle();
            pTriangle->m_pMaterial = std::shared_ptr<Material>(new MaterialDiffuseSpecular(0,0,1));
            scene.AddObject(pTriangle);

            pTriangle   = new Object();
            pTriangle->m_pTransform	= new Transform(0,0,0,
                                                        90,0,180, .2,2,2);
            pTriangle->m_pMesh = new MeshTriangle();
            pTriangle->m_pMaterial = std::shared_ptr<Material>(new MaterialDiffuseSpecular(0,0,1));
            scene.AddObject(pTriangle);
        }

//        // Источник света #2
//        {               //right lighter
//            Light * pLight = new Light(LightType::LIGHT_POINT);
//            pLight->SetColor(1,1,1);
//            pLight->SetIntensity(1);

//            Object * pLightObject = new Object();
//            pLightObject->m_pTransform	= new Transform(6,0,10, 0,0,0, 1,1,1);
//            pLightObject->AddComponent(pLight);

//            scene.AddLight(pLight);
//        }

//        // Источник света #3
//        {               //upper lighter (precisely)
//            Light * pLight = new Light(LightType::LIGHT_SPOT);
//            pLight->SetColor(0.3f,0.95f,0.5f);
//            pLight->SetIntensity(1);

//            Object * pLightObject = new Object();
//            pLightObject->m_pTransform	= new Transform(0,6,10, 90,0,0, 1,1,1);
//            pLightObject->AddComponent(pLight);

//            scene.AddLight(pLight);
//        }
    }

    virtual void Update()
    {
       // if (Input::GetKey(KEY_CODE_A))
    }
};

}

