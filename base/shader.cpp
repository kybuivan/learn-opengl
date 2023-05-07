#include "shader.h"

Shader::Shader(const char* vertPath, const char* fragPath)
{
    m_programID = setupShader(vertPath, fragPath);
}

Shader::~Shader()
{
    glDeleteProgram(m_programID);
}

void Shader::use() const
{
    glUseProgram(m_programID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_programID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
}

const char* Shader::readFile(const char *filePath) const
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content.c_str();
}

GLuint Shader::setupShader(const char* vertPath, const char* fragPath) const
{
    // Create and compile our GLSL program from the shaders
    // Vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Give GLSL the source code of vertexShader
    auto vertexShaderSource = readFile(vertPath);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    // Compile the vertex shader
    glCompileShader(vertexShader);

    // Fragment shaders
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Give GLSL the source code of fragmentShader
    auto fragmentShaderSource = readFile(fragPath);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    // Compile the fragment shader
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    GLuint shaderProgramID = glCreateProgram();
    // Attach our shaders to our program
    glAttachShader(shaderProgramID, vertexShader);
    glAttachShader(shaderProgramID, fragmentShader);
    // Link the program
    glLinkProgram(shaderProgramID);

    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Use our shader
    return shaderProgramID;
}