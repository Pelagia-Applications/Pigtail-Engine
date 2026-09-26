#include "Core/Time.hpp"

#include <chrono>

namespace Pigtail
{

double Time::s_deltaTime = 0.0;
double Time::s_elapsedTime = 0.0;
double Time::s_lastTime = 0.0;

unsigned long long Time::s_frameCount = 0;

void Time::initialize()
{
    using Clock = std::chrono::steady_clock;

    const auto now =
        Clock::now().time_since_epoch();

    s_lastTime =
        std::chrono::duration<double>(now).count();

    s_deltaTime = 0.0;
    s_elapsedTime = 0.0;
    s_frameCount = 0;
}

void Time::update()
{
    using Clock = std::chrono::steady_clock;

    const auto now =
        Clock::now().time_since_epoch();

    const double currentTime =
        std::chrono::duration<double>(now).count();

    s_deltaTime =
        currentTime - s_lastTime;

    s_lastTime = currentTime;

    s_elapsedTime += s_deltaTime;

    ++s_frameCount;
}

float Time::deltaTime()
{
    return static_cast<float>(s_deltaTime);
}

float Time::elapsedTime()
{
    return static_cast<float>(s_elapsedTime);
}

float Time::framesPerSecond()
{
    if (s_deltaTime <= 0.0)
        return 0.0f;

    return static_cast<float>(
        1.0 / s_deltaTime
    );
}

double Time::deltaTimePrecise()
{
    return s_deltaTime;
}

double Time::elapsedTimePrecise()
{
    return s_elapsedTime;
}

unsigned long long Time::frameCount()
{
    return s_frameCount;
}

}