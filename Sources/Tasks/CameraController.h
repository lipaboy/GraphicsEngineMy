#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Input.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"
#include "GraphicsEngine/SceneUtils.h"

class CameraController : public Component
{
	Vector3 mousePos;
    Transform * pTransform;
    Transform * pLightTransform;
    bool isCamera = true;
    int _cameraSpeed = 10;

public:
    CameraController() {
        mousePos = Vector3::Zero();
	}

    CameraController(int speed) : CameraController() {
        _cameraSpeed = speed;
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
            //Vector3 up = pTransform->GetUp();
            double dt = Time::GetDeltaTime();

            double speed = (isCamera) ? _cameraSpeed
                                      : 1.0 * 3;
            //* (1.0 / 20)
            Vector3 direction;

            //Input::GetKey(KEY_)
            if (Input::GetKey(KEY_CODE_W) || Input::GetKey(KEY_CODE_UP_ARROW))
            {
                // TODO: Task08
                // Move forward
                //pTransform->RotateAroundCenter(-right.Normalize() * speed);

                direction = forward * speed;
            }
            else if (Input::GetKey(KEY_CODE_S) || Input::GetKey(KEY_CODE_DOWN_ARROW))
            {
                // TODO: Task08
                // Move backward
               // pTransform->RotateAroundCenter(right.Normalize() * speed);
                direction = -forward * speed;
            }

            if (Input::GetKey(KEY_CODE_D) || Input::GetKey(KEY_CODE_RIGHT_ARROW))
            {
                // TODO: Task08
                // Move right
                //pTransform->RotateAroundCenter(up.Normalize() * speed );
                direction = right * speed;
            }
            else if (Input::GetKey(KEY_CODE_A) || Input::GetKey(KEY_CODE_LEFT_ARROW))
            {
                // TODO: Task08
                // Move left
                //pTransform->RotateAroundCenter(-up.Normalize() * speed );
                direction = -right * speed;
            }

            if (Input::GetKey(KEY_CODE_LEFT_SHIFT))
            {
                // TODO: Task08
                // Move speed up (multiply speed by 10)
                speed *= 10;
            }
            if (Input::GetKey(KEY_CODE_RIGHT_SHIFT))
                speed /= 10;

            pObjectTransform->Translate( speed * dt * direction );
        }

        // Rotation
        {
            const double speedAngle = 0.3;
            if (Input::GetMouseButton(1))
            {
                // TODO: Task08
                // Rotate pTransform
                Vector3 currPos = Input::GetMousePosition();
                Vector3 vec = (currPos - mousePos) * speedAngle;
                //pObjectTransform->Rotate(Vector3(-vec.y, -vec.x, 0));
               // pObjectTransform->RotateByOperator(Vector3(-vec.y, -vec.x, 0), PI / 200.);
                if (std::abs(vec.x) > 1e-6) {
                    pObjectTransform->Rotate(Vector3(0, vec.x, 0));
                    mousePos = currPos;
                }
                if (std::abs(vec.y) > 1e-6) {
                    pObjectTransform->Rotate(Vector3(vec.y, 0, 0));
                    mousePos = currPos;
                }
            } else {
                mousePos = Input::GetMousePosition();
            }
        }
    }
};
