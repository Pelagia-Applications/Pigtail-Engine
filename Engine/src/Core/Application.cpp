#include <Core/Application.hpp>

#include <Core/Logger.hpp>

namespace Pelagia
{

Application::Application() = default;

Application::~Application()
{
    shutdown();
}

bool Application::initialize()
{
    Logger::info("================================");
    Logger::info("      Pigtail Engine 0.1.0");
    Logger::info("================================");

    Logger::info("Initializing application...");

    m_window = std::make_unique<Window>(
        "Pigtail Engine",
        1280,
        720
    );

    if (!m_window->initialize())
    {
        Logger::error(
            "Application initialization failed."
        );

        return false;
    }

    m_running = true;

    Logger::info(
        "Application initialized successfully."
    );

    return true;
}

void Application::run()
{
    Logger::info("Entering main loop.");

    while (m_running && !m_window->shouldClose())
    {
        m_window->pollEvents();

        // Rendering will go here later.

        m_window->swapBuffers();
    }

    Logger::info("Leaving main loop.");
}

void Application::shutdown()
{
    if (!m_running && !m_window)
    {
        return;
    }

    Logger::info("Shutting down application...");

    m_window.reset();

    m_running = false;

    Logger::info("Application shutdown complete.");
}

}