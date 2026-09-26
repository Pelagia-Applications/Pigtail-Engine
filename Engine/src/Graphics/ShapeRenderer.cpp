#include "Graphics/ShapeRenderer.hpp"

#include "Graphics/Camera2D.hpp"
#include "Graphics/Shader.hpp"

#include <Math/Mat4.hpp>
#include <Math/Quaternion.hpp>
#include <Math/Vec2.hpp>
#include <Math/Vec3.hpp>
#include <Math/Math.hpp>

#include <glad/glad.h>

#include <cmath>
#include <vector>

namespace Pigtail
{


ShapeRenderer::ShapeRenderer()
    : m_shader(nullptr),
      m_vao(0),
      m_vbo(0),
      m_camera(nullptr),
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

    m_drawing = false;
    m_camera = nullptr;

    destroyBuffers();

    delete m_shader;
    m_shader = nullptr;

    m_initialized = false;
}

void ShapeRenderer::createBuffers()
{
    glGenVertexArrays(
        1,
        &m_vao
    );

    glGenBuffers(
        1,
        &m_vbo
    );

    glBindVertexArray(m_vao);

    glBindBuffer(
        GL_ARRAY_BUFFER,
        m_vbo
    );

    // Large enough for reasonably sized dynamic geometry.
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(float) * 4096,
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

    glBindBuffer(
        GL_ARRAY_BUFFER,
        0
    );

    glBindVertexArray(0);
}

void ShapeRenderer::destroyBuffers()
{
    if (m_vbo != 0)
    {
        glDeleteBuffers(
            1,
            &m_vbo
        );

        m_vbo = 0;
    }

    if (m_vao != 0)
    {
        glDeleteVertexArrays(
            1,
            &m_vao
        );

        m_vao = 0;
    }
}

void ShapeRenderer::begin(const Camera2D& camera)
{
    if (!m_initialized || !m_shader)
        return;

    m_camera = &camera;
    m_drawing = true;

    m_shader->bind();

    m_shader->setMat4(
        "u_viewProjection",
        camera.viewProjectionMatrix()
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

    m_camera = nullptr;
    m_drawing = false;
}

void ShapeRenderer::drawQuad(
    const Vec2& position,
    const Vec2& size,
    const Vec4& color,
    float rotation
)
{
    if (!m_drawing || !m_shader)
        return;

    const float halfWidth =
        size.x * 0.5f;

    const float halfHeight =
        size.y * 0.5f;

    const float vertices[] =
    {
        -halfWidth, -halfHeight,
         halfWidth, -halfHeight,
         halfWidth,  halfHeight,

        -halfWidth, -halfHeight,
         halfWidth,  halfHeight,
        -halfWidth,  halfHeight
    };

    glBindBuffer(
        GL_ARRAY_BUFFER,
        m_vbo
    );

    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        sizeof(vertices),
        vertices
    );

    Mat4 model =
        Mat4::translation(
            Vec3(
                position.x,
                position.y,
                0.0f
            )
        );

    model =
        model *
        Mat4::rotation(
            Quaternion::fromAxisAngle(
                Vec3(0.0f, 0.0f, 1.0f),
                rotation * Math::DEG_TO_RAD
            )
        );

    m_shader->setMat4(
        "u_model",
        model
    );

    m_shader->setVec4(
        "u_color",
        color
    );

    glDrawArrays(
        GL_TRIANGLES,
        0,
        6
    );
}

void ShapeRenderer::drawRectangle(
    const Vec2& position,
    const Vec2& size,
    const Vec4& color,
    float rotation
)
{
    drawQuad(
        position,
        size,
        color,
        rotation
    );
}

void ShapeRenderer::drawRectangleOutline(
    const Vec2& position,
    const Vec2& size,
    const Vec4& color,
    float rotation,
    float thickness
)
{
    if (!m_drawing || !m_shader)
        return;

    const float halfWidth =
        size.x * 0.5f;

    const float halfHeight =
        size.y * 0.5f;

    const float vertices[] =
    {
        -halfWidth,  halfHeight,
         halfWidth,  halfHeight,

         halfWidth,  halfHeight,
         halfWidth, -halfHeight,

         halfWidth, -halfHeight,
        -halfWidth, -halfHeight,

        -halfWidth, -halfHeight,
        -halfWidth,  halfHeight
    };

    Mat4 model =
        Mat4::translation(
            Vec3(
                position.x,
                position.y,
                0.0f
            )
        );

    model =
        model *
        Mat4::rotation(
            Quaternion::fromAxisAngle(
                Vec3(0.0f, 0.0f, 1.0f),
                rotation * Math::DEG_TO_RAD
            )
        );

    m_shader->setMat4(
        "u_model",
        model
    );

    m_shader->setVec4(
        "u_color",
        color
    );

    glBindBuffer(
        GL_ARRAY_BUFFER,
        m_vbo
    );

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
    const Vec2& start,
    const Vec2& end,
    const Vec4& color,
    float thickness
)
{
    if (!m_drawing || !m_shader)
        return;

    const float vertices[] =
    {
        start.x,
        start.y,

        end.x,
        end.y
    };

    const Mat4 model =
        Mat4::identity();

    m_shader->setMat4(
        "u_model",
        model
    );

    m_shader->setVec4(
        "u_color",
        color
    );

    glBindBuffer(
        GL_ARRAY_BUFFER,
        m_vbo
    );

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
    const Vec2& center,
    float radius,
    const Vec4& color,
    int segments
)
{
    if (!m_drawing || !m_shader)
        return;

    if (segments < 3)
        segments = 3;

    const int vertexCount =
        segments + 2;

    std::vector<float> vertices(
        static_cast<std::size_t>(vertexCount) * 2
    );

    // Center vertex.
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;

    for (int i = 0; i <= segments; ++i)
    {
        const float angle =
            (
                static_cast<float>(i)
                /
                static_cast<float>(segments)
            )
            * 2.0f
            * Math::PI;

        vertices[
            static_cast<std::size_t>(i + 1) * 2
        ] =
            std::cos(angle) * radius;

        vertices[
            static_cast<std::size_t>(i + 1) * 2 + 1
        ] =
            std::sin(angle) * radius;
    }

    glBindBuffer(
        GL_ARRAY_BUFFER,
        m_vbo
    );

    glBufferData(
        GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(
            vertices.size() * sizeof(float)
        ),
        vertices.data(),
        GL_DYNAMIC_DRAW
    );

    const Mat4 model =
        Mat4::translation(
            Vec3(
                center.x,
                center.y,
                0.0f
            )
        );

    m_shader->setMat4(
        "u_model",
        model
    );

    m_shader->setVec4(
        "u_color",
        color
    );

    glDrawArrays(
        GL_TRIANGLE_FAN,
        0,
        vertexCount
    );
}

}