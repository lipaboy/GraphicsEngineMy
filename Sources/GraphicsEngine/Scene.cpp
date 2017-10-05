﻿// TODO: ”казать полный путь дл¤ #include во всЄм проекте
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/Meshes/Mesh.h"
#include "GraphicsEngine/Light.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Application.h"

#include "GraphicsEngine/GraphicsEngineFabric.h"

void Scene::Init()
{
	m_pCamera = NULL;

    pRenderTextureImpl = GraphicsEngineFabric::CreateRenderTexture();
    pRenderTextureImpl -> Init();
}

void Scene::Deinit()
{
	// ”дал¤ем объекты
	{
		std::list<const Object *>::iterator iter;
		for (iter = m_objects.begin(); iter != m_objects.end(); iter++)
		{
			const Object * pObject = (*iter);
			delete pObject;
		}
	}

	m_lights.clear();
	m_objects.clear();	

	// ”дал¤ем камеру
	m_pCamera = NULL;
}

void Scene::AddObject(Object * pObject)
{
	if (NULL == pObject)
	{
		return;
	}

	pObject->Init();
	m_objects.push_back(pObject);
}

void Scene::AddLight(Light * pLight)
{
	if (NULL == pLight)
	{
		return;
	}

	m_lights.push_back(pLight);

	if (NULL != pLight->GetObjectPtr())
	{
		AddObject(pLight->GetObjectPtr());
	}
}

void Scene::SetCamera(Camera * pCamera)
{
	if (NULL != pCamera)
	{
		m_pCamera = pCamera;
		m_objects.push_back(m_pCamera->GetObjectPtr());
	}
}

Camera & Scene::GetCamera() const
{
	return (*m_pCamera);
}

const std::list<const Light *> & Scene::GetLights() const
{
	return m_lights;
}

void Scene::Update()
{
	std::list<const Object *>::iterator iter;
	for (iter = m_objects.begin(); iter != m_objects.end(); iter++)
	{
		const Object * pObject = (*iter);
		if (NULL != pObject)
		{
			pObject->Update();
		}
	}
}

void Scene::Render() {
    pRenderTextureImpl -> setRenderLocation(DEPTH_TEXTURE);

    // Set camera at light source

    Camera & camera = GetCamera();
    Transform transformTemp(*(camera.GetObjectPtr()->m_pTransform));
    const std::list<const Light *> & lights = GetLights();
    Transform * cameraTransform = camera.GetConstObjectPtr()->m_pTransform;
    Transform * lightTransform ((lights.front() -> GetConstObjectPtr() -> m_pTransform));

    cameraTransform -> SetPosition(-10 * lightTransform->GetForward());
    cameraTransform -> SetEulerAngles(lightTransform->GetEulerAngles());
    cameraTransform -> Rotate(0, 180, 0);
   // cameraTransform -> RotateByOperator(//lightTransform->GetUp()
        //                                cameraTransform->GetUp(), PI);

    camera.isPerspective = false;

    {
        // Render
        Render1();
    }

    //camera.GetObjectPtr()->m_pTransform = transformTemp;
    cameraTransform->SetPosition(transformTemp.GetPosition());
    cameraTransform->SetEulerAngles(transformTemp.GetEulerAngles());
    // cameraTransform -> RotateByOperator(lightTransform->GetUp(), PI);
    camera.isPerspective = true;

    pRenderTextureImpl -> setRenderLocation(SCREEN);

    {
        Render1();
    }
}

void Scene::Render1()
{
	if (NULL == m_pCamera)
	{
		return;
	}

	// Set viewport of current camera
	{
		Rect viewport = m_pCamera->GetViewport();

		GraphicsEngineContext *	pContext	= Application::Instance().GetContext();
		GraphicsEngineImpl *	pImpl		= pContext->m_pImpl;
		
		pImpl->SetViewport(viewport);
	}
	
	std::list<const Object *>::iterator iter;
	for (iter = m_objects.begin(); iter != m_objects.end(); iter++)
	{
		const Object * pObject = (*iter);
		if (NULL == pObject) continue;

		Material *	pMaterial	= pObject->m_pMaterial;
		Mesh *		pMesh		= pObject->m_pMesh;
		if ((NULL == pMaterial) || (NULL == pMesh)) continue;
		if (!pMaterial->IsInited()) continue;
		
		pMaterial->SetMaterial();
		pMesh->Render();
		pMaterial->ResetMaterial();
	}
}
