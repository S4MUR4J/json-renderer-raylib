#include "renderer.h"

#include "component_utils.h"
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


auto Renderer::renderScene(const Scene& scene) -> void {
  for (const auto& entity : scene.entities) {
    if (!entity.isMeshRenderer) {
      continue;
    }

    const auto& pos   = entity.transformComponent.position;
    const auto& scale = entity.transformComponent.scale;
    const Color color = HexToColor(entity.materialComponent.color, entity.materialComponent.opacity);
    const std::string& geometry = entity.isMeshFilter ? entity.meshFilterComponent.geometry : "Cube";

    DrawShape(geometry, pos, scale, color);
  }
}

// TODO: Install RayGUI, ImGUI.
auto Renderer::renderGui() -> void {
  DrawFPS(UI_FPS_SPACING, UI_FPS_SPACING);
}
