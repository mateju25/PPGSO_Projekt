//
// Created by Matej on 14. 11. 2021.
//

#ifndef PPGSO_Fish_H
#define PPGSO_Fish_H

#include <ppgso/ppgso.h>

#include "scene.h"
#include "object.h"

class Fish final : public Object {
private:
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    std::vector<glm::vec3> path_points;
    float total_time_interval;
    float current_time_interval;

    glm::vec3 bezierRec(std::vector<glm::vec3> points, float t);
    glm::vec3 getPoint(glm::vec3 p1, glm::vec3 p2, float t);

public:
    Fish(std::vector<glm::vec3> path_points, float total_time_interval);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;

private:
};


#endif //PPGSO_Fish_H
