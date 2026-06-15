#include "renderer.h"

#include <string>

#include "raylib.h"

Renderer::Renderer() : _sceneRenderEnable(true), _guiRenderEnable(true) {
}

Renderer::Renderer(const bool sceneRenderEnable, const bool uiRenderEnable)
    : _sceneRenderEnable(sceneRenderEnable), _guiRenderEnable(uiRenderEnable) {
}

auto Renderer::render(const Scene& scene, const Camera& camera) const -> void {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  BeginMode3D(camera);
  if (_sceneRenderEnable) {
    renderScene(scene);
  }

  DrawGrid(UI_GRID_SLICE, UI_GRID_SPACING);
  EndMode3D();

  if (_guiRenderEnable) {
    renderGui();
  }
  EndDrawing();
}

static auto HexToColor(const std::string& hex, float opacity) -> Color {
  const unsigned long rgb = std::stoul(hex.substr(1), nullptr, 16);
  return Color{
      .r = static_cast<unsigned char>(rgb >> 16 & 0xFF),
      .g = static_cast<unsigned char>(rgb >> 8 & 0xFF),
      .b = static_cast<unsigned char>(rgb & 0xFF),
      .a = static_cast<unsigned char>(opacity * 255.0F),
  };
}

auto Renderer::renderScene(const Scene& scene) -> void {
  for (const auto& entity : scene.entities) {
    if (!entity.isMeshRenderer) { continue;
}

    const auto* const transform = &entity.transformComponent;
    const Color color = HexToColor(entity.materialComponent.color, entity.materialComponent.opacity);
    DrawCube(transform->position, transform->scale.x, transform->scale.y, transform->scale.z, color);
    DrawCubeWires(transform->position, transform->scale.x, transform->scale.y, transform->scale.z, GRAY);
  }
}

// TODO: Install RayGUI, ImGUI.
auto Renderer::renderGui() -> void {
  DrawFPS(UI_FPS_SPACING, UI_FPS_SPACING);
}
