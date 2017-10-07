#pragma once
#include <list>
#include "Object.h"

#include "GraphicsEngine/GraphicsApi/RenderTextureImpl.h"
#include <memory>

class Camera;
class Light;


class Scene
{
public:

	void Init();
	void Deinit();

	void AddObject	(Object * pObject);
	void AddLight	(Light * pLight);
	
	void SetCamera	(Camera * pCamera);	
	Camera &		GetCamera() const;
	
	const std::list<const Light *> & GetLights() const;
	
	void Update();
	void Render();

private:
    void Render1();

private:
	std::list<const Object *>	m_objects;
	std::list<const Light *>	m_lights;
	Camera *					m_pCamera;

    std::shared_ptr<RenderTextureImpl> pRenderTextureImpl;

    // Save temporary data

};
