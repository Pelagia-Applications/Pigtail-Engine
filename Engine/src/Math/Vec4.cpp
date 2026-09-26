#include "Math/Vec4.hpp"

#include <cmath>

namespace Pigtail
{

Vec4::Vec4()
    : x(0.0f),
      y(0.0f),
      z(0.0f),
      w(0.0f)
{
}

Vec4::Vec4(
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

Vec4::Vec4(
    const Vec3& vector,
    float w
)
    : x(vector.x),
      y(vector.y),
      z(vector.z),
      w(w)
{
}

Vec4 Vec4::zero()
{
    return Vec4(
        0.0f,
        0.0f,
        0.0f,
        0.0f
    );
}

Vec4 Vec4::one()
{
    return Vec4(
        1.0f,
        1.0f,
        1.0f,
        1.0f
    );
}

float Vec4::length() const
{
    return std::sqrt(
        x * x +
        y * y +
        z * z +
        w * w
    );
}

float Vec4::lengthSquared() const
{
    return
        x * x +
        y * y +
        z * z +
        w * w;
}

Vec4 Vec4::normalized() const
{
    const float len = length();

    if (len <= 0.000001f)
        return Vec4::zero();

    return Vec4(
        x / len,
        y / len,
        z / len,
        w / len
    );
}

void Vec4::normalize()
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

float Vec4::dot(const Vec4& other) const
{
    return
        x * other.x +
        y * other.y +
        z * other.z +
        w * other.w;
}

float Vec4::dot(
    const Vec4& a,
    const Vec4& b
)
{
    return
        a.x * b.x +
        a.y * b.y +
        a.z * b.z +
        a.w * b.w;
}

Vec4 Vec4::operator+(const Vec4& other) const
{
    return Vec4(
        x + other.x,
        y + other.y,
        z + other.z,
        w + other.w
    );
}

Vec4 Vec4::operator-(const Vec4& other) const
{
    return Vec4(
        x - other.x,
        y - other.y,
        z - other.z,
        w - other.w
    );
}

Vec4 Vec4::operator*(float scalar) const
{
    return Vec4(
        x * scalar,
        y * scalar,
        z * scalar,
        w * scalar
    );
}

Vec4 Vec4::operator/(float scalar) const
{
    return Vec4(
        x / scalar,
        y / scalar,
        z / scalar,
        w / scalar
    );
}

Vec4& Vec4::operator+=(const Vec4& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;

    return *this;
}

Vec4& Vec4::operator-=(const Vec4& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;

    return *this;
}

Vec4& Vec4::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;

    return *this;
}

Vec4& Vec4::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;

    return *this;
}

Vec4 Vec4::operator-() const
{
    return Vec4(
        -x,
        -y,
        -z,
        -w
    );
}

bool Vec4::operator==(const Vec4& other) const
{
    return
        x == other.x &&
        y == other.y &&
        z == other.z &&
        w == other.w;
}

bool Vec4::operator!=(const Vec4& other) const
{
    return !(*this == other);
}

Vec4 operator*(
    float scalar,
    const Vec4& vector
)
{
    return vector * scalar;
}

}