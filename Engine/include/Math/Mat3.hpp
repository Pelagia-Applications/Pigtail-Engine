#pragma once

#include "Math/Vec3.hpp"

namespace Pigtail
{

class Mat3
{
public:
    float m[3][3];

    Mat3();
    explicit Mat3(float diagonal);

    static Mat3 identity();

    static Mat3 rotation(float radians);
    static Mat3 scale(float x, float y);
    static Mat3 translation(float x, float y);

float* operator[](int column);
const float* operator[](int column) const;

    Mat3 operator*(const Mat3& other) const;
    Vec3 operator*(const Vec3& vector) const;

    Mat3& operator*=(const Mat3& other);

    Mat3 transposed() const;
    float determinant() const;
    Mat3 inverse() const;
};

}