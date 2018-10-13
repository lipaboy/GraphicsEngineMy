#include "Object.h"
#include "Component.h"
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/Materials/MaterialShadowMappingDepth.h"
#include "Meshes/Mesh.h"
#include "Transform.h"

namespace graphics_engine {

Object::Object()
{
    m_pTransform	= nullptr;
    m_pMesh			= nullptr;
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
            if (nullptr != pComponent)
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

    if (nullptr != m_pMesh)
	{
		m_pMesh->Deinit();
		delete m_pMesh;
        m_pMesh = nullptr;
	}

    if (nullptr != m_pTransform)
	{
		delete m_pTransform;
        m_pTransform = nullptr;
	}	

    if (nullptr != m_pDepthMaterial) {
        m_pDepthMaterial->Deinit();
        m_pDepthMaterial = nullptr;
    }
}

void Object::Init()
{
    if (nullptr != m_pMesh)
	{
		m_pMesh->Init();
	}

    if (nullptr != m_pMaterial)
	{
		m_pMaterial->Init(this);
	}

    if (nullptr == m_pDepthMaterial)
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
        if (nullptr != pComponent)
		{
			pComponent->Update();
		}
	}
}

}
