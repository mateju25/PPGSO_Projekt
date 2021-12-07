//
// Created by samue on 25-Nov-21.
//

#include "fish_spawn.h"
#include "fish.h"
#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>
#include <shaders/phong_frag_glsl.h>
#include <shaders/phong_vert_glsl.h>

// Static resources
std::unique_ptr<ppgso::Mesh> fish_spawn::mesh;
std::unique_ptr<ppgso::Texture> fish_spawn::texture;
std::unique_ptr<ppgso::Shader> fish_spawn::shader;

fish_spawn::fish_spawn(std::vector<glm::vec3> path_points, double interval, double time_interval) {

    this->path_points = path_points;
    this->interval = interval;
    this->time_interval = time_interval;
    this->elapsed_time = -interval;
    this->isFish = false;

    position = path_points.at(0);
    scale = {0.6,0.6,0.6};
    rotation = {3*ppgso::PI/2, 0 , 0};
    color = {1,0.79,0.86};

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(phong_vert_glsl, phong_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("projekt/sasasanka.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("projekt/sasasanka.obj");
}

bool fish_spawn::update(Scene &scene, float dt) {

    elapsed_time += dt;
    if (elapsed_time > interval) {
        elapsed_time -= interval;

        for (int i = 0; i < 10; ++i) {

            auto fish = std::make_unique<Fish>(scene, path_points, time_interval);
            scene.objects.push_back(move(fish));
        }

    }

    generateModelMatrix();

    return true;
}

void fish_spawn::render(Scene &scene) {
    shader->use();

    // Set up light
    shader->setUniform("LightDirection", scene.lightDirection);

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
//    shader->setUniform("Transparency", 0f);
//    shader->setUniform("OverallColor", color);
    shader->setUniform("Texture", *texture);
    mesh->render();
}

