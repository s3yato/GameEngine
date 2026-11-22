#include <atlas/graphics/Texture.hpp>
#include <stb_image.h>
#include <stdexcept>
#include <glad/glad.h>

#include <iostream>
#include <filesystem>

namespace atlas
{
    Texture::Texture(const std::string& path)
    {

        if (glGetString(GL_VERSION) == nullptr)
        {
            throw std::runtime_error(
                "OpenGL context is not active while creating Texture"
            );
        }
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(
            path.c_str(),
            &m_width,
            &m_height,
            &m_channels,
            STBI_rgb_alpha
        );

        if (!data)
        {
            throw std::runtime_error(
                "Failed to load texture: " + path
            );
        }

        glGenTextures(1, &m_id);

        if (m_id == 0)
        {
            stbi_image_free(data);
            throw std::runtime_error("Failed to create OpenGL texture");
        }
        glBindTexture(GL_TEXTURE_2D, m_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            m_width,
            m_height,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            data
        );

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    Texture::~Texture() = default;

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}
}