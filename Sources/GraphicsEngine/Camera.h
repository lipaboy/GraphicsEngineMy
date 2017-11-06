#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Matrix4x4.h"
#include "GraphicsEngine/Rect.h"
#include "Lights/Light.h"

#include <memory>

class Camera : public Component
{
public:
	Camera();
	
	// Установка вертикального угла обзора (в градусах)
	void SetFovY		(float fovY);
	// Установка ближней отсекающей плоскости
	void SetNearPlane	(float nearPlane);
	// Установка дальней отсекающей плоскости
	void SetFarPlane	(float farPlane);

	/**
	* @brief Where on the screen is the camera rendered in normalized coordinates
	* http://www.gamedev.net/page/resources/_/technical/game-programming/a-room-with-a-view-r3901.
	*/
	void SetViewport	(Rect rect = Rect(0.0f, 0.0f, 1.0f, 1.0f));
	Rect GetViewport	();
		
	const Matrix4x4 & GetMatrixView();
	const Matrix4x4 & GetMatrixProj();

    // Camera will be looking from light position
    void SetLightSide(AbstractLight const * light) { lightSide = light; }
    void SetCameraSide() { lightSide = nullptr; }
    const AbstractLight * GetLightSide() const { return lightSide; }

       // I don't know: need it or not?
//    const Object * GetConstObjectPtr() const
//    { return (nullptr == lightSide) ? m_pObject : lightSide->GetConstObjectPtr(); }

private:
    // TODO: May be move it to Update virtual method??
	void RecalculateMatrixProj();

private:
    const AbstractLight * lightSide = nullptr;

	// Вертикальный угол обзора в градусах
	float m_fovY;
	float m_nearPlane;
	float m_farPlane;

	Matrix4x4 m_matProj;

	Rect viewport;


};
