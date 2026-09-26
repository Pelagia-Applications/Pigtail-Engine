#pragma once

#include "Math/Vec3.hpp"
#include "Math/Vec4.hpp"
#include "Math/Quaternion.hpp"

namespace Pigtail
{

class Mat4
{
public:
    float m[16];

    Mat4();

    explicit Mat4(float diagonal);

    static Mat4 identity();

    static Mat4 translation(
        const Vec3& position
    );

    static Mat4 scale(
        const Vec3& scale
    );

    static Mat4 rotation(const Quaternion& rotation);

    static Mat4 perspective(
        float fovRadians,
        float aspect,
        float nearPlane,
        float farPlane
    );

    static Mat4 orthographic(
        float left,
        float right,
        float bottom,
        float top,
        float nearPlane,
        float farPlane
    );

    static Mat4 lookAt(
        const Vec3& position,
        const Vec3& target,
        const Vec3& up
    );

    Mat4 transposed() const;
    Mat4 inverted() const;

    Vec4 operator*(const Vec4& vector) const;

    Mat4 operator*(const Mat4& other) const;

    Mat4& operator*=(const Mat4& other);

    float* operator[](int row);
    const float* operator[](int row) const;

    float& operator()(int row, int column);
    float operator()(int row, int column) const;

    const float* data() const;
    float* data();
};

}