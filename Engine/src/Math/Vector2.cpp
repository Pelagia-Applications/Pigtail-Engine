#include "Math/Vector2.hpp"

namespace Pigtail
{

Vector2::Vector2()
    : x(0.0f), y(0.0f)
{
}

Vector2::Vector2(float x, float y)
    : x(x), y(y)
{
}

Vector2 Vector2::zero()
{
    return Vector2(0.0f, 0.0f);
}

Vector2 Vector2::one()
{
    return Vector2(1.0f, 1.0f);
}

Vector2 Vector2::up()
{
    return Vector2(0.0f, 1.0f);
}

Vector2 Vector2::down()
{
    return Vector2(0.0f, -1.0f);
}

Vector2 Vector2::right()
{
    return Vector2(1.0f, 0.0f);
}

Vector2 Vector2::left()
{
    return Vector2(-1.0f, 0.0f);
}

float Vector2::length() const
{
    return std::sqrt(x * x + y * y);
}

float Vector2::lengthSquared() const
{
    return x * x + y * y;
}

Vector2 Vector2::normalized() const
{
    const float len = length();

    if (len <= 0.000001f)
        return Vector2::zero();

    return Vector2(x / len, y / len);
}

void Vector2::normalize()
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

float Vector2::dot(const Vector2& other) const
{
    return x * other.x + y * other.y;
}

float Vector2::dot(
    const Vector2& a,
    const Vector2& b
)
{
    return a.x * b.x + a.y * b.y;
}

float Vector2::distanceTo(const Vector2& other) const
{
    return (*this - other).length();
}

float Vector2::distance(
    const Vector2& a,
    const Vector2& b
)
{
    return (a - b).length();
}

Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2(
        x + other.x,
        y + other.y
    );
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return Vector2(
        x - other.x,
        y - other.y
    );
}

Vector2 Vector2::operator*(float scalar) const
{
    return Vector2(
        x * scalar,
        y * scalar
    );
}

Vector2 Vector2::operator/(float scalar) const
{
    return Vector2(
        x / scalar,
        y / scalar
    );
}

Vector2& Vector2::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;

    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

Vector2& Vector2::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

Vector2& Vector2::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;

    return *this;
}

Vector2 Vector2::operator-() const
{
    return Vector2(-x, -y);
}

bool Vector2::operator==(const Vector2& other) const
{
    return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2& other) const
{
    return !(*this == other);
}

Vector2 operator*(
    float scalar,
    const Vector2& vector
)
{
    return vector * scalar;
}

}