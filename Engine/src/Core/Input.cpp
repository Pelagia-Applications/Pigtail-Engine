#include "Core/Input.hpp"

namespace Pigtail
{

bool Input::s_initialized = false;

bool Input::s_keys[SDL_SCANCODE_COUNT] = {};
bool Input::s_previousKeys[SDL_SCANCODE_COUNT] = {};

bool Input::s_mouseButtons[Input::MouseButtonCount] = {};
bool Input::s_previousMouseButtons[Input::MouseButtonCount] = {};

float Input::s_mouseX = 0.0f;
float Input::s_mouseY = 0.0f;

float Input::s_mouseDeltaX = 0.0f;
float Input::s_mouseDeltaY = 0.0f;

float Input::s_mouseWheelX = 0.0f;
float Input::s_mouseWheelY = 0.0f;

bool Input::initialize()
{
    if (s_initialized)
        return true;

    for (int i = 0; i < SDL_SCANCODE_COUNT; ++i)
    {
        s_keys[i] = false;
        s_previousKeys[i] = false;
    }

    for (int i = 0; i < MouseButtonCount; ++i)
    {
        s_mouseButtons[i] = false;
        s_previousMouseButtons[i] = false;
    }

    s_mouseX = 0.0f;
    s_mouseY = 0.0f;

    s_mouseDeltaX = 0.0f;
    s_mouseDeltaY = 0.0f;

    s_mouseWheelX = 0.0f;
    s_mouseWheelY = 0.0f;

    s_initialized = true;

    return true;
}

void Input::shutdown()
{
    if (!s_initialized)
        return;

    for (int i = 0; i < SDL_SCANCODE_COUNT; ++i)
    {
        s_keys[i] = false;
        s_previousKeys[i] = false;
    }

    for (int i = 0; i < MouseButtonCount; ++i)
    {
        s_mouseButtons[i] = false;
        s_previousMouseButtons[i] = false;
    }

    s_mouseX = 0.0f;
    s_mouseY = 0.0f;

    s_mouseDeltaX = 0.0f;
    s_mouseDeltaY = 0.0f;

    s_mouseWheelX = 0.0f;
    s_mouseWheelY = 0.0f;

    s_initialized = false;
}

void Input::beginFrame()
{
    if (!s_initialized)
        return;

    for (int i = 0; i < SDL_SCANCODE_COUNT; ++i)
    {
        s_previousKeys[i] = s_keys[i];
    }

    for (int i = 0; i < MouseButtonCount; ++i)
    {
        s_previousMouseButtons[i] = s_mouseButtons[i];
    }

    // These are per-frame values.
    s_mouseDeltaX = 0.0f;
    s_mouseDeltaY = 0.0f;

    s_mouseWheelX = 0.0f;
    s_mouseWheelY = 0.0f;
}

void Input::processEvent(const SDL_Event& event)
{
    if (!s_initialized)
        return;

    switch (event.type)
    {
        case SDL_EVENT_KEY_DOWN:
        {
            const SDL_Scancode key = event.key.scancode;

            if (key >= 0 && key < SDL_SCANCODE_COUNT)
            {
                s_keys[key] = true;
            }

            break;
        }

        case SDL_EVENT_KEY_UP:
        {
            const SDL_Scancode key = event.key.scancode;

            if (key >= 0 && key < SDL_SCANCODE_COUNT)
            {
                s_keys[key] = false;
            }

            break;
        }

        case SDL_EVENT_MOUSE_MOTION:
        {
            s_mouseX = event.motion.x;
            s_mouseY = event.motion.y;

            s_mouseDeltaX += event.motion.xrel;
            s_mouseDeltaY += event.motion.yrel;

            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        {
            const Uint8 button = event.button.button;

            if (button < MouseButtonCount)
            {
                s_mouseButtons[button] = true;
            }

            break;
        }

        case SDL_EVENT_MOUSE_BUTTON_UP:
        {
            const Uint8 button = event.button.button;

            if (button < MouseButtonCount)
            {
                s_mouseButtons[button] = false;
            }

            break;
        }

        case SDL_EVENT_MOUSE_WHEEL:
        {
            s_mouseWheelX += event.wheel.x;
            s_mouseWheelY += event.wheel.y;

            break;
        }

        default:
            break;
    }
}

bool Input::isKeyDown(SDL_Scancode key)
{
    if (!s_initialized)
        return false;

    if (key < 0 || key >= SDL_SCANCODE_COUNT)
        return false;

    return s_keys[key];
}

bool Input::isKeyPressed(SDL_Scancode key)
{
    if (!s_initialized)
        return false;

    if (key < 0 || key >= SDL_SCANCODE_COUNT)
        return false;

    return s_keys[key] && !s_previousKeys[key];
}

bool Input::isKeyReleased(SDL_Scancode key)
{
    if (!s_initialized)
        return false;

    if (key < 0 || key >= SDL_SCANCODE_COUNT)
        return false;

    return !s_keys[key] && s_previousKeys[key];
}

bool Input::isMouseButtonDown(Uint8 button)
{
    if (!s_initialized)
        return false;

    if (button >= MouseButtonCount)
        return false;

    return s_mouseButtons[button];
}

bool Input::isMouseButtonPressed(Uint8 button)
{
    if (!s_initialized)
        return false;

    if (button >= MouseButtonCount)
        return false;

    return s_mouseButtons[button] &&
           !s_previousMouseButtons[button];
}

bool Input::isMouseButtonReleased(Uint8 button)
{
    if (!s_initialized)
        return false;

    if (button >= MouseButtonCount)
        return false;

    return !s_mouseButtons[button] &&
           s_previousMouseButtons[button];
}

float Input::mouseX()
{
    return s_mouseX;
}

float Input::mouseY()
{
    return s_mouseY;
}

float Input::mouseDeltaX()
{
    return s_mouseDeltaX;
}

float Input::mouseDeltaY()
{
    return s_mouseDeltaY;
}

float Input::mouseWheelX()
{
    return s_mouseWheelX;
}

float Input::mouseWheelY()
{
    return s_mouseWheelY;
}

}