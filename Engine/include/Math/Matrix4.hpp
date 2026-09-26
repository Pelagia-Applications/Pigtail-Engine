#pragma once

#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"

namespace Pigtail
{

class Matrix4
{
public:
    float m[16];

    Matrix4();

    explicit Matrix4(float diagonal);

    static Matrix4 identity();

    static Matrix4 translation(
        const Vector3& position
    );

    static Matrix4 scale(
        const Vector3& scale
    );

    static Matrix4 rotationX(
        float radians
    );

    static Matrix4 rotationY(
        float radians
    );

    static Matrix4 rotationZ(
        float radians
    );

    static Matrix4 perspective(
        float fovRadians,
        float aspect,
        float nearPlane,
        float farPlane
    );

    static Matrix4 orthographic(
        float left,
        float right,
        float bottom,
        float top,
        float nearPlane,
        float farPlane
    );

    static Matrix4 lookAt(
        const Vector3& position,
        const Vector3& target,
        const Vector3& up
    );

    Matrix4 transposed() const;
    Matrix4 inverted() const;

    Vector4 operator*(const Vector4& vector) const;

    Matrix4 operator*(const Matrix4& other) const;

    Matrix4& operator*=(const Matrix4& other);

    float& operator()(int row, int column);
    float operator()(int row, int column) const;

    const float* data() const;
    float* data();
};

}