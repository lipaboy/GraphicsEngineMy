// TODO: ”казать полный путь дл¤ #include во всЄм проекте
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/Meshes/Mesh.h"
#include "GraphicsEngine/Lights/Light.h"
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

    pRenderTextureImpl -> Deinit();
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

void Scene::AddLight(AbstractLight * pLight)
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

const std::list<const AbstractLight *> & Scene::GetLights() const
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

    Camera & camera = GetCamera();

    const std::list<const AbstractLight *> & lights = GetLights();
    camera.SetLightSide(lights.front());

    pRenderTextureImpl -> SetRenderTarget(DEPTH_TEXTURE);
    {
        Render1();
    }

    pRenderTextureImpl -> SetRenderTarget(SCREEN);
    camera.SetCameraSide();
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

    RenderTarget currentRenderLocation = pRenderTextureImpl -> GetRenderTarget();
	std::list<const Object *>::iterator iter;
	for (iter = m_objects.begin(); iter != m_objects.end(); iter++)
	{
		const Object * pObject = (*iter);
		if (NULL == pObject) continue;

        // You can play with switching of shaders (etc. set the same shader)
        std::shared_ptr<Material> pMaterial =
                (SCREEN == currentRenderLocation) ? pObject->m_pMaterial :
                                                         pObject->m_pDepthMaterial;
		Mesh *		pMesh		= pObject->m_pMesh;
        if ((nullptr == pMaterial) || (NULL == pMesh)) continue;
		if (!pMaterial->IsInited()) continue;
		
		pMaterial->SetMaterial();
		pMesh->Render();
		pMaterial->ResetMaterial();
	}
}
