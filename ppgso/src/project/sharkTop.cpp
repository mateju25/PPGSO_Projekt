//
// Created by Matej on 14. 11. 2021.
//

#include "sharkTop.h"

#include <shaders/phong_frag_glsl.h>
#include <shaders/phong_vert_glsl.h>

// Static resources
std::unique_ptr<ppgso::Mesh> SharkTop::mesh;
std::unique_ptr<ppgso::Texture> SharkTop::texture;
std::unique_ptr<ppgso::Shader> SharkTop::shader;

SharkTop::SharkTop(glm::vec3 pos, glm::vec3 rot, float freq){
    position = pos;
    rotation = rot;
    rotSpeed = freq;
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(phong_vert_glsl, phong_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("projekt/shark.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("projekt/sharkTop.obj");
}

bool SharkTop::update(Scene &scene, float dt) {

    if (rotationZ <= -ppgso::PI/2) {
        rotSpeed = rotSpeed*-1;
    }
    if (rotationZ >= 0.5) {
        rotSpeed = rotSpeed*-1;
    }
    rotationZ += rotSpeed;

    rotation.x = rotationZ;

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

void SharkTop::render(Scene &scene) {
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
