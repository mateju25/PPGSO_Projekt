#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"
#include <glm/gtx/euler_angles.hpp>

Camera::Camera() {

    float fow = 90.0f, ratio = 1.0f, near = 0.0001f, far = 1000.0f;

    projectionMatrix = glm::perspective((ppgso::PI / 180.0f) * fow, ratio, near, far);

    position = glm::vec3(50.0f, 50.0f, 50.0f);
    target = glm::vec3(50.0f, 40.0f, 50.0f);

    yaw = -90;
    pitch = 0;
}

void  Camera::update() {
    direction = glm::normalize(position - target);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraRight = glm::normalize(glm::cross(up, direction));
    cameraUp = glm::cross(direction, cameraRight);

    viewMatrix = glm::lookAt(position, position + cameraFront, cameraUp);
}

void  Camera::calculateCameraFront() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void Camera::mouseUpdate(glm::vec2 mvector) {

    const float sensitivity = 0.05f;

//    yaw += mvector[0] * sensitivity;
    pitch +=  mvector[1] * sensitivity;


    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    calculateCameraFront();
}

void Camera::moveForward() {
    position += MOV_SPEED * cameraFront;
}

void Camera::moveBackward() {
    position -= MOV_SPEED * cameraFront;
}

void Camera::strafeLeft() {
    yaw -=  1;
    calculateCameraFront();
//    position -= glm::normalize(glm::cross(cameraFront, cameraUp)) * MOV_SPEED;
}

void Camera::strafeRight() {
    yaw +=  1;
    calculateCameraFront();
//    position += glm::normalize(glm::cross(cameraFront, cameraUp)) * MOV_SPEED;
}