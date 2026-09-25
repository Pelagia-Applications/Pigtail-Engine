#pragma once

#include <memory>

#include <Window/Window.hpp>

namespace Pelagia
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

    bool m_running = false;
};

}