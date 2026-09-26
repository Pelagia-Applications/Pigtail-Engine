#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

namespace Pigtail
{

class Camera2D
{
public:
    Camera2D(float width, float height);

    void setPosition(float x, float y);
    void setPosition(const glm::vec2& position);

    void move(float x, float y);
    void move(const glm::vec2& offset);

    void setZoom(float zoom);
    void zoom(float amount);

    void setRotation(float degrees);
    void rotate(float degrees);

    void resize(float width, float height);

    const glm::vec2& position() const;
    float zoomLevel() const;
    float rotation() const;

    float width() const;
    float height() const;

    glm::mat4 viewMatrix() const;
    glm::mat4 projectionMatrix() const;
    glm::mat4 viewProjectionMatrix() const;

    glm::vec2 screenToWorld(float screenX, float screenY) const;
    glm::vec2 worldToScreen(float worldX, float worldY) const;

private:
    glm::vec2 m_position{0.0f, 0.0f};

    float m_zoom{1.0f};
    float m_rotation{0.0f};

    float m_width;
    float m_height;
};

}