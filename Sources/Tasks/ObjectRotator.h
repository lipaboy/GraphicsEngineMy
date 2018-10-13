#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"
#include "GraphicsEngine/Input.h"

#include "lipaboyLibrary/src/maths/vector2d.h"

using lipaboy_lib::Vector2D;

class ObjectRotator : public Component
{
	Vector3 speed;

public:
    ObjectRotator(double x, double y, double z)
	{
		speed = Vector3(x, y, z);
	}

	virtual ~ObjectRotator() {}

	virtual void Update() 
	{
        if ((nullptr == m_pObject) || (nullptr == m_pObject->m_pTransform))
		{
			return;
		}
		
		double deltaTime = Time::GetDeltaTime();

        m_pObject->m_pTransform->Rotate(speed * deltaTime);
        //m_pObject->m_pTransform->RotateByOperator(m_pObject->m_pTransform->GetUp(),
          //                                       speed.x * deltaTime * (PI / 180));
        //m_pObject->m_pTransform->RotateAroundCenter(speed * deltaTime);
	}
};

//------------------------------------------------------//
//------------------------------------------------------//
//------------------------------------------------------//

class DominoFalling : public Component
{
public:
    DominoFalling(Vector3 directionOfFalling, Vector3 floorNormal,
                  double angularStartSpeed, double height, double width)
        : m_Direction(directionOfFalling),
          m_FloorNormal(floorNormal),
          m_AngularStartSpeed(angularStartSpeed),
          m_Height(height),
          m_Width(width)
    {
        rotationAxis = Vector3::Cross(directionOfFalling, floorNormal).Normalize();
        currAngle = std::asin(m_Width / Vector2D(m_Height, m_Width).length());
        currAngularSpeed = angularStartSpeed;
        currAngularBoost = calcBoost(currAngle);
    }

    virtual ~DominoFalling() {}

    virtual void Update()
    {
        if ((nullptr == m_pObject) || (nullptr == m_pObject->m_pTransform))
        {
            return;
        }

        if (Input::GetKey(KEY_CODE_H)) {
            isFalling_ = true;
            startTime_ = Time::GetTime();
        }

        if (isFalling_) {
            double deltaTime = Time::GetTime() - startTime_;
            startTime_ = Time::GetTime();

            auto previousAngle = currAngle;
            currAngle += currAngularSpeed * deltaTime;
            currAngularSpeed += currAngularBoost * deltaTime;
            currAngularBoost = calcBoost(currAngle);

            m_pObject->m_pTransform->RotateByOperator(rotationAxis,
                                                      currAngle - previousAngle
//                                                      deltaTime * PI / 5
                                                      );

//            if (currAngle >= PI / 2)
//                isFalling_ = false;
        }
    }

public:
    double calcBoost(double angle) {
        return 3. / 2. * GRAVITY_FORCE * m_Height * m_Width
                / Vector2D(m_Height, m_Width).length()
                * std::sin(angle + std::asin(m_Width / Vector2D(m_Height, m_Width).length()));
    }

private:
    Vector3 m_Direction;
    Vector3 m_FloorNormal;
    double m_AngularStartSpeed;
    double m_Height;
    double m_Width;

    Vector3 rotationAxis;

    double currAngle;
    double currAngularSpeed;
    double currAngularBoost;

    static constexpr double GRAVITY_FORCE = 9.8;

    bool isFalling_ = false;
    double startTime_;
};
