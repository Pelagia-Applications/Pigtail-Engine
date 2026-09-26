#pragma once

#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"

namespace Pigtail
{

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    VertexArray(VertexArray&& other) noexcept;
    VertexArray& operator=(VertexArray&& other) noexcept;

    bool create();
    void destroy();

    void bind() const;
    void unbind() const;

    void setVertexBuffer(
        const VertexBuffer& vertexBuffer
    );

    void setIndexBuffer(
        const IndexBuffer& indexBuffer
    );

    unsigned int id() const;
    bool isValid() const;

private:
    unsigned int m_id = 0;
};

}