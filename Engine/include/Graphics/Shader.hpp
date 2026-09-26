#pragma once

#include <string>
#include <string_view>

#include <Math/Vec2.hpp>
#include <Math/Vec3.hpp>
#include <Math/Vec4.hpp>
#include <Math/Mat4.hpp>

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

    void bind() const;
    void unbind() const;

    bool isValid() const;

    void setBool(
        const std::string& name,
        bool value
    );

    void setInt(
        const std::string& name,
        int value
    );

    void setFloat(
        const std::string& name,
        float value
    );

    void setVec2(
        const std::string& name,
        const Vec2& value
    );

    void setVec3(
        const std::string& name,
        const Vec3& value
    );

    void setVec4(
        const std::string& name,
        const Vec4& value
    );

    void setMat4(
        const std::string& name,
        const Mat4& value
    );

private:
    unsigned int m_program = 0;

    void destroy();

    static bool readFile(
        const std::string& path,
        std::string& output
    );

    static unsigned int createProgram(
        unsigned int vertexShader,
        unsigned int fragmentShader
    );
};

}