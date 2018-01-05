#include "MaterialLightReflect.h"

#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Lights/Light.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"

#include <ctime>
#include <chrono>
#include <cmath>

//MaterialLightReflect::MaterialDiffuse()
//{
//    setShaderFilename();
//}

//#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20GraphicsEngine.h"
//#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20.h"

// TODO: Реализовать переключение Graphics API при нажатии на кнопки (1 - DirectX 11, 2 - OpenGL 2.0, 9 - DirectX 9)
// и отладить на этом механизм использования функций Init() и Deinit()
void MaterialLightReflect::Init(Object * pObject)
{
    Material::Init(pObject);

    // TODO: Нужно при компиляции скопировать папку с шейдерами
    // Google it: "visual studio during build copy files into application folder"
}

void MaterialLightReflect::Deinit()
{
    Material::Deinit();
}

void MaterialLightReflect::SetMaterial()
{

    // Заполняем матрицы World, View, Proj
    const Matrix4x4 & matWorld	= SceneUtils::GetMatrixWorld(m_pObject);
    const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
    const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();

    const Matrix4x4 matWorldViewProjT	= MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);
    const Matrix4x4 matWorldT			= matWorld.Transpose();
    const Matrix4x4 matWorldNormal		= matWorld.Inverse();

    // Получили список всех источников света в сцене
    const std::list<const AbstractLight *> & lights = SceneUtils::GetLights();
    const Vector4 cameraPosition = Vector4(SceneUtils::GetEyePosition(), 1);

    // This constraint needs because you can have only static arrays in shader
    const size_t MAX_LIGHT_COUNT = 10;
    const size_t count = lights.size() < MAX_LIGHT_COUNT ? lights.size() : MAX_LIGHT_COUNT;

    // Need for making move objects on scene
    using namespace std::chrono;
    milliseconds ms = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
        );

    Camera & camera = Application::Instance().GetScene().GetCamera();
    
    SetMaterialBegin();
    {
        SetVertexShaderBegin();
        SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
        SetVertexShaderVector4  ("timeT", Vector4( 0 * std::sin((double)ms.count() / 800),
                    0 * std::cos((double)ms.count() / 800), 0, 0));
        SetPixelShaderVector4	("lightsCount",		Vector4(count, 1, 1, 1));
        int i = 0;
        std::list<const AbstractLight *>::const_iterator iter;
        for (iter = lights.begin(); iter != lights.end(); ++iter, ++i)
        {
            const AbstractLight * pLight = *iter;
            std::string lightStr = "lightSpaceMatrix[" + std::to_string(static_cast<long long>(i)) + "]";
            SetVertexShaderMatrix4x4(lightStr.c_str(), pLight->GetLightSpaceMatrix() * matWorldT);
        }
        SetVertexShaderEnd();

        SetPixelShaderBegin();      // == fragment shader
        SetPixelShaderMatrix4x4	("matWorldNormal",	matWorldNormal);
        SetPixelShaderMatrix4x4	("matWorldT",		matWorldT);
        SetPixelShaderVector4	("materialColor",	Vector4(ambientColor, 1));
        SetPixelShaderVector4	("lightsCount",		Vector4(count, 1, 1, 1));
        SetPixelShaderVector4	("cameraPosition",		cameraPosition);
        SetPixelShaderVector4("farPlane", Vector4(camera.getFarPlane(), 0., 0., 0.));
        SetPixelShaderVector4("nearPlane", Vector4(camera.getNearPlane(), 0., 0., 0.));

        // Передаём параметры каждого источника света
        i = 0;
        //std::list<const AbstractLight *>::const_iterator iter;
        for (iter = lights.begin(); iter != lights.end(); ++iter, ++i)
        {
            const AbstractLight * pLight = *iter;
            const Vector4 lightType			= pLight->GetType();
            const Vector4 lightPosition		= Vector4( pLight->GetPosition(), 1 );
            const Vector4 lightDirection	= Vector4( pLight->GetDirection(), 0 );
            const Vector4 lightColor		= pLight->GetColor();

            // "lights[i]"
            std::string lightStr = "lights[" + std::to_string(static_cast<long long>(i)) + "]";

            // "lights[i].type", "lights[i].position", "lights[i].direction", "lights[i].color"
            SetPixelShaderVector4( (lightStr + ".type").c_str(),		lightType);
            SetPixelShaderVector4( (lightStr + ".position").c_str(),	lightPosition );
            SetPixelShaderVector4( (lightStr + ".direction").c_str(),	lightDirection );
            SetPixelShaderVector4( (lightStr + ".color").c_str(),		lightColor );
            //SetPixelShaderM( (lightStr + ".color").c_str(),		lightColor );
        }

        SetPixelShaderEnd();
    }
    SetMaterialEnd();
}
