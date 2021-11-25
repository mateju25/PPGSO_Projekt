//
// Created by samue on 25-Nov-21.
//

#include "fish_spawn.h"
#include "fish.h"

fish_spawn::fish_spawn(std::vector<glm::vec3> path_points, double interval, double time_interval) {

    this->path_points = path_points;
    this->interval = interval;
    this->time_interval = time_interval;
}

bool fish_spawn::update(Scene &scene, float dt) {

    elapsed_time += dt;

    if (elapsed_time > interval) {
        elapsed_time -= interval;

        auto fish = std::make_unique<Fish>(path_points, time_interval);
        scene.objects.push_back(move(fish));
    }

    return true;
}

void fish_spawn::render(Scene &scene) {
    // much wow
    // much work
}

