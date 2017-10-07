#pragma once
#include <list>
#include <memory>


class Mesh;
class Component;
class Material;
class Transform;
class MaterialShadowMappingDepth;


class Object
{
public:
	Object();
	~Object();

	void Init();
	void AddComponent(Component * pComponent);
	
	void Update() const;

	// Содержит матрицу World (position, rotation, scale)
	Transform * m_pTransform;

	// Содержит меш (vertex & index buffers)
	Mesh *		m_pMesh;

	// Содержит Vertex & Pixel Shaders
    std::shared_ptr<Material>	m_pMaterial;

    std::shared_ptr<Material> m_pDepthMaterial;

	// Содержит объекты пользователя
	std::list<Component *> m_components;
};
