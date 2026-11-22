#pragma once

#include <atlas/math/Matrix4.hpp>	
#include <atlas/math/Vec2.hpp>

namespace atlas
{
	class Camera2D
	{
	public:
		Camera2D(float viewportWidth, float viewportHeight);

		Vec2& position();
		const Vec2& position() const;

		Matrix4 viewMatrix() const;
		Matrix4 projectionMatrix() const;

		void setViewportSize(float width, float height);
	private:
		Vec2 m_position;
		float m_viewportWidth;
		float m_viewportHeight;
		float m_worldHeight = 2.0f;
	};
}