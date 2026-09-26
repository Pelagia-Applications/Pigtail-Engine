#pragma once

#include <cmath>

namespace Pigtail
{

class Vec2
{
public:
    float x;
    float y;

    Vec2();
    Vec2(float x, float y);

    static Vec2 zero();
    static Vec2 one();
    static Vec2 up();
    static Vec2 down();
    static Vec2 right();
    static Vec2 left();

    float length() const;
    float lengthSquared() const;

    Vec2 normalized() const;
    void normalize();

    float dot(const Vec2& other) const;

    static float dot(
        const Vec2& a,
        const Vec2& b
    );

    float distanceTo(const Vec2& other) const;

    static float distance(
        const Vec2& a,
        const Vec2& b
    );

    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;

    Vec2 operator*(float scalar) const;
    Vec2 operator/(float scalar) const;

    Vec2& operator+=(const Vec2& other);
    Vec2& operator-=(const Vec2& other);

    Vec2& operator*=(float scalar);
    Vec2& operator/=(float scalar);

    Vec2 operator-() const;

    bool operator==(const Vec2& other) const;
    bool operator!=(const Vec2& other) const;
};

Vec2 operator*(
    float scalar,
    const Vec2& vector
);

}