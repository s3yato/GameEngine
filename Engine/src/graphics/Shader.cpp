#include <atlas/graphics/Shader.hpp>

#include <OpenGL/gl3.h>
#include <stdexcept>

namespace atlas
{
    Shader::Shader(
        const std::string& vertexSource,
        const std::string& fragmentSource
    )
    {
        // -------------------------
        // Vertex Shader
        // -------------------------

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
}