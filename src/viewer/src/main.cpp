#include <iostream>
#include <vector>

#include "domain.h"
#include "loader.h"
#include "raylib.h"

constexpr char APP_NAME[] = "SceneKeeper Viewer";
constexpr int SCREEN_WIDTH = 1024;
constexpr int SCREEN_HEIGHT = 768;
constexpr int TARGET_FPS = 60;
constexpr float CAMERA_FOVY = 45.0F;
constexpr int GRID_SLICE = 10;
constexpr int GRID_SPACING = 1;
constexpr int FPS_STATS_SPACING = 10;

auto validateInput(int argc, char** argv) -> bool;
auto gameInit(const Scene& scene) -> void;
auto getCamera() -> Camera3D;
auto gameLoop(const Camera3D& camera, const Scene& scene) -> void;
auto drawScene(const Scene& scene) -> void;

auto main(const int argc, char** argv) -> int {
  if (!validateInput(argc, argv)) {
    return EXIT_FAILURE;
  }

  const auto sceneOpt = Loader::GetScene(argv[1]);
  if (!sceneOpt) {
    return EXIT_FAILURE;
  }

  gameInit(sceneOpt.value());

  return EXIT_SUCCESS;
}

auto validateInput(const int argc, char** argv) -> bool {
  if (argc != 2) {
    std::cout << "SceneKeeper Viewer, not enough params passed.";
    return false;
  }

  (void)argv;  // TODO: Hack for compiler...

  return true;
}

auto gameInit(const Scene& scene) -> void {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME);
  SetTargetFPS(TARGET_FPS);

  const auto camera = getCamera();

  gameLoop(camera, scene);
}

auto getCamera() -> Camera3D {
  Camera3D camera{};
  camera.position = Vector3{0.0F, 10.0F, 10.0F};
  camera.target = Vector3{0.0F, 0.0F, 0.0F};
  camera.up = Vector3{0.0F, 1.0F, 0.0F};
  camera.fovy = CAMERA_FOVY;
  camera.projection = CAMERA_PERSPECTIVE;
  return camera;
}

// TODO: ImGUI?!
auto gameLoop(const Camera3D& camera, const Scene& scene) -> void {
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);

    DrawGrid(GRID_SLICE, GRID_SPACING);
    drawScene(scene);

    EndMode3D();

    DrawFPS(FPS_STATS_SPACING, FPS_STATS_SPACING);

    EndDrawing();
  }

  CloseWindow();
}

auto drawScene(const Scene& scene) -> void {
  for (const auto& entity : scene.entities) {
    const auto* const transform = &entity.transformComponent;
    const auto* const material = &entity.materialComponent;

    const Color color{material->r, material->g, material->b, material->a};
    DrawCube(transform->position, transform->scale.x, transform->scale.y, transform->scale.z, color);
    DrawCubeWires(transform->position, transform->scale.x, transform->scale.y, transform->scale.z, GRAY);
  }
}