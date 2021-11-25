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

Volcano::Volcano(bool burst, glm::vec3  position) {
    // Set random scale speed and rotation
    this->position = position;
    rotation = {0, 0, 0};
    scale = {0.5, 0.5, 0.5};

    isBurst = burst;

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("projekt/ocean.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("projekt/volcano.obj");
}

bool Volcano::update(Scene &scene, float dt) {
    if (isBurst) {
        if (((int) dt) % 20 == 0) {
            for (int i = 0; i < 30; ++i) {
                if (i % 5 == 0) {
                    auto tmp = this->position;
                    tmp.y += 3;
                    auto bubble = std::make_unique<Bubble>(tmp, ((float) rand() / (float) RAND_MAX) * (40 - 15) + 15);
                    scene.objects.push_back(move(bubble));
                }
            }
        }
    } else {
        if (((int) dt) % 2 == 0) {
            if (!isSending) {
                isSending = true;
                auto tmp = this->position;
                tmp.y += 3;
                auto bubble = std::make_unique<Bubble>(tmp, ((float) rand() / (float) RAND_MAX) * (100 - 55) + 55);
                scene.objects.push_back(move(bubble));
            }
        } else {
            isSending = false;
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
//    shader->setUniform("Texture", *texture);
    mesh->render();
}

