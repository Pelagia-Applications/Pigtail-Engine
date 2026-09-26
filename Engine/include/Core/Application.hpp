#pragma once

#include <memory>

#include <Core/ShapeRenderer.hpp>
#include <Window/Window.hpp>
#include <Graphics/Renderer.hpp>
#include <Graphics/Camera2D.hpp>

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

    ShapeRenderer m_shapeRenderer;

    bool m_running = false;
    
    Camera2D m_Camera2D;
};

}