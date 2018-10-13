#pragma once
#include "GraphicsEngine/GraphicsApi/MeshImpl.h"

namespace graphics_engine {

// Interface for a mesh.
// Subclasses implement concrete meshes, e.g. triagle, quad, cube, sphere.
// Design Patterns: Strategy (role - Context) or Bridge (role - Abstraction).
class Mesh
{
public:

	Mesh();
    virtual ~Mesh() {}

	virtual void Init();
	virtual void Deinit();

	void Render();

protected:
	MeshImpl * meshImpl;
};

}
