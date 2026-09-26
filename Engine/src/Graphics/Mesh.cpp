#include "Graphics/Mesh.hpp"

#include <glad/glad.h>

namespace Pigtail
{

Mesh::Mesh(
    const std::vector<Vertex>& vertices,
    const std::vector<unsigned int>& indices
)
{
    create(vertices, indices);
}

bool Mesh::create(
    const std::vector<Vertex>& vertices,
    const std::vector<unsigned int>& indices
)
{
    destroy();

    if (vertices.empty() || indices.empty())
        return false;

    m_vertexBuffer.create(
        vertices.data(),
        vertices.size() * sizeof(Vertex)
    );

    if (!m_vertexBuffer.isValid())
        return false;

    m_indexBuffer.create(
        indices.data(),
        indices.size()
    );

    if (!m_indexBuffer.isValid())
    {
        m_vertexBuffer.destroy();
        return false;
    }

    m_vertexArray.create();

    if (!m_vertexArray.isValid())
    {
        m_vertexBuffer.destroy();
        m_indexBuffer.destroy();
        return false;
    }

    m_vertexArray.setVertexBuffer(m_vertexBuffer);
    m_vertexArray.setIndexBuffer(m_indexBuffer);

    m_valid = true;

    return true;
}

void Mesh::destroy()
{
    m_vertexArray.destroy();
    m_vertexBuffer.destroy();
    m_indexBuffer.destroy();

    m_valid = false;
}

void Mesh::bind() const
{
    m_vertexArray.bind();
}

void Mesh::unbind() const
{
    m_vertexArray.unbind();
}

void Mesh::draw() const
{
    if (!m_valid)
        return;

    bind();

    glDrawElements(
        GL_TRIANGLES,
        static_cast<GLsizei>(m_indexBuffer.count()),
        GL_UNSIGNED_INT,
        nullptr
    );

    unbind();
}

bool Mesh::isValid() const
{
    return m_valid;
}

Mesh Mesh::createCube()
{
    std::vector<Vertex> vertices =
    {
        // Front
        {{-0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, { 0.0f,  0.0f,  1.0f}, {0.0f, 1.0f}},

        // Back
        {{ 0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, { 0.0f,  0.0f, -1.0f}, {0.0f, 1.0f}},

        // Left
        {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},

        // Right
        {{0.5f, -0.5f,  0.5f}, {1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
        {{0.5f,  0.5f, -0.5f}, {1.0f,  0.0f, 0.0f}, {1.0f, 1.0f}},
        {{0.5f,  0.5f,  0.5f}, {1.0f,  0.0f, 0.0f}, {0.0f, 1.0f}},

        // Top
        {{-0.5f, 0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 0.5f, 0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{ 0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

        // Bottom
        {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}}
    };

    std::vector<unsigned int> indices =
    {
        // Front
        0, 1, 2,
        2, 3, 0,

        // Back
        4, 5, 6,
        6, 7, 4,

        // Left
        8, 9, 10,
        10, 11, 8,

        // Right
        12, 13, 14,
        14, 15, 12,

        // Top
        16, 17, 18,
        18, 19, 16,

        // Bottom
        20, 21, 22,
        22, 23, 20
    };

    return Mesh(vertices, indices);
}

}