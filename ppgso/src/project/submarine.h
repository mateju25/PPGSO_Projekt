//
// Created by Matej on 14. 11. 2021.
//

#ifndef PPGSO_SUBMARINE_H
#define PPGSO_SUBMARINE_H

#include <ppgso/ppgso.h>
#include "scene.h"
#include "object.h"

class Submarine final : public Object {
private:
    float BASIC_ROTATION_X = 1.5f;
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;


public:
    Submarine();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;

    void rotateRight();

    void rotateLeft();

    void rotateDown();

    void rotateUp();

    void moveForward();

    void moveBackward();
private:
};


#endif