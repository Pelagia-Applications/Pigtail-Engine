#pragma once

#include "Graphics/Vertex.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/VertexBuffer.hpp"
#include "Graphics/IndexBuffer.hpp"

#include <vector>

namespace Pigtail
{

class Mesh
{
public:
    Mesh() = default;

    Mesh(
        const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices
    );

    ~Mesh() = default;

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(Mesh&&) noexcept = default;
    Mesh& operator=(Mesh&&) noexcept = default;

    bool create(
        const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices
    );

    void destroy();

    void bind() const;
    void unbind() const;

    void draw() const;

    bool isValid() const;

    static Mesh createCube();

private:
    VertexArray m_vertexArray;
    VertexBuffer m_vertexBuffer;
    IndexBuffer m_indexBuffer;

    bool m_valid = false;
};

}