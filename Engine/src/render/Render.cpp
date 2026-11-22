#include <atlas/render/Render.hpp>
#include <atlas/math/Transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <array>
#include <string>

namespace atlas
{

    Render::Render()
        : m_mesh(
        std::vector<float>{
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
    },
        std::vector<unsigned int>{
            0, 1, 3,
            1, 2, 3
    }
        ),
        m_material(0.0f, 1.0f, 0.0f, 1.0f),
        m_shader(std::make_unique<Shader>(
            std::string(ATLAS_SHADER_DIR) + "/basic.vert",
            std::string(ATLAS_SHADER_DIR) + "/basic.frag"
        ))
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Render::~Render() = default;

    void Render::clear()
    {
        glClearColor(0.18f, 0.20f, 0.24f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Render::render(
        const Matrix4& model,
        const Matrix4& view,
        const Matrix4& projection
    )
    {
        m_shader->use();

        const auto colors = m_material.getColor();

        m_shader->changeColor(
            colors[0],
            colors[1],
            colors[2],
            colors[3]
        );

        m_shader->setMat4("model", model);
        m_shader->setMat4("view", view);
        m_shader->setMat4("projection", projection);

        m_mesh.draw();
    }
}