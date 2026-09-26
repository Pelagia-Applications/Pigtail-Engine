#include "Graphics/Shader.hpp"

#include "Core/Logger.hpp"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

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
        Logger::error(
            "Failed to read vertex shader: " + vertexPath
        );

        return false;
    }

    if (!readFile(fragmentPath, fragmentSource))
    {
        Logger::error(
            "Failed to read fragment shader: " + fragmentPath
        );

        return false;
    }

    const unsigned int vertexShader =
        compileShader(GL_VERTEX_SHADER, vertexSource);

    if (vertexShader == 0)
    {
        return false;
    }

    const unsigned int fragmentShader =
        compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    if (fragmentShader == 0)
    {
        glDeleteShader(vertexShader);
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

void Shader::destroy()
{
    if (m_program != 0)
    {
        glDeleteProgram(m_program);
        m_program = 0;
    }
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

unsigned int Shader::id() const
{
    return m_program;
}

int Shader::getUniformLocation(
    const std::string& name
) const
{
    if (m_program == 0)
    {
        return -1;
    }

    return glGetUniformLocation(
        m_program,
        name.c_str()
    );
}

void Shader::setBool(
    const std::string& name,
    bool value
)
{
    const int location = getUniformLocation(name);

    if (location >= 0)
    {
        glUniform1i(location, value ? 1 : 0);
    }
}

void Shader::setInt(
    const std::string& name,
    int value
)
{
    const int location = getUniformLocation(name);

    if (location >= 0)
    {
        glUniform1i(location, value);
    }
}

void Shader::setFloat(
    const std::string& name,
    float value
)
{
    const int location = getUniformLocation(name);

    if (location >= 0)
    {
        glUniform1f(location, value);
    }
}

void Shader::setVec2(
    const std::string& name,
    const glm::vec2& value
)
{
    const int location = getUniformLocation(name);

    if (location >= 0)
    {
        glUniform2fv(
            location,
            1,
            glm::value_ptr(value)
        );
    }
}

void Shader::setVec3(
    const std::string& name,
    const glm::vec3& value
)
{
    const int location = getUniformLocation(name);

    if (location >= 0)
    {
        glUniform3fv(
            location,
            1,
            glm::value_ptr(value)
        );
    }
}

void Shader::setVec4(
    const std::string& name,
    const glm::vec4& value
)
{
    const int location = getUniformLocation(name);

    if (location >= 0)
    {
        glUniform4fv(
            location,
            1,
            glm::value_ptr(value)
        );
    }
}

void Shader::setMat4(
    const std::string& name,
    const glm::mat4& value
)
{
    const int location = getUniformLocation(name);

    if (location >= 0)
    {
        glUniformMatrix4fv(
            location,
            1,
            GL_FALSE,
            glm::value_ptr(value)
        );
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
            "Could not open shader file: " + path
        );

        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    output = buffer.str();

    return true;
}

unsigned int Shader::compileShader(
    unsigned int type,
    const std::string& source
)
{
    const unsigned int shader =
        glCreateShader(type);

    if (shader == 0)
    {
        Logger::error(
            "Failed to create OpenGL shader."
        );

        return 0;
    }

    const char* sourceData = source.c_str();

    glShaderSource(
        shader,
        1,
        &sourceData,
        nullptr
    );

    glCompileShader(shader);

    int success = 0;

    glGetShaderiv(
        shader,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success)
    {
        int logLength = 0;

        glGetShaderiv(
            shader,
            GL_INFO_LOG_LENGTH,
            &logLength
        );

        std::string log(
            static_cast<size_t>(logLength),
            '\0'
        );

        glGetShaderInfoLog(
            shader,
            logLength,
            nullptr,
            log.data()
        );

        if (type == GL_VERTEX_SHADER)
        {
            Logger::error(
                "Vertex shader compilation failed:\n" + log
            );
        }
        else
        {
            Logger::error(
                "Fragment shader compilation failed:\n" + log
            );
        }

        glDeleteShader(shader);

        return 0;
    }

    return shader;
}

unsigned int Shader::createProgram(
    unsigned int vertexShader,
    unsigned int fragmentShader
)
{
    const unsigned int program =
        glCreateProgram();

    if (program == 0)
    {
        Logger::error(
            "Failed to create OpenGL shader program."
        );

        return 0;
    }

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    int success = 0;

    glGetProgramiv(
        program,
        GL_LINK_STATUS,
        &success
    );

    if (!success)
    {
        int logLength = 0;

        glGetProgramiv(
            program,
            GL_INFO_LOG_LENGTH,
            &logLength
        );

        std::string log(
            static_cast<size_t>(logLength),
            '\0'
        );

        glGetProgramInfoLog(
            program,
            logLength,
            nullptr,
            log.data()
        );

        Logger::error(
            "Shader program linking failed:\n" + log
        );

        glDeleteProgram(program);

        return 0;
    }

    return program;
}

}