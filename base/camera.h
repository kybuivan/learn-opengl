#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/gl.h>

const float SPEED = 10.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = -90.0f,
           float pitch = 0.0f);

    glm::mat4 getViewMatrix() const;
    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);
    void processMouseScroll(float yOffset);

    glm::vec3 getPosition() const { return m_position; }
    glm::vec3 getFront() const { return m_front; }
    glm::vec3 getUp() const { return m_up; }
    glm::vec3 getRight() const { return m_right; }
    float getYaw() const { return m_yaw; }
    float getPitch() const { return m_pitch; }
    float getMovementSpeed() const { return m_movementSpeed; }
    float getMouseSensitivity() const { return m_mouseSensitivity; }
    float getZoom() const { return m_zoom; }

    void setPosition(glm::vec3 position) { m_position = position; }
    void setFront(glm::vec3 front) { m_front = front; }
    void setUp(glm::vec3 up) { m_up = up; }
    void setRight(glm::vec3 right) { m_right = right; }
    void setYaw(float yaw) { m_yaw = yaw; }
    void setPitch(float pitch) { m_pitch = pitch; }
    void setMovementSpeed(float movementSpeed) { m_movementSpeed = movementSpeed; }
    void setMouseSensitivity(float mouseSensitivity) { m_mouseSensitivity = mouseSensitivity; }
    void setZoom(float zoom) { m_zoom = zoom; }
    
private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;

    float m_yaw;
    float m_pitch;

    float m_movementSpeed;
    float m_mouseSensitivity;
    float m_zoom;

    void updateCameraVectors();
};

#endif // _CAMERA_H_
