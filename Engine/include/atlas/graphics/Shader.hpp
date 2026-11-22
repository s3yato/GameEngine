#pragma once

#include <string>
#include <glad/glad.h>
#include <atlas/math/Matrix4.hpp>

namespace atlas
{
    class Shader
    {
        public:
            Shader(
                const std::string& vertexPath,
                const std::string& fragmentPath
            );

            ~Shader();

            void use();
            void changeColor(float r, float g, float b, float a);
            void setMat4(const std::string& name, const Matrix4& matrix);
        private:
            unsigned int m_program;
    };
}