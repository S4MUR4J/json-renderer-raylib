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
  unsigned char r{};
  unsigned char g{};
  unsigned char b{};
  unsigned char a{};
};

struct Entity {
  std::string id;
  bool isCamera = false;
  bool isTransform = false;
  bool isMaterial = false;
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