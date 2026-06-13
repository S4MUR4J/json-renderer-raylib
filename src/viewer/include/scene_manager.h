#pragma once

#include <optional>

#include "domain.h"
#include "raylib.h"

class SceneManager {
 public:
  explicit SceneManager(const char* scenePath);

  auto loadScene() -> std::optional<Scene>;
  auto reloadIfSceneFileChanged() -> bool;

  [[nodiscard]] auto getScene() const -> const Scene& {
    return _scene;
  }
  [[nodiscard]] auto getCamera() const -> const Camera& {
    return _camera;
  }

  auto updateCamera(const Camera& camera) -> void {
    _camera = camera;
  }

 private:
  auto updateFileModTime() -> void;
  static auto spawnBaseCamera() -> Camera;
  static auto getCamera(const Scene& scene) -> Camera;

  const char* _scenePath;
  Scene _scene;
  Camera _camera;
  long _lastFileModTime;
};