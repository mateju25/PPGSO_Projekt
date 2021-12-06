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
    position = {-14.2862, 0.0871516, -6.35545};
    rotation = {BASIC_ROTATION_X, BASIC_ROTATION_Y, BASIC_ROTATION_Z};
    scale = {1, 1, 1};

    auto part = std::make_unique<SubmarinePropeler>();
    parts.push_back(move(part));


    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(texture_vert_glsl, texture_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("projekt/submarine.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("projekt/Sub.obj");
}

bool Submarine::update(Scene &scene, float dt) {
    if (scene.camera->mode != Camera::FOLLOW) {
        speed = 0;
    }
    if (scene.keyboard[GLFW_KEY_D]) {
        rotation.y -= rot_speed * dt * 30;
    }
    if (scene.keyboard[GLFW_KEY_A]) {
        rotation.y += rot_speed * dt * 30;
    }
    if (scene.keyboard[GLFW_KEY_SPACE]) {
        position.y += 0.05 * dt * 30;
    }
    if (scene.keyboard[GLFW_KEY_LEFT_SHIFT]) {
        position.y -= 0.05 * dt * 30;
    }
    if (scene.keyboard[GLFW_KEY_W]) {
        speed += 0.01f * dt * 30;
    }
    if (scene.keyboard[GLFW_KEY_S]) {
        speed -= 0.01f * dt * 30;
    }
    if (scene.keyboard[GLFW_KEY_C]) {
        speed = 0;
    }
    if (scene.keyboard[GLFW_KEY_ENTER]) {
        std::cout << position.x << " " << position.y << " " << position.z << " " << std::endl;
        std::cout << "Y-terrain: " << scene.getHeight(position.x, position.z) << std::endl;
    }

    auto oldPos = position;

    position.z += speed * cos(rotation.y - BASIC_ROTATION_Y);
    position.x += speed * -sin(rotation.y - BASIC_ROTATION_Y) * -1;
    if (position.y > 22.5)
        position.y = 22.5;

    //bounding border main
    if (position.x < -44)
        position.x = oldPos.x;
    if (position.x > 44)
        position.x = oldPos.x;
    if (position.z < -41.8)
        position.z = oldPos.z;

    if (position.x < -14.48 || position.x > 14.48)
        if (position.z > 17.8 && oldPos.z < 17.8)
            position.z = oldPos.z;


    if (position.z > 17.8) {
        //bounding border cave
        if (position.x < -14.48)
            position.x = oldPos.x;
        if (position.x > 14.48)
            position.x = oldPos.x;
        if (position.z > 53.5)
            position.z = oldPos.z;
    }

    if (checkCollisions(scene, dt)) //kolizia so stlpmi
        position = oldPos;

    auto tmp = rotation;
    tmp.x -= BASIC_ROTATION_X;
    tmp.y -= BASIC_ROTATION_Y;
    tmp.z -= BASIC_ROTATION_Z;

    if (position.y < scene.getHeight(position.x, position.z) + 0.7f) { //kolizia s terenom
        position.y = scene.getHeight(position.x, position.z) + 0.7f;
    }

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
    for (auto &obj: scene.objects) {
        if (obj.get() == this) continue;

        auto piller = dynamic_cast<DecorationPiller *>(obj.get());
        if (piller) {
            auto distance = (this->position - piller->position);

            if (piller->mode == 1) {
                // x
                if ((abs(distance.x) < 2.07104) && (abs(distance.z) < 3.159)) {
                    if (distance.y < -0.951036 || distance.y > 0.951036)
                        return false;
                    return true;
                }
            } else {
                if ((abs(distance.x) + abs(distance.z) < piller->scale.x * 0.62f)) {
                    if (piller->mode == 0 && distance.y > 3.78637)
                        return false;
                    if (piller->mode == 2 && distance.y > 2.78637)
                        return false;
                    return true;
                }
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

