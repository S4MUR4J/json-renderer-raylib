#ifndef LOADER_H
#define LOADER_H

#include <filesystem>
#include <nlohmann/json.hpp>
#include <optional>

#include "domain.h"

class Loader {
public:
  using json = nlohmann::json;
  static auto GetScene(const std::string& fileName) -> std::optional<Scene>;

private:
  static auto GetFilePath(const std::string& fileName)
    -> std::optional<std::filesystem::path>;
  static auto ReadJsonFromFilePath(const std::filesystem::path& filePath)
    -> std::optional<json>;

  static auto LoadScene(const json& sceneJson) -> Scene;
};

#endif /* LOADER_H */