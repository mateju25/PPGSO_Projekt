#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <ppgso/ppgso.h>

/*!
 * Simple camera object that keeps track of viewMatrix and projectionMatrix
 * the projectionMatrix is by default constructed as perspective projection
 * the viewMatrix is generated from up, position and back vectors on update
 */
class Camera {
public:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 direction;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    float yaw;
    float pitch;


    const float MOV_SPEED = 0.9f;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    /*!
     * Create new Camera that will generate viewMatrix and projectionMatrix based on its position, up and back vectors
     * @param fow - Field of view in degrees
     * @param ratio - Viewport screen ratio (usually width/height of the render window)
     * @param near - Distance to the near frustum plane
     * @param far - Distance to the far frustum plane
     */
    Camera();

    /*!
     * Update Camera viewMatrix based on up, position and back vectors
     */
    void update();
    void mouseUpdate(glm::vec2 mvector);

    void moveForward();
    void moveBackward();
    void strafeLeft();
    void strafeRight();
private:
    void calculateCameraFront();
};

