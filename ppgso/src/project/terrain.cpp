//
// Created by Matej on 14. 11. 2021.
//

#include "terrain.h"
#include <glm/gtc/random.hpp>

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Terrain::mesh;
std::unique_ptr<ppgso::Texture> Terrain::texture;
std::unique_ptr<ppgso::Shader> Terrain::shader;

Terrain::Terrain() {
    // Set random scale speed and rotation
    position = {0, 0, 0};
    rotation = {0, 0, 0};
    scale = {10, 10, 5};

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
//    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("lena.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("projekt/terrain_01.obj");
}

bool Terrain::update(Scene &scene, float dt) {

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void Terrain::render(Scene &scene) {
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

