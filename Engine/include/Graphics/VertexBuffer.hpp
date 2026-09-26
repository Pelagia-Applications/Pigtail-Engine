#pragma once

#include <cstddef>

namespace Pigtail
{

class VertexBuffer
{
public:
    VertexBuffer() = default;

    VertexBuffer(
        const void* data,
        std::size_t size
    );

    ~VertexBuffer();

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    VertexBuffer(VertexBuffer&& other) noexcept;
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    bool create(
        const void* data,
        std::size_t size
    );

    void destroy();

    void bind() const;
    void unbind() const;

    unsigned int id() const;
    bool isValid() const;

private:
    unsigned int m_id = 0;
};

}