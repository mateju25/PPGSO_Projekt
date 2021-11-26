//
// Created by Matej on 14. 11. 2021.
//

#ifndef PPGSO_FishTail_H
#define PPGSO_FishTail_H

#include <ppgso/ppgso.h>

#include "scene.h"
#include "object.h"
#include "fish.h"

class FishTail final : public Object {
private:
    Fish &fish;
    glm::vec3 offset;
    float rotationZ = -0.01;
    float rotSpeed = .01f;
    int out = 0;

    float distanceX = 0;
    float distanceY = -0.1;
    float distanceZ = 2.2;
    glm::vec3 positionOffset;
    glm::vec3 fishPositionBeforeMovement;

    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

public:
    FishTail(Scene &scene, Fish &fish);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;

private:
    glm::vec3 random_vec3 (float mini, float maxi);
};


#endif //PPGSO_Fish_H
