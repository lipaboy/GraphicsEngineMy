#ifndef GL20SHADOWMATERIAL_H
#define GL20SHADOWMATERIAL_H

#include "GraphicsEngine/Materials/Material.h"

#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Light.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"
#include "GraphicsEngine/Matrix4x4.h"

#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20.h"

#include <chrono>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ShadowMaterial : public Material {
public:
    ShadowMaterial() {
        m_vsFileName = "ShadowMap";
        m_psFileName = "ShadowMap";
    }

    void Init(Object * pObject)
    {
        Material::Init(pObject);

        // TODO: Нужно при компиляции скопировать папку с шейдерами
        // Google it: "visual studio during build copy files into application folder"
    }

    void Deinit()
    {
        Material::Deinit();
    }


    void SetMaterial() {


        // Заполняем матрицы World, View, Proj
        const Matrix4x4 & matWorld	= SceneUtils::GetMatrixWorld(m_pObject);
        const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
        const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();

        const Matrix4x4 matWorldViewProjT	= MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);
        const Matrix4x4 matWorldT			= matWorld.Transpose();
        const Matrix4x4 matWorldNormal		= matWorld.Inverse();

        // Получили список всех источников света в сцене
        std::list<const Light *> lights = SceneUtils::GetLights();
        const Vector4 cameraPosition = Vector4(SceneUtils::GetEyePosition(), 1);
        const size_t MAX_LIGHT_COUNT = 3;
        const size_t count = lights.size() < MAX_LIGHT_COUNT ? lights.size() : MAX_LIGHT_COUNT;     //?????
        //const size_t count = lights.size();

        using namespace std::chrono;
        milliseconds ms = duration_cast< milliseconds >(
            system_clock::now().time_since_epoch()
            );

        SetMaterialBegin();
        {


             // Send our transformation to the currently bound shader,
             // in the "MVP" uniform
             //glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthMVP[0][0]);

            SetVertexShaderBegin();

            Vector3 lightInvDir = -lights.front()->GetDirection();

            // Compute the MVP matrix from the light's point of view
            glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
            glm::mat4 depthViewMatrix = glm::lookAt(
                        //lightInvDir.toGlmVec3(),
                        glm::vec3(10, 0, 10),
                                                    glm::vec3(0,0,10), glm::vec3(0,1,0));
            glm::mat4 depthModelMatrix = glm::mat4(1.0);
            glm::mat4 depthMVP = //depthProjectionMatrix * depthViewMatrix *
                    depthModelMatrix;

            Matrix4x4 depthMVP2;
            depthMVP2 = depthMVP;
            SetVertexShaderMatrix4x4("depthMVP", depthMVP2);
            // rotate our figure
           // SetVertexShaderVector4("timeT", Vector4( 0 * std::sin((double)ms.count() / 800),
             //  0 * std::cos((double)ms.count() / 800), 0, 0));

            SetVertexShaderEnd();


        }
        SetMaterialEnd();

    }
};

#endif // GL20SHADOWMATERIAL_H
