#pragma once

#include "Math/Transform.hpp"
#include "Math/Mat4.hpp"

namespace Pigtail
{

class Camera3D
{
public:
    Camera3D();

    void setPerspective(
        float fieldOfView,
        float aspectRatio,
        float nearPlane,
        float farPlane
    );

    void setAspectRatio(float aspectRatio);

    const Transform& getTransform() const;
    Transform& getTransform();

    const Vec3& getPosition() const;
    void setPosition(const Vec3& position);

    const Quaternion& getRotation() const;
    void setRotation(const Quaternion& rotation);

    Vec3 forward() const;
    Vec3 right() const;
    Vec3 up() const;

    Mat4 viewMatrix() const;
    Mat4 projectionMatrix() const;
    Mat4 viewProjectionMatrix() const;

    float fieldOfView() const;
    float aspectRatio() const;
    float nearPlane() const;
    float farPlane() const;

private:
    Transform m_transform;

    float m_fieldOfView;
    float m_aspectRatio;
    float m_nearPlane;
    float m_farPlane;
};

}