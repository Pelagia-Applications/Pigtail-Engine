#include <Core/Logger.hpp>

#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Pigtail
{

void Logger::debug(std::string_view message)
{
    log(LogLevel::Debug, message);
}

void Logger::info(std::string_view message)
{
    log(LogLevel::Info, message);
}

void Logger::warning(std::string_view message)
{
    log(LogLevel::Warning, message);
}

void Logger::error(std::string_view message)
{
    log(LogLevel::Error, message);
}

void Logger::log(
    LogLevel level,
    std::string_view message
)
{
    std::string prefix;

    switch (level)
    {
        case LogLevel::Debug:
            prefix = "[DEBUG]";
            break;

        case LogLevel::Info:
            prefix = "[INFO ]";
            break;

        case LogLevel::Warning:
            prefix = "[WARN ]";
            break;

        case LogLevel::Error:
            prefix = "[ERROR]";
            break;
    }

    std::string output =
        prefix + " " + std::string(message) + "\n";

    std::cout << output;

#ifdef _WIN32
    OutputDebugStringA(output.c_str());
#endif
}

}