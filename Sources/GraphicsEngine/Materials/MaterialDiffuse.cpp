#include "MaterialDiffuse.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Lights/Light.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"

namespace graphics_engine {

MaterialDiffuse::MaterialDiffuse()
{
    m_vsFileName = "ShaderDiffuse";
    m_psFileName = "ShaderDiffuse";
}

// TODO: Реализовать переключение Graphics API при нажатии на кнопки (1 - DirectX 11, 2 - OpenGL 2.0, 9 - DirectX 9)
// и отладить на этом механизм использования функций Init() и Deinit()
void MaterialDiffuse::Init(Object * pObject)
{
    MaterialLightReflect::Init(pObject);
	
	// TODO: Нужно при компиляции скопировать папку с шейдерами
	// Google it: "visual studio during build copy files into application folder"
}

void MaterialDiffuse::Deinit()
{
    MaterialLightReflect::Deinit();
}

}
