#pragma once

#include <cmath>

namespace Pigtail
{

class Vector2
{
public:
    float x;
    float y;

    Vector2();
    Vector2(float x, float y);

    static Vector2 zero();
    static Vector2 one();
    static Vector2 up();
    static Vector2 down();
    static Vector2 right();
    static Vector2 left();

    float length() const;
    float lengthSquared() const;

    Vector2 normalized() const;
    void normalize();

    float dot(const Vector2& other) const;

    static float dot(
        const Vector2& a,
        const Vector2& b
    );

    float distanceTo(const Vector2& other) const;

    static float distance(
        const Vector2& a,
        const Vector2& b
    );

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;

    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;

    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);

    Vector2& operator*=(float scalar);
    Vector2& operator/=(float scalar);

    Vector2 operator-() const;

    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;
};

Vector2 operator*(
    float scalar,
    const Vector2& vector
);

}