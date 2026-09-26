#pragma once
#include <Math/Vector3.hpp>

namespace Pigtail
{

class Vector4
{
public:
    float x;
    float y;
    float z;
    float w;

    Vector4();
    Vector4(float x, float y, float z, float w);
    Vector4(const Vector3& vector, float w);

    static Vector4 zero();
    static Vector4 one();

    float length() const;
    float lengthSquared() const;

    Vector4 normalized() const;
    void normalize();

    float dot(const Vector4& other) const;

    static float dot(
        const Vector4& a,
        const Vector4& b
    );

    Vector4 operator+(const Vector4& other) const;
    Vector4 operator-(const Vector4& other) const;

    Vector4 operator*(float scalar) const;
    Vector4 operator/(float scalar) const;

    Vector4& operator+=(const Vector4& other);
    Vector4& operator-=(const Vector4& other);

    Vector4& operator*=(float scalar);
    Vector4& operator/=(float scalar);

    Vector4 operator-() const;

    bool operator==(const Vector4& other) const;
    bool operator!=(const Vector4& other) const;
};

Vector4 operator*(
    float scalar,
    const Vector4& vector
);

}