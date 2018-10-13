﻿#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Lights/Light.h"
#include "GraphicsEngine/Materials/MaterialUnlit.h"
#include "GraphicsEngine/Meshes/MeshCube.h"
#include "GraphicsEngine/Meshes/MeshCylinder.h"
#include "GraphicsEngine/Meshes/MeshTriangle.h"
#include "GraphicsEngine/Meshes/MeshQuad.h"
#include "GraphicsEngine/Meshes/MeshSphere.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Transform.h"
#include "Tasks/Task.h"
#include "Tasks/ObjectRotator.h"

namespace graphics_engine {

class Task01: public Task
{
public:
	virtual ~Task01() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
	
		// Камера
		{
			Object * pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform( Vector3(0, 2, -10), Vector3(20.0f, 0.0f, 0.0f));
			Camera * pCamera = new Camera();
			pCamera->SetFovY(90);
			pCamera->SetNearPlane(0.01f);
			pCamera->SetFarPlane(100);
			pCameraObj->AddComponent( pCamera );

			scene.SetCamera( pCamera );
		}

		// Объект - Куб #1
		Object * pObj1 = NULL;
		{
			Object * pObject = new Object();
			pObject->m_pMesh		= new MeshCube(3);
			pObject->m_pTransform	= new Transform();
            pObject->m_pMaterial	= std::shared_ptr<Material>(new MaterialUnlit());
			pObject->AddComponent( new ObjectRotator(0, 45, 0) );
			
			scene.AddObject( pObject );

			pObj1 = pObject;
		}

		// Объект - Куб #2
		Object * pObj2 = NULL;
		{
			Object * pObject = new Object();
			pObject->m_pMesh		= new MeshCube(3);
			pObject->m_pTransform	= new Transform(7, 0, 0,  0, 0, 23,  1, 1, 1);
            pObject->m_pMaterial	= std::shared_ptr<Material>(new MaterialUnlit());
			pObject->AddComponent( new ObjectRotator(0, 100, 0) );

			pObject->m_pTransform->SetParent( pObj1->m_pTransform );
			
			scene.AddObject( pObject );

			pObj2 = pObject;
		}

		// Объект - Куб #3
		{
			Object * pObject = new Object();
			pObject->m_pMesh		= new MeshCube(4);
			pObject->m_pTransform	= new Transform(3, 0, 0);
            pObject->m_pMaterial	= std::shared_ptr<Material>(new MaterialUnlit());
			pObject->AddComponent( new ObjectRotator(0, 360, 0) );

			pObject->m_pTransform->SetParent( pObj2->m_pTransform );
			
			scene.AddObject( pObject );
		}
	}

	virtual void Update()
	{
		
	}
};

}
