#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <glad/gl.h>
#include <string>

class Texture
{
public:
    Texture(const char *path, const std::string &type = "");
    ~Texture();

    void bind() const;
    void unbind() const;
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    GLuint getTextureID() const { return m_textureID; }

    std::string getType() const { return m_type; }
    std::string getPath() const { return m_path; }
private:
    GLuint m_textureID;
    int m_width = 0;
    int m_height = 0;
    std::string m_type = "";
    std::string m_path = "";
};

#endif // _TEXTURE_H_
