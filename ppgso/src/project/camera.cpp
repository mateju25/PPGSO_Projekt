#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"
#include <glm/gtx/euler_angles.hpp>

Camera::Camera() {

    float fow = 90.0f, ratio = 1.0f, near = 0.0001f, far = 1000.0f;

    projectionMatrix = glm::perspective((ppgso::PI / 180.0f) * fow, ratio, near, far);

}

void  Camera::update() {
    viewMatrix = glm::lookAt(getTotalPosition(), position - back, up);
}


glm::vec3 Camera::getTotalPosition() const {
    return (position) + (distance * (rotation));
}

void Camera::moveTo(const glm::vec3 &pos, const glm::vec3 &rot) {
    positionOffset = {0, 4, -10};
    position = pos + positionOffset;
    rotation = {-std::sin(rot.z + offset.x), offset.y, -std::cos(rot.z + offset.z)};
}