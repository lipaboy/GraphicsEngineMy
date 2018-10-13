#pragma once
#include "GraphicsEngine/Vector3.h"
#include "GraphicsEngine/Matrix4x4.h"

#include "lipaboyLibrary/src/maths/rotateoperator.h"

namespace graphics_engine {

class Transform
{
public:
	Transform();
	// TODO: Заменить float на double
	Transform(float x, float y, float z);
	// position (px, py, pz), rotation (rx, ry, rz), scale (sx, sy, sz)
	Transform(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz);
	Transform(Vector3 position, Vector3 eulerAngles = Vector3(0,0,0), Vector3 scale = Vector3(1,1,1));
	
	/*
	* @brief Set parent object.
	* Position, rotation and scale will be relative to parent.
	*/
	void SetParent(Transform * const pParent);

	const Vector3 & GetForward();
	const Vector3 & GetRight();
	const Vector3 & GetUp();

	void SetPosition	(Vector3 position);
	void SetEulerAngles	(Vector3 eulerAngles);
	void SetScale		(Vector3 scale);

	void Translate		(Vector3 vec);
	void Translate		(float x, float y, float z);

	/*
	* @brief Rotate object in local coordinate system.
	*/
    void Rotate             (const Vector3 & euler);
    void RotateAroundCenter (const Vector3 & euler);
    void RotateByOperator     (Vector3 const & asixRotation, double angle);

	/*
	* @brief Rotate object in local coordinate system.
	*/
	void Rotate			(float x, float y, float z);

	const Vector3 & GetPosition() const;
	const Vector3 & GetEulerAngles() const;
	const Vector3 & GetScale() const;

	const Matrix4x4 & GetMatWorld();
    const Matrix4x4 & GetMatView();

private:

	void Recalc();

	Transform * m_pParent;

	Vector3 m_position;
	Vector3 m_eulerAngles;
	Vector3 m_scale;
    // Rotate around center
    Vector3 m_eulerAnglesAroundCenter = Vector3(0, 0, 0);
    lipaboy_lib::Matrix4x4 matRotOp = lipaboy_lib::Matrix4x4::getEye();
//    lipaboy_lib::Matrix4x4 matRotDomino = lipaboy_lib::Matrix4x4::getEye();
public:
    Vector3 preliminaryTranslation = Vector3(0, 0, 0);
private:

	// Вектор "вперёд" в глобальной с.к. (равен (0,0,1) в локальной с.к.)
	Vector3 m_forward;
	// Вектор "вправо" в глобальной с.к. (равен (1,0,0) в локальной с.к.)
	Vector3 m_right;
	// Вектор "вверх" в глобальной с.к. (равен (0,1,0) в локальной с.к.)
	Vector3 m_up;

	Matrix4x4 m_matWorld;
	Matrix4x4 m_matView;

	bool m_shouldRecalc;
};

}
