#include <atlas/render/Mesh.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
namespace atlas
{
	Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) :
		m_vertices(vertices), m_indices(indices)
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

		glBufferData(
			GL_ARRAY_BUFFER,
			m_vertices.size() * sizeof(float),
			m_vertices.data(),
			GL_STATIC_DRAW
		);

		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			m_indices.size() * sizeof(unsigned int),
			m_indices.data(),
			GL_STATIC_DRAW
		);

		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			5 * sizeof(float),
			nullptr
		);

		glEnableVertexAttribArray(0);

		glVertexAttribPointer(
			1, 2, GL_FLOAT, GL_FALSE,
			5 * sizeof(float),
			reinterpret_cast<void*>(3 * sizeof(float))
		);

		glEnableVertexAttribArray(1);
	}

	Mesh::~Mesh()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
	}

	void Mesh::draw()
	{
		glBindVertexArray(m_VAO);
		glDrawElements(
			GL_TRIANGLES,
			static_cast<GLsizei>(m_indices.size()),
			GL_UNSIGNED_INT,
			0
		);
	}
}