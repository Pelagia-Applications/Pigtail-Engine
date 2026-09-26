#include "Core/Logger.hpp"

#include <iostream>

namespace Pigtail
{

void Logger::debug(std::string_view message)
{
    std::cout << "[DEBUG] " << message << '\n';
}

void Logger::info(std::string_view message)
{
    std::cout << "[INFO ] " << message << '\n';
}

void Logger::warning(std::string_view message)
{
    std::cout << "[WARN ] " << message << '\n';
}

void Logger::warn(std::string_view message)
{
    warning(message);
}

void Logger::error(std::string_view message)
{
    std::cerr << "[ERROR] " << message << '\n';
}

}