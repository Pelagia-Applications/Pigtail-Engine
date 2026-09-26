#include "Math/Vec3.hpp"

namespace Pigtail
{

Vec3::Vec3()
    : x(0.0f), y(0.0f), z(0.0f)
{
}

Vec3::Vec3(float x, float y, float z)
    : x(x), y(y), z(z)
{
}

Vec3 Vec3::zero()
{
    return Vec3(0.0f, 0.0f, 0.0f);
}

Vec3 Vec3::one()
{
    return Vec3(1.0f, 1.0f, 1.0f);
}

Vec3 Vec3::up()
{
    return Vec3(0.0f, 1.0f, 0.0f);
}

Vec3 Vec3::down()
{
    return Vec3(0.0f, -1.0f, 0.0f);
}

Vec3 Vec3::right()
{
    return Vec3(1.0f, 0.0f, 0.0f);
}

Vec3 Vec3::left()
{
    return Vec3(-1.0f, 0.0f, 0.0f);
}

Vec3 Vec3::forward()
{
    return Vec3(0.0f, 0.0f, -1.0f);
}

Vec3 Vec3::back()
{
    return Vec3(0.0f, 0.0f, 1.0f);
}

float Vec3::length() const
{
    return std::sqrt(
        x * x +
        y * y +
        z * z
    );
}

float Vec3::lengthSquared() const
{
    return x * x + y * y + z * z;
}

Vec3 Vec3::normalized() const
{
    const float len = length();

    if (len <= 0.000001f)
        return Vec3::zero();

    return Vec3(
        x / len,
        y / len,
        z / len
    );
}

void Vec3::normalize()
{
    const float len = length();

    if (len <= 0.000001f)
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        return;
    }

    x /= len;
    y /= len;
    z /= len;
}

float Vec3::dot(const Vec3& other) const
{
    return
        x * other.x +
        y * other.y +
        z * other.z;
}

float Vec3::dot(
    const Vec3& a,
    const Vec3& b
)
{
    return
        a.x * b.x +
        a.y * b.y +
        a.z * b.z;
}

Vec3 Vec3::cross(const Vec3& other) const
{
    return Vec3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

Vec3 Vec3::cross(
    const Vec3& a,
    const Vec3& b
)
{
    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

float Vec3::distanceTo(const Vec3& other) const
{
    return (*this - other).length();
}

float Vec3::distance(
    const Vec3& a,
    const Vec3& b
)
{
    return (a - b).length();
}

Vec3 Vec3::operator+(const Vec3& other) const
{
    return Vec3(
        x + other.x,
        y + other.y,
        z + other.z
    );
}

Vec3 Vec3::operator-(const Vec3& other) const
{
    return Vec3(
        x - other.x,
        y - other.y,
        z - other.z
    );
}

Vec3 Vec3::operator*(float scalar) const
{
    return Vec3(
        x * scalar,
        y * scalar,
        z * scalar
    );
}

Vec3 Vec3::operator/(float scalar) const
{
    return Vec3(
        x / scalar,
        y / scalar,
        z / scalar
    );
}

Vec3& Vec3::operator+=(const Vec3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Vec3& Vec3::operator-=(const Vec3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

Vec3& Vec3::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
}

Vec3& Vec3::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;

    return *this;
}

Vec3 Vec3::operator-() const
{
    return Vec3(-x, -y, -z);
}

bool Vec3::operator==(const Vec3& other) const
{
    return
        x == other.x &&
        y == other.y &&
        z == other.z;
}

bool Vec3::operator!=(const Vec3& other) const
{
    return !(*this == other);
}

Vec3 operator*(
    float scalar,
    const Vec3& vector
)
{
    return vector * scalar;
}

}