//
// Created by Matej on 14. 11. 2021.
//

#ifndef PPGSO_TERRAIN_H
#define PPGSO_TERRAIN_H

#include <ppgso/ppgso.h>

#include "scene.h"
#include "object.h"

class Terrain final : public Object {
private:
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;


public:
    Terrain();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;

private:
};


#endif //PPGSO_TERRAIN_H
