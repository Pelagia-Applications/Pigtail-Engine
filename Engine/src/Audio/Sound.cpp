#include "Audio/Sound.hpp"

namespace Pigtail
{

Sound::~Sound()
{
    unload();
}

Sound::Sound(Sound&& other) noexcept
    : m_spec(other.m_spec),
      m_data(other.m_data),
      m_dataSize(other.m_dataSize),
      m_loaded(other.m_loaded)
{
    other.m_data = nullptr;
    other.m_dataSize = 0;
    other.m_loaded = false;
    other.m_spec = {};
}

Sound& Sound::operator=(Sound&& other) noexcept
{
    if (this == &other)
        return *this;

    unload();

    m_spec = other.m_spec;
    m_data = other.m_data;
    m_dataSize = other.m_dataSize;
    m_loaded = other.m_loaded;

    other.m_data = nullptr;
    other.m_dataSize = 0;
    other.m_loaded = false;
    other.m_spec = {};

    return *this;
}

bool Sound::load(const std::string& path)
{
    unload();

    if (!SDL_LoadWAV(
        path.c_str(),
        &m_spec,
        &m_data,
        &m_dataSize))
    {
        return false;
    }

    m_loaded = true;

    return true;
}

void Sound::unload()
{
    if (m_data)
    {
        SDL_free(m_data);
        m_data = nullptr;
    }

    m_dataSize = 0;
    m_spec = {};
    m_loaded = false;
}

bool Sound::isLoaded() const
{
    return m_loaded;
}

const SDL_AudioSpec& Sound::spec() const
{
    return m_spec;
}

const Uint8* Sound::data() const
{
    return m_data;
}

Uint32 Sound::dataSize() const
{
    return m_dataSize;
}

}