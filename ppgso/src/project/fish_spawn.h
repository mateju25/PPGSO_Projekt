//
// Created by samue on 25-Nov-21.
//

#ifndef PPGSO_FISH_SPAWN_H
#define PPGSO_FISH_SPAWN_H

#include <glm/glm.hpp>
#include "scene.h"
#include "object.h"


class fish_spawn : public Object {
private:

    std::vector<glm::vec3> path_points;

    double interval;
    double time_interval;

    double elapsed_time = 0;

public:

    fish_spawn(std::vector<glm::vec3> path_points, double interval, double time_interval);

    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};


#endif //PPGSO_FISH_SPAWN_H
