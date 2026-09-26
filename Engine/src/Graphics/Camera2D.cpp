#include "Graphics/Camera2D.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>
#include <cmath>

namespace Pigtail
{

Camera2D::Camera2D(float width, float height)
    : m_width(width),
      m_height(height)
{
}

void Camera2D::setPosition(float x, float y)
{
    m_position = glm::vec2(x, y);
}

void Camera2D::setPosition(const glm::vec2& position)
{
    m_position = position;
}

void Camera2D::move(float x, float y)
{
    m_position += glm::vec2(x, y);
}

void Camera2D::move(const glm::vec2& offset)
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

const glm::vec2& Camera2D::position() const
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

glm::mat4 Camera2D::viewMatrix() const
{
    glm::mat4 view(1.0f);

    // Move the world opposite to the Camera2D.
    view = glm::translate(
        view,
        glm::vec3(-m_position.x, -m_position.y, 0.0f)
    );

    // Rotate the world opposite to the Camera2D.
    view = glm::rotate(
        view,
        glm::radians(-m_rotation),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );

    // Zoom the world.
    view = glm::scale(
        view,
        glm::vec3(m_zoom, m_zoom, 1.0f)
    );

    return view;
}

glm::mat4 Camera2D::projectionMatrix() const
{
    const float halfWidth = m_width * 0.5f;
    const float halfHeight = m_height * 0.5f;

    return glm::ortho(
        -halfWidth,
        halfWidth,
        -halfHeight,
        halfHeight,
        -1.0f,
        1.0f
    );
}

glm::mat4 Camera2D::viewProjectionMatrix() const
{
    return projectionMatrix() * viewMatrix();
}

glm::vec2 Camera2D::screenToWorld(float screenX, float screenY) const
{
    glm::mat4 inverse = glm::inverse(viewProjectionMatrix());

    // Convert screen coordinates to normalized device coordinates.
    float ndcX =
        (screenX / m_width) * 2.0f - 1.0f;

    float ndcY =
        1.0f - (screenY / m_height) * 2.0f;

    glm::vec4 screenPosition(
        ndcX,
        ndcY,
        0.0f,
        1.0f
    );

    glm::vec4 worldPosition = inverse * screenPosition;

    if (std::abs(worldPosition.w) > 0.00001f)
    {
        worldPosition /= worldPosition.w;
    }

    return glm::vec2(
        worldPosition.x,
        worldPosition.y
    );
}

glm::vec2 Camera2D::worldToScreen(float worldX, float worldY) const
{
    glm::vec4 worldPosition(
        worldX,
        worldY,
        0.0f,
        1.0f
    );

    glm::vec4 clipPosition =
        viewProjectionMatrix() * worldPosition;

    if (std::abs(clipPosition.w) > 0.00001f)
    {
        clipPosition /= clipPosition.w;
    }

    float screenX =
        (clipPosition.x + 1.0f) * 0.5f * m_width;

    float screenY =
        (1.0f - clipPosition.y) * 0.5f * m_height;

    return glm::vec2(screenX, screenY);
}

}