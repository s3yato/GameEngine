#pragma once

#include <atlas/math/Matrix4.hpp>
#include <atlas/graphics/Texture.hpp>
#include <atlas/graphics/Shader.hpp>
#include <atlas/render/RenderStats.hpp>

#include <memory>
#include <vector>
#include <cstddef>


namespace atlas
{

    struct TextureRegion 
    {
        float uMin = 0.0f;
        float vMin = 0.0f;
        float uMax = 1.0f;
        float vMax = 1.0f;
    };

    class SpriteBatch final
    {
    public:
        explicit SpriteBatch(const Texture& texture);
        ~SpriteBatch();

        SpriteBatch(const SpriteBatch&) = delete;
        SpriteBatch& operator=(const SpriteBatch&) = delete;

        void begin(const Matrix4& view, const Matrix4& projection);
        bool submit(const Matrix4& transform, const TextureRegion& region);
        void flush();
        void setStats(RenderStats* stats);
    private:
        const Texture& m_texture;
        RenderStats* m_stats = nullptr;

        unsigned int m_vao = 0;
        unsigned int m_vbo = 0;
        unsigned int m_ebo = 0;

        static constexpr std::size_t MaxSprites = 1000;
        static constexpr std::size_t VerticesPerSprite = 4;
        static constexpr std::size_t IndicesPerSprite = 6;
        static constexpr std::size_t FloatsPerVertex = 5;
        static constexpr std::size_t PositionComponents = 3;

        std::vector<float> m_vertices;
        std::vector<unsigned int> m_indices;

        std::unique_ptr<Shader> m_shader;

        Matrix4 m_view;
        Matrix4 m_projection;

        bool m_isDrawing = false;

        void initializeBuffers();
    };
}