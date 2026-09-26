#pragma once

#include "Math/Vec3.hpp"
#include "Math/Quaternion.hpp"
#include "Math/Mat4.hpp"

namespace Pigtail
{

class Transform
{
public:
    Transform();

    Vec3 position;
    Quaternion rotation;
    Vec3 scale;

    Mat4 matrix() const;

    Vec3 forward() const;
    Vec3 right() const;
    Vec3 up() const;

    void translate(const Vec3& amount);
    void rotate(const Quaternion& amount);
    void scaleBy(const Vec3& amount);

    void setPosition(const Vec3& position);
    void setRotation(const Quaternion& rotation);
    void setScale(const Vec3& scale);

    const Vec3& getPosition() const;
    const Quaternion& getRotation() const;
    const Vec3& getScale() const;
};

}