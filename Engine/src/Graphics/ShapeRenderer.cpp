#include "Core/ShapeRenderer.hpp"

#include "Graphics/Camera2D.hpp"
#include "Graphics/Shader.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <cmath>

namespace Pigtail
{

ShapeRenderer::ShapeRenderer()
    : m_vao(0),
      m_vbo(0),
      m_shader(nullptr),
      m_Camera2D(nullptr),
      m_initialized(false),
      m_drawing(false)
{
}

ShapeRenderer::~ShapeRenderer()
{
    shutdown();
}

bool ShapeRenderer::initialize()
{
    if (m_initialized)
        return true;

    m_shader = new Shader();

    if (!m_shader->loadFromFiles(
            "Assets/Shaders/basic.vert",
            "Assets/Shaders/basic.frag"))
    {
        delete m_shader;
        m_shader = nullptr;

        return false;
    }

    createBuffers();

    m_initialized = true;

    return true;
}

void ShapeRenderer::shutdown()
{
    if (!m_initialized && m_shader == nullptr)
        return;

    destroyBuffers();

    delete m_shader;
    m_shader = nullptr;

    m_Camera2D = nullptr;
    m_drawing = false;
    m_initialized = false;
}

void ShapeRenderer::createBuffers()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(float) * 12,
        nullptr,
        GL_DYNAMIC_DRAW
    );

    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float) * 2,
        nullptr
    );

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ShapeRenderer::destroyBuffers()
{
    if (m_vbo != 0)
    {
        glDeleteBuffers(1, &m_vbo);
        m_vbo = 0;
    }

    if (m_vao != 0)
    {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }
}

void ShapeRenderer::begin(const Camera2D& Camera2D)
{
    if (!m_initialized || m_shader == nullptr)
        return;

    m_Camera2D = &Camera2D;
    m_drawing = true;

    m_shader->bind();

    m_shader->setMat4(
        "u_viewProjection",
        Camera2D.viewProjectionMatrix()
    );

    glBindVertexArray(m_vao);
}

void ShapeRenderer::end()
{
    if (!m_drawing)
        return;

    glBindVertexArray(0);

    if (m_shader)
        m_shader->unbind();

    m_Camera2D = nullptr;
    m_drawing = false;
}

void ShapeRenderer::drawQuad(
    const glm::vec2& position,
    const glm::vec2& size,
    const glm::vec4& color,
    float rotation)
{
    if (!m_drawing || !m_shader)
        return;

    const float halfWidth = size.x * 0.5f;
    const float halfHeight = size.y * 0.5f;

    const float vertices[] =
    {
        -halfWidth, -halfHeight,
         halfWidth, -halfHeight,
         halfWidth,  halfHeight,

        -halfWidth, -halfHeight,
         halfWidth,  halfHeight,
        -halfWidth,  halfHeight
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        sizeof(vertices),
        vertices
    );

    glm::mat4 model(1.0f);

    model = glm::translate(
        model,
        glm::vec3(position, 0.0f)
    );

    model = glm::rotate(
        model,
        glm::radians(rotation),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );

    m_shader->setMat4("u_model", model);
    m_shader->setVec4("u_color", color);

    glDrawArrays(
        GL_TRIANGLES,
        0,
        6
    );
}

void ShapeRenderer::drawRectangle(
    const glm::vec2& position,
    const glm::vec2& size,
    const glm::vec4& color,
    float rotation)
{
    drawQuad(
        position,
        size,
        color,
        rotation
    );
}

void ShapeRenderer::drawRectangleOutline(
    const glm::vec2& position,
    const glm::vec2& size,
    const glm::vec4& color,
    float rotation,
    float thickness)
{
    if (!m_drawing || !m_shader)
        return;

    const float halfWidth = size.x * 0.5f;
    const float halfHeight = size.y * 0.5f;

    const glm::vec2 topLeft(
        -halfWidth,
        halfHeight
    );

    const glm::vec2 topRight(
        halfWidth,
        halfHeight
    );

    const glm::vec2 bottomRight(
        halfWidth,
        -halfHeight
    );

    const glm::vec2 bottomLeft(
        -halfWidth,
        -halfHeight
    );

    glm::mat4 model(1.0f);

    model = glm::translate(
        model,
        glm::vec3(position, 0.0f)
    );

    model = glm::rotate(
        model,
        glm::radians(rotation),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );

    m_shader->setMat4("u_model", model);
    m_shader->setVec4("u_color", color);

    const float vertices[] =
    {
        topLeft.x,     topLeft.y,
        topRight.x,    topRight.y,

        topRight.x,    topRight.y,
        bottomRight.x, bottomRight.y,

        bottomRight.x, bottomRight.y,
        bottomLeft.x,  bottomLeft.y,

        bottomLeft.x,  bottomLeft.y,
        topLeft.x,     topLeft.y
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        sizeof(vertices),
        vertices
    );

    glLineWidth(thickness);

    glDrawArrays(
        GL_LINES,
        0,
        8
    );

    glLineWidth(1.0f);
}

void ShapeRenderer::drawLine(
    const glm::vec2& start,
    const glm::vec2& end,
    const glm::vec4& color,
    float thickness)
{
    if (!m_drawing || !m_shader)
        return;

    const float vertices[] =
    {
        start.x, start.y,
        end.x,   end.y
    };

    glm::mat4 model(1.0f);

    m_shader->setMat4("u_model", model);
    m_shader->setVec4("u_color", color);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        sizeof(vertices),
        vertices
    );

    glLineWidth(thickness);

    glDrawArrays(
        GL_LINES,
        0,
        2
    );

    glLineWidth(1.0f);
}

void ShapeRenderer::drawCircle(
    const glm::vec2& center,
    float radius,
    const glm::vec4& color,
    int segments)
{
    if (!m_drawing || !m_shader)
        return;

    if (segments < 3)
        segments = 3;

    const float pi = 3.14159265358979323846f;

    const int vertexCount = segments + 2;

    float* vertices = new float[vertexCount * 2];

    vertices[0] = 0.0f;
    vertices[1] = 0.0f;

    for (int i = 0; i <= segments; ++i)
    {
        const float angle =
            (static_cast<float>(i) / static_cast<float>(segments))
            * 2.0f
            * pi;

        vertices[(i + 1) * 2] =
            std::cos(angle) * radius;

        vertices[(i + 1) * 2 + 1] =
            std::sin(angle) * radius;
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(float) * vertexCount * 2,
        vertices,
        GL_DYNAMIC_DRAW
    );

    glm::mat4 model(1.0f);

    model = glm::translate(
        model,
        glm::vec3(center, 0.0f)
    );

    m_shader->setMat4("u_model", model);
    m_shader->setVec4("u_color", color);

    glDrawArrays(
        GL_TRIANGLE_FAN,
        0,
        vertexCount
    );

    delete[] vertices;
}

}