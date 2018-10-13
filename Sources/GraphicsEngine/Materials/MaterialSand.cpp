#include "MaterialSand.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/MathUtils.h"
#include "GraphicsEngine/SceneUtils.h"

namespace graphics_engine {

MaterialTexture::MaterialTexture(std::string const & filename, TextureFilterMode filterMode)
{
	m_vsFileName = "ShaderSand";
	m_psFileName = "ShaderSand";

	m_pTexture1 = NULL;
	m_filterMode = filterMode;
    filename_ = filename;
}

void MaterialTexture::Init(Object * pObject)
{
	Material::Init(pObject);

    m_pTexture1 = new Texture2D(filename_.c_str());
			
	m_pTexture1->SetFilterMode(m_filterMode);	
}

void MaterialTexture::Deinit()
{
	delete m_pTexture1;
	m_pTexture1 = NULL;

	Material::Deinit();
}

void MaterialTexture::SetMaterial()
{
	const Matrix4x4 & matWorld	= SceneUtils::GetMatrixWorld(m_pObject);
	const Matrix4x4 & matView	= SceneUtils::GetMatrixView();
	const Matrix4x4 & matProj	= SceneUtils::GetMatrixProj();
	
	const Matrix4x4 matWorldViewProjT = MathUtils::GetMatrixWorldViewProjT(matWorld, matView, matProj);

	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4("constColor", Vector4(1, 1, 1, 1));
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderTexture2d("texture1", m_pTexture1);
		SetPixelShaderEnd();
	}
	SetMaterialEnd();
}

}
