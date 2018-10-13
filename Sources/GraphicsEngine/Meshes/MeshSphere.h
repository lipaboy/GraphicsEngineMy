#pragma once
#include "Mesh.h"

namespace graphics_engine {

// Design Patterns: Bridge (role - RefinedAbstraction).
class MeshSphere : public Mesh
{
public:

	MeshSphere(int levelCount = 3);

	virtual void Init();
	virtual void Deinit();

private:
	int m_levelCount;	
};

}
