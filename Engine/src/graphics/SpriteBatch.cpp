#include <atlas/graphics/SpriteBatch.hpp>

#include <glad/glad.h>
#include <string>
#include <cstdint>

namespace atlas
{
	SpriteBatch::SpriteBatch(const Texture& texture)
		: m_texture(texture),
		m_shader(std::make_unique<Shader>(
			std::string(ATLAS_SHADER_DIR) + "/sprite_batch.vert",
			std::string(ATLAS_SHADER_DIR) + "/basic.frag"
		))
	{
        m_vertices.reserve(
            MaxSprites * VerticesPerSprite * FloatsPerVertex
        );

        m_indices.reserve(
            MaxSprites * IndicesPerSprite
        );

		initializeBuffers();
	}
    void SpriteBatch::initializeBuffers()
    {

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(
            GL_ARRAY_BUFFER,
            MaxSprites * VerticesPerSprite * FloatsPerVertex * sizeof(float),
            nullptr,
            GL_DYNAMIC_DRAW
        );

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            MaxSprites * IndicesPerSprite * sizeof(unsigned int),
            nullptr,
            GL_DYNAMIC_DRAW
        );

        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            static_cast<GLsizei>(FloatsPerVertex * sizeof(float)),
            nullptr
        );
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(
            1,
            2,
            GL_FLOAT,
            GL_FALSE,
            static_cast<GLsizei>(FloatsPerVertex * sizeof(float)),
            reinterpret_cast<void*>(PositionComponents * sizeof(float))
        );
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    SpriteBatch::~SpriteBatch()
    {
        if (m_ebo != 0)
            glDeleteBuffers(1, &m_ebo);

        if (m_vbo != 0)
            glDeleteBuffers(1, &m_vbo);

        if (m_vao != 0)
            glDeleteVertexArrays(1, &m_vao);
    }

    void SpriteBatch::begin(
        const Matrix4& view,
        const Matrix4& projection
    )
    {
        if (m_isDrawing)
            return;

        m_vertices.clear();
        m_indices.clear();

        m_view = view;
        m_projection = projection;
        m_isDrawing = true;
    }

    bool SpriteBatch::submit(const Matrix4& transform, const TextureRegion& region)
    {
        if (!m_isDrawing)
            return false;

        const std::size_t spriteCount =
            m_indices.size() / IndicesPerSprite;

        if (spriteCount >= MaxSprites)
        {
            flush();
            begin(m_view, m_projection);
        }

        const unsigned int baseIndex =
            static_cast<unsigned int>(
                m_vertices.size() / FloatsPerVertex
                );

        const float vertices[] = {
            -0.5f, -0.5f, 0.0f, region.uMin, region.vMin,
             0.5f, -0.5f, 0.0f, region.uMax, region.vMin,
             0.5f,  0.5f, 0.0f, region.uMax, region.vMax,
            -0.5f,  0.5f, 0.0f, region.uMin, region.vMax
        };

        for (std::size_t i = 0; i < VerticesPerSprite; ++i)
        {
            const std::size_t offset = i * FloatsPerVertex;

            const float x = vertices[offset];
            const float y = vertices[offset + 1];
            const float z = vertices[offset + 2];

            const float transformedX =
                transform.at(0, 0) * x +
                transform.at(0, 1) * y +
                transform.at(0, 2) * z +
                transform.at(0, 3);

            const float transformedY =
                transform.at(1, 0) * x +
                transform.at(1, 1) * y +
                transform.at(1, 2) * z +
                transform.at(1, 3);

            const float transformedZ =
                transform.at(2, 0) * x +
                transform.at(2, 1) * y +
                transform.at(2, 2) * z +
                transform.at(2, 3);

            m_vertices.push_back(transformedX);
            m_vertices.push_back(transformedY);
            m_vertices.push_back(transformedZ);
            m_vertices.push_back(vertices[offset + 3]);
            m_vertices.push_back(vertices[offset + 4]); 
        }
        const unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
        };

        for (unsigned int index : indices)
            m_indices.push_back(baseIndex + index);

        return true;
    }

	void SpriteBatch::flush()
	{
        if (!m_isDrawing)
            return;

        m_isDrawing = false;

        if (m_vertices.empty() || m_indices.empty())
        {
            m_vertices.clear();
            m_indices.clear();
            return;
        }
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferSubData(
			GL_ARRAY_BUFFER,
			0,
			m_vertices.size() * sizeof(float),
			m_vertices.data()
		);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferSubData(
			GL_ELEMENT_ARRAY_BUFFER,
			0,
			m_indices.size() * sizeof(unsigned int),
			m_indices.data()
		);
        m_shader->use();
        m_shader->setMat4("view", m_view);
        m_shader->setMat4("projection", m_projection);

		m_texture.bind();

		glDrawElements(
			GL_TRIANGLES,
			static_cast<GLsizei>(m_indices.size()),
			GL_UNSIGNED_INT,
			nullptr
		);

        if (m_stats != nullptr)
        {
            ++m_stats->drawCalls;
            m_stats->sprites += static_cast<std::uint32_t>(
                m_indices.size() / IndicesPerSprite
            );
            m_stats->triangles += static_cast<std::uint32_t>(
                m_indices.size() / 3
            );
        }

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

        m_vertices.clear();
        m_indices.clear();
	}

    void SpriteBatch::setStats(RenderStats* stats)
    {
        m_stats = stats;
    }
}
