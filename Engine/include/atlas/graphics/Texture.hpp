#pragma once
#include <string>

namespace atlas
{
	class Texture
	{
	public:
		explicit Texture(const std::string& path);
		~Texture();

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		void bind() const;

		int width() const { return m_width; }
		int height() const { return m_height; }

	private:
		unsigned int m_id = 0;
		int m_width = 0;
		int m_height = 0;
		int m_channels = 0;
	};
}