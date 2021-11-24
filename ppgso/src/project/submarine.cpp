//
// Created by Matej on 14. 11. 2021.
//

#include "submarine.h"
#include <glm/gtc/random.hpp>

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Submarine::mesh;
std::unique_ptr<ppgso::Texture> Submarine::texture;
std::unique_ptr<ppgso::Shader> Submarine::shader;

Submarine::Submarine() {
    // Set random scale speed and rotation
    position = {50, 10, 10};
    rotation = {BASIC_ROTATION_X, 0, 0};
    scale = {3, 3, 3};

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("projekt/submarine.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("projekt/Sub.obj");
}

bool Submarine::update(Scene &scene, float dt) {
    if (scene.keyboard[GLFW_KEY_LEFT]) {
        rotation.y += 0.05;
        if (rotation.y >= 6.25)
            rotation.y -= 6.25;
    }
    else if (scene.keyboard[GLFW_KEY_RIGHT]) {
        rotation.y -= 0.05;
        if (rotation.y <= -6.25)
            rotation.y += 6.25;
    }
    else if (scene.keyboard[GLFW_KEY_DOWN]) {
        rotation.x -= 0.05;
        if (rotation.x <= -6.25)
            rotation.x += 6.25;

    }
    else if (scene.keyboard[GLFW_KEY_UP]) {
        rotation.x += 0.05;
        if (rotation.x >= 6.25)
            rotation.x -= 6.25;

    }
    else if (scene.keyboard[GLFW_KEY_SPACE]) {
//        position.x += 0.5f  * -(std::sin(rotation.y));
//        if (rotation.y > 1.5)
//            position.z += 0.5f  * -(std::sin(rotation.y));
//        else
//            position.z += 0.5f  * (std::sin(rotation.y));
//        position.y += 0.5f  * -std::sin(rotation.x - BASIC_ROTATION_X);

        position.y += rotation.x - BASIC_ROTATION_X;
        position.x += rotation.y;
        position.z += rotation.z;
//        position.x = cos(rotation.y) * cos(rotation.x - BASIC_ROTATION_X);
//        position.y = sin(rotation.x - BASIC_ROTATION_X);
//        position.z = sin(rotation.y) * cos(rotation.x - BASIC_ROTATION_X);

        std::cout << position.x << " " << position.y << " "<< position.z << std::endl;
        std::cout << "ROTATION" << std::endl;
        std::cout << rotation.x - BASIC_ROTATION_X << " " << rotation.y << " "<< rotation.z << std::endl;
        std::cout << "" << std::endl;

    }
    else if (scene.keyboard[GLFW_KEY_LEFT_SHIFT]) {
        position.x -= 0.5f  * -(std::sin(rotation.y));
        position.y -= 0.5f  * -std::sin(rotation.x - BASIC_ROTATION_X);
        position.z -= 0.5f;
        std::cout << position.x << " " << position.y << " "<< position.z << std::endl;

    }

    scene.setTargetPosition(position, rotation);

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void Submarine::rotateRight() {

}

void Submarine::rotateLeft() {
}

void Submarine::rotateDown() {

}

void Submarine::rotateUp() {
}

void Submarine::moveForward() {

}

void Submarine::moveBackward() {

}

void Submarine::render(Scene &scene) {
    shader->use();

    // Set up light
    shader->setUniform("LightDirection", scene.lightDirection);

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
//    shader->setUniform("Texture", *texture);
    mesh->render();
}

