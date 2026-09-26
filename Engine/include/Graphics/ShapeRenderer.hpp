#pragma once

#include <Math/Vec2.hpp>
#include <Math/Vec4.hpp>

namespace Pigtail
{

class Camera2D;
class Shader;

class ShapeRenderer
{
public:
    ShapeRenderer();
    ~ShapeRenderer();

    ShapeRenderer(const ShapeRenderer&) = delete;
    ShapeRenderer& operator=(const ShapeRenderer&) = delete;

    bool initialize();
    void shutdown();

    void begin(const Camera2D& camera);
    void end();

    void drawRectangle(
        const Vec2& position,
        const Vec2& size,
        const Vec4& color,
        float rotation = 0.0f
    );

    void drawRectangleOutline(
        const Vec2& position,
        const Vec2& size,
        const Vec4& color,
        float rotation = 0.0f,
        float thickness = 1.0f
    );

    void drawLine(
        const Vec2& start,
        const Vec2& end,
        const Vec4& color,
        float thickness = 1.0f
    );

    void drawCircle(
        const Vec2& center,
        float radius,
        const Vec4& color,
        int segments = 32
    );

private:
    void createBuffers();
    void destroyBuffers();

    void drawQuad(
        const Vec2& position,
        const Vec2& size,
        const Vec4& color,
        float rotation
    );

private:
    Shader* m_shader = nullptr;

    unsigned int m_vao = 0;
    unsigned int m_vbo = 0;

    const Camera2D* m_camera = nullptr;

    bool m_initialized = false;
    bool m_drawing = false;
};

}