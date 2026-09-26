#include <Core/Application.hpp>
#include <Core/Input.hpp>
#include <Core/Logger.hpp>
#include <Core/ShapeRenderer.hpp>
#include <Window/Window.hpp>
#include <Graphics/Renderer.hpp>
#include <Graphics/GLContext.hpp>


namespace Pigtail
{

Pigtail::Application::Application()
    : m_camera(1280.0f, 720.0f)
{
}

Pigtail::Application::~Application()
{
    shutdown();
}

bool Pigtail::Application::initialize()
{
    Logger::info(
        "================================"
    );

    Logger::info(
        "      Pigtail Engine 0.1.0"
    );

    Logger::info(
        "================================"
    );

    Logger::info(
        "Initializing application..."
    );

    // -----------------------------------------------------
    // Window
    // -----------------------------------------------------

    m_window = std::make_unique<Window>(
        "Pigtail Engine",
        1280,
        720
    );

    if (!m_window->initialize())
    {
        Logger::error(
            "Failed to initialize window."
        );

        return false;
    }

    // -----------------------------------------------------
    // OpenGL / GLAD
    // -----------------------------------------------------

    if (!GLContext::initialize())
    {
        Logger::error(
            "Failed to initialize OpenGL."
        );

        return false;
    }

    // -----------------------------------------------------
    // Renderer
    // -----------------------------------------------------

    m_renderer = std::make_unique<Renderer>();

    if (!m_renderer->initialize())
    {
        Logger::error(
            "Failed to initialize renderer."
        );

        return false;
    }

    if (!m_shapeRenderer.initialize())
    {
        Logger::error(
            "Failed to initialize shape renderer."
        );

        return false;
    }

    m_running = true;

    Logger::info(
        "Application initialized successfully."
    );

    return true;
}

void Pigtail::Application::run()
{
    Logger::info(
        "Entering main loop."
    );

    while (
        m_running &&
        !m_window->shouldClose()
    )
    {
        m_window->pollEvents();

        m_renderer->beginFrame();

        m_renderer->clear();

        m_shapeRenderer.begin(m_camera);

        m_shapeRenderer.drawRectangle(
            glm::vec2(0.0f, 0.0f),
            glm::vec2(200.0f, 100.0f),
            glm::vec4(1.0f, 0.2f, 0.2f, 1.0f)
        );

        m_shapeRenderer.drawRectangleOutline(
            glm::vec2(0.0f, 0.0f),
            glm::vec2(220.0f, 120.0f),
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            0.0f,
            3.0f
        );

        m_shapeRenderer.drawLine(
            glm::vec2(-300.0f, -100.0f),
            glm::vec2(300.0f, -100.0f),
            glm::vec4(0.2f, 1.0f, 0.2f, 1.0f),
            4.0f
        );

        m_shapeRenderer.drawCircle(
            glm::vec2(300.0f, 100.0f),
            50.0f,
            glm::vec4(0.2f, 0.5f, 1.0f, 1.0f)
        );

        m_shapeRenderer.end();

        m_renderer->endFrame();

        m_window->swapBuffers();
    }

    Logger::info(
        "Leaving main loop."
    );
}

void Pigtail::Application::shutdown()
{
    if (!m_running &&
        !m_window &&
        !m_renderer)
    {
        return;
    }

    Logger::info(
        "Shutting down application..."
    );

    if (m_renderer)
    {
        m_renderer->shutdown();

        m_renderer.reset();
    }

    m_shapeRenderer.shutdown();

    GLContext::shutdown();

    if (m_window)
    {
        m_window.reset();
    }

    m_running = false;

    Logger::info(
        "Application shutdown complete."
    );
}

}