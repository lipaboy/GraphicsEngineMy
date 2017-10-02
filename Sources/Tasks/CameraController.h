#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Input.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"


class CameraController : public Component
{
	Vector3 mousePos;

public:
	CameraController()
	{
		mousePos = Vector3::Zero();
	}

	virtual ~CameraController() {}

	virtual void Update() 
	{
		Transform * pTransform = m_pObject->m_pTransform;
		
		// Camera Translation
		{
            Vector3 forward	= pTransform->GetForward();
            Vector3 right	= pTransform->GetRight();
            Vector3 up = pTransform->GetUp();
			double dt = Time::GetDeltaTime();

            const double speed = 1.0 * .5 * 2 * 10;
			Vector3 direction;

			if (Input::GetKey(KEY_CODE_W) || Input::GetKey(KEY_CODE_UP_ARROW))
			{
				// TODO: Task08
				// Move forward
                pTransform->RotateAroundCenter(-right.Normalize() * speed* (1.0 / 20));
                //direction = forward;
			}
			else if (Input::GetKey(KEY_CODE_S) || Input::GetKey(KEY_CODE_DOWN_ARROW))
			{
				// TODO: Task08
				// Move backward
                pTransform->RotateAroundCenter(right.Normalize() * speed* (1.0 / 20));
                //direction = -forward;
			}

			if (Input::GetKey(KEY_CODE_D) || Input::GetKey(KEY_CODE_RIGHT_ARROW))
			{
				// TODO: Task08
				// Move right
                pTransform->RotateAroundCenter(up.Normalize() * speed * (1.0 / 20));
			}
			else if (Input::GetKey(KEY_CODE_A) || Input::GetKey(KEY_CODE_LEFT_ARROW))
			{
				// TODO: Task08
				// Move left
                pTransform->RotateAroundCenter(-up.Normalize() * speed * (1.0 / 20));
			}

			if (Input::GetKey(KEY_CODE_LEFT_SHIFT) || Input::GetKey(KEY_CODE_RIGHT_SHIFT))
			{
				// TODO: Task08
				// Move speed up (multiply speed by 10)
			}

			pTransform->Translate( speed * dt * direction );
		}

		// Camera Rotation
		{
			mousePos = Input::GetMousePosition();

            const double speedAngle = 0.3;
			if (Input::GetMouseButton(1))
			{
				// TODO: Task08
				// Rotate pTransform
			}
		}
	}
};
