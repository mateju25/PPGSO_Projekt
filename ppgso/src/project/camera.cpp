#include <glm/glm.hpp>

#include "camera.h"
#include <glm/gtx/euler_angles.hpp>

Camera::Camera() {

    float fow = 90.0f, ratio = 1.0f, near = 0.0001f, far = 1000.0f;

    projectionMatrix = glm::perspective((ppgso::PI / 180.0f) * fow, ratio, near, far);

    position = {50, 50, 50};
    rotation = {0, 0, 0};
    offset = {0, 10, 0};
}

void Camera::update() {

    glm::vec3 forward = {sin(rotation.z) * cos(rotation.y), cos(rotation.z) * cos(rotation.y), sin(rotation.y)};

    std::cout << "X: " << forward.x << " Y: " << forward.y << " Z: " << forward.z << std::endl;

    viewMatrix = lookAt(position, (position + offset) * forward, up);
}

void Camera::updateRotation(glm::vec2 mvector) {

    float sensitivity = 0.1;

    rotation.z += mvector.x * sensitivity;
    rotation.y += mvector.y * sensitivity;

    if (rotation.y > 0.6) {
        rotation.y = 0.6;
    }
    if (rotation.y < -0.6) {
        rotation.y = -0.6;
    }

}

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
