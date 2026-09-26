#pragma once

#include <SDL3/SDL.h>

#include <string>

namespace Pigtail
{

class Sound
{
public:
    Sound() = default;
    ~Sound();

    Sound(const Sound&) = delete;
    Sound& operator=(const Sound&) = delete;

    Sound(Sound&& other) noexcept;
    Sound& operator=(Sound&& other) noexcept;

    bool load(const std::string& path);
    void unload();

    bool isLoaded() const;

    const SDL_AudioSpec& spec() const;
    const Uint8* data() const;
    Uint32 dataSize() const;

private:
    SDL_AudioSpec m_spec{};
    Uint8* m_data = nullptr;
    Uint32 m_dataSize = 0;

    bool m_loaded = false;
};

}