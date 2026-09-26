#include "Math/Transform.hpp"

namespace Pigtail
{

Transform::Transform()
    : position(0.0f, 0.0f, 0.0f),
      rotation(Quaternion::identity()),
      scale(1.0f, 1.0f, 1.0f)
{
}

Mat4 Transform::matrix() const
{
    /*
        Translation * Rotation * Scale

        This creates the standard model matrix used
        by the 3D renderer.
    */

    Mat4 translationMatrix =
        Mat4::translation(position);

    Mat4 rotationMatrix =
        Mat4::rotation(rotation);

    Mat4 scaleMatrix =
        Mat4::scale(scale);

    return translationMatrix *
           rotationMatrix *
           scaleMatrix;
}

Vec3 Transform::forward() const
{
    return rotation * Vec3(0.0f, 0.0f, -1.0f);
}

Vec3 Transform::right() const
{
    return rotation * Vec3(1.0f, 0.0f, 0.0f);
}

Vec3 Transform::up() const
{
    return rotation * Vec3(0.0f, 1.0f, 0.0f);
}

void Transform::translate(const Vec3& amount)
{
    position += amount;
}

void Transform::rotate(const Quaternion& amount)
{
    rotation = (rotation * amount).normalized();
}

void Transform::scaleBy(const Vec3& amount)
{
    scale.x *= amount.x;
    scale.y *= amount.y;
    scale.z *= amount.z;
}

void Transform::setPosition(const Vec3& newPosition)
{
    position = newPosition;
}

void Transform::setRotation(const Quaternion& newRotation)
{
    rotation = newRotation.normalized();
}

void Transform::setScale(const Vec3& newScale)
{
    scale = newScale;
}

const Vec3& Transform::getPosition() const
{
    return position;
}

const Quaternion& Transform::getRotation() const
{
    return rotation;
}

const Vec3& Transform::getScale() const
{
    return scale;
}

}