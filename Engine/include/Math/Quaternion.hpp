#pragma once

#include "Math/Vec3.hpp"

namespace Pigtail
{

class Quaternion
{
public:
    float x;
    float y;
    float z;
    float w;

    Quaternion();
    Quaternion(float x, float y, float z, float w);

    static Quaternion identity();

    static Quaternion fromAxisAngle(
        const Vec3& axis,
        float radians
    );

    static Quaternion fromEuler(
        float pitch,
        float yaw,
        float roll
    );

    float length() const;
    float lengthSquared() const;

    Quaternion normalized() const;
    Quaternion conjugate() const;
    Quaternion inverse() const;

    Quaternion operator*(const Quaternion& other) const;

    Vec3 operator*(const Vec3& vector) const;

    Quaternion& operator*=(const Quaternion& other);

    static float dot(
        const Quaternion& a,
        const Quaternion& b
    );

    static Quaternion slerp(
        const Quaternion& a,
        const Quaternion& b,
        float t
    );
};

}