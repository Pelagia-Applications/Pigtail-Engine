#pragma once

#include <stdint.h>
namespace Pigtail
{

class GLContext
{
public:

    static bool initialize();

    static void shutdown();

    static bool isInitialized();

private:

    static bool s_initialized;
};

}