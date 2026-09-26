#pragma once

namespace Pigtail
{

class Time
{
public:
    static void initialize();
    static void update();

    static float deltaTime();
    static float elapsedTime();
    static float framesPerSecond();

    static double deltaTimePrecise();
    static double elapsedTimePrecise();

    static unsigned long long frameCount();

private:
    static double s_deltaTime;
    static double s_elapsedTime;
    static double s_lastTime;

    static unsigned long long s_frameCount;
};

} 