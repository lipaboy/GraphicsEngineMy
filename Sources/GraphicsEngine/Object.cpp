#include "Object.h"
#include "Component.h"
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/Materials/MaterialShadowMappingDepth.h"
#include "Meshes/Mesh.h"
#include "Transform.h"


Object::Object()
{
	m_pTransform	= NULL;
	m_pMesh			= NULL;
    m_pMaterial		= nullptr;
    m_pDepthMaterial= nullptr;
}

Object::~Object()
{
	// Очищаем список компонент
	{
		std::list<Component *>::iterator iter;
		for (iter = m_components.begin(); iter != m_components.end(); iter++)
		{
			Component * pComponent = (*iter);
			if (NULL != pComponent)
			{
				delete pComponent;
			}
		}

		m_components.clear();
	}

    if (nullptr != m_pMaterial)
	{
		m_pMaterial->Deinit();
        //delete m_pMaterial;
        m_pMaterial = nullptr;
	}

	if (NULL != m_pMesh)
	{
		m_pMesh->Deinit();
		delete m_pMesh;
		m_pMesh = NULL;
	}

	if (NULL != m_pTransform)
	{
		delete m_pTransform;
		m_pTransform = NULL;
	}	

    if (nullptr != m_pDepthMaterial) {
        m_pDepthMaterial->Deinit();
        m_pDepthMaterial = nullptr;
    }
}

void Object::Init()
{
	if (NULL != m_pMesh)
	{
		m_pMesh->Init();
	}

    if (nullptr != m_pMaterial)
	{
		m_pMaterial->Init(this);
	}

    m_pDepthMaterial = std::shared_ptr<Material>(new MaterialShadowMappingDepth());
    m_pDepthMaterial->Init(this);
}

void Object::AddComponent(Component * pComponent)
{
	m_components.push_back(pComponent);
	pComponent->Init(this);
}

void Object::Update() const
{
	std::list<Component *>::const_iterator iter;
	for (iter = m_components.begin(); iter != m_components.end(); iter++)
	{
		Component * pComponent = (*iter);
		if (NULL != pComponent)
		{
			pComponent->Update();
		}
	}
}
