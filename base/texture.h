#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <glad/gl.h>

class Texture
{
public:
    Texture(const char* path);
    ~Texture();

    void bind() const;
    void unbind() const;

    GLuint getTextureID() const { return m_textureID; }
private:
    GLuint m_textureID;
};

#endif // _TEXTURE_H_
