#pragma once

#include <atlas/graphics/Shader.hpp>
#include <atlas/render/Mesh.hpp>
#include <atlas/render/Material.hpp>
#include <atlas/math/Matrix4.hpp>

#include <memory>

namespace atlas
{
    class Render
    {
        public:
            Render();
            ~Render();

            Render(const Render&) = delete;
            Render& operator=(const Render&) = delete;

            void clear();
            void render(
                const Matrix4& model,
                const Matrix4& view,
                const Matrix4& projection
            );
        private:
            Mesh m_mesh;
            Material m_material;
            std::unique_ptr<Shader> m_shader;
    };
}