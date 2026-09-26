#include "Math/Mat4.hpp"

#include <cmath>
#include <algorithm>

namespace Pigtail
{

Mat4::Mat4()
    : m{}
{
}

Mat4::Mat4(float diagonal)
    : m{}
{
    m[0]  = diagonal;
    m[5]  = diagonal;
    m[10] = diagonal;
    m[15] = diagonal;
}

Mat4 Mat4::identity()
{
    return Mat4(1.0f);
}

Mat4 Mat4::translation(
    const Vec3& position
)
{
    Mat4 result = Mat4::identity();

    result.m[12] = position.x;
    result.m[13] = position.y;
    result.m[14] = position.z;

    return result;
}

Mat4 Mat4::scale(
    const Vec3& scale
)
{
    Mat4 result;

    result.m[0]  = scale.x;
    result.m[5]  = scale.y;
    result.m[10] = scale.z;
    result.m[15] = 1.0f;

    return result;
}

Mat4 Mat4::rotation(const Quaternion& q)
{
    Mat4 result = Mat4::identity();

    const float xx = q.x * q.x;
    const float yy = q.y * q.y;
    const float zz = q.z * q.z;

    const float xy = q.x * q.y;
    const float xz = q.x * q.z;
    const float yz = q.y * q.z;

    const float wx = q.w * q.x;
    const float wy = q.w * q.y;
    const float wz = q.w * q.z;

    result(0, 0) = 1.0f - 2.0f * (yy + zz);
    result(0, 1) = 2.0f * (xy - wz);
    result(0, 2) = 2.0f * (xz + wy);

    result(1, 0) = 2.0f * (xy + wz);
    result(1, 1) = 1.0f - 2.0f * (xx + zz);
    result(1, 2) = 2.0f * (yz - wx);

    result(2, 0) = 2.0f * (xz - wy);
    result(2, 1) = 2.0f * (yz + wx);
    result(2, 2) = 1.0f - 2.0f * (xx + yy);

    return result;
}

Mat4 Mat4::perspective(
    float fovRadians,
    float aspect,
    float nearPlane,
    float farPlane
)
{
    Mat4 result;

    const float tanHalfFov =
        std::tan(fovRadians * 0.5f);

    result.m[0] =
        1.0f / (aspect * tanHalfFov);

    result.m[5] =
        1.0f / tanHalfFov;

    result.m[10] =
        -(farPlane + nearPlane) /
        (farPlane - nearPlane);

    result.m[11] = -1.0f;

    result.m[14] =
        -(2.0f * farPlane * nearPlane) /
        (farPlane - nearPlane);

    return result;
}

Mat4 Mat4::orthographic(
    float left,
    float right,
    float bottom,
    float top,
    float nearPlane,
    float farPlane
)
{
    Mat4 result = Mat4::identity();

    result.m[0] =
        2.0f / (right - left);

    result.m[5] =
        2.0f / (top - bottom);

    result.m[10] =
        -2.0f / (farPlane - nearPlane);

    result.m[12] =
        -(right + left) /
        (right - left);

    result.m[13] =
        -(top + bottom) /
        (top - bottom);

    result.m[14] =
        -(farPlane + nearPlane) /
        (farPlane - nearPlane);

    return result;
}

Mat4 Mat4::lookAt(
    const Vec3& position,
    const Vec3& target,
    const Vec3& up
)
{
    const Vec3 forward =
        (target - position).normalized();

    const Vec3 right =
        Vec3::cross(forward, up).normalized();

    const Vec3 cameraUp =
        Vec3::cross(right, forward);

    Mat4 result = Mat4::identity();

    result.m[0] = right.x;
    result.m[1] = cameraUp.x;
    result.m[2] = -forward.x;

    result.m[4] = right.y;
    result.m[5] = cameraUp.y;
    result.m[6] = -forward.y;

    result.m[8] = right.z;
    result.m[9] = cameraUp.z;
    result.m[10] = -forward.z;

    result.m[12] =
        -Vec3::dot(right, position);

    result.m[13] =
        -Vec3::dot(cameraUp, position);

    result.m[14] =
        Vec3::dot(forward, position);

    return result;
}

Mat4 Mat4::transposed() const
{
    Mat4 result;

    for (int row = 0; row < 4; ++row)
    {
        for (int column = 0; column < 4; ++column)
        {
            result(row, column) =
                (*this)(column, row);
        }
    }

    return result;
}

Mat4 Mat4::inverted() const
{
    Mat4 result;

    const float* a = m;
    float* inv = result.m;

    inv[0] =
        a[5]  * a[10] * a[15] -
        a[5]  * a[11] * a[14] -
        a[9]  * a[6]  * a[15] +
        a[9]  * a[7]  * a[14] +
        a[13] * a[6]  * a[11] -
        a[13] * a[7]  * a[10];

    inv[4] =
        -a[4]  * a[10] * a[15] +
        a[4]  * a[11] * a[14] +
        a[8]  * a[6]  * a[15] -
        a[8]  * a[7]  * a[14] -
        a[12] * a[6]  * a[11] +
        a[12] * a[7]  * a[10];

    inv[8] =
        a[4]  * a[9] * a[15] -
        a[4]  * a[11] * a[13] -
        a[8]  * a[5] * a[15] +
        a[8]  * a[7] * a[13] +
        a[12] * a[5] * a[11] -
        a[12] * a[7] * a[9];

    inv[12] =
        -a[4]  * a[9] * a[14] +
        a[4]  * a[10] * a[13] +
        a[8]  * a[5] * a[14] -
        a[8]  * a[6] * a[13] -
        a[12] * a[5] * a[10] +
        a[12] * a[6] * a[9];

    inv[1] =
        -a[1]  * a[10] * a[15] +
        a[1]  * a[11] * a[14] +
        a[9]  * a[2]  * a[15] -
        a[9]  * a[3]  * a[14] -
        a[13] * a[2]  * a[11] +
        a[13] * a[3]  * a[10];

    inv[5] =
        a[0]  * a[10] * a[15] -
        a[0]  * a[11] * a[14] -
        a[8]  * a[2]  * a[15] +
        a[8]  * a[3]  * a[14] +
        a[12] * a[2]  * a[11] -
        a[12] * a[3]  * a[10];

    inv[9] =
        -a[0]  * a[9] * a[15] +
        a[0]  * a[11] * a[13] +
        a[8]  * a[1] * a[15] -
        a[8]  * a[3] * a[13] -
        a[12] * a[1] * a[11] +
        a[12] * a[3] * a[9];

    inv[13] =
        a[0]  * a[9] * a[14] -
        a[0]  * a[10] * a[13] -
        a[8]  * a[1] * a[14] +
        a[8]  * a[2] * a[13] +
        a[12] * a[1] * a[10] -
        a[12] * a[2] * a[9];

    inv[2] =
        a[1]  * a[6] * a[15] -
        a[1]  * a[7] * a[14] -
        a[5]  * a[2] * a[15] +
        a[5]  * a[3] * a[14] +
        a[13] * a[2] * a[7] -
        a[13] * a[3] * a[6];

    inv[6] =
        -a[0]  * a[6] * a[15] +
        a[0]  * a[7] * a[14] +
        a[4]  * a[2] * a[15] -
        a[4]  * a[3] * a[14] -
        a[12] * a[2] * a[7] +
        a[12] * a[3] * a[6];

    inv[10] =
        a[0]  * a[5] * a[15] -
        a[0]  * a[7] * a[13] -
        a[4]  * a[1] * a[15] +
        a[4]  * a[3] * a[13] +
        a[12] * a[1] * a[7] -
        a[12] * a[3] * a[5];

    inv[14] =
        -a[0]  * a[5] * a[14] +
        a[0]  * a[6] * a[13] +
        a[4]  * a[1] * a[14] -
        a[4]  * a[2] * a[13] -
        a[12] * a[1] * a[6] +
        a[12] * a[2] * a[5];

    inv[3] =
        -a[1]  * a[6] * a[11] +
        a[1]  * a[7] * a[10] +
        a[5]  * a[2] * a[11] -
        a[5]  * a[3] * a[10] -
        a[9]  * a[2] * a[7] +
        a[9]  * a[3] * a[6];

    inv[7] =
        a[0]  * a[6] * a[11] -
        a[0]  * a[7] * a[10] -
        a[4]  * a[2] * a[11] +
        a[4]  * a[3] * a[10] +
        a[8]  * a[2] * a[7] -
        a[8]  * a[3] * a[6];

    inv[11] =
        -a[0]  * a[5] * a[11] +
        a[0]  * a[7] * a[9] +
        a[4]  * a[1] * a[11] -
        a[4]  * a[3] * a[9] -
        a[8]  * a[1] * a[7] +
        a[8]  * a[3] * a[5];

    inv[15] =
        a[0]  * a[5] * a[10] -
        a[0]  * a[6] * a[9] -
        a[4]  * a[1] * a[10] +
        a[4]  * a[2] * a[9] +
        a[8]  * a[1] * a[6] -
        a[8]  * a[2] * a[5];

    const float determinant =
        a[0] * inv[0] +
        a[1] * inv[4] +
        a[2] * inv[8] +
        a[3] * inv[12];

    if (std::abs(determinant) <= 0.000001f)
        return Mat4::identity();

    const float inverseDeterminant =
        1.0f / determinant;

    for (float& value : result.m)
        value *= inverseDeterminant;

    return result;
}

Vec4 Mat4::operator*(const Vec4& vector) const
{
    return Vec4(
        m[0]  * vector.x +
        m[4]  * vector.y +
        m[8]  * vector.z +
        m[12] * vector.w,

        m[1]  * vector.x +
        m[5]  * vector.y +
        m[9]  * vector.z +
        m[13] * vector.w,

        m[2]  * vector.x +
        m[6]  * vector.y +
        m[10] * vector.z +
        m[14] * vector.w,

        m[3]  * vector.x +
        m[7] * vector.y +
        m[11] * vector.z +
        m[15] * vector.w
    );
}

Mat4 Mat4::operator*(const Mat4& other) const
{
    Mat4 result;

    for (int column = 0; column < 4; ++column)
    {
        for (int row = 0; row < 4; ++row)
        {
            result(row, column) =
                (*this)(row, 0) * other(0, column) +
                (*this)(row, 1) * other(1, column) +
                (*this)(row, 2) * other(2, column) +
                (*this)(row, 3) * other(3, column);
        }
    }

    return result;
}

Mat4& Mat4::operator*=(const Mat4& other)
{
    *this = *this * other;

    return *this;
}

float* Mat4::operator[](int column)
{
    return &m[column * 4];
}

const float* Mat4::operator[](int column) const
{
    return &m[column * 4];
}

float& Mat4::operator()(
    int row,
    int column
)
{
    return m[column * 4 + row];
}

float Mat4::operator()(
    int row,
    int column
) const
{
    return m[column * 4 + row];
}

float* Mat4::data()
{
    return m;
}

}