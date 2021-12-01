#include "scene.h"

void Scene::update(float time) {
  // Use iterator to update all objects so we can remove while iterating
  auto i = std::begin(objects);

  while (i != std::end(objects)) {
    // Update and remove from list if needed
    auto obj = i->get();
    if (!obj->update(*this, time))
      i = objects.erase(i); // NOTE: no need to call destructors as we store shared pointers in the scene
    else
      ++i;
  }

    camera->update();
}

void Scene::render() {
  // Simply render all objects
  for ( auto& obj : objects )
    obj->render(*this);
}

void Scene::setTargetPosition(const glm::vec3 &position, const glm::vec3 &rotation) {
    camera->moveTo(position, rotation);
}

float Scene::getHeight(float x, float y) {
    //invert
    int i = (-1*x - 440) *  -4.363636;
    int j = (y - 178) * -4.362392;

    float color =  heightFramebuffer[3 * (i * imgWidth + j)] + heightFramebuffer[3 * (i * imgWidth + j) + 1] + heightFramebuffer[3 * (i * imgWidth + j) + 2];
    return (color - 258) * 0.62812 - 54.6012;
//    return color;
}

std::vector<Object*> Scene::intersect(const glm::vec3 &position, const glm::vec3 &direction) {
  std::vector<Object*> intersected = {};
  for(auto& object : objects) {
    // Collision with sphere of size object->scale.x
    auto oc = position - object->position;
    auto radius = object->scale.x;
    auto a = glm::dot(direction, direction);
    auto b = glm::dot(oc, direction);
    auto c = glm::dot(oc, oc) - radius * radius;
    auto dis = b * b - a * c;

    if (dis > 0) {
      auto e = sqrt(dis);
      auto t = (-b - e) / a;

      if ( t > 0 ) {
        intersected.push_back(object.get());
        continue;
      }

      t = (-b + e) / a;

      if ( t > 0 ) {
        intersected.push_back(object.get());
        continue;
      }
    }
  }

  return intersected;
}
