#include "Math/Vec2.hpp"

namespace Pigtail
{

Vec2::Vec2()
    : x(0.0f), y(0.0f)
{
}

Vec2::Vec2(float x, float y)
    : x(x), y(y)
{
}

Vec2 Vec2::zero()
{
    return Vec2(0.0f, 0.0f);
}

Vec2 Vec2::one()
{
    return Vec2(1.0f, 1.0f);
}

Vec2 Vec2::up()
{
    return Vec2(0.0f, 1.0f);
}

Vec2 Vec2::down()
{
    return Vec2(0.0f, -1.0f);
}

Vec2 Vec2::right()
{
    return Vec2(1.0f, 0.0f);
}

Vec2 Vec2::left()
{
    return Vec2(-1.0f, 0.0f);
}

float Vec2::length() const
{
    return std::sqrt(x * x + y * y);
}

float Vec2::lengthSquared() const
{
    return x * x + y * y;
}

Vec2 Vec2::normalized() const
{
    const float len = length();

    if (len <= 0.000001f)
        return Vec2::zero();

    return Vec2(x / len, y / len);
}

void Vec2::normalize()
{
    const float len = length();

    if (len <= 0.000001f)
    {
        x = 0.0f;
        y = 0.0f;
        return;
    }

    x /= len;
    y /= len;
}

float Vec2::dot(const Vec2& other) const
{
    return x * other.x + y * other.y;
}

float Vec2::dot(
    const Vec2& a,
    const Vec2& b
)
{
    return a.x * b.x + a.y * b.y;
}

float Vec2::distanceTo(const Vec2& other) const
{
    return (*this - other).length();
}

float Vec2::distance(
    const Vec2& a,
    const Vec2& b
)
{
    return (a - b).length();
}

Vec2 Vec2::operator+(const Vec2& other) const
{
    return Vec2(
        x + other.x,
        y + other.y
    );
}

Vec2 Vec2::operator-(const Vec2& other) const
{
    return Vec2(
        x - other.x,
        y - other.y
    );
}

Vec2 Vec2::operator*(float scalar) const
{
    return Vec2(
        x * scalar,
        y * scalar
    );
}

Vec2 Vec2::operator/(float scalar) const
{
    return Vec2(
        x / scalar,
        y / scalar
    );
}

Vec2& Vec2::operator+=(const Vec2& other)
{
    x += other.x;
    y += other.y;

    return *this;
}

Vec2& Vec2::operator-=(const Vec2& other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

Vec2& Vec2::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

Vec2& Vec2::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;

    return *this;
}

Vec2 Vec2::operator-() const
{
    return Vec2(-x, -y);
}

bool Vec2::operator==(const Vec2& other) const
{
    return x == other.x && y == other.y;
}

bool Vec2::operator!=(const Vec2& other) const
{
    return !(*this == other);
}

Vec2 operator*(
    float scalar,
    const Vec2& vector
)
{
    return vector * scalar;
}

}