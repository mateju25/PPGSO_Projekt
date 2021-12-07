//
// Created by Matej on 14. 11. 2021.
//

#include "sharkBottom.h"
#include <glm/gtc/random.hpp>

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>
#include <shaders/phong_frag_glsl.h>
#include <shaders/phong_vert_glsl.h>

// Static resources
std::unique_ptr<ppgso::Mesh> SharkBottom::mesh;
std::unique_ptr<ppgso::Texture> SharkBottom::texture;
std::unique_ptr<ppgso::Shader> SharkBottom::shader;

SharkBottom::SharkBottom(glm::vec3 pos, glm::vec3 rot){
    position = pos;
    rotation = rot;
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(phong_vert_glsl, phong_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("projekt/shark.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("projekt/sharkBottom.obj");
}

bool SharkBottom::update(Scene &scene, float dt) {
    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void SharkBottom::render(Scene &scene) {
    shader->use();

    // Set up light
    shader->setUniform("LightDirection", scene.lightDirection);

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}
