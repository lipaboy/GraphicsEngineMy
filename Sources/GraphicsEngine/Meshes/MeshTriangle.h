#pragma once
#include "Mesh.h"

namespace graphics_engine {

// Design Patterns: Bridge (role - RefinedAbstraction).
class MeshTriangle : public Mesh
{
public:
	virtual void Init();
	virtual void Deinit();
};

}
