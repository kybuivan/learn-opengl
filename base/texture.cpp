#include "texture.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stb_image.h>

Texture::Texture(const char *path, const std::string &type)
{
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // Set the texture wrapping/filtering options (on the currently bound texture object)
    // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    // Set texture filtering to nearest neighbor interpolation
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    // Set texture filtering to nearest neighbor interpolation
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;
        // Set the Correct Channel Format
        switch (nrChannels)
        {
            case 1 : format = GL_ALPHA;     break;
            case 2 : format = GL_LUMINANCE16_EXT; break;
            case 3 : format = GL_RGB;       break;
            case 4 : format = GL_RGBA;      break;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        m_width = width;
        m_height = height;
    }
    else
    {
        std::cerr << "Failed to load texture" << std::endl;
    }

    m_type = type;
    m_path = path;
    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_textureID);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
