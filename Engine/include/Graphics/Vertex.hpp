#pragma once

#include "Math/Vec2.hpp"
#include "Math/Vec3.hpp"

namespace Pigtail
{

struct Vertex
{
    Vec3 position;
    Vec3 normal;
    Vec2 texCoord;

    Vertex() = default;

    Vertex(
        const Vec3& position,
        const Vec3& normal,
        const Vec2& texCoord
    )
        : position(position),
          normal(normal),
          texCoord(texCoord)
    {
    }
};

}