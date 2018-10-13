#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Input.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"
#include "GraphicsEngine/SceneUtils.h"

namespace graphics_engine {

class CameraController : public Component
{
    Vector3 mousePos;
    bool isCamera = true;

public:
	CameraController()
	{
        mousePos = Vector3::Zero();
	}

	virtual ~CameraController() {}

	virtual void Update() 
	{
        if (Input::GetKeyUp(KEY_CODE_R)) {
            isCamera = !isCamera;
        }
        moveObject((isCamera) ? m_pObject->m_pTransform
                              : SceneUtils::GetLights().front()->GetConstObjectPtr()->m_pTransform);
	}

protected:
    void moveObject(Transform * pObjectTransform) {
        // Translation
        {
            Vector3 forward	= pObjectTransform->GetForward();
            Vector3 right	= pObjectTransform->GetRight();
            Vector3 up = pObjectTransform->GetUp();
            Vector3_T dt = Time::GetDeltaTime();

            Vector3_T speed = (isCamera) ? 1.0 * .5 * 2 * 10
                                      : 1.0 * 3;
            //* (1.0 / 20)
            Vector3 direction;

            if (Input::GetKey(KEY_CODE_W) || Input::GetKey(KEY_CODE_UP_ARROW))
            {
                // Move forward
                direction = forward * speed;
            }
            else if (Input::GetKey(KEY_CODE_S) || Input::GetKey(KEY_CODE_DOWN_ARROW))
            {
                // Move backward
                direction = -forward * speed;
            }

            if (Input::GetKey(KEY_CODE_D) || Input::GetKey(KEY_CODE_RIGHT_ARROW))
            {
                // Move right
                direction = right * speed;
            }
            else if (Input::GetKey(KEY_CODE_A) || Input::GetKey(KEY_CODE_LEFT_ARROW))
            {
                // Move left
                direction = -right * speed;
            }

            if (Input::GetKey(KEY_CODE_Q))
            {
                // Lift up
                direction = up * speed;
            }
            else if (Input::GetKey(KEY_CODE_E))
            {
                // Lift down
                direction = -up * speed;
            }

            if (Input::GetKey(KEY_CODE_LEFT_SHIFT))
                speed *= 10;
            if (Input::GetKey(KEY_CODE_RIGHT_SHIFT))
                speed /= 10;

            pObjectTransform->Translate( speed * dt * direction );
        }

        // Rotation
        {
            const Vector3_T speedAngle = Vector3_T(0.3);
            const Vector3_T epsilon = Vector3_T(1e-6);
            if (Input::GetMouseButton(1))
            {
                // TODO: Task08
                // Rotate pTransform
                Vector3 currPos = Input::GetMousePosition();
                Vector3 vec = (currPos - mousePos) * speedAngle;
                //pObjectTransform->Rotate(Vector3(-vec.y, -vec.x, 0));
               // pObjectTransform->RotateByOperator(Vector3(-vec.y, -vec.x, 0), PI / 200.);
                if (std::abs(vec.x) > epsilon) {
                    pObjectTransform->Rotate(Vector3(0, vec.x, 0));
                    mousePos = currPos;
                }
                if (std::abs(vec.y) > epsilon) {
                    pObjectTransform->Rotate(Vector3(vec.y, 0, 0));
                    mousePos = currPos;
                }
            } else {
                mousePos = Input::GetMousePosition();
            }
        }
    }
};

}
