#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

#include <string>

namespace Pigtail
{

class Shader
{
public:
    Shader() = default;
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    bool loadFromFiles(
        const std::string& vertexPath,
        const std::string& fragmentPath
    );

    void destroy();

    void bind() const;
    void unbind() const;

    bool isValid() const;

    unsigned int id() const;

    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);

    void setVec2(const std::string& name, const glm::vec2& value);
    void setVec3(const std::string& name, const glm::vec3& value);
    void setVec4(const std::string& name, const glm::vec4& value);

    void setMat4(
        const std::string& name,
        const glm::mat4& value
    );

private:
    unsigned int m_program = 0;

    int getUniformLocation(const std::string& name) const;

    static bool readFile(
        const std::string& path,
        std::string& output
    );

    static unsigned int compileShader(
        unsigned int type,
        const std::string& source
    );

    static unsigned int createProgram(
        unsigned int vertexShader,
        unsigned int fragmentShader
    );
};

}