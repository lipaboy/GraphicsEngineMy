#pragma once
#include <math.h>
#include "GraphicsEngine/Math.h"
#include "GraphicsEngine/PlatformApi/Platform.h"

#include "lipaboyLibrary/src/maths/vector3d.h"

#ifdef CAN_USE_OPEN_GL
#include <glm/vec3.hpp>
#endif

namespace graphics_engine {

template <class T>
class Vector3Base
{
public:
    using value_type = T;
public:
    union {
        struct {
            T x, y, z;
        };
        struct {
            T width, height, length;
        };
    };

public:

    Vector3Base()
        : x(0), y(0), z(0)
    {}

    Vector3Base(T x_or_width, T y_or_height, T z_or_length)
        : x(x_or_width), y(y_or_height), z(z_or_length)
    {}

    Vector3Base(const Vector3Base & vec)
        : x(vec.x), y(vec.y), z(vec.z)
    {}

    Vector3Base(const lipaboy_lib::Vector3D & vec)
        : x(vec.x()), y(vec.y()), z(vec.z())
    {}

#ifdef CAN_USE_OPEN_GL
    glm::vec3 toGlmVec3() const {
        return glm::vec3(x, y, z);
    }
#endif

    Vector3Base operator - () const
	{
        return Vector3Base(-x, -y, -z);
	}

    const Vector3Base & operator += (const Vector3Base & vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;

		return *this;
	}

    const Vector3Base & operator -= (const Vector3Base & vec)
	{
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;

		return *this;
	}

    const Vector3Base & operator *= (const T k)
	{
		this->x *= k;
		this->y *= k;
		this->z *= k;

		return *this;
	}

    T Length() const
	{
		return sqrt(x*x + y*y + z*z);
    }

    Vector3Base & Normalize()
	{
		*this *= (1.0 / this->Length());

		return *this;
	}	

    static T Dot(const Vector3Base & a, const Vector3Base & b)
	{
        return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

    static Vector3Base Cross(const Vector3Base & a, const Vector3Base & b)
	{
        return	Vector3Base
				(
					  a.y * b.z - a.z * b.y,
					-(a.x * b.z - a.z * b.x),
					  a.x * b.y - a.y * b.x
				);
	}

	/**
	* @brief Clamps vector coordinates by interval [0,1].
	*/
    static Vector3Base Clamp01(const Vector3Base & a)
	{
        return	Vector3Base
				(
					Math::Clamp(a.x, 0.0, 1.0),
					Math::Clamp(a.y, 0.0, 1.0),
					Math::Clamp(a.z, 0.0, 1.0)
				);
	}

    static Vector3Base Zero()
	{
        return Vector3Base(0, 0, 0);
	}
};

//-----------------------------Free functions---------------------------//

template <class T>
Vector3Base<T> operator + (const Vector3Base<T> & vec1, const Vector3Base<T> & vec2)
{
    Vector3Base<T> result(vec1);

    result += vec2;

    return result;
}

template <class T>
Vector3Base<T> operator - (const Vector3Base<T> & vec1, const Vector3Base<T> & vec2)
{
    Vector3Base<T> result(vec1);

    result -= vec2;

    return result;
}

template <class T>
Vector3Base<T> operator * (const Vector3Base<T> & vec, const T k)
{
    Vector3Base<T> result(vec);

    result *= k;

    return result;
}

template <class T>
Vector3Base<T> operator * (const T k, const Vector3Base<T> & vec)
{
    Vector3Base<T> result(vec * k);

    return result;
}

//--------------------------Vector3-------------------------//

using Vector3 = Vector3Base<double>;
using Vector3_T = typename Vector3::value_type;


}
