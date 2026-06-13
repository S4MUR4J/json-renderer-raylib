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

  _camera = getCamera(_scene);

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

auto SceneManager::spawnBaseCamera() -> Camera {
  Camera camera{};
  camera.position = {.x = 10.0F, .y = 10.0F, .z = 10.0F};
  camera.target = {.x = 0.0F, .y = 0.0F, .z = 0.0F};
  camera.up = {.x = 0.0F, .y = 1.0F, .z = 0.0F};
  camera.fovy = 45.0F;
  camera.projection = CAMERA_PERSPECTIVE;
  return camera;
}

auto SceneManager::getCamera(const Scene& scene) -> Camera
{
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

    TraceLog(LOG_INFO, "Camera loaded from scene");
    return camera;
  }

  TraceLog(LOG_WARNING, "No camera found in scene, using base camera");
  return spawnBaseCamera();
}
