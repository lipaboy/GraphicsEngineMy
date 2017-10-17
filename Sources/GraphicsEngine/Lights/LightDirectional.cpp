#include "LightDirectional.h"

#include "GraphicsEngine/MathUtils.h"

#ifdef CAN_USE_OPEN_GL
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#endif

const Matrix4x4 & LightDirectional::GetProjectionMatrix() const
{
//    float val = 2 ;
//    m_spaceMatrix = glm::ortho<float>(-val,val,-val,val
//                                                       // ,-10, 15
//                                  ,0.001, 10000
//                                  );
//    m_spaceMatrix = m_spaceMatrix.Transpose();

    return m_spaceMatrix;
}
