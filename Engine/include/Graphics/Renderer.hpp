#pragma once

namespace Pigtail
{

class Renderer
{
public:

    Renderer() = default;
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    bool initialize();

    void shutdown();

    void beginFrame();

    void clear();

    void endFrame();

    bool isInitialized() const;

private:

    bool m_initialized = false;
};

}