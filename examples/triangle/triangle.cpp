#include "window.h"

// Vertex shader
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// Fragment shader
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};

int main()
{
    // Create a window
    Window window("triangle", 1080, 720, true);

    // Set callbacks
	window.set_key_callback([&](int key, int action) noexcept {
        if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
            window.set_should_close();
        }
    });

    // Create Vertex Array Object
    GLuint vertexArrayID;
    // Generate 1 vertex array and put the resulting identifier in vertexArrayID
    glGenVertexArrays(1, &vertexArrayID);
    // Bind our Vertex Array ID first, then bind and set our buffers and pointers.
    glBindVertexArray(vertexArrayID);

    // This will identify our vertex buffer
    GLuint vertexBuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexBuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Create and compile our GLSL program from the shaders
    // Vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Give GLSL the source code of vertexShader
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    // Compile the vertex shader
    glCompileShader(vertexShader);

    // Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Give GLSL the source code of fragmentShader
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
    glUseProgram(shaderProgramID);

	window.run([&]{
        glBindVertexArray(vertexArrayID);

        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        // Bind our vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        // Give our vertices to OpenGL.
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        // No need to unbind at all as we directly bind a different VAO the next few lines
        glDisableVertexAttribArray(0);
    });

    // Cleanup VBO and shader
    glDeleteProgram(shaderProgramID);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vertexArrayID);

	return 0;
}