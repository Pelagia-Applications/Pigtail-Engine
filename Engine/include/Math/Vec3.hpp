#pragma once

#include <cmath>

namespace Pigtail
{

class Vec3
{
public:
    float x;
    float y;
    float z;

    Vec3();
    Vec3(float x, float y, float z);

    static Vec3 zero();
    static Vec3 one();

    static Vec3 up();
    static Vec3 down();

    static Vec3 right();
    static Vec3 left();

    static Vec3 forward();
    static Vec3 back();

    float length() const;
    float lengthSquared() const;

    Vec3 normalized() const;
    void normalize();

    float dot(const Vec3& other) const;

    static float dot(
        const Vec3& a,
        const Vec3& b
    );

    Vec3 cross(const Vec3& other) const;

    static Vec3 cross(
        const Vec3& a,
        const Vec3& b
    );

    float distanceTo(const Vec3& other) const;

    static float distance(
        const Vec3& a,
        const Vec3& b
    );

    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;

    Vec3 operator*(float scalar) const;
    Vec3 operator/(float scalar) const;

    Vec3& operator+=(const Vec3& other);
    Vec3& operator-=(const Vec3& other);

    Vec3& operator*=(float scalar);
    Vec3& operator/=(float scalar);

    Vec3 operator-() const;

    bool operator==(const Vec3& other) const;
    bool operator!=(const Vec3& other) const;
};

Vec3 operator*(
    float scalar,
    const Vec3& vector
);

}