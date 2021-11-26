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

FishTail::FishTail(Scene &scene, Fish &fish) : fish(fish){


    scale = fish.scale;
    position = positionOffset = {distanceX, distanceY, distanceZ};

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("projekt/ocean.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("projekt/tail.obj");
}

bool FishTail::update(Scene &scene, float dt) {
    offset = {(distanceZ + distanceX) * sin(fish.rotation.y), distanceY, (distanceZ + distanceX) * cos(fish.rotation.y)};
    position = fish.position + offset;

    rotation = fish.rotation;


    if (rotationZ <= -0.2) {
        rotSpeed = rotSpeed*-1;
    }
    if (rotationZ >= 0.18) {
        rotSpeed = rotSpeed*-1;
    }
    rotationZ += rotSpeed;
    rotation.z = rotationZ;


    if (!fish.isAlive)
        return false;

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
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
//    shader->setUniform("Texture", *texture);
    mesh->render();
}
