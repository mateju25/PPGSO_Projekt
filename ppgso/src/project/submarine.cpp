//
// Created by Matej on 14. 11. 2021.
//

#include "submarine.h"
#include <glm/gtc/random.hpp>

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Submarine::mesh;
std::unique_ptr<ppgso::Texture> Submarine::texture;
std::unique_ptr<ppgso::Shader> Submarine::shader;

Submarine::Submarine() {
    // Set random scale speed and rotation
    position = {0, 0, 0};
    rotation = {BASIC_ROTATION_X, BASIC_ROTATION_Y, BASIC_ROTATION_Z};
    scale = {2, 2, 2};

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("projekt/submarine.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("projekt/Sub.obj");
}

bool Submarine::update(Scene &scene, float dt) {

    if (scene.keyboard[GLFW_KEY_RIGHT]) {
        rotation.y -= rot_speed;
    }
    if (scene.keyboard[GLFW_KEY_LEFT]) {
        rotation.y += rot_speed;
    }
    if (scene.keyboard[GLFW_KEY_UP]) {
        position.y += 0.5;
//        rotation.x -= rot_speed;
//        if (rotation.x - BASIC_ROTATION_X <= -0.6)
//            rotation.x = -0.6 + BASIC_ROTATION_X;
    }
    if (scene.keyboard[GLFW_KEY_DOWN]) {
        position.y -= 0.5;
//        rotation.x += rot_speed ;
//        if (rotation.x - BASIC_ROTATION_X >= 0.6)
//            rotation.x = 0.6 + BASIC_ROTATION_X;
    }
    if (scene.keyboard[GLFW_KEY_SPACE]) {
        speed += 0.01f;
    }
    if (scene.keyboard[GLFW_KEY_LEFT_SHIFT]) {
        speed -= 0.01f;
    }
    if (scene.keyboard[GLFW_KEY_P]) {
        speed = 0;
    }
//    speed = 0;
    position.z += speed * cos(rotation.y - BASIC_ROTATION_Y) ;
    position.x += speed * -sin(rotation.y - BASIC_ROTATION_Y) *-1;
//    position.y += speed * -cos(rotation.y) * sin(rotation.x - BASIC_ROTATION_X);

    auto tmp = rotation;
    tmp.x -= BASIC_ROTATION_X;
    tmp.y -= BASIC_ROTATION_Y;
    tmp.z -= BASIC_ROTATION_Z;
    scene.setTargetPosition(position, tmp);

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
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

