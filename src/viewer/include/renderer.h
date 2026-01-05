#ifndef RENDERER_H
#define RENDERER_H

#include "domain.h"

constexpr int UI_PADDING = 20;
constexpr int UI_FPS_SPACING = 10;

constexpr int UI_GRID_SLICE = 10;
constexpr int UI_GRID_SPACING = 1;

class Renderer {
 public:
  Renderer();
  Renderer(bool sceneRenderEnable, bool uiRenderEnable);

  auto render(const Scene& scene, const Camera& camera) const -> void;

 private:
  bool _sceneRenderEnable;
  bool _guiRenderEnable;

  static auto renderScene(const Scene& scene) -> void;
  static auto renderGui() -> void;
};

#endif /* RENDERER_H */
