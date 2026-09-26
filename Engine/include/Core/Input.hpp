#pragma once

#include <SDL3/SDL.h>

namespace Pigtail
{

class Input
{
public:
    static bool initialize();
    static void shutdown();

    static void beginFrame();
    static void processEvent(const SDL_Event& event);

    // Keyboard
    static bool isKeyDown(SDL_Scancode key);
    static bool isKeyPressed(SDL_Scancode key);
    static bool isKeyReleased(SDL_Scancode key);

    // Mouse buttons
    static bool isMouseButtonDown(Uint8 button);
    static bool isMouseButtonPressed(Uint8 button);
    static bool isMouseButtonReleased(Uint8 button);

    // Mouse position
    static float mouseX();
    static float mouseY();

    // Mouse movement
    static float mouseDeltaX();
    static float mouseDeltaY();

    // Mouse wheel
    static float mouseWheelX();
    static float mouseWheelY();

private:
    static constexpr int MouseButtonCount = 8;

    static bool s_initialized;

    static bool s_keys[SDL_SCANCODE_COUNT];
    static bool s_previousKeys[SDL_SCANCODE_COUNT];

    static bool s_mouseButtons[MouseButtonCount];
    static bool s_previousMouseButtons[MouseButtonCount];

    static float s_mouseX;
    static float s_mouseY;

    static float s_mouseDeltaX;
    static float s_mouseDeltaY;

    static float s_mouseWheelX;
    static float s_mouseWheelY;
};

}