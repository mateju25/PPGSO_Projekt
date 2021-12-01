//
// Created by Matej on 14. 11. 2021.
//

#include "submarine.h"
#include "submarinePropeler.h"
#include "decorationPiller.h"
#include <glm/gtc/random.hpp>

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>
#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>


// Static resources
std::unique_ptr<ppgso::Mesh> Submarine::mesh;
std::unique_ptr<ppgso::Texture> Submarine::texture;
std::unique_ptr<ppgso::Shader> Submarine::shader;

Submarine::Submarine(Scene &scene) {
    // Set random scale speed and rotation
    position = {330, 0, -234.618};
    rotation = {BASIC_ROTATION_X, BASIC_ROTATION_Y, BASIC_ROTATION_Z};
    scale = {2, 2, 2};

    auto part = std::make_unique<SubmarinePropeler>();
    parts.push_back(move(part));


    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("projekt/submarine.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("projekt/Sub.obj");
}

bool Submarine::update(Scene &scene, float dt) {
    if (scene.camera->mode == Camera::STATIONARY) {
        speed = 0;
    }
    if (scene.keyboard[GLFW_KEY_D]) {
        rotation.y -= rot_speed * dt * 30;
    }
    if (scene.keyboard[GLFW_KEY_A]) {
        rotation.y += rot_speed * dt * 30;
    }
    if (scene.keyboard[GLFW_KEY_W]) {
        position.y += 0.5 * dt * 30;
    }
    if (scene.keyboard[GLFW_KEY_S]) {
        position.y -= 0.5 * dt * 30;
    }
    if (scene.keyboard[GLFW_KEY_SPACE]) {
        speed += 0.01f * dt * 30;
    }
    if (scene.keyboard[GLFW_KEY_LEFT_SHIFT]) {
        speed -= 0.01f * dt * 30;
    }
    if (scene.keyboard[GLFW_KEY_C]) {
        speed = 0;
    }
    if (scene.keyboard[GLFW_KEY_ENTER]) {
        std::cout << position.x << " " << position.y << " "<< position.z << " " << std::endl;
        std::cout << "Y-terrain: " << scene.getHeight(position.x, position.z) << std::endl;
    }

    auto oldPos = position;

    position.z += speed * cos(rotation.y - BASIC_ROTATION_Y);
    position.x += speed * -sin(rotation.y - BASIC_ROTATION_Y) * -1;
    if (position.y > 225)
        position.y = 225;

    if (checkCollisions(scene, dt))
        position = oldPos;

    auto tmp = rotation;
    tmp.x -= BASIC_ROTATION_X;
    tmp.y -= BASIC_ROTATION_Y;
    tmp.z -= BASIC_ROTATION_Z;


    for (auto &obj: parts) {
        auto propeler = dynamic_cast<SubmarinePropeler *>(obj.get());
        propeler->updateModel(scene, position, rotation, scale, speed);
    }

    scene.setTargetPosition(position, tmp);

    // Generate modelMatrix from position, rotation and scale
    generateModelMatrix();

    return true;
}

bool Submarine::checkCollisions(Scene &scene, float dt) {
    for (auto &obj : scene.objects) {
        if (obj.get() == this) continue;

        auto piller = dynamic_cast<DecorationPiller*>(obj.get());
        if (piller) {
            auto distance = (this->position - piller->position);

            float size = 0.3f;

            if (distance.y > 38)
                return false;

            if (distance.y > 32)
                size = 0.4f;
            if (distance.y < 4)
                size = 0.4f;

            if ( (abs(distance.x) < piller->scale.x * size) &&
                    (abs(distance.z) < piller->scale.z * size)) {
                return true;
            }
        }
    }
    return false;
}

void Submarine::render(Scene &scene) {
    for (auto &obj: parts) {
        auto propeler = dynamic_cast<SubmarinePropeler *>(obj.get());
        propeler->render(scene);
    }


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

