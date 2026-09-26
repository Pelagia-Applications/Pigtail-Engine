#pragma once

#include <memory>

#include <Window/Window.hpp>
#include <Graphics/Renderer.hpp>
#include <Graphics/Camera.hpp>

namespace Pigtail
{

class Application
{
public:

    Application();

    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    bool initialize();

    void run();

    void shutdown();

private:

    std::unique_ptr<Window> m_window;

    std::unique_ptr<Renderer> m_renderer;

    bool m_running = false;
    
    Camera m_camera;
};

}