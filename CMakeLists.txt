cmake_minimum_required(VERSION 3.24)

project(PigtailEngine
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =========================================================
# Dependencies
# =========================================================

find_package(SDL3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# =========================================================
# Engine
# =========================================================

add_library(PigtailEngine STATIC

    # Core
    Engine/src/Core/Application.cpp
    Engine/src/Core/Engine.cpp
    Engine/src/Core/Logger.cpp
    Engine/src/Core/Time.cpp

    # Window
    Engine/src/Window/Window.cpp

    # Camera
    Engine/src/Camera/Camera.cpp

    # Graphics
    Engine/src/Graphics/Mesh.cpp
    Engine/src/Graphics/Renderer.cpp
    Engine/src/Graphics/Shader.cpp
    Engine/src/Graphics/Texture.cpp

    # Physics
    Engine/src/Physics/PhysicsWorld.cpp

    # Resources
    Engine/src/Resources/ResourceManager.cpp

    # Scene
    Engine/src/Scene/Entity.cpp
    Engine/src/Scene/Scene.cpp
    Engine/src/Scene/Transform.cpp

    # Scripting
    Engine/src/Scripting/Lua/LuaEngine.cpp
    Engine/src/Scripting/Python/PythonEngine.cpp
)

# =========================================================
# Include directories
# =========================================================

target_include_directories(PigtailEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/include
)

# =========================================================
# Libraries
# =========================================================

target_link_libraries(PigtailEngine
    PUBLIC
        SDL3::SDL3
        OpenGL::GL
)

# =========================================================
# Compiler warnings
# =========================================================

if(MSVC)

    target_compile_options(PigtailEngine PRIVATE
        /W4
    )

else()

    target_compile_options(PigtailEngine PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )

endif()

# =========================================================
# Sandbox / executable
# =========================================================

add_executable(PigtailSandbox

    Engine/src/main.cpp

)

target_link_libraries(PigtailSandbox
    PRIVATE
        PigtailEngine
)

# =========================================================
# Windows
# =========================================================

if(WIN32)

    target_link_libraries(PigtailEngine
        PUBLIC
            opengl32
    )

endif()