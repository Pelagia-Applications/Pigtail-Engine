#include "Graphics/VertexBuffer.hpp"

#include <glad/glad.h>

namespace Pigtail
{

VertexBuffer::VertexBuffer(
    const void* data,
    std::size_t size
)
{
    create(data, size);
}

VertexBuffer::~VertexBuffer()
{
    destroy();
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
    : m_id(other.m_id)
{
    other.m_id = 0;
}

VertexBuffer& VertexBuffer::operator=(
    VertexBuffer&& other
) noexcept
{
    if (this == &other)
        return *this;

    destroy();

    m_id = other.m_id;
    other.m_id = 0;

    return *this;
}

bool VertexBuffer::create(
    const void* data,
    std::size_t size
)
{
    destroy();

    if (data == nullptr || size == 0)
        return false;

    glGenBuffers(1, &m_id);

    if (m_id == 0)
        return false;

    bind();

    glBufferData(
        GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(size),
        data,
        GL_STATIC_DRAW
    );

    unbind();

    return true;
}

void VertexBuffer::destroy()
{
    if (m_id != 0)
    {
        glDeleteBuffers(1, &m_id);
        m_id = 0;
    }
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int VertexBuffer::id() const
{
    return m_id;
}

bool VertexBuffer::isValid() const
{
    return m_id != 0;
}

}