#pragma once

#include <cmath>

namespace Pigtail
{

class Vector3
{
public:
    float x;
    float y;
    float z;

    Vector3();
    Vector3(float x, float y, float z);

    static Vector3 zero();
    static Vector3 one();

    static Vector3 up();
    static Vector3 down();

    static Vector3 right();
    static Vector3 left();

    static Vector3 forward();
    static Vector3 back();

    float length() const;
    float lengthSquared() const;

    Vector3 normalized() const;
    void normalize();

    float dot(const Vector3& other) const;

    static float dot(
        const Vector3& a,
        const Vector3& b
    );

    Vector3 cross(const Vector3& other) const;

    static Vector3 cross(
        const Vector3& a,
        const Vector3& b
    );

    float distanceTo(const Vector3& other) const;

    static float distance(
        const Vector3& a,
        const Vector3& b
    );

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;

    Vector3 operator*(float scalar) const;
    Vector3 operator/(float scalar) const;

    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);

    Vector3& operator*=(float scalar);
    Vector3& operator/=(float scalar);

    Vector3 operator-() const;

    bool operator==(const Vector3& other) const;
    bool operator!=(const Vector3& other) const;
};

Vector3 operator*(
    float scalar,
    const Vector3& vector
);

}