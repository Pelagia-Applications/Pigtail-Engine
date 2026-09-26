#pragma once

#include <cstdint>

#include <glad/glad.h>
#include <glm/glm.hpp>

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

    void begin(const Camera2D& Camera2D);
    void end();

    void drawRectangle(
        const glm::vec2& position,
        const glm::vec2& size,
        const glm::vec4& color,
        float rotation = 0.0f
    );

    void drawRectangleOutline(
        const glm::vec2& position,
        const glm::vec2& size,
        const glm::vec4& color,
        float rotation = 0.0f,
        float thickness = 1.0f
    );

    void drawLine(
        const glm::vec2& start,
        const glm::vec2& end,
        const glm::vec4& color,
        float thickness = 1.0f
    );

    void drawCircle(
        const glm::vec2& center,
        float radius,
        const glm::vec4& color,
        int segments = 32
    );

private:
    void createBuffers();
    void destroyBuffers();

    void drawQuad(
        const glm::vec2& position,
        const glm::vec2& size,
        const glm::vec4& color,
        float rotation
    );

private:
    GLuint m_vao;
    GLuint m_vbo;

    Shader* m_shader;
    const Camera2D* m_Camera2D;

    bool m_initialized;
    bool m_drawing;
};

}