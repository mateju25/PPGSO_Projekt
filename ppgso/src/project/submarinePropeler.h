//
// Created by Matej on 14. 11. 2021.
//

#ifndef PPGSO_SUBMARINE_PROPELER_H
#define PPGSO_SUBMARINE_PROPELER_H

#include <ppgso/ppgso.h>
#include "scene.h"
#include "object.h"

class SubmarinePropeler final : public Object {
private:
    glm::vec3 offset;
    float rotationZ = -0.01;
    float rotSpeed = .08f;

    float distanceX = 1.7;
    float distanceY = 0;
    float distanceZ = 0;

    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;


public:
    SubmarinePropeler();

    bool update(Scene &scene, float dt) override;

    void updateModel(Scene &scene, glm::vec3 pos, glm::vec3 rot, glm::vec3 sc, float speed);

    void render(Scene &scene) override;

private:
};


#endif