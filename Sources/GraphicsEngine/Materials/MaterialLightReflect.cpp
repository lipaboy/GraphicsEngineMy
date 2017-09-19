#include "MaterialLightReflect.h"

#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Light.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"

#include <ctime>
#include <chrono>
#include <cmath>

//MaterialLightReflect::MaterialDiffuse()
//{
//    setShaderFilename();
//}


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
        SetVertexShaderBegin();
        SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
        SetVertexShaderVector4("timeT", Vector4( 0 * std::sin((double)ms.count() / 800),
           0 * std::cos((double)ms.count() / 800), 0, 0));
        SetVertexShaderEnd();

        SetPixelShaderBegin();
        SetPixelShaderMatrix4x4	("matWorldNormal",	matWorldNormal);
        SetPixelShaderMatrix4x4	("matWorldT",		matWorldT);
        SetPixelShaderVector4	("materialColor",	Vector4(1, 1, 1, 1));
        SetPixelShaderVector4	("lightsCount",		Vector4(count, 1, 1, 1));
        SetPixelShaderVector4	("cameraPosition",		cameraPosition);

        // Передаём параметры каждого источника света
        int i = 0;
        std::list<const Light *>::iterator iter;
        for (iter = lights.begin(); iter != lights.end(); ++iter, ++i)
        {
            const Light * pLight = *iter;
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
        }

        SetPixelShaderEnd();
    }
    SetMaterialEnd();
}
