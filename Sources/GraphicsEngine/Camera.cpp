#include "Camera.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Math.h"
#include "GraphicsEngine/Screen.h"



Camera::Camera()
{
	m_fovY		= 45.0f;
	m_nearPlane	= 0.1f;
	m_farPlane	= 1000.0f;
}


// Установка вертикального угла обзора (в градусах)
void Camera::SetFovY( float fovY )
{
	m_fovY = Math::Clamp(fovY, 1, 179);
}

// Установка ближней отсекающей плоскости
void Camera::SetNearPlane( float nearPlane )
{
	//TODO: Добавить проверку на положительность и far > near
	m_nearPlane = nearPlane;
}

// Установка дальней отсекающей плоскости
void Camera::SetFarPlane( float farPlane )
{
	//TODO: Добавить проверку на положительность и far > near
	m_farPlane = farPlane;
}

void Camera::SetViewport(Rect rect)
{
	viewport = rect;
}

Rect Camera::GetViewport()
{
	return viewport;
}

const Matrix4x4 & Camera::GetMatrixView()
{
    // TODO:    wrong LightDirectional's matView
    if (nullptr == lightSide)
        return m_pObject->m_pTransform->GetMatView();
    return lightSide->GetConstObjectPtr()->m_pTransform->GetMatView();
}

const Matrix4x4 & Camera::GetMatrixProj()
{
	RecalculateMatrixProj();	

	return m_matProj;
}

#ifdef CAN_USE_OPEN_GL
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#endif

void Camera::RecalculateMatrixProj()
{
	float sw = Screen::GetWidth();
	float sh = Screen::GetHeight();

	float vw = viewport.w;
	float vh = viewport.h;

	float aspect = (sw * vw) / (sh * vh);
	
    if (nullptr == lightSide || LIGHT_SPOT == lightSide->GetType().x)
        m_matProj = Matrix4x4::PerspectiveFovLH( m_fovY, aspect, m_nearPlane, m_farPlane );
    else if (LIGHT_DIRECTIONAL == lightSide->GetType().x) {
#ifdef CAN_USE_OPEN_GL
        float val = 20;
        m_matProj = Matrix4x4::OrhographicLH(val, val, m_nearPlane, m_farPlane);
#endif
    }
}
