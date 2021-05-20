#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/glm/mat4x4.hpp>

namespace RenderEngine {
    class ShaderProgram {
    public:
        ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
        ~ShaderProgram();
        bool isCompiled() const { return m_isCompiled; }
        void use() const;
        void setInt(const std::string& name, const GLint value);
        void setMatrix4(const std::string& name, const glm::mat4& matrix);

        //запрещаем конструктор без параметров
        ShaderProgram() = delete;
        //запрещаем конструирование шейд.пр с другой шейд.пр
        ShaderProgram(const ShaderProgram&) = delete;
        //запрещаем оператор =, чтобы не приравнивать 1 шейдер к др
        ShaderProgram& operator=(const ShaderProgram&) = delete;
        ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
        ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

        GLuint m_ID = 0;
    private:
        bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);

        bool m_isCompiled = false;

    };
}