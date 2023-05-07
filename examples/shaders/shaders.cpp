#include "window.h"
#include "imgui.h"
#include "config.h"
#include "shader.h"

// An array of 3 vectors which represents 3 vertices
static const float g_vertex_buffer_data[] = {
    // positions
     0.5f, -0.5f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f   // top 
};    

int main()
{
    // Create a window
    Window window("shaders", 800, 600, true);

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    // Create and compile our GLSL program from the shaders
    std::string vertPath = std::string(SOURCE_DIR) + "/shaders/shaders.vert";
    std::string fragPath = std::string(SOURCE_DIR) + "/shaders/shaders.frag";
    Shader shader(vertPath.c_str(), fragPath.c_str());

    static ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	window.run([&]{

        glBindVertexArray(VAO);
        shader.use();

        // update shader uniform
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Triangle Color", (float*)&color);
        ImGui::End();
        
        // update shader uniform
        int vertexColorLocation = glGetUniformLocation(shader.getProgramID(), "ourColor");
        glUniform4f(vertexColorLocation, color.x, color.y, color.z, color.w);

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    });

    // Cleanup VBO and shader
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

	return 0;
}