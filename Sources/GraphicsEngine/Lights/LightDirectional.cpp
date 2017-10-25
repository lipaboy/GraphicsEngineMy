#include "LightDirectional.h"

#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"

#ifdef CAN_USE_OPEN_GL
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#endif

void LightDirectional::RecalcLightSpaceMatrix()
{
    Matrix4x4 biasMatrix = {
        0.5, 0.0, 0.0, 0.0,
        0.0, 0.5, 0.0, 0.0,
        0.0, 0.0, 0.5, 0.0,
        0.5, 0.5, 0.5, 1.0
    };

    Camera & camera = Application::Instance().GetScene().GetCamera();

    bool temp = camera.isPerspective;
    camera.isPerspective = false;

    Matrix4x4 depthViewMatrix;
    depthViewMatrix = glm::lookAt(
                glm::vec3(20, 0, 0),
                                glm::vec3(0,0,0), glm::vec3(0,1,0));
    depthViewMatrix = depthViewMatrix.Transpose();
    m_spaceMatrix = MathUtils::GetMatrixWorldViewProjT(Matrix4x4::Identity(), depthViewMatrix,
                                                                        SceneUtils::GetMatrixProj());

    camera.isPerspective = temp;

}
