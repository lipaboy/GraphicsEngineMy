#pragma once
#include "GraphicsEngine/Matrix4x4.h"

namespace graphics_engine {

class FixedFunctionPipelineImpl
{
public:
	virtual void Init() = 0;
	virtual void Deinit() = 0;

    virtual ~FixedFunctionPipelineImpl() {}

	virtual void SetMatrixWorld			(const Matrix4x4 & matrix) = 0;
	virtual void SetMatrixView			(const Matrix4x4 & matrix) = 0;
	virtual void SetMatrixProjection	(const Matrix4x4 & matrix) = 0;
};

}
