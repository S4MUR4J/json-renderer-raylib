#include "renderer.h"

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
    const auto* const transform = &entity.transformComponent;
    const auto* const material = &entity.materialComponent;

    const Color color{.r = material->r, .g = material->g, .b = material->b, .a = material->a};
    DrawCube(transform->position, transform->scale.x, transform->scale.y, transform->scale.z, color);
    DrawCubeWires(transform->position, transform->scale.x, transform->scale.y, transform->scale.z, GRAY);
  }
}

// TODO: Install RayGUI, ImGUI.
auto Renderer::renderGui() -> void {
  DrawFPS(UI_FPS_SPACING, UI_FPS_SPACING);
}
