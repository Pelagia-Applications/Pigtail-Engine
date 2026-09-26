#pragma once
#include <Math/Vec3.hpp>

namespace Pigtail
{

class Vec4
{
public:
    float x;
    float y;
    float z;
    float w;

    Vec4();
    Vec4(float x, float y, float z, float w);
    Vec4(const Vec3& vector, float w);

    static Vec4 zero();
    static Vec4 one();

    float length() const;
    float lengthSquared() const;

    Vec4 normalized() const;
    void normalize();

    float dot(const Vec4& other) const;

    static float dot(
        const Vec4& a,
        const Vec4& b
    );

    Vec4 operator+(const Vec4& other) const;
    Vec4 operator-(const Vec4& other) const;

    Vec4 operator*(float scalar) const;
    Vec4 operator/(float scalar) const;

    Vec4& operator+=(const Vec4& other);
    Vec4& operator-=(const Vec4& other);

    Vec4& operator*=(float scalar);
    Vec4& operator/=(float scalar);

    Vec4 operator-() const;

    bool operator==(const Vec4& other) const;
    bool operator!=(const Vec4& other) const;
};

Vec4 operator*(
    float scalar,
    const Vec4& vector
);

}