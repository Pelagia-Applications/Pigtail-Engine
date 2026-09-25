#include <Core/Application.hpp>
#include <Core/Logger.hpp>
#include <Core/Input.hpp>

int main()
{
    Pigtail::Logger::info(
        "Starting Pigtail Engine."
    );

    Pigtail::Application application;
    Pigtail::Input::initialize();

    if (!application.initialize())
    {
        Pigtail::Logger::error(
            "Failed to initialize Pigtail Engine."
        );

        return 1;
    }

    application.run();


    Pigtail::Logger::info(
        "Pigtail Engine exited normally."
    );

    return 0;
}