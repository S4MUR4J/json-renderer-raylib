#include "loader.h"

#include <fstream>
#include <string>
#include <vector>

#include "raylib.h"

auto Loader::GetScene(const std::string& fileName) -> std::optional<Scene> {
  const auto scenePathResult = GetFilePath(fileName);
  if (!scenePathResult) {
    TraceLog(LOG_ERROR, "Scene file not found.");
    return std::nullopt;
  }

  const auto& scenePath = scenePathResult.value();
  TraceLog(LOG_INFO, "Scene path: %s", scenePath.string().c_str());
  const auto jsonResult = ReadJsonFromFilePath(scenePath);
  if (!jsonResult) {
    TraceLog(LOG_ERROR, "Scene loading error.");
    return std::nullopt;
  }

  const auto& sceneJson = jsonResult.value();
  return LoadScene(sceneJson);
}

auto Loader::GetFilePath(const std::string& fileName) -> std::optional<std::filesystem::path> {
  std::filesystem::path cwdFilePath = std::filesystem::current_path() / fileName;
  if (std::error_code errorCode; std::filesystem::exists(cwdFilePath, errorCode)) {
    return cwdFilePath;
  }

  TraceLog(LOG_ERROR, "File '%s' not found in path: %s", fileName.c_str(), cwdFilePath.string().c_str());
  return std::nullopt;
}

auto Loader::ReadJsonFromFilePath(const std::filesystem::path& filePath) -> std::optional<json> {
  std::ifstream file(filePath);
  if (!file.is_open()) {
    TraceLog(LOG_ERROR, "Cannot open file: %s", filePath.string().c_str());
    return std::nullopt;
  }

  try {
    return json::parse(file);
  } catch (const json::parse_error& error) {
    TraceLog(LOG_ERROR, "Parsing file %s to JSON error: %s", filePath.string().c_str(), error.what());
    return std::nullopt;
  }
}

auto Loader::LoadScene(const json& sceneJson) -> Scene {
  Scene scene{};
  std::vector<Entity> entities;

  scene.version = sceneJson.at("version").get<std::string>();
  scene.sceneVersion = sceneJson.at("scene_version").get<int>();

  const auto& entitiesJson = sceneJson.at("entities");
  entities.reserve(entitiesJson.size());

  for (const auto& entityJson : entitiesJson) {
    Entity entity;
    entity.id = entityJson.at("id").get<std::string>();

    for (const auto& [componentName, componentJson] : entityJson.at("components").items()) {
      if (componentName == "transform") {
        const auto& position = componentJson.at("position");
        const auto& scale = componentJson.at("scale");

        entity.isTransform = true;
        entity.transformComponent.position = Vector3{
            position[0].get<float>(),
            position[1].get<float>(),
            position[2].get<float>(),
        };

        entity.transformComponent.scale = Vector3{
            scale[0].get<float>(),
            scale[1].get<float>(),
            scale[2].get<float>(),
        };
      } else if (componentName == "material") {
        entity.isMaterial = true;
        const auto& rgb = componentJson.at("rgb");
        const auto& alpha = componentJson.at("a");

        entity.materialComponent.r = rgb[0].get<unsigned char>();
        entity.materialComponent.g = rgb[1].get<unsigned char>();
        entity.materialComponent.b = rgb[2].get<unsigned char>();
        entity.materialComponent.a = alpha.get<unsigned char>();
      } else if (componentName == "camera") {
        entity.isCamera = true;
        const auto& position = componentJson.at("position");
        const auto& target = componentJson.at("target");
        const auto& up = componentJson.at("up");
        const auto& fovy = componentJson.at("fovy");
        const auto& projection = componentJson.at("projection");

        entity.cameraComponent.position = Vector3{
            position[0].get<float>(),
            position[1].get<float>(),
            position[2].get<float>(),
        };
        entity.cameraComponent.target = Vector3{
            target[0].get<float>(),
            target[1].get<float>(),
            target[2].get<float>(),
        };
        entity.cameraComponent.up = Vector3{
            up[0].get<float>(),
            up[1].get<float>(),
            up[2].get<float>(),
        };
        entity.cameraComponent.fovy = fovy.get<float>();
        entity.cameraComponent.projection = projection.get<int>();
      } else {
        TraceLog(LOG_WARNING, "Component not implemented %s.", componentName.c_str());
      }
    }

    entities.push_back(std::move(entity));
  }

  scene.entities = std::move(entities);
  return scene;
}