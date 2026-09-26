#include "Math/Quaternion.hpp"

#include <cmath>
#include <algorithm>

namespace Pigtail
{

Quaternion::Quaternion()
    : x(0.0f),
      y(0.0f),
      z(0.0f),
      w(1.0f)
{
}

Quaternion::Quaternion(float x, float y, float z, float w)
    : x(x),
      y(y),
      z(z),
      w(w)
{
}

Quaternion Quaternion::identity()
{
    return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
}

Quaternion Quaternion::fromAxisAngle(
    const Vec3& axis,
    float radians)
{
    const Vec3 normalizedAxis = axis.normalized();

    const float halfAngle = radians * 0.5f;
    const float s = std::sin(halfAngle);

    return Quaternion(
        normalizedAxis.x * s,
        normalizedAxis.y * s,
        normalizedAxis.z * s,
        std::cos(halfAngle)
    );
}

Quaternion Quaternion::fromEuler(
    float pitch,
    float yaw,
    float roll)
{
    const float hp = pitch * 0.5f;
    const float hy = yaw * 0.5f;
    const float hr = roll * 0.5f;

    const float cp = std::cos(hp);
    const float sp = std::sin(hp);

    const float cy = std::cos(hy);
    const float sy = std::sin(hy);

    const float cr = std::cos(hr);
    const float sr = std::sin(hr);

    Quaternion result;

    result.w = cr * cp * cy + sr * sp * sy;
    result.x = sr * cp * cy - cr * sp * sy;
    result.y = cr * sp * cy + sr * cp * sy;
    result.z = cr * cp * sy - sr * sp * cy;

    return result;
}

float Quaternion::lengthSquared() const
{
    return
        x * x +
        y * y +
        z * z +
        w * w;
}

float Quaternion::length() const
{
    return std::sqrt(lengthSquared());
}

Quaternion Quaternion::normalized() const
{
    const float len = length();

    if (len < 0.000001f)
        return identity();

    return Quaternion(
        x / len,
        y / len,
        z / len,
        w / len
    );
}

Quaternion Quaternion::conjugate() const
{
    return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::inverse() const
{
    const float lenSq = lengthSquared();

    if (lenSq < 0.000001f)
        return identity();

    const Quaternion c = conjugate();

    return Quaternion(
        c.x / lenSq,
        c.y / lenSq,
        c.z / lenSq,
        c.w / lenSq
    );
}

Quaternion Quaternion::operator*(const Quaternion& other) const
{
    return Quaternion(
        w * other.x + x * other.w + y * other.z - z * other.y,

        w * other.y - x * other.z + y * other.w + z * other.x,

        w * other.z + x * other.y - y * other.x + z * other.w,

        w * other.w - x * other.x - y * other.y - z * other.z
    );
}

Vec3 Quaternion::operator*(const Vec3& vector) const
{
    Quaternion q(
        vector.x,
        vector.y,
        vector.z,
        0.0f
    );

    Quaternion result = (*this) * q * inverse();

    return Vec3(
        result.x,
        result.y,
        result.z
    );
}

Quaternion& Quaternion::operator*=(const Quaternion& other)
{
    *this = *this * other;
    return *this;
}

float Quaternion::dot(
    const Quaternion& a,
    const Quaternion& b)
{
    return
        a.x * b.x +
        a.y * b.y +
        a.z * b.z +
        a.w * b.w;
}

Quaternion Quaternion::slerp(
    const Quaternion& a,
    const Quaternion& b,
    float t)
{
    Quaternion bCopy = b;

    float cosTheta = dot(a, b);

    if (cosTheta < 0.0f)
    {
        bCopy.x = -bCopy.x;
        bCopy.y = -bCopy.y;
        bCopy.z = -bCopy.z;
        bCopy.w = -bCopy.w;

        cosTheta = -cosTheta;
    }

    cosTheta = std::clamp(cosTheta, -1.0f, 1.0f);

    if (cosTheta > 0.9995f)
    {
        Quaternion result(
            a.x + t * (bCopy.x - a.x),
            a.y + t * (bCopy.y - a.y),
            a.z + t * (bCopy.z - a.z),
            a.w + t * (bCopy.w - a.w)
        );

        return result.normalized();
    }

    const float theta = std::acos(cosTheta);
    const float sinTheta = std::sin(theta);

    const float weightA =
        std::sin((1.0f - t) * theta) / sinTheta;

    const float weightB =
        std::sin(t * theta) / sinTheta;

    return Quaternion(
        a.x * weightA + bCopy.x * weightB,
        a.y * weightA + bCopy.y * weightB,
        a.z * weightA + bCopy.z * weightB,
        a.w * weightA + bCopy.w * weightB
    );
}

}