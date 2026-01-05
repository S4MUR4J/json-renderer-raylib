#include "scene_manager.h"

#include "loader.h"

SceneManager::SceneManager(const char* scenePath) : _scenePath(scenePath), _camera{}, _lastFileModTime(0) {
  updateFileModTime();
}

auto SceneManager::loadScene() -> std::optional<Scene> {
  const auto sceneOpt = Loader::GetScene(_scenePath);
  if (!sceneOpt) {
    TraceLog(LOG_ERROR, "Failed to load scene from: %s", _scenePath);
    return std::nullopt;
  }

  _scene = sceneOpt.value();
  TraceLog(LOG_INFO, "Scene loaded successfully from: %s", _scenePath);

  if (const auto cameraOpt = getCamera(_scene)) {
    _camera = cameraOpt.value();
    TraceLog(LOG_INFO, "Camera loaded from scene");
  } else {
    TraceLog(LOG_WARNING, "No camera found in scene, keeping previous camera");
  }

  updateFileModTime();
  return _scene;
}

auto SceneManager::reloadIfSceneFileChanged() -> bool {
  const long currentFileModTime = GetFileModTime(_scenePath);

  if (currentFileModTime == _lastFileModTime || currentFileModTime == 0) {
    return false;
  }

  _lastFileModTime = currentFileModTime;

  const auto sceneOpt = this->loadScene();
  if (!sceneOpt) {
    TraceLog(LOG_ERROR, "Failed to auto-reload scene");
    return false;
  }
  _scene = sceneOpt.value();

  TraceLog(LOG_INFO, "Scene auto-reloaded from file change");
  return true;
}

auto SceneManager::updateFileModTime() -> void {
  _lastFileModTime = GetFileModTime(_scenePath);
}

auto SceneManager::getCamera(const Scene& scene) -> std::optional<Camera> {
  for (const auto& entity : scene.entities) {
    if (!entity.isCamera) {
      continue;
    }

    const auto& [position, target, up, fovy, projection] = entity.cameraComponent;

    Camera camera{};
    camera.position = position;
    camera.target = target;
    camera.up = up;
    camera.fovy = fovy;
    camera.projection = projection;

    return camera;
  }

  return std::nullopt;
}
