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
#include <shaders/phong_frag_glsl.h>
#include <shaders/phong_vert_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Volcano::mesh;
std::unique_ptr<ppgso::Texture> Volcano::texture;
std::unique_ptr<ppgso::Shader> Volcano::shader;

Volcano::Volcano(bool burst, glm::vec3 position) {
    // Set random scale speed and rotation
    this->position = position;
    rotation = {-1.5f, 0, 0};
    scale = {3, 3, 3};

    isBurst = burst;

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(phong_vert_glsl, phong_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("projekt/geysir.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("projekt/Geyser.obj");
}

bool Volcano::update(Scene &scene, float dt) {
    auto tmp = this->position;
    tmp.z += 0.02f;
    tmp.y += 0.6f;
    if (isBurst) {
        if (((float) rand() / (float) RAND_MAX) < 0.005) {
            for (int i = 0; i < 30; ++i) {
                    auto bubble = std::make_unique<Bubble>(tmp, ((float) rand() / (float) RAND_MAX) * (500 - 400) + 400, 0.04, 0.06, 0.1);
                    scene.objects.push_back(move(bubble));
            }
        }
    } else {
        if (((float) rand() / (float) RAND_MAX) < 0.02) {

                auto bubble = std::make_unique<Bubble>(tmp, ((float) rand() / (float) RAND_MAX) * (1500 - 1350) + 1350, 0.04, 0.06, 0.2);
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
    shader->setUniform("global_lighting_on", scene.global_lighting_on);

    shader->setUniform("material.ambient", {0.19125f, 0.0735f, 0.0225f});
    shader->setUniform("material.diffuse", {0.35038f, 0.29f, 0.7828f});
    shader->setUniform("material.specular", {0.256777f, 0.137622f, 0.086014f});
    shader->setUniform("material.shininess", 12.8f);

    shader->setUniform("lights.count", scene.lights.count);
    for (int i = 0; i < scene.lights.count; i++) {
        shader->setUniform("lights.positions[" + std::to_string(i) + "]", scene.lights.positions[i]);
        shader->setUniform("lights.colors[" + std::to_string(i) + "]", scene.lights.colors[i]);
        shader->setUniform("lights.ranges[" + std::to_string(i) + "]", scene.lights.ranges[i]);
        if (scene.lights.strengths[i] < 0) {
            shader->setUniform("lights.strengths[" + std::to_string(i) + "]", 0.0f);
        }
        else {
            shader->setUniform("lights.strengths[" + std::to_string(i) + "]", scene.lights.strengths[i]);
        }
    }

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}

