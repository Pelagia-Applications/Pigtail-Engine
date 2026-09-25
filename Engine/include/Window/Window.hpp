#pragma once

#include <string>

#include <SDL3/SDL.h>

namespace Pelagia
{

class Window
{
public:

    Window(
        const std::string& title,
        int width,
        int height
    );

    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool initialize();

    void shutdown();

    void pollEvents();

    void swapBuffers();

    bool shouldClose() const;

    SDL_Window* nativeHandle() const;

    SDL_GLContext glContext() const;

    int width() const;

    int height() const;

private:

    std::string m_title;

    int m_width;
    int m_height;

    SDL_Window* m_window = nullptr;

    SDL_GLContext m_glContext = nullptr;

    bool m_shouldClose = false;
};

}