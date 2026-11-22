#pragma once

#include <vector>

namespace atlas
{
	class Mesh
	{
	public:
		Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
		~Mesh();

		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;
		void draw();
	private:
		unsigned int m_VAO = 0;
		unsigned int m_VBO = 0;
		unsigned int m_EBO = 0;
		std::vector<float> m_vertices;
		std::vector<unsigned int> m_indices;
	};
}
