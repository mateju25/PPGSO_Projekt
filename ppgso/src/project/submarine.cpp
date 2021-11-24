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
    position = {0, 20, 0};
    rotation = {BASIC_ROTATION_X, 0, 0};
    scale = {3, 3, 3};

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("projekt/submarine.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("projekt/Sub.obj");
}

bool Submarine::update(Scene &scene, float dt) {
    float flag = -1;
    float speed = 0.5f;
    if (scene.keyboard[GLFW_KEY_RIGHT]) {
        rotation.y += 0.05;
        if (rotation.y >= ppgso::PI*2)
            rotation.y -=  ppgso::PI*2;
    }
    else if (scene.keyboard[GLFW_KEY_LEFT]) {
        rotation.y -= 0.05;
        if (rotation.y <= - ppgso::PI*2)
            rotation.y +=  ppgso::PI*2;
    }
    else if (scene.keyboard[GLFW_KEY_UP]) {
        rotation.x -= 0.05;
        if (rotation.x - BASIC_ROTATION_X <= -0.6)
            rotation.x = -0.6 + BASIC_ROTATION_X;

    }
    else if (scene.keyboard[GLFW_KEY_DOWN]) {
        rotation.x += 0.05;
        if (rotation.x - BASIC_ROTATION_X >= 0.6)
            rotation.x = 0.6 + BASIC_ROTATION_X;
    }
    else if (scene.keyboard[GLFW_KEY_SPACE]) {
        speed += 0.1f;
    }
    else if (scene.keyboard[GLFW_KEY_LEFT_SHIFT]) {
        speed -= 0.1f;
    }

    if (abs(rotation.y) >= ppgso::PI/2 && abs(rotation.y) <= 3*ppgso::PI/2)
        flag = 1;

    position.z += speed * cos(rotation.y);
    position.x += speed * -sin(rotation.y);
    position.y += speed * flag * sin(rotation.x - BASIC_ROTATION_X);

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

