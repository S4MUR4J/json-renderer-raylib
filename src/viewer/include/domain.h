#ifndef DOMAIN_H
#define DOMAIN_H

#include <string>
#include <vector>

#include "raylib.h"

struct TransformComponent {
  Vector3 position{};
  Vector3 scale{};
};

struct MaterialComponent {
  unsigned char r{};
  unsigned char g{};
  unsigned char b{};
  unsigned char a{};
};

struct Entity {
  std::string id;
  TransformComponent transformComponent{};
  MaterialComponent materialComponent{};
};

struct Scene {
  std::vector<Entity> entities;
};

#endif /* DOMAIN_H */