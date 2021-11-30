//
// Created by Matej on 14. 11. 2021.
//

#include "volcano.h"
#include "Bubble.h"
#include <glm/gtc/random.hpp>

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>
#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Volcano::mesh;
std::unique_ptr<ppgso::Texture> Volcano::texture;
std::unique_ptr<ppgso::Shader> Volcano::shader;

Volcano::Volcano(bool burst, glm::vec3 position) {
    // Set random scale speed and rotation
    this->position = position;
    rotation = {-1.5f, 0, 0};
    scale = {9, 9, 9};

    isBurst = burst;

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("projekt/geysir.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("projekt/Geyser.obj");
}

bool Volcano::update(Scene &scene, float dt) {
    auto tmp = this->position;
    tmp.z += 0.2f;
    tmp.y += 1.7f;
    if (isBurst) {
        if (((float) rand() / (float) RAND_MAX) < 0.005) {
            for (int i = 0; i < 300; ++i) {
                    auto bubble = std::make_unique<Bubble>(tmp, ((float) rand() / (float) RAND_MAX) * (1500 - 1000) + 1000, 0.1, 0.2);
                    scene.objects.push_back(move(bubble));
            }
        }
    } else {
        if (((float) rand() / (float) RAND_MAX) < 0.02) {

                auto bubble = std::make_unique<Bubble>(tmp, ((float) rand() / (float) RAND_MAX) * (2000 - 1850) + 1850, 0.1, 0.2);
                scene.objects.push_back(move(bubble));
        }
    }

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void Volcano::render(Scene &scene) {
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

