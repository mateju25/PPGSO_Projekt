#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"
#include <glm/gtx/euler_angles.hpp>

Camera::Camera() {

    float fow = 90.0f, ratio = 1.0f, near = 0.0001f, far = 1000.0f;


    projectionMatrix = glm::perspective((ppgso::PI / 180.0f) * fow, ratio, near, far);

    position = {50, 50, 50};
    rotation = {0, 0, 0};
    offset = {0, 10, 0};
}

void Camera::mouseUpdate(glm::vec2 &newMousePosition) {
    glm::vec2 mousedelta = newMousePosition - oldMousePosition;
    if (glm::length(mousedelta) > 50.0) {
        oldMousePosition = newMousePosition;
        return;
    }


    glm::vec3 toRotateAround = glm::cross(viewDirection, up);
    glm::mat4 rotator = glm::rotate(-mousedelta.x * ROTATIONAL_SPEED, up) *
                        rotate(viewDirection, -mousedelta.y * ROTATIONAL_SPEED, toRotateAround);


    viewDirection = glm::mat3(rotator) * viewDirection;

    oldMousePosition = newMousePosition;

    viewMatrix =  glm::lookAt(position, position + viewDirection, up);
}

//void Camera::update() {
//
//    glm::vec3 forward = { sin(rotation.z)*cos(rotation.y), cos(rotation.z)*cos(rotation.y),sin(rotation.y)};
//
////    std::cout << "X: " << forward.x << " Y: " << forward.y << " Z: " << forward.z << std::endl;
//
//    viewMatrix = lookAt(position, (position + offset) * forward, up);
//}

void Camera::moveForward() {
    position += MOV_SPEED * viewDirection;
}

void Camera::moveBackward() {
    position += -MOV_SPEED * viewDirection;
}

void Camera::strafeLeft() {
    glm::vec3 strafeDirection = glm::cross(viewDirection, up);
    position += -MOV_SPEED * strafeDirection;
}

void Camera::strafeRight() {
    glm::vec3 strafeDirection = glm::cross(viewDirection, up);
    position += MOV_SPEED * strafeDirection;
}

void Camera::moveUp() {
    position += MOV_SPEED * up;
}

void Camera::moveDown() {
    position += -MOV_SPEED * up;
}

//void Camera::updateRotation(glm::vec2 mvector) {
//
//    float sensitivity = 0.1;
//
//    rotation.z += mvector.x * sensitivity;
//    rotation.y += mvector.y * sensitivity;
//
//    if (rotation.y > 0.6) {
//        rotation.y = 0.6;
//    }
//    if (rotation.y < -0.6) {
//        rotation.y = -0.6;
//    }
//}

glm::vec3 Camera::cast(double u, double v) {
    // Create point in Screen coordinates
    glm::vec4 screenPosition{u, v, 0.0f, 1.0f};

    // Use inverse matrices to get the point in world coordinates
    auto invProjection = glm::inverse(projectionMatrix);
    auto invView = glm::inverse(viewMatrix);

    // Compute position on the camera plane
    auto planePosition = invView * invProjection * screenPosition;
    planePosition /= planePosition.w;

    // Create direction vector
    auto direction = glm::normalize(planePosition - glm::vec4{position, 1.0f});
    return glm::vec3{direction};
}
