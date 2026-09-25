#include <Window/Window.hpp>

#include <Core/Logger.hpp>

namespace Pigtail
{

Window::Window(
    const std::string& title,
    int width,
    int height
)
    : m_title(title),
      m_width(width),
      m_height(height)
{
}

Window::~Window()
{
    shutdown();
}

bool Window::initialize()
{
    Logger::debug("Initializing SDL video subsystem...");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        Logger::error(
            std::string("SDL_Init failed: ") +
            SDL_GetError()
        );

        return false;
    }

    Logger::info("SDL initialized.");

    // -----------------------------------------------------
    // OpenGL configuration
    // -----------------------------------------------------

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MAJOR_VERSION,
        3
    );

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MINOR_VERSION,
        3
    );

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
    );

    SDL_GL_SetAttribute(
        SDL_GL_DOUBLEBUFFER,
        1
    );

    SDL_GL_SetAttribute(
        SDL_GL_DEPTH_SIZE,
        24
    );

    // -----------------------------------------------------
    // Create window
    // -----------------------------------------------------

    Logger::debug("Creating window...");

    m_window = SDL_CreateWindow(
        m_title.c_str(),
        m_width,
        m_height,
        SDL_WINDOW_OPENGL |
        SDL_WINDOW_RESIZABLE
    );

    if (!m_window)
    {
        Logger::error(
            std::string("Failed to create window: ") +
            SDL_GetError()
        );

        SDL_Quit();

        return false;
    }

    Logger::info(
        "Window created: " +
        std::to_string(m_width) +
        "x" +
        std::to_string(m_height)
    );

    // -----------------------------------------------------
    // Create OpenGL context
    // -----------------------------------------------------

    Logger::debug("Creating OpenGL context...");

    m_glContext = SDL_GL_CreateContext(m_window);

    if (!m_glContext)
    {
        Logger::error(
            std::string(
                "Failed to create OpenGL context: "
            ) +
            SDL_GetError()
        );

        SDL_DestroyWindow(m_window);

        m_window = nullptr;

        SDL_Quit();

        return false;
    }

    Logger::info("OpenGL context created.");

    // -----------------------------------------------------
    // VSync
    // -----------------------------------------------------

    if (SDL_GL_SetSwapInterval(1))
    {
        Logger::info("VSync enabled.");
    }
    else
    {
        Logger::warning(
            std::string(
                "Could not enable VSync: "
            ) +
            SDL_GetError()
        );
    }

    return true;
}

void Window::shutdown()
{
    if (m_glContext)
    {
        Logger::debug("Destroying OpenGL context...");

        SDL_GL_DestroyContext(m_glContext);

        m_glContext = nullptr;
    }

    if (m_window)
    {
        Logger::debug("Destroying window...");

        SDL_DestroyWindow(m_window);

        m_window = nullptr;
    }

    SDL_Quit();
}

void Window::pollEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_QUIT:
            {
                m_shouldClose = true;
                break;
            }

            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            {
                m_shouldClose = true;
                break;
            }

            case SDL_EVENT_WINDOW_RESIZED:
            {
                m_width = event.window.data1;
                m_height = event.window.data2;

                Logger::debug(
                    "Window resized to " +
                    std::to_string(m_width) +
                    "x" +
                    std::to_string(m_height)
                );

                break;
            }

            default:
                break;
        }
    }
}

void Window::swapBuffers()
{
    if (m_window)
    {
        SDL_GL_SwapWindow(m_window);
    }
}

bool Window::shouldClose() const
{
    return m_shouldClose;
}

SDL_Window* Window::nativeHandle() const
{
    return m_window;
}

SDL_GLContext Window::glContext() const
{
    return m_glContext;
}

int Window::width() const
{
    return m_width;
}

int Window::height() const
{
    return m_height;
}

}