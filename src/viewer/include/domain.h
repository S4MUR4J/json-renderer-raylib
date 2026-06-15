#ifndef DOMAIN_H
#define DOMAIN_H

#include <string>
#include <vector>

#include "raylib.h"

struct CameraComponent {
  Vector3 position{};
  Vector3 target{};
  Vector3 up{};
  float fovy{};
  int projection{};
};

struct TransformComponent {
  Vector3 position{};
  Vector3 scale{};
};

struct MaterialComponent {
  std::string color{"#ffffff"};
  float opacity{1.0F};
};

struct Entity {
  std::string id;
  bool isCamera = false;
  bool isTransform = false;
  bool isMeshRenderer = false;
  CameraComponent cameraComponent{};
  TransformComponent transformComponent{};
  MaterialComponent materialComponent{};
};

struct Scene {
  std::string version;
  int sceneVersion{};
  std::vector<Entity> entities;
};

#endif /* DOMAIN_H */