#ifndef _SHADER_H_
#define _SHADER_H_

#include <iostream>
#include <string>
#include <fstream>

#include <glad/gl.h>

class Shader
{
public:
    Shader(const char* vertPath, const char* fragPath);
    ~Shader();

    void use() const;

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    GLuint getProgramID() const { return m_programID; }
private:
    GLuint m_programID;

    const char* readFile(const char *filePath) const;
    GLuint setupShader(const char* vertPath, const char* fragPath) const;
};

#endif // _SHADER_H_