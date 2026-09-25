#include <Core/Application.hpp>
#include <Core/Logger.hpp>

int main()
{
    Pelagia::Logger::info(
        "Starting Pigtail Engine."
    );

    Pelagia::Application application;

    if (!application.initialize())
    {
        Pelagia::Logger::error(
            "Failed to initialize Pigtail Engine."
        );

        return 1;
    }

    application.run();

    Pelagia::Logger::info(
        "Pigtail Engine exited normally."
    );

    return 0;
}