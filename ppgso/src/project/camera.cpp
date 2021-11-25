#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"
#include <glm/gtx/euler_angles.hpp>

Camera::Camera() {

    float fow = 90.0f, ratio = 1.0f, near = 0.0001f, far = 1000.0f;

    projectionMatrix = glm::perspective((ppgso::PI / 180.0f) * fow, ratio, near, far);

    position = positionOffset = {0, distanceY, -distanceZ};
}

void  Camera::update() {
    glm::vec3 lookAtOff = {0,5,0};
    viewMatrix = glm::lookAt(position/*getTotalPosition()*/, submarinePos + lookAtOff, up);
}


glm::vec3 Camera::getTotalPosition() const {
    return (position) + (distanceY * (rotation));
}

void Camera::moveTo(const glm::vec3 &pos, const glm::vec3 &rot) {
    auto deltaPos = submarinePos - pos;
    submarinePos = pos;

    glm::vec3 deltaRot;
    deltaRot.x = (distanceZ * -sin(rotation.y * -1)) - (distanceZ * -sin(rot.y * -1));
    deltaRot.z = (distanceZ * -cos(rotation.y * -1)) - (distanceZ * -cos(rot.y * -1));
    deltaRot.y = (distanceY * cos(rotation.y) * sin(rotation.x) + positionOffset.y) -
                 (distanceY * cos(rot.y) * sin(rot.x) + positionOffset.y);

    rotation = rot;

    position -= deltaRot;
    position -= deltaPos;
}