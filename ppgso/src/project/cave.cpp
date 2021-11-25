//
// Created by Matej on 14. 11. 2021.
//

#include "cave.h"
#include <glm/gtc/random.hpp>

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Cave::mesh;
std::unique_ptr<ppgso::Texture> Cave::texture;
std::unique_ptr<ppgso::Shader> Cave::shader;

Cave::Cave() {
    // Set random scale speed and rotation
    position = {0, 0, 0};
    rotation = {3*ppgso::PI/2, 0, 0};
    scale = {20, 20, 15};

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("projekt/ocean.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("projekt/cave.obj");
}

bool Cave::update(Scene &scene, float dt) {

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void Cave::render(Scene &scene) {
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

