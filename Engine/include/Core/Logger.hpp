#pragma once

#include <string>
#include <string_view>
#include <sstream>
#include <utility>

namespace Pigtail
{

class Logger
{
public:
    static void debug(std::string_view message);
    static void info(std::string_view message);
    static void warning(std::string_view message);
    static void warn(std::string_view message);
    static void error(std::string_view message);

    template<typename... Args>
    static void debug(std::string_view format, Args&&... args)
    {
        debug(formatString(format, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void info(std::string_view format, Args&&... args)
    {
        info(formatString(format, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void warning(std::string_view format, Args&&... args)
    {
        warning(formatString(format, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void warn(std::string_view format, Args&&... args)
    {
        warn(formatString(format, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void error(std::string_view format, Args&&... args)
    {
        error(formatString(format, std::forward<Args>(args)...));
    }

private:
    template<typename T>
    static std::string valueToString(T&& value)
    {
        std::ostringstream stream;
        stream << std::forward<T>(value);
        return stream.str();
    }

    static std::string formatString(std::string_view format)
    {
        return std::string(format);
    }

    template<typename T, typename... Args>
    static std::string formatString(
        std::string_view format,
        T&& value,
        Args&&... args)
    {
        const std::size_t position = format.find("{}");

        if (position == std::string_view::npos)
        {
            return std::string(format);
        }

        std::string result;

        result.reserve(format.size() + 32);

        result.append(format.substr(0, position));
        result += valueToString(std::forward<T>(value));

        result += formatString(
            format.substr(position + 2),
            std::forward<Args>(args)...
        );

        return result;
    }
};

}