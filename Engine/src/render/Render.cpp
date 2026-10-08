#include <atlas/render/Render.hpp>
#include <OpenGL/gl3.h>

namespace atlas
{

    Render::Render()
    {
        const std::string vertexSource = R"(
        #version 330 core 

        layout (location = 0) in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos, 1.0);
        }
        )";

        const std::string fragmentSource = R"(
        #version 330 core 

        out vec4 FragColor;

        void main() 
        {
            FragColor = vec4(1.0, 0.0, 0.0, 0.1);
        }
        
        )";

        m_shader = new Shader(vertexSource, fragmentSource);

        float vertices[] = {
            0.0f, 0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
        };

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        
        glBindVertexArray(m_VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        
        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(vertices),
            vertices,
            GL_STATIC_DRAW
        );
        
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            3 * sizeof(float),
            nullptr
        );
        
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    Render::~Render()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);

        delete m_shader;
    }

    void Render::clear() {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Render::render() 
    {
        m_shader->use();

        glBindVertexArray(m_VAO);
        glDrawArrays(
            GL_TRIANGLES,
            0,
            3
        );
    }
}