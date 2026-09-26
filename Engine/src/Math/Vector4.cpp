#include "Math/Vector4.hpp"

#include <cmath>

namespace Pigtail
{

Vector4::Vector4()
    : x(0.0f),
      y(0.0f),
      z(0.0f),
      w(0.0f)
{
}

Vector4::Vector4(
    float x,
    float y,
    float z,
    float w
)
    : x(x),
      y(y),
      z(z),
      w(w)
{
}

Vector4::Vector4(
    const Vector3& vector,
    float w
)
    : x(vector.x),
      y(vector.y),
      z(vector.z),
      w(w)
{
}

Vector4 Vector4::zero()
{
    return Vector4(
        0.0f,
        0.0f,
        0.0f,
        0.0f
    );
}

Vector4 Vector4::one()
{
    return Vector4(
        1.0f,
        1.0f,
        1.0f,
        1.0f
    );
}

float Vector4::length() const
{
    return std::sqrt(
        x * x +
        y * y +
        z * z +
        w * w
    );
}

float Vector4::lengthSquared() const
{
    return
        x * x +
        y * y +
        z * z +
        w * w;
}

Vector4 Vector4::normalized() const
{
    const float len = length();

    if (len <= 0.000001f)
        return Vector4::zero();

    return Vector4(
        x / len,
        y / len,
        z / len,
        w / len
    );
}

void Vector4::normalize()
{
    const float len = length();

    if (len <= 0.000001f)
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        w = 0.0f;
        return;
    }

    x /= len;
    y /= len;
    z /= len;
    w /= len;
}

float Vector4::dot(const Vector4& other) const
{
    return
        x * other.x +
        y * other.y +
        z * other.z +
        w * other.w;
}

float Vector4::dot(
    const Vector4& a,
    const Vector4& b
)
{
    return
        a.x * b.x +
        a.y * b.y +
        a.z * b.z +
        a.w * b.w;
}

Vector4 Vector4::operator+(const Vector4& other) const
{
    return Vector4(
        x + other.x,
        y + other.y,
        z + other.z,
        w + other.w
    );
}

Vector4 Vector4::operator-(const Vector4& other) const
{
    return Vector4(
        x - other.x,
        y - other.y,
        z - other.z,
        w - other.w
    );
}

Vector4 Vector4::operator*(float scalar) const
{
    return Vector4(
        x * scalar,
        y * scalar,
        z * scalar,
        w * scalar
    );
}

Vector4 Vector4::operator/(float scalar) const
{
    return Vector4(
        x / scalar,
        y / scalar,
        z / scalar,
        w / scalar
    );
}

Vector4& Vector4::operator+=(const Vector4& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;

    return *this;
}

Vector4& Vector4::operator-=(const Vector4& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;

    return *this;
}

Vector4& Vector4::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;

    return *this;
}

Vector4& Vector4::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;

    return *this;
}

Vector4 Vector4::operator-() const
{
    return Vector4(
        -x,
        -y,
        -z,
        -w
    );
}

bool Vector4::operator==(const Vector4& other) const
{
    return
        x == other.x &&
        y == other.y &&
        z == other.z &&
        w == other.w;
}

bool Vector4::operator!=(const Vector4& other) const
{
    return !(*this == other);
}

Vector4 operator*(
    float scalar,
    const Vector4& vector
)
{
    return vector * scalar;
}

}