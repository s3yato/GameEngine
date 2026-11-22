#include <atlas/render/Material.hpp>

namespace atlas
{
	std::array<float, 4> Material::getColor() const {
		return std::array<float, 4>{
			m_r, m_g, m_b, m_a
		};
	}

	void Material::changeColor(float r, float g, float b, float a) {
		m_r = r;
		m_g = g;
		m_b = b;
		m_a = a;
	}
}