#include "Graphics/Camera2D.hpp"

#include "Math/Quaternion.hpp"

#include <algorithm>
#include <cmath>

namespace Pigtail
{

Camera2D::Camera2D(float width, float height)
    : m_position(0.0f, 0.0f),
      m_zoom(1.0f),
      m_rotation(0.0f),
      m_width(std::max(width, 1.0f)),
      m_height(std::max(height, 1.0f))
{
}

void Camera2D::setPosition(float x, float y)
{
    m_position = Vec2(x, y);
}

void Camera2D::setPosition(const Vec2& position)
{
    m_position = position;
}

void Camera2D::move(float x, float y)
{
    m_position += Vec2(x, y);
}

void Camera2D::move(const Vec2& offset)
{
    m_position += offset;
}

void Camera2D::setZoom(float zoom)
{
    m_zoom = std::max(zoom, 0.01f);
}

void Camera2D::zoom(float amount)
{
    setZoom(m_zoom + amount);
}

void Camera2D::setRotation(float degrees)
{
    m_rotation = degrees;
}

void Camera2D::rotate(float degrees)
{
    m_rotation += degrees;
}

void Camera2D::resize(float width, float height)
{
    m_width = std::max(width, 1.0f);
    m_height = std::max(height, 1.0f);
}

const Vec2& Camera2D::position() const
{
    return m_position;
}

float Camera2D::zoomLevel() const
{
    return m_zoom;
}

float Camera2D::rotation() const
{
    return m_rotation;
}

float Camera2D::width() const
{
    return m_width;
}

float Camera2D::height() const
{
    return m_height;
}

Mat4 Camera2D::viewMatrix() const
{
    Mat4 view = Mat4::identity();

    // Move the world opposite to the camera.
    view =
        Mat4::translation(
            Vec3(
                -m_position.x,
                -m_position.y,
                0.0f
            )
        );

    // Rotate the world opposite to the camera.
    view =
        view *
        Mat4::rotation(
            Quaternion::fromAxisAngle(
                Vec3(0.0f, 0.0f, 1.0f),
                -m_rotation * 0.01745329251994329577f
            )
        );

    // Zoom the world.
    view =
        view *
        Mat4::scale(
            Vec3(
                m_zoom,
                m_zoom,
                1.0f
            )
        );

    return view;
}

Mat4 Camera2D::projectionMatrix() const
{
    const float halfWidth = m_width * 0.5f;
    const float halfHeight = m_height * 0.5f;

    return Mat4::orthographic(
        -halfWidth,
        halfWidth,
        -halfHeight,
        halfHeight,
        -1.0f,
        1.0f
    );
}

Mat4 Camera2D::viewProjectionMatrix() const
{
    return projectionMatrix() * viewMatrix();
}

Vec2 Camera2D::screenToWorld(
    float screenX,
    float screenY
) const
{
    Mat4 inverse =
        viewProjectionMatrix().inverted();

    const float ndcX =
        (screenX / m_width) * 2.0f - 1.0f;

    const float ndcY =
        1.0f - (screenY / m_height) * 2.0f;

    Vec4 screenPosition(
        ndcX,
        ndcY,
        0.0f,
        1.0f
    );

    Vec4 worldPosition =
        inverse * screenPosition;

    if (std::abs(worldPosition.w) > 0.00001f)
    {
        worldPosition /= worldPosition.w;
    }

    return Vec2(
        worldPosition.x,
        worldPosition.y
    );
}

Vec2 Camera2D::worldToScreen(
    float worldX,
    float worldY
) const
{
    Vec4 worldPosition(
        worldX,
        worldY,
        0.0f,
        1.0f
    );

    Vec4 clipPosition =
        viewProjectionMatrix() * worldPosition;

    if (std::abs(clipPosition.w) > 0.00001f)
    {
        clipPosition /= clipPosition.w;
    }

    const float screenX =
        (clipPosition.x + 1.0f)
        * 0.5f
        * m_width;

    const float screenY =
        (1.0f - clipPosition.y)
        * 0.5f
        * m_height;

    return Vec2(
        screenX,
        screenY
    );
}

}