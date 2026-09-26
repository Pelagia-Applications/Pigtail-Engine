#include <Graphics/Shader.hpp>

#include <Core/Logger.hpp>

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <utility>

namespace Pigtail
{

Shader::~Shader()
{
    destroy();
}

Shader::Shader(Shader&& other) noexcept
    : m_program(other.m_program)
{
    other.m_program = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept
{
    if (this != &other)
    {
        destroy();

        m_program = other.m_program;
        other.m_program = 0;
    }

    return *this;
}

bool Shader::loadFromFiles(
    const std::string& vertexPath,
    const std::string& fragmentPath
)
{
    destroy();

    std::string vertexSource;
    std::string fragmentSource;

    if (!readFile(vertexPath, vertexSource))
    {
        Logger::error("Failed to read vertex shader.");
        return false;
    }

    if (!readFile(fragmentPath, fragmentSource))
    {
        Logger::error("Failed to read fragment shader.");
        return false;
    }

    const char* vertexCode = vertexSource.c_str();
    const char* fragmentCode = fragmentSource.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(
        vertexShader,
        1,
        &vertexCode,
        nullptr
    );

    glCompileShader(vertexShader);

    int success = 0;
    glGetShaderiv(
        vertexShader,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[1024];

        glGetShaderInfoLog(
            vertexShader,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        Logger::error(
            std::string("Vertex shader compilation failed: ") +
            infoLog
        );

        glDeleteShader(vertexShader);

        return false;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(
        fragmentShader,
        1,
        &fragmentCode,
        nullptr
    );

    glCompileShader(fragmentShader);

    glGetShaderiv(
        fragmentShader,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[1024];

        glGetShaderInfoLog(
            fragmentShader,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        Logger::error(
            std::string("Fragment shader compilation failed: ") +
            infoLog
        );

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return false;
    }

    m_program = createProgram(
        vertexShader,
        fragmentShader
    );

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if (m_program == 0)
    {
        return false;
    }

    Logger::info(
        "Shader program created successfully."
    );

    return true;
}

void Shader::bind() const
{
    if (m_program != 0)
    {
        glUseProgram(m_program);
    }
}

void Shader::unbind() const
{
    glUseProgram(0);
}

bool Shader::isValid() const
{
    return m_program != 0;
}

void Shader::setBool(
    const std::string& name,
    bool value
)
{
    setInt(name, value ? 1 : 0);
}

void Shader::setInt(
    const std::string& name,
    int value
)
{
    if (m_program == 0)
        return;

    glUniform1i(
        glGetUniformLocation(
            m_program,
            name.c_str()
        ),
        value
    );
}

void Shader::setFloat(
    const std::string& name,
    float value
)
{
    if (m_program == 0)
        return;

    glUniform1f(
        glGetUniformLocation(
            m_program,
            name.c_str()
        ),
        value
    );
}

void Shader::setVec2(
    const std::string& name,
    const Vec2& value
)
{
    if (m_program == 0)
        return;

    glUniform2f(
        glGetUniformLocation(
            m_program,
            name.c_str()
        ),
        value.x,
        value.y
    );
}

void Shader::setVec3(
    const std::string& name,
    const Vec3& value
)
{
    if (m_program == 0)
        return;

    glUniform3f(
        glGetUniformLocation(
            m_program,
            name.c_str()
        ),
        value.x,
        value.y,
        value.z
    );
}

void Shader::setVec4(
    const std::string& name,
    const Vec4& value
)
{
    if (m_program == 0)
        return;

    glUniform4f(
        glGetUniformLocation(
            m_program,
            name.c_str()
        ),
        value.x,
        value.y,
        value.z,
        value.w
    );
}

void Shader::setMat4(
    const std::string& name,
    const Mat4& value
)
{
    if (m_program == 0)
        return;

    glUniformMatrix4fv(
        glGetUniformLocation(
            m_program,
            name.c_str()
        ),
        1,
        GL_FALSE,
        value.data()
    );
}

void Shader::destroy()
{
    if (m_program != 0)
    {
        glDeleteProgram(m_program);
        m_program = 0;
    }
}

bool Shader::readFile(
    const std::string& path,
    std::string& output
)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        Logger::error(
            std::string("Failed to open shader file: ") +
            path
        );

        return false;
    }

    std::stringstream buffer;

    buffer << file.rdbuf();

    output = buffer.str();

    return true;
}

unsigned int Shader::createProgram(
    unsigned int vertexShader,
    unsigned int fragmentShader
)
{
    unsigned int program = glCreateProgram();

    glAttachShader(
        program,
        vertexShader
    );

    glAttachShader(
        program,
        fragmentShader
    );

    glLinkProgram(program);

    int success = 0;

    glGetProgramiv(
        program,
        GL_LINK_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[1024];

        glGetProgramInfoLog(
            program,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        Logger::error(
            std::string("Shader program linking failed: ") +
            infoLog
        );

        glDeleteProgram(program);

        return 0;
    }

    return program;
}

}