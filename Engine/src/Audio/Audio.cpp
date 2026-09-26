#include "Audio/Audio.hpp"

#include "Core/Logger.hpp"

#include <algorithm>
#include <string>

namespace Pigtail
{

SDL_AudioDeviceID Audio::s_device = 0;
bool Audio::s_initialized = false;
float Audio::s_masterVolume = 1.0f;

std::vector<Audio::Voice> Audio::s_voices;

bool Audio::initialize()
{
    Logger::debug("Initializing audio system...");

    if (!SDL_InitSubSystem(SDL_INIT_AUDIO))
    {
        Logger::error(
            "Failed to initialize SDL audio: {}",
            SDL_GetError()
        );
        return false;
    }

    SDL_AudioSpec spec{};
    spec.format = SDL_AUDIO_F32;
    spec.channels = 2;
    spec.freq = 48000;

    s_device = SDL_OpenAudioDevice(
        SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,
        &spec
    );

    if (!s_device)
    {
        Logger::error(
            "Failed to open audio device: {}",
            SDL_GetError()
        );

        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        return false;
    }

    s_initialized = true;

    Logger::info("Audio system initialized.");

    return true;
}

void Audio::shutdown()
{
    if (!s_initialized)
        return;

    Logger::debug("Shutting down audio system...");

    stopAll();

    if (s_device != 0)
    {
        SDL_CloseAudioDevice(s_device);
        s_device = 0;
    }

    s_initialized = false;

    Logger::info("Audio system shut down.");
}

bool Audio::isInitialized()
{
    return s_initialized;
}

std::shared_ptr<Sound> Audio::loadSound(
    const std::string& path)
{
    if (!s_initialized)
    {
        Logger::error(
            "Cannot load sound before audio initialization."
        );

        return nullptr;
    }

    auto sound = std::make_shared<Sound>();

    if (!sound->load(path))
    {
        Logger::error(
            std::string("Failed to load sound '") +
            path +
            "': " +
            SDL_GetError()
        );

        return nullptr;
    }

    Logger::debug(
        std::string("Loaded sound: ") + path
    );

    return sound;
}

void Audio::play(
    const std::shared_ptr<Sound>& sound,
    float volume,
    bool loop)
{
    if (!s_initialized)
    {
        Logger::warning(
            "Attempted to play sound before audio initialization."
        );

        return;
    }

    if (!sound || !sound->isLoaded())
    {
        Logger::warning(
            "Attempted to play an invalid sound."
        );

        return;
    }

    SDL_AudioStream* stream =
        SDL_CreateAudioStream(
            &sound->spec(),
            nullptr
        );

    if (!stream)
    {
        Logger::error(
            std::string("Failed to create audio stream: ") +
            SDL_GetError()
        );

        return;
    }

    if (!SDL_BindAudioStream(
        s_device,
        stream))
    {
        Logger::error(
            std::string("Failed to bind audio stream: ") +
            SDL_GetError()
        );

        SDL_DestroyAudioStream(stream);

        return;
    }

    float finalVolume =
        std::clamp(volume, 0.0f, 1.0f) *
        s_masterVolume;

    SDL_SetAudioStreamGain(
        stream,
        finalVolume
    );

    if (!SDL_PutAudioStreamData(
        stream,
        sound->data(),
        static_cast<int>(sound->dataSize())))
    {
        Logger::error(
            std::string("Failed to queue audio data: ") +
            SDL_GetError()
        );

        SDL_DestroyAudioStream(stream);

        return;
    }

    SDL_ResumeAudioStreamDevice(stream);

    Voice voice;

    voice.stream = stream;
    voice.sound = sound;
    voice.volume = std::clamp(volume, 0.0f, 1.0f);
    voice.loop = loop;

    s_voices.push_back(
        std::move(voice)
    );
}

void Audio::stopAll()
{
    for (auto& voice : s_voices)
    {
        if (voice.stream)
        {
            SDL_DestroyAudioStream(
                voice.stream
            );

            voice.stream = nullptr;
        }
    }

    s_voices.clear();
}

void Audio::setMasterVolume(float volume)
{
    s_masterVolume =
        std::clamp(volume, 0.0f, 1.0f);

    for (auto& voice : s_voices)
    {
        if (!voice.stream)
            continue;

        float gain =
            voice.volume *
            s_masterVolume;

        SDL_SetAudioStreamGain(
            voice.stream,
            gain
        );
    }
}

float Audio::masterVolume()
{
    return s_masterVolume;
}

void Audio::update()
{
    if (!s_initialized)
        return;

    for (auto it = s_voices.begin();
         it != s_voices.end();)
    {
        Voice& voice = *it;

        if (!voice.stream)
        {
            it = s_voices.erase(it);
            continue;
        }

        int queued =
            SDL_GetAudioStreamQueued(
                voice.stream
            );

        if (queued <= 0)
        {
            if (voice.loop)
            {
                SDL_PutAudioStreamData(
                    voice.stream,
                    voice.sound->data(),
                    static_cast<int>(
                        voice.sound->dataSize()
                    )
                );

                ++it;
                continue;
            }

            SDL_DestroyAudioStream(
                voice.stream
            );

            voice.stream = nullptr;

            it = s_voices.erase(it);
            continue;
        }

        ++it;
    }
}

}