#include <Core/Application.hpp>
#include <Core/Input.hpp>
#include <Core/Logger.hpp>
#include <Graphics/ShapeRenderer.hpp>
#include <Core/Time.hpp>

#include <Window/Window.hpp>

#include <Graphics/Renderer.hpp>
#include <Graphics/GLContext.hpp>
#include <Graphics/Shader.hpp>
#include <Graphics/Mesh.hpp>
#include <Graphics/Camera2D.hpp>
#include <Graphics/Camera3D.hpp>

#include <Audio/Audio.hpp>

#include <Math/Transform.hpp>
#include <Math/Math.hpp>

#include <glad/glad.h>


namespace Pigtail
{

Application::Application()
    : m_Camera2D(1280.0f, 720.0f)
{
}

Application::~Application()
{
    shutdown();
}


bool Application::initialize()
{
    Logger::info(
        "================================"
    );

    Logger::info(
        "      Pigtail Engine 0.1.0"
    );

    Logger::info(
        "================================"
    );

    Logger::info(
        "Initializing application..."
    );


    // -----------------------------------------------------
    // Window
    // -----------------------------------------------------

    m_window = std::make_unique<Window>(
        "Pigtail Engine",
        1280,
        720
    );

    if (!m_window->initialize())
    {
        Logger::error(
            "Failed to initialize window."
        );

        return false;
    }

    // ------------------------------------------------------
    // Time
    // -----------------------------------------------------

    Time::initialize();

    // -----------------------------------------------------
    // OpenGL / GLAD
    // -----------------------------------------------------

    if (!GLContext::initialize())
    {
        Logger::error(
            "Failed to initialize OpenGL."
        );

        return false;
    }


    // -----------------------------------------------------
    // Depth testing
    // -----------------------------------------------------

    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LESS);


    // -----------------------------------------------------
    // Audio
    // -----------------------------------------------------

    if (!Audio::initialize())
    {
        Logger::error(
            "Failed to initialize audio."
        );

        return false;
    }


    // -----------------------------------------------------
    // Renderer
    // -----------------------------------------------------

    m_renderer = std::make_unique<Renderer>();

    if (!m_renderer->initialize())
    {
        Logger::error(
            "Failed to initialize renderer."
        );

        return false;
    }


    // -----------------------------------------------------
    // Shape Renderer
    // -----------------------------------------------------

    if (!m_shapeRenderer.initialize())
    {
        Logger::error(
            "Failed to initialize shape renderer."
        );

        return false;
    }


    m_running = true;

    Logger::info(
        "Application initialized successfully."
    );

    return true;
}


void Application::run()
{
    Logger::info(
        "Entering main loop."
    );


    // =====================================================
    // 3D SHADER
    // =====================================================

    Shader shader;

    if (!shader.loadFromFiles(
        "Assets/Shaders/basic3d.vert",
        "Assets/Shaders/basic3d.frag"
    ))
    {
        Logger::error(
            "Failed to load 3D shader."
        );

        m_running = false;
        return;
    }


    // =====================================================
    // CUBE
    // =====================================================

    Mesh cube = Mesh::createCube();

    if (!cube.isValid())
    {
        Logger::error(
            "Failed to create cube mesh."
        );

        m_running = false;
        return;
    }


    // =====================================================
    // CUBE TRANSFORM AND ROTATION
    // =====================================================

    Transform cubeTransform;

    cubeTransform.setPosition(
        Vec3(
            0.0f,
            0.0f,
            0.0f
        )
    );

    float angle = 0.0f;

    // =====================================================
    // 3D CAMERA
    // =====================================================

    Camera3D camera;

    camera.setPosition(
        Vec3(
            0.0f,
            0.0f,
            3.0f
        )
    );

    camera.setPerspective(
        Math::radians(60.0f),
        1280.0f / 720.0f,
        0.1f,
        100.0f
    );
    
    angle = 0.0f;

    // =====================================================
    // MAIN LOOP
    // =====================================================

    while (
        m_running &&
        !m_window->shouldClose()
    )
    {
        // -------------------------------------------------
        // Input
        // -------------------------------------------------

        Input::beginFrame();

        m_window->pollEvents();


        // -------------------------------------------------
        // Renderer
        // -------------------------------------------------

        m_renderer->beginFrame();

        Audio::update();

        m_renderer->clear();

        // -------------------------------------------------
        // Time
        // -------------------------------------------------

        Time::update();


        // =================================================
        // 3D RENDERING
        // =================================================

        Mat4 model =
        Mat4::translation(cubeTransform.position) *
        Mat4::rotation(
            Quaternion::fromEuler(
                angle * 0.7f,
                angle,
                0.0f
            )
        ) *
        
        Mat4::scale(cubeTransform.scale);

        shader.bind();

        shader.setMat4(
            "u_viewProjection",
            camera.viewProjectionMatrix()
        );

        shader.setMat4(
            "u_model",
            model
        );

        shader.setVec4(
            "u_color",
            Vec4(0.2f, 0.6f, 1.0f, 1.0f)
        );

        shader.setVec3(
            "u_lightDirection",
            Vec3(-1.0f, -1.0f, -1.0f)
        );

        shader.setVec3(
            "u_lightColor",
            Vec3(1.0f, 1.0f, 1.0f)
        );

        angle += Time::deltaTime();
        
        cube.draw();

        shader.unbind();


        shader.unbind();


        // =================================================
        // 2D RENDERING
        // =================================================

        m_shapeRenderer.begin(
            m_Camera2D
        );


        m_shapeRenderer.drawRectangle(
            Vec2(
                0.0f,
                0.0f
            ),
            Vec2(
                200.0f,
                100.0f
            ),
            Vec4(
                1.0f,
                0.2f,
                0.2f,
                1.0f
            )
        );



        m_shapeRenderer.drawRectangleOutline(
            Vec2(
                0.0f,
                0.0f
            ),
            Vec2(
                220.0f,
                120.0f
            ),
            Vec4(
                1.0f,
                1.0f,
                1.0f,
                1.0f
            ),
            0.0f,
            3.0f
        );


        m_shapeRenderer.drawLine(
            Vec2(
                -300.0f,
                -100.0f
            ),
            Vec2(
                300.0f,
                -100.0f
            ),
            Vec4(
                0.2f,
                1.0f,
                0.2f,
                1.0f
            ),
            4.0f
        );


        m_shapeRenderer.drawCircle(
            Vec2(
                300.0f,
                100.0f
            ),
            50.0f,
            Vec4(
                0.2f,
                0.5f,
                1.0f,
                1.0f
            )
        );


        m_shapeRenderer.end();


        // -------------------------------------------------
        // End frame
        // -------------------------------------------------

        m_renderer->endFrame();

        m_window->swapBuffers();
    }


    Logger::info(
        "Leaving main loop."
    );
}


void Application::shutdown()
{
    if (
        !m_running &&
        !m_window &&
        !m_renderer
    )
    {
        return;
    }


    Logger::info(
        "Shutting down application..."
    );


    if (m_renderer)
    {
        m_renderer->shutdown();

        m_renderer.reset();
    }


    m_shapeRenderer.shutdown();


    Audio::shutdown();


    GLContext::shutdown();


    if (m_window)
    {
        m_window.reset();
    }


    m_running = false;


    Logger::info(
        "Application shutdown complete."
    );
}

}