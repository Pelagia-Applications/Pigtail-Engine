#include "Math/Mat3.hpp"

#include <cmath>
#include <stdexcept>

namespace Pigtail
{

Mat3::Mat3()
    : Mat3(1.0f)
{
}

Mat3::Mat3(float diagonal)
    : m{}
{
    m[0][0] = diagonal;
    m[1][1] = diagonal;
    m[2][2] = diagonal;
}

Mat3 Mat3::identity()
{
    return Mat3(1.0f);
}

Mat3 Mat3::rotation(float radians)
{
    Mat3 result(1.0f);

    const float c = std::cos(radians);
    const float s = std::sin(radians);

    result[0][0] = c;
    result[0][1] = -s;
    result[1][0] = s;
    result[1][1] = c;

    return result;
}

Mat3 Mat3::scale(float x, float y)
{
    Mat3 result(1.0f);

    result[0][0] = x;
    result[1][1] = y;

    return result;
}

Mat3 Mat3::translation(float x, float y)
{
    Mat3 result(1.0f);

    result[0][2] = x;
    result[1][2] = y;

    return result;
}

float* Mat3::operator[](int row)
{
    return m[row];
}

const float* Mat3::operator[](int row) const
{
    return m[row];
}

Mat3 Mat3::operator*(const Mat3& other) const
{
    Mat3 result(0.0f);

    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            for (int k = 0; k < 3; ++k)
            {
                result[row][column] +=
                    m[row][k] * other[k][column];
            }
        }
    }

    return result;
}

Vec3 Mat3::operator*(const Vec3& vector) const
{
    return Vec3(
        m[0][0] * vector.x +
        m[0][1] * vector.y +
        m[0][2] * vector.z,

        m[1][0] * vector.x +
        m[1][1] * vector.y +
        m[1][2] * vector.z,

        m[2][0] * vector.x +
        m[2][1] * vector.y +
        m[2][2] * vector.z
    );
}

Mat3& Mat3::operator*=(const Mat3& other)
{
    *this = *this * other;
    return *this;
}

Mat3 Mat3::transposed() const
{
    Mat3 result(0.0f);

    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            result[row][column] = m[column][row];
        }
    }

    return result;
}

float Mat3::determinant() const
{
    return
        m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
        - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
        + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

Mat3 Mat3::inverse() const
{
    const float det = determinant();

    if (std::abs(det) < 0.000001f)
        throw std::runtime_error("Mat3 is not invertible.");

    Mat3 result(0.0f);

    result[0][0] =  (m[1][1] * m[2][2] - m[1][2] * m[2][1]);
    result[0][1] = -(m[0][1] * m[2][2] - m[0][2] * m[2][1]);
    result[0][2] =  (m[0][1] * m[1][2] - m[0][2] * m[1][1]);

    result[1][0] = -(m[1][0] * m[2][2] - m[1][2] * m[2][0]);
    result[1][1] =  (m[0][0] * m[2][2] - m[0][2] * m[2][0]);
    result[1][2] = -(m[0][0] * m[1][2] - m[0][2] * m[1][0]);

    result[2][0] =  (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    result[2][1] = -(m[0][0] * m[2][1] - m[0][1] * m[2][0]);
    result[2][2] =  (m[0][0] * m[1][1] - m[0][1] * m[1][0]);

    for (int row = 0; row < 3; ++row)
    {
        for (int column = 0; column < 3; ++column)
        {
            result[row][column] /= det;
        }
    }

    return result;
}

}