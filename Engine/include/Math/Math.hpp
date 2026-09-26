#pragma once

#include <cmath>
#include <algorithm>

#include "Math/Vec2.hpp"
#include "Math/Vec3.hpp"
#include "Math/Vec4.hpp"
#include "Math/Mat3.hpp"
#include "Math/Mat4.hpp"
#include "Math/Quaternion.hpp"

namespace Pigtail::Math
{

constexpr float PI = 3.14159265358979323846f;
constexpr float TWO_PI = PI * 2.0f;
constexpr float HALF_PI = PI * 0.5f;

constexpr float DEG_TO_RAD = PI / 180.0f;
constexpr float RAD_TO_DEG = 180.0f / PI;

template<typename T>
constexpr T min(T a, T b)
{
    return a < b ? a : b;
}

template<typename T>
constexpr T max(T a, T b)
{
    return a > b ? a : b;
}

template<typename T>
constexpr T clamp(T value, T minimum, T maximum)
{
    return value < minimum
        ? minimum
        : (value > maximum ? maximum : value);
}

template<typename T>
constexpr T lerp(const T& a, const T& b, float t)
{
    return a + (b - a) * t;
}

constexpr float radians(float degrees)
{
    return degrees * DEG_TO_RAD;
}

constexpr float degrees(float radiansValue)
{
    return radiansValue * RAD_TO_DEG;
}

constexpr float square(float value)
{
    return value * value;
}

inline float inverseSqrt(float value)
{
    return 1.0f / std::sqrt(value);
}

inline float smoothstep(
    float edge0,
    float edge1,
    float x)
{
    const float t = clamp(
        (x - edge0) / (edge1 - edge0),
        0.0f,
        1.0f
    );

    return t * t * (3.0f - 2.0f * t);
}

}