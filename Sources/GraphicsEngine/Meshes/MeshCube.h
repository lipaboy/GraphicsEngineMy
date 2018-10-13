#pragma once
#include "Mesh.h"

namespace graphics_engine {

class MeshCube : public Mesh
{
public:
	MeshCube(int levelCount = 1);

	virtual void Init();
	virtual void Deinit();

private:
	void InitCubeSimple();
	void InitCubeDetailedStrip();
	void InitCubeDetailedList();	

	int m_levelCount;	
};

}
