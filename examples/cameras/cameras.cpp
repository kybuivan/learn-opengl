#include "window.h"
#include "imgui.h"
#include "config.h"
#include "shader.h"
#include "texture.h"
#include "utils.h"
#include "camera.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// An array of 3 vectors which represents 3 vertices
float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

// world space positions of our cubes
glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

int main()
{
    // Create a window
    Window window("camera", SCR_WIDTH, SCR_HEIGHT, true);

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

    // Set callbacks
	window.set_key_callback([&](int key, int action) noexcept {
        if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) {
            window.set_should_close();
        }

        if (key == GLFW_KEY_W) {
            camera.processKeyboard(FORWARD, deltaTime);
        }

        if (key == GLFW_KEY_S) {
            camera.processKeyboard(BACKWARD, deltaTime);
        }

        if (key == GLFW_KEY_A) {
            camera.processKeyboard(LEFT, deltaTime);
        }

        if (key == GLFW_KEY_D) {
            camera.processKeyboard(RIGHT, deltaTime);
        }
    });

    window.set_scroll_callback([&](double xpos, double ypos) noexcept {
        camera.processMouseScroll(ypos);
    });

    window.set_mouse_callback([&](double xpos, double ypos) noexcept {
        static bool firstMouse = true;
        static double lastX = 0.0, lastY = 0.0;

        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        double xoffset = xpos - lastX;
        double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera.processMouseMovement(xoffset, yoffset);
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

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    // Create and compile our GLSL program from the shaders
    std::string vertPath = std::string(SOURCE_DIR) + "/coordinate_systems/coordinate_systems.vert";
    std::string fragPath = std::string(SOURCE_DIR) + "/coordinate_systems/coordinate_systems.frag";
    Shader shader(vertPath.c_str(), fragPath.c_str());

    // load and create a texture
    std::string texturePath = std::string(SOURCE_DIR) + "/data/container.jpg";
    Texture texture(texturePath.c_str());

    int width = SCR_WIDTH;
    int height = SCR_HEIGHT;
    // Create a texture to hold the captured image
    // Generate an OpenGL texture from the image data.
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    window.run([&]{
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        ImGui::Begin("Settings");
        glm::vec3 m_position = camera.getPosition();
        ImGui::SliderFloat3("Position", &m_position[0], -10.0f, 10.0f);
        camera.setPosition(m_position);
        glm::vec3 m_front = camera.getFront();
        ImGui::SliderFloat3("Front", &m_front[0], -10.0f, 10.0f);
        camera.setFront(m_front);
        glm::vec3 m_up = camera.getUp();
        ImGui::SliderFloat3("Up", &m_up[0], -10.0f, 10.0f);
        camera.setUp(m_up);
        glm::vec3 m_right = camera.getRight();
        ImGui::SliderFloat3("Right", &m_right[0], -10.0f, 10.0f);
        camera.setRight(m_right);

        float m_yaw = camera.getYaw();
        ImGui::SliderFloat("Yaw", &m_yaw, -100.0f, 100.0f);
        camera.setYaw(m_yaw);
        float m_pitch = camera.getPitch();
        ImGui::SliderFloat("Pitch", &m_pitch, -100.0f, 100.0f);
        camera.setPitch(m_pitch);

        float m_movementSpeed = camera.getMovementSpeed();
        ImGui::SliderFloat("Movement Speed", &m_movementSpeed, 0.0f, 100.0f);
        camera.setMovementSpeed(m_movementSpeed);
        float m_mouseSensitivity = camera.getMouseSensitivity();
        ImGui::SliderFloat("Mouse Sensitivity", &m_mouseSensitivity, 0.0f, 100.0f);
        camera.setMouseSensitivity(m_mouseSensitivity);
        float m_zoom = camera.getZoom();
        ImGui::SliderFloat("Zoom", &m_zoom, 0.0f, 100.0f);
        camera.setZoom(m_zoom);
        ImGui::End();

        texture.bind();
        shader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.getViewMatrix();
        shader.setMat4("view", view);

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        // Allocate a byte array to hold the image data.
        int imageSize = width * height * 3; // Assuming 3 color channels (RGB)
        unsigned char* imageBytes = new unsigned char[imageSize];

        // Read the image bytes from the OpenGL framebuffer.
        glBindTexture(GL_TEXTURE_2D, textureID);
        glPixelStorei(GL_PACK_ALIGNMENT, 1);

        glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageBytes);

        // Flip the image vertically
        for (int y = 0; y < height / 2; ++y) {
            int swapY = height - 1 - y;
            for (int x = 0; x < width; ++x) {
                std::swap(imageBytes[(y * width + x) * 3], imageBytes[(swapY * width + x) * 3]);
                std::swap(imageBytes[(y * width + x) * 3 + 1], imageBytes[(swapY * width + x) * 3 + 1]);
                std::swap(imageBytes[(y * width + x) * 3 + 2], imageBytes[(swapY * width + x) * 3 + 2]);
            }
        }

        // update the textureId with the image data
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageBytes);
        glPixelStorei(GL_PACK_ROW_LENGTH, -width); // Flip the texture vertically

        ImGui::Begin("My Window");
        ImGui::Image((void*)(intptr_t)textureID, ImVec2(width, height));
        ImGui::End();
        delete[] imageBytes;
    });

    // Cleanup VBO and shader
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &textureID);

	return 0;
}