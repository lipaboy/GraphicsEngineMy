#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"
#include "GraphicsEngine/Input.h"

#include "lipaboyLibrary/src/maths/vector2d.h"

namespace graphics_engine {

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
		
        Vector3_T deltaTime = Time::GetDeltaTime();

        m_pObject->m_pTransform->Rotate(speed * deltaTime);
        //m_pObject->m_pTransform->RotateByOperator(m_pObject->m_pTransform->GetUp(),
          //                                       speed.x * deltaTime * (PI / 180));
        //m_pObject->m_pTransform->RotateAroundCenter(speed * deltaTime);
	}
};

//------------------------------------------------------//
//------------------------------------------------------//
//------------------------------------------------------//

}
