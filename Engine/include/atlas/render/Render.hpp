#pragma once

#include <atlas/graphics/Shader.hpp>

namespace atlas
{
    class Render
    {
        public:
            Render();
            ~Render();

            void clear();
            void render();
        private:
            Shader* m_shader;

            unsigned int m_VAO;
            unsigned int m_VBO;
    };
}