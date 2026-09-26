#include "Graphics/IndexBuffer.hpp"

#include <glad/glad.h>

namespace Pigtail
{

IndexBuffer::IndexBuffer(
    const unsigned int* indices,
    std::size_t count
)
{
    create(indices, count);
}

IndexBuffer::~IndexBuffer()
{
    destroy();
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
    : m_id(other.m_id),
      m_count(other.m_count)
{
    other.m_id = 0;
    other.m_count = 0;
}

IndexBuffer& IndexBuffer::operator=(
    IndexBuffer&& other
) noexcept
{
    if (this == &other)
        return *this;

    destroy();

    m_id = other.m_id;
    m_count = other.m_count;

    other.m_id = 0;
    other.m_count = 0;

    return *this;
}

bool IndexBuffer::create(
    const unsigned int* indices,
    std::size_t count
)
{
    destroy();

    if (indices == nullptr || count == 0)
        return false;

    glGenBuffers(1, &m_id);

    if (m_id == 0)
        return false;

    m_count = count;

    bind();

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(
            count * sizeof(unsigned int)
        ),
        indices,
        GL_STATIC_DRAW
    );

    unbind();

    return true;
}

void IndexBuffer::destroy()
{
    if (m_id != 0)
    {
        glDeleteBuffers(1, &m_id);
        m_id = 0;
    }

    m_count = 0;
}

void IndexBuffer::bind() const
{
    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        m_id
    );
}

void IndexBuffer::unbind() const
{
    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        0
    );
}

unsigned int IndexBuffer::id() const
{
    return m_id;
}

std::size_t IndexBuffer::count() const
{
    return m_count;
}

bool IndexBuffer::isValid() const
{
    return m_id != 0;
}

}