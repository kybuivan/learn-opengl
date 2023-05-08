#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <glad/gl.h>

class Texture
{
public:
    Texture(const char *path);
    ~Texture();

    void bind() const;
    void unbind() const;
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    GLuint getTextureID() const { return m_textureID; }

private:
    GLuint m_textureID;
    int m_width;
    int m_height;
};

#endif // _TEXTURE_H_
