#include "Graphics/GLContext.hpp"

#include "Core/Logger.hpp"

#include <glad/gl.h>

#include <SDL3/SDL.h>

namespace Pigtail
{

bool GLContext::s_initialized = false;

bool GLContext::initialize()
{
    if (s_initialized)
    {
        Logger::warning("OpenGL context is already initialized.");
        return true;
    }

    Logger::debug("Initializing GLAD...");

    // SDL_GL_GetProcAddress already returns the function-pointer
    // type expected by GLAD on this platform.
    if (!gladLoadGL(
            [](const char* name) -> GLADapiproc
            {
                return reinterpret_cast<GLADapiproc>(
                    SDL_GL_GetProcAddress(name)
                );
            }))
    {
        Logger::error("Failed to initialize GLAD.");
        return false;
    }

    s_initialized = true;

    Logger::info("GLAD initialized successfully.");

    Logger::info(
        "OpenGL Vendor: " +
        std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR)))
    );

    Logger::info(
        "OpenGL Renderer: " +
        std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER)))
    );

    Logger::info(
        "OpenGL Version: " +
        std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION)))
    );

    return true;
}

void GLContext::shutdown()
{
    if (!s_initialized)
        return;

    Logger::debug("Shutting down OpenGL context loader.");

    s_initialized = false;
}

bool GLContext::isInitialized()
{
    return s_initialized;
}

}