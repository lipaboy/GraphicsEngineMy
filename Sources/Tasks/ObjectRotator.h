#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"


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
    DominoFalling(Vector3 direction, Vector3 floorNormal, double angularSpeed)
        : m_Direction(direction), m_FloorNormal(floorNormal), m_AngularStartSpeed(angularSpeed)
    {}

    virtual ~DominoFalling() {}

    virtual void Update()
    {
        if ((nullptr == m_pObject) || (nullptr == m_pObject->m_pTransform))
        {
            return;
        }

        double deltaTime = Time::GetDeltaTime();

//        m_pObject->m_pTransform->Rotate(speed * deltaTime);
        //m_pObject->m_pTransform->RotateByOperator(m_pObject->m_pTransform->GetUp(),
          //                                       speed.x * deltaTime * (PI / 180));
        //m_pObject->m_pTransform->RotateAroundCenter(speed * deltaTime);
    }

private:
    Vector3 m_Direction;
    Vector3 m_FloorNormal;
    double m_AngularStartSpeed;
};
