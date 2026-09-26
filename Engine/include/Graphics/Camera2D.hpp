#pragma once

#include <Math/Vec2.hpp>
#include <Math/Mat4.hpp>

namespace Pigtail
{

class Camera2D
{
public:
    Camera2D(float width, float height);

    void setPosition(float x, float y);
    void setPosition(const Vec2& position);

    void move(float x, float y);
    void move(const Vec2& offset);

    void setZoom(float zoom);
    void zoom(float amount);

    void setRotation(float degrees);
    void rotate(float degrees);

    void resize(float width, float height);

    const Vec2& position() const;
    float zoomLevel() const;
    float rotation() const;

    float width() const;
    float height() const;

    Mat4 viewMatrix() const;
    Mat4 projectionMatrix() const;
    Mat4 viewProjectionMatrix() const;

    Vec2 screenToWorld(float screenX, float screenY) const;
    Vec2 worldToScreen(float worldX, float worldY) const;

private:
    Vec2 m_position{0.0f, 0.0f};

    float m_zoom{1.0f};
    float m_rotation{0.0f};

    float m_width;
    float m_height;
};

}