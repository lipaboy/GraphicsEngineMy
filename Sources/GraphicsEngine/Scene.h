#pragma once
#include <list>
#include "Object.h"

#include "GraphicsEngine/GraphicsApi/RenderTextureImpl.h"
#include <memory>

namespace graphics_engine {

class Camera;
class AbstractLight;


class Scene
{
public:

	void Init();
	void Deinit();

	void AddObject	(Object * pObject);
	void AddLight	(AbstractLight * pLight);
	
	void SetCamera	(Camera * pCamera);	
	Camera &		GetCamera() const;
	
	const std::list<const AbstractLight *> & GetLights() const;
	
	void Update();
	void Render();

private:
    void Render1();

private:
	std::list<const Object *>	m_objects;
	std::list<const AbstractLight *>	m_lights;
	Camera *					m_pCamera;

    std::shared_ptr<RenderTextureImpl> pRenderTextureImpl;

    // Save temporary data

};

}
