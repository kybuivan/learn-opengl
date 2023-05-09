#include "window.h"
#include "imgui.h"
#include "config.h"
#include "shader.h"
#include "texture.h"
#include "utils.h"
#include "camera.h"
#include "model.h"
#include <stb_image.h>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // Create a window
    Window window("models", SCR_WIDTH, SCR_HEIGHT, true);

    Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    // Create and compile our GLSL program from the shaders
    std::string vertPath = std::string(SOURCE_DIR) + "/models/models.vert";
    std::string fragPath = std::string(SOURCE_DIR) + "/models/models.frag";
    Shader shader(vertPath.c_str(), fragPath.c_str());

    // load models
    // -----------
    std::string path = std::string(SOURCE_DIR) + "/data/cyborg/cyborg.obj";
    Model ourModel(path);
    
    window.run([&]{
        shader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.getZoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        shader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.getViewMatrix();
        shader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // it's a bit too big for our scene, so scale it down
        shader.setMat4("model", model);
        ourModel.Draw(shader);

    });

    return 0;
}