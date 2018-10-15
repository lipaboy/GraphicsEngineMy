#pragma once

#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Vector3.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Input.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/GUI.h"

#include "lipaboyLibrary/src/maths/vector2d.h"
#include "lipaboyLibrary/src/maths/rotateoperator.h"

namespace graphics_engine {

using lipaboy_lib::Vector2D;

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
//        currAngle = std::asin(m_Width / Vector2D(m_Height, m_Width).length());
        currAngle = 0;
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

        double coef = 1.01;
        if (Input::GetKey(KEY_CODE_J))
            speed *= coef;
        if (Input::GetKey(KEY_CODE_K))
            speed /= coef;

        if (isFalling_) {
            double deltaTime = speed * Time::GetDeltaTime();

            double diffAngle = 0.;
            for (size_t i = 0; i < FRAGMENTATION_COUNT; i++) {
                auto previousAngle = currAngle;
                currAngle += currAngularSpeed * deltaTime / FRAGMENTATION_COUNT;
                currAngularSpeed += currAngularBoost * deltaTime / FRAGMENTATION_COUNT;
                currAngularBoost = calcBoost(currAngle);
                diffAngle += currAngle - previousAngle;
            }

            m_pObject->m_pTransform->RotateByOperator(rotationAxis, diffAngle);
            if (currAngle >= PI / 2) {
                swingCounter++;
                GUI::Label(5, 5, 100, 20, std::to_string(swingCounter));
            }
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
    size_t FRAGMENTATION_COUNT = 1e3;

    double currAngle;
    double currAngularSpeed;
    double currAngularBoost;

    static constexpr double GRAVITY_FORCE = 9.8;

    bool isFalling_ = false;
    double startTime_;
    double speed = 1.;
    size_t swingCounter = 0;
};

}
