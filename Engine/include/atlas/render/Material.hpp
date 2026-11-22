#pragma once

#include <array>
namespace atlas
{
	class Material
	{
	public:
		Material(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {};

		std::array<float, 4> getColor() const;
		void changeColor(float r, float g, float b, float a);
	private:
		float m_r;
		float m_g;
		float m_b;
		float m_a;
	};
}