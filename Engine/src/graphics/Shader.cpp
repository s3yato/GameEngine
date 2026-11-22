#include <atlas/graphics/Shader.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
namespace atlas
{
    std::string readShaderFile(const std::string& path)
    {
        std::ifstream file(path);

        if (!file.is_open()) {
            throw std::runtime_error(
                "Failed to open shader file: " + path
            );
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        return buffer.str();
    }

    Shader::Shader(
        const std::string& vertexPath,
        const std::string& fragmentPath
    )
    {
        const std::string vertexSource = readShaderFile(vertexPath);
        const std::string fragmentSource = readShaderFile(fragmentPath);

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const char* vertexCode = vertexSource.c_str();

        glShaderSource(
            vertexShader, 
            1,
            &vertexCode,
            nullptr
        );

        glCompileShader(vertexShader);

        GLint success;
        glGetShaderiv(
            vertexShader,
            GL_COMPILE_STATUS,
            &success
        );

        if (!success)
        {
            char infoLog[512];

            glGetShaderInfoLog(
                vertexShader,
                512,
                nullptr,
                infoLog
            );

            glDeleteShader(vertexShader);

            throw std::runtime_error(
                std::string("Vertex shader compilation failed:\n") +
                infoLog
            );
        }

        // -------------------------
        // Fragment Shader
        // -------------------------

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        const char* fragmentCode = fragmentSource.c_str();

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
            char infoLog[512];

            glGetShaderInfoLog(
                fragmentShader,
                512,
                nullptr,
                infoLog
            );

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            throw std::runtime_error(
                std::string("Fragment shader compilation failed:\n") +
                infoLog
            );
        }

        // -------------------------
        // Shader Program
        // -------------------------

        m_program = glCreateProgram();

        glAttachShader(m_program, vertexShader);
        glAttachShader(m_program, fragmentShader);

        glLinkProgram(m_program);

        glGetProgramiv(
            m_program,
            GL_LINK_STATUS,
            &success
        );

        if (!success)
        {
            char infoLog[512];

            glGetProgramInfoLog(
                m_program,
                512,
                nullptr,
                infoLog
            );

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            glDeleteProgram(m_program);

            throw std::runtime_error(
                std::string("Shader program linking failed:\n") +
                infoLog
            );
        }

        // После linking отдельные shaders больше не нужны
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_program);
    }

    void Shader::use()
    {
        glUseProgram(m_program);
    }

    void Shader::changeColor(float r, float g, float b, float a)
    {  
        int vertexColorLocation = glGetUniformLocation(m_program, "ourColor");
        glUniform4f(vertexColorLocation, r, g, b, a);

    }

    void Shader::setMat4(const std::string& name, const Matrix4& matrix)
    {
        GLint location = glGetUniformLocation(m_program, name.c_str());
		glUniformMatrix4fv(location, 1,
			GL_FALSE,
			matrix.data()
		);
    }
}