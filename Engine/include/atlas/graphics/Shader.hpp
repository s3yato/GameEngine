#pragma once

#include <string>

namespace atlas
{
    class Shader
    {
        public:
            Shader(
                const std::string& vertexSource,
                const std::string& fragmentSource
            );

            ~Shader();

            void use();
        private:
            unsigned int m_program;
    };
}