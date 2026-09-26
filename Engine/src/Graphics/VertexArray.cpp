#include "Graphics/VertexArray.hpp"
#include "Graphics/Vertex.hpp"

#include <glad/glad.h>

namespace Pigtail
{

VertexArray::VertexArray()
{
    create();
}

VertexArray::~VertexArray()
{
    destroy();
}

VertexArray::VertexArray(VertexArray&& other) noexcept
    : m_id(other.m_id)
{
    other.m_id = 0;
}

VertexArray& VertexArray::operator=(
    VertexArray&& other
) noexcept
{
    if (this == &other)
        return *this;

    destroy();

    m_id = other.m_id;
    other.m_id = 0;

    return *this;
}

bool VertexArray::create()
{
    destroy();

    glGenVertexArrays(1, &m_id);

    return m_id != 0;
}

void VertexArray::destroy()
{
    if (m_id != 0)
    {
        glDeleteVertexArrays(1, &m_id);
        m_id = 0;
    }
}

void VertexArray::bind() const
{
    glBindVertexArray(m_id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::setVertexBuffer(
    const VertexBuffer& vertexBuffer
)
{
    bind();
    vertexBuffer.bind();

    /*
        Vertex layout:

        location 0 → position
        location 1 → normal
        location 2 → texture coordinates

        Vertex:
        Vec3 position = 12 bytes
        Vec3 normal   = 12 bytes
        Vec2 texCoord = 8 bytes

        Total = 32 bytes
    */

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<const void*>(
            offsetof(Vertex, position)
        )
    );

    glEnableVertexAttribArray(1);

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<const void*>(
            offsetof(Vertex, normal)
        )
    );

    glEnableVertexAttribArray(2);

    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<const void*>(
            offsetof(Vertex, texCoord)
        )
    );

    vertexBuffer.unbind();
    unbind();
}

void VertexArray::setIndexBuffer(
    const IndexBuffer& indexBuffer
)
{
    bind();

    /*
        Element array buffers are stored as part
        of the VAO state, so leave the index buffer
        bound while the VAO is bound.
    */

    indexBuffer.bind();

    unbind();
}

unsigned int VertexArray::id() const
{
    return m_id;
}

bool VertexArray::isValid() const
{
    return m_id != 0;
}

}