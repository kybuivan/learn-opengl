#include "window.h"
#include "imgui.h"
#include "config.h"
#include "shader.h"
#include "texture.h"

// An array of 3 vectors which represents 3 vertices
float vertices[] = {
// set up vertex data (and buffer(s)) and configure vertex attributes
// positions             // colors          // texture coords
     0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f  // top left 
};

unsigned int indices[] = {  
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};  

int main()
{
    // Create a window
    Window window("textures", 800, 600, true);

    // Set callbacks
	window.set_key_callback([&](int key, int action) noexcept {
        if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
            window.set_should_close();
        }
    });

    // Create Vertex Array Object
    GLuint VAO;
    // Generate 1 vertex array and put the resulting identifier in VAO
    glGenVertexArrays(1, &VAO);
    // Bind our Vertex Array ID first, then bind and set our buffers and pointers.
    glBindVertexArray(VAO);

    // This will identify our vertex buffer
    GLuint VBO;
    // Generate 1 buffer, put the resulting identifier in VBO
    glGenBuffers(1, &VBO);
    // The following commands will talk about our 'VBO' buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // This will identify our element buffer
    GLuint EBO;
    // Generate 1 buffer, put the resulting identifier in EBO
    glGenBuffers(1, &EBO);
    // The following commands will talk about our 'EBO' buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Give our vertices to OpenGL.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Create and compile our GLSL program from the shaders
    std::string vertPath = std::string(SOURCE_DIR) + "/textures/textures.vert";
    std::string fragPath = std::string(SOURCE_DIR) + "/textures/textures.frag";
    Shader shader(vertPath.c_str(), fragPath.c_str());

    // load and create a texture
    std::string texturePath = std::string(SOURCE_DIR) + "/data/container.jpg";
    Texture texture(texturePath.c_str());

	window.run([&]{
        texture.bind();
        glBindVertexArray(VAO);
        shader.use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    });

    // Cleanup VBO and shader
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

	return 0;
}