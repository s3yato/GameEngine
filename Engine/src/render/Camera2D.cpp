#include <atlas/render/Camera2D.hpp>

namespace atlas
{
	Camera2D::Camera2D(float viewportWidth, float viewportHeight)
		: m_viewportWidth(viewportWidth),
		m_viewportHeight(viewportHeight)
	{

	}

	Vec2& Camera2D::position()
	{
		return m_position;
	}

	const Vec2& Camera2D::position() const 
	{
		return m_position;
	}

	Matrix4 Camera2D::viewMatrix() const
	{
		return Matrix4::translation(
			-m_position.x(),
			-m_position.y(),
			0.0f
		);
	}

	Matrix4 Camera2D::projectionMatrix() const
	{
		const float aspect = m_viewportWidth / m_viewportHeight;
		const float halfHeight = m_worldHeight * 0.5f;
		const float halfWidth = halfHeight * aspect;

		return Matrix4::orthographic(
			-halfWidth,
			halfWidth,
			-halfHeight,
			halfHeight,
			-1.0f,
			1.0f
		);
	}

	void Camera2D::setViewportSize(float width, float height)
	{
		if (width <= 0.0f || height <= 0.0f)
		{
			return;
		}

		m_viewportWidth = width;
		m_viewportHeight = height;
	}
}