#ifndef PYLOSTASK_H
#define PYLOSTASK_H

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

#include "GraphicsEngine/Meshes/MeshTriangle.h"
#include "GraphicsEngine/Meshes/MeshQuad.h"
#include "GraphicsEngine/Meshes/MeshSphere.h"
#include "GraphicsEngine/Meshes/MeshCube.h"
#include "GraphicsEngine/Meshes/MeshCylinder.h"
#include "GraphicsEngine/Meshes/mesh_pylos_board.h"

#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Transform.h"
#include "Tasks/Task.h"
#include "Tasks/ObjectRotator.h"

#include "CameraController.h"

namespace PylosGame {

class PylosTask: public Task
{
public:
    virtual ~PylosTask() { }

    virtual void Init()
    {
        Scene & scene = Application::Instance().GetScene();

        // Камера
        {
            Object * pCameraObj = new Object();
            pCameraObj->m_pTransform = new Transform( Vector3(2.0f, 0.0f,-10), Vector3(0, 0, 0));
            Camera * pCamera = new Camera();
            pCameraObj->AddComponent( pCamera );
            pCameraObj->AddComponent(new CameraController());

            scene.SetCamera( pCamera );
        }

        //объект #1 - Board
        {
           Object * pObject1 = new Object();

           pObject1->m_pTransform	= new Transform(5,0,0, 0,0,0, 3,3,3);
           pObject1->m_pMesh		= new MeshPylosBoard(1);
                   //new MeshCube(3);      //why system coordinates is changing when I replace Sphere on Cube???
           pObject1->m_pMaterial = std::shared_ptr<Material>(//new MaterialDiffuse();
               new MaterialDiffuseAttenuation());
               //new MaterialDiffuseSpecular();

           scene.AddObject( pObject1 );
        }

        //объект #1 - Sphere
        {
           Object * pObject1 = new Object();

           pObject1->m_pTransform	= new Transform(8,0,0, 0,0,0, 3,3,3);
           pObject1->m_pMesh		= new MeshSphere(20);
                   //new MeshCube(3);      //why system coordinates is changing when I replace Sphere on Cube???
           pObject1->m_pMaterial = std::shared_ptr<Material>(//new MaterialDiffuse();
               new MaterialDiffuseAttenuation());
               //new MaterialDiffuseSpecular();

           pObject1->AddComponent(new ObjectRotator(0, 0, 100));

           scene.AddObject( pObject1 );
        }
        // Lights
        {
//            //AbstractLight * pLight = new LightDirectional();
//            AbstractLight * pLight = new LightSpot();
//            //AbstractLight * pLight = new LightPoint();
//            pLight->SetColor(.9,.9,.2);
//            pLight->SetIntensity(1);
//            Object * pLightObject   = new Object();
//            pLightObject->m_pTransform	= new Transform(8,3,-5, //position - no mean for LIGHT_DIRECTIONAL (but it wrong in that case)
//                                                        50,-20,0, 1,1,1);
//            pLightObject->AddComponent(pLight);

//            scene.AddLight(pLight);
        }
        {
            AbstractLight * pLight = new LightDirectional();
            pLight->SetColor(.9,.9,.2);
            pLight->SetIntensity(1);
            Object * pLightObject   = new Object();
            pLightObject->m_pTransform	= new Transform(18,3,-5, //position - no mean for LIGHT_DIRECTIONAL (but it wrong in that case)
                                                        0,0,0, 1,1,1);
            pLightObject->AddComponent(pLight);

            scene.AddLight(pLight);
        }
        {
            AbstractLight * pLight = new LightDirectional();
            pLight->SetColor(.8,.3,.2);
            pLight->SetIntensity(1);
            Object * pLightObject   = new Object();
            pLightObject->m_pTransform	= new Transform(18,3,-5, //position - no mean for LIGHT_DIRECTIONAL (but it wrong in that case)
                                                        90,0,0, 1,1,1);
            pLightObject->AddComponent(pLight);

            scene.AddLight(pLight);
        }
//        {
//            AbstractLight * pLight = new LightDirectional();
//            pLight->SetColor(.2,.3,.8);
//            pLight->SetIntensity(1);
//            Object * pLightObject   = new Object();
//            pLightObject->m_pTransform	= new Transform(18,3,-5, //position - no mean for LIGHT_DIRECTIONAL (but it wrong in that case)
//                                                        180,0,0, 1,1,1);
//            pLightObject->AddComponent(pLight);

//            scene.AddLight(pLight);
//        }
//        {
//            AbstractLight * pLight = new LightDirectional();
//            pLight->SetColor(.3,.1,.7);
//            pLight->SetIntensity(1);
//            Object * pLightObject   = new Object();
//            pLightObject->m_pTransform	= new Transform(18,3,-5, //position - no mean for LIGHT_DIRECTIONAL (but it wrong in that case)
//                                                        -90,0,0, 1,1,1);
//            pLightObject->AddComponent(pLight);

//            scene.AddLight(pLight);
//        }
//        {
//            AbstractLight * pLight = new LightDirectional();
//            pLight->SetColor(.2,.3,.3);
//            pLight->SetIntensity(1);
//            Object * pLightObject   = new Object();
//            pLightObject->m_pTransform	= new Transform(18,3,-5, //position - no mean for LIGHT_DIRECTIONAL (but it wrong in that case)
//                                                        0,90,0, 1,1,1);
//            pLightObject->AddComponent(pLight);

//            scene.AddLight(pLight);
//        }
//        {
//            AbstractLight * pLight = new LightDirectional();
//            pLight->SetColor(.1,.5,.2);
//            pLight->SetIntensity(1);
//            Object * pLightObject   = new Object();
//            pLightObject->m_pTransform	= new Transform(18,3,-5, //position - no mean for LIGHT_DIRECTIONAL (but it wrong in that case)
//                                                        0,-90,0, 1,1,1);
//            pLightObject->AddComponent(pLight);

//            scene.AddLight(pLight);
//        }

        /////////////////////////////////////////////////////////////////////////////////////

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
    }

    virtual void Update()
    {

    }
};

}


#endif // PYLOSTASK_H
