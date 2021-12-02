//
// Created by Matej on 14. 11. 2021.
//

#include "fishTail.h"
#include <glm/gtc/random.hpp>

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

// Static resources
std::unique_ptr<ppgso::Mesh> FishTail::mesh;
std::unique_ptr<ppgso::Texture> FishTail::texture;
std::unique_ptr<ppgso::Shader> FishTail::shader;

FishTail::FishTail(){
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("projekt/fish.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("projekt/fich_tail.obj");
}

void FishTail::updateModel(Scene &scene, glm::vec3 pos, glm::vec3 rot, glm::vec3 sc, bool isAlive) {
    scale = sc;

    offset = {(distanceZ + distanceX) * sin(rot.y), distanceY, (distanceZ + distanceX) * cos(rot.y)};
    position = pos + offset;

    rotation = rot;


    if (rotationZ <= -0.3) {
        rotSpeed = rotSpeed*-1;
    }
    if (rotationZ >= 0.28) {
        rotSpeed = rotSpeed*-1;
    }
    rotationZ += rotSpeed;
    rotation.z = rotationZ;

    this->isAlive = isAlive;

    update(scene, 0);
//    render(scene);
}

bool FishTail::update(Scene &scene, float dt) {
    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return isAlive;
}

void FishTail::render(Scene &scene) {
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
