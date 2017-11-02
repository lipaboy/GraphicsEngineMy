#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Lights/Light.h"
#include "GraphicsEngine/Lights/LightDirectional.h"

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

#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Transform.h"
#include "Tasks/Task.h"
#include "Tasks/ObjectRotator.h"

#include "CameraController.h"


class Task04: public Task
{
private:
    //Object * m_pCameraObj;
   // Object * m_pSphereObj;
public:
	virtual ~Task04() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
		
		// Камера
		{
			Object * pCameraObj = new Object();
            pCameraObj->m_pTransform = new Transform( Vector3(0.0f, 0.0f,-20), Vector3(0, 0, 0));
			Camera * pCamera = new Camera();
			pCameraObj->AddComponent( pCamera );
            //pCameraObj->AddComponent( new ObjectRotator(100,0,0) );
            pCameraObj->AddComponent(new CameraController());

			scene.SetCamera( pCamera );
		}

         //объект #1 - Сфера
        {
            Object * pObject1 = new Object();

            pObject1->m_pTransform	= new Transform(4,0,0, 0,0,0, 3,3,3);
            pObject1->m_pMesh		= new MeshSphere(20);
                    //new MeshCube(3);      //why system coordinates is changing when I replace Sphere on Cube???
            pObject1->m_pMaterial = std::shared_ptr<Material>(//new MaterialDiffuse();
                new MaterialDiffuseAttenuation());
                //new MaterialDiffuseSpecular();
            //pObject1->AddComponent( new ObjectRotator(0,2*50,0) );
            pObject1->AddComponent(new CameraController());

            scene.AddObject( pObject1 );
        }

        // объект #2 - Quad
        {
            Object * pObject1 = new Object();
            pObject1->m_pTransform	= new Transform(-3,0,0, 0,-90,0, 6,6,6);
            pObject1->m_pMesh		= //new MeshSphere(20);
                    new MeshQuad();      //why system coordinates is changing when I replace Sphere on Cube???
            pObject1->m_pMaterial = std::shared_ptr<Material>(//new MaterialDiffuse();
                new MaterialDiffuseAttenuation());
                //new MaterialDiffuseSpecular();
            //pObject1->AddComponent( new ObjectRotator(0,100,100) );


            scene.AddObject( pObject1 );
        }

//		 Источник света #1
        {
            AbstractLight * pLight = new LightDirectional();
            pLight->SetColor(1,1,0);
            pLight->SetIntensity(1);
            Object * pLightObject   = new Object();
            pLightObject->m_pTransform	= new Transform(20,0,0, //position - no mean for LIGHT_DIRECTIONAL (but it wrong in that case)
                                                        0,-90,0, 1,1,1);
            pLightObject->AddComponent(pLight);
            //pLightObject->AddComponent(new ObjectRotator(0, 0, 100));

            scene.AddLight(pLight);
        }
        //		 Источник света #1
        {
            AbstractLight * pLight = new LightDirectional();
            pLight->SetColor(0.5,0,0);
            pLight->SetIntensity(1);
            Object * pLightObject   = new Object();
            pLightObject->m_pTransform	= new Transform(20,0,0, //position - no mean for LIGHT_DIRECTIONAL (but it wrong in that case)
                                                        0,-80,0, 1,1,1);
            pLightObject->AddComponent(pLight);
            //pLightObject->AddComponent(new ObjectRotator(0, 0, 100));

            scene.AddLight(pLight);
        }
//-------------------------------------------
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
