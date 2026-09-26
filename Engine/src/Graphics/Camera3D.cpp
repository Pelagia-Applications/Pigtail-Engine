#include "Graphics/Camera3D.hpp"

#include "Math/Math.hpp"

#include <cmath>

namespace Pigtail
{

Camera3D::Camera3D()
    : m_transform(),
      m_fieldOfView(Math::radians(60.0f)),
      m_aspectRatio(16.0f / 9.0f),
      m_nearPlane(0.1f),
      m_farPlane(1000.0f)
{
}

void Camera3D::setPerspective(
    float fieldOfView,
    float aspectRatio,
    float nearPlane,
    float farPlane)
{
    m_fieldOfView = fieldOfView;
    m_aspectRatio = aspectRatio;
    m_nearPlane = nearPlane;
    m_farPlane = farPlane;
}

void Camera3D::setAspectRatio(float aspectRatio)
{
    if (aspectRatio > 0.0f)
        m_aspectRatio = aspectRatio;
}

const Transform& Camera3D::getTransform() const
{
    return m_transform;
}

Transform& Camera3D::getTransform()
{
    return m_transform;
}

const Vec3& Camera3D::getPosition() const
{
    return m_transform.position;
}

void Camera3D::setPosition(const Vec3& position)
{
    m_transform.position = position;
}

const Quaternion& Camera3D::getRotation() const
{
    return m_transform.rotation;
}

void Camera3D::setRotation(const Quaternion& rotation)
{
    m_transform.rotation = rotation.normalized();
}

Vec3 Camera3D::forward() const
{
    return m_transform.forward();
}

Vec3 Camera3D::right() const
{
    return m_transform.right();
}

Vec3 Camera3D::up() const
{
    return m_transform.up();
}

Mat4 Camera3D::viewMatrix() const
{
    /*
        The Camera3D transform describes where the Camera3D
        is in the world.

        The view matrix is its inverse.
    */

    const Quaternion inverseRotation =
        m_transform.rotation.inverse();

    const Vec3 inversePosition =
        -(inverseRotation * m_transform.position);

    Mat4 rotation =
        Mat4::rotation(inverseRotation);

    Mat4 translation =
        Mat4::translation(inversePosition);

    return rotation * translation;
}

Mat4 Camera3D::projectionMatrix() const
{
    const float tanHalfFov =
        std::tan(m_fieldOfView * 0.5f);

    Mat4 result(0.0f);

    result[0][0] =
        1.0f / (m_aspectRatio * tanHalfFov);

    result[1][1] =
        1.0f / tanHalfFov;

    result[2][2] =
        -(m_farPlane + m_nearPlane) /
        (m_farPlane - m_nearPlane);

    result[2][3] =
        -(2.0f * m_farPlane * m_nearPlane) /
        (m_farPlane - m_nearPlane);

    result[3][2] = -1.0f;

    return result;
}

Mat4 Camera3D::viewProjectionMatrix() const
{
    return projectionMatrix() * viewMatrix();
}

float Camera3D::fieldOfView() const
{
    return m_fieldOfView;
}

float Camera3D::aspectRatio() const
{
    return m_aspectRatio;
}

float Camera3D::nearPlane() const
{
    return m_nearPlane;
}

float Camera3D::farPlane() const
{
    return m_farPlane;
}

}