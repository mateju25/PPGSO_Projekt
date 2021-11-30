//
// Created by Matej on 14. 11. 2021.
//

#include "submarinePropeler.h"
#include "Bubble.h"
#include <glm/gtc/random.hpp>

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> SubmarinePropeler::mesh;
std::unique_ptr<ppgso::Texture> SubmarinePropeler::texture;
std::unique_ptr<ppgso::Shader> SubmarinePropeler::shader;

SubmarinePropeler::SubmarinePropeler(){

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("projekt/geysir.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("projekt/Sub_Propeller.obj");
}

void SubmarinePropeler::updateModel(Scene &scene, glm::vec3 pos, glm::vec3 rot, glm::vec3 sc, float speed) {
    scale = sc;

    offset = {(distanceZ + distanceX) * sin(rot.y), distanceY, (distanceZ + distanceX) * cos(rot.y)};
    position = pos + offset;

    rotation.x = rot.x;
    rotation.y = 3*ppgso::PI/2;
    rotation.z = rot.y - ppgso::PI/2;

    if (speed >= 0)
        rotationZ += rotSpeed;
    else
        rotationZ -= rotSpeed;
    rotation.x = rotationZ;

    if (((float) rand() / (float) RAND_MAX) < 0.1) {
        auto bubble = std::make_unique<Bubble>(position, ((float) rand() / (float) RAND_MAX) * (90 - 85) + 85, 0.01, 0.1);
        scene.objects.push_back(move(bubble));
    }

    update(scene, 0);
//    render(scene);
}

bool SubmarinePropeler::update(Scene &scene, float dt) {

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void SubmarinePropeler::render(Scene &scene) {
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

