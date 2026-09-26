#include "Core/Application.hpp"
#include "Audio/Audio.hpp"
#include "Math/Vec3.hpp"
#include "Math/Vec4.hpp"
#include "Math/Mat4.hpp"

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

    Vec3 position(10.0f, 5.0f, -2.0f);

    Mat4 transform =
        Mat4::translation(position);

    Vec4 point(0.0f, 0.0f, 0.0f, 1.0f);

    Vec4 result = transform * point;

    std::cout
        << result.x << ", "
        << result.y << ", "
        << result.z << ", "
        << result.w << '\n';

    app.run();

    return 0;
}