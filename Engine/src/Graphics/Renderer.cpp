#include <Graphics/Renderer.hpp>

#include <Core/Logger.hpp>
#include <Graphics/GLContext.hpp>

#include <glad/glad.h>

namespace Pigtail
{

Renderer::~Renderer()
{
    shutdown();
}

bool Renderer::initialize()
{
    if (m_initialized)
    {
        Logger::warning(
            "Renderer is already initialized."
        );

        return true;
    }

    if (!GLContext::isInitialized())
    {
        Logger::error(
            "Cannot initialize Renderer before "
            "OpenGL has been initialized."
        );

        return false;
    }

    Logger::info(
        "Initializing renderer..."
    );

    glEnable(GL_DEPTH_TEST);

    m_initialized = true;

    Logger::info(
        "Renderer initialized."
    );

    return true;
}

void Renderer::shutdown()
{
    if (!m_initialized)
        return;

    Logger::debug(
        "Shutting down renderer."
    );

    m_initialized = false;
}

void Renderer::beginFrame()
{
    if (!m_initialized)
        return;
}

void Renderer::clear()
{
    if (!m_initialized)
        return;

    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );
}

void Renderer::endFrame()
{
    if (!m_initialized)
        return;
}

bool Renderer::isInitialized() const
{
    return m_initialized;
}

}