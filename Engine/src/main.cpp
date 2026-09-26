#include "Core/Application.hpp"
#include "Audio/Audio.hpp"

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

    app.run();

    return 0;
}