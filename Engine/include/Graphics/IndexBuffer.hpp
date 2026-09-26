#pragma once

#include <cstddef>

namespace Pigtail
{

class IndexBuffer
{
public:
    IndexBuffer() = default;

    IndexBuffer(
        const unsigned int* indices,
        std::size_t count
    );

    ~IndexBuffer();

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;

    IndexBuffer(IndexBuffer&& other) noexcept;
    IndexBuffer& operator=(IndexBuffer&& other) noexcept;

    bool create(
        const unsigned int* indices,
        std::size_t count
    );

    void destroy();

    void bind() const;
    void unbind() const;

    unsigned int id() const;
    std::size_t count() const;
    bool isValid() const;

private:
    unsigned int m_id = 0;
    std::size_t m_count = 0;
};

}