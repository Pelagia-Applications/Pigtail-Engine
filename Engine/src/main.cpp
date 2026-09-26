#include "Core/Application.hpp"
#include "Audio/Audio.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"
#include "Math/Matrix4.hpp"

#include <iostream>

#include <memory>

int main()
{
    Pigtail::Application app;

    if (!app.initialize())
        return -1;

    auto sound =
        Pigtail::Audio::loadSound(
            "assets/audio/test.wav"
        );

    if (sound)
    {
        Pigtail::Audio::play(
            sound,
            1.0f,
            false
        );
    }

    using namespace Pigtail;

    Vector3 position(10.0f, 5.0f, -2.0f);

    Matrix4 transform =
        Matrix4::translation(position);

    Vector4 point(0.0f, 0.0f, 0.0f, 1.0f);

    Vector4 result = transform * point;

    std::cout
        << result.x << ", "
        << result.y << ", "
        << result.z << ", "
        << result.w << '\n';

    app.run();

    return 0;
}