#include <atlas/math/Matrix4.hpp>
#include <numbers>

namespace atlas
{
	Matrix4::Matrix4()
	{
		m_data.fill(0.0f);
	}

	float& Matrix4::at(std::size_t row, std::size_t col)
	{
		return m_data[col * 4 + row];
	}

	float Matrix4::at(std::size_t row, std::size_t col) const
	{
		return m_data[col * 4 + row];
	}

	Matrix4 Matrix4::operator*(const Matrix4& other) const
	{
		Matrix4 result;
		for (std::size_t row = 0; row < 4; ++row)
		{
			for (std::size_t col = 0; col < 4; ++col)
			{
				result.at(row, col) = 0.0f;
				for (std::size_t k = 0; k < 4; ++k)
				{
					result.at(row, col) += this->at(row, k) * other.at(k, col);
				}
			}
		}
		return result;
	}

	Matrix4 Matrix4::identity()
	{
		Matrix4 result;
		result.at(0, 0) = 1.0f;
		result.at(1, 1) = 1.0f;
		result.at(2, 2) = 1.0f;
		result.at(3, 3) = 1.0f;

		return result;
	}

	Matrix4 Matrix4::scale(float x, float y, float z)
	{
		Matrix4 matrix = Matrix4::identity();

		matrix.at(0, 0) = x;
		matrix.at(1, 1) = y;
		matrix.at(2, 2) = z;

		return matrix;
	}

	Matrix4 Matrix4::translation(float x, float y, float z)
	{
		Matrix4 matrix = identity();
		matrix.at(0, 3) = x;
		matrix.at(1, 3) = y;
		matrix.at(2, 3) = z;
		return matrix;
	}
	Matrix4 Matrix4::rotationX(float angle)
	{
		float a = angle * (std::numbers::pi_v<float> / 180.0f);

		Matrix4 matrix = identity();

		matrix.at(1, 1) = std::cos(a);
		matrix.at(1, 2) = -std::sin(a);
		matrix.at(2, 1) = std::sin(a);
		matrix.at(2, 2) = std::cos(a);

		return matrix;
	}

	Matrix4 Matrix4::rotationY(float angle)
	{
		float a = angle * (std::numbers::pi_v<float> / 180.0f);

		Matrix4 matrix = identity();

		matrix.at(0, 0) = std::cos(a);
		matrix.at(0, 2) = std::sin(a);
		matrix.at(2, 0) = -std::sin(a);
		matrix.at(2, 2) = std::cos(a);

		return matrix;
	}

	Matrix4 Matrix4::rotationZ(float angle)
	{
		float a = angle * (std::numbers::pi_v<float> / 180.0f);

		Matrix4 matrix = identity();

		matrix.at(0, 0) = std::cos(a);
		matrix.at(0, 1) = -std::sin(a);
		matrix.at(1, 0) = std::sin(a);
		matrix.at(1, 1) = std::cos(a);

		return matrix;
	}
	Matrix4 Matrix4::perspective(float fov, float aspect, float near, float far)
	{
		float f = 1.0f / std::tan(fov * 0.5f * (std::numbers::pi_v<float> / 180.0f));
		Matrix4 matrix;
		matrix.at(0, 0) = f / aspect;
		matrix.at(1, 1) = f;
		matrix.at(2, 2) = (far + near) / (near - far);
		matrix.at(2, 3) = (2.0f * far * near) / (near - far);
		matrix.at(3, 2) = -1.0f;
		return matrix;
	}

	Matrix4 Matrix4::orthographic(
		float left,
		float right,
		float bottom,
		float top,
		float near,
		float far
	) {
		Matrix4 matrix = Matrix4::identity();

		matrix.at(0, 0) = 2.0f / (right - left);
		matrix.at(1, 1) = 2.0f / (top - bottom);
		matrix.at(2, 2) = -2.0f / (far - near);

		matrix.at(0, 3) = -(right + left) / (right - left);
		matrix.at(1, 3) = -(top + bottom) / (top - bottom);
		matrix.at(2, 3) = -(far + near) / (far - near);

		return matrix;
	}
}