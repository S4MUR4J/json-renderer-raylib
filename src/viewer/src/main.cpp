#include <iostream>

#include "domain.h"
#include "input_manager.h"
#include "raylib.h"
#include "renderer.h"
#include "scene_manager.h"

constexpr char APP_NAME[] = "SceneKeeper Viewer";
constexpr int SCREEN_WIDTH = 1024;
constexpr int SCREEN_HEIGHT = 768;
constexpr int TARGET_FPS = 60;

struct ViewerState {
  bool cameraControlMode = false;
};

auto validateInput(int argc) -> bool;
auto gameInit(const char* scenePath) -> void;
auto gameLoop(SceneManager& sceneManager, InputManager& inputManager, ViewerState& viewerState) -> void;

auto main(const int argc, char** argv) -> int {
  if (!validateInput(argc)) {
    return EXIT_FAILURE;
  }

  gameInit(argv[1]);

  return EXIT_SUCCESS;
}

auto validateInput(const int argc) -> bool {
  if (argc != 2) {
    std::cout << "SceneKeeper Viewer, not enough params passed.";
    return false;
  }

  return true;
}

auto gameInit(const char* scenePath) -> void {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME);
  SetTargetFPS(TARGET_FPS);

  SceneManager sceneManager(scenePath);

  if (!sceneManager.loadScene()) {
    CloseWindow();
    return;
  }

  ViewerState state{};
  InputManager inputManager;
  inputManager.setEventCallback([&state](const InputEvent event) -> void {
    switch (event) {
      case InputEvent::TOGGLE_CAMERA_MODE:
        state.cameraControlMode = !state.cameraControlMode;
        if (state.cameraControlMode) {
          DisableCursor();
        } else {
          EnableCursor();
        }
        break;

      default:
        break;
    }
  });

  gameLoop(sceneManager, inputManager, state);
}

auto gameLoop(SceneManager& sceneManager, InputManager& inputManager, ViewerState& viewerState) -> void {
  auto camera = sceneManager.getCamera();
  const Renderer renderer{};

  while (!WindowShouldClose()) {
    inputManager.updateInput();

    sceneManager.reloadIfSceneFileChanged();

    if (viewerState.cameraControlMode) {
      UpdateCamera(&camera, CAMERA_THIRD_PERSON);
      sceneManager.updateCamera(camera);
    }

    renderer.render(sceneManager.getScene(), sceneManager.getCamera());
  }

  CloseWindow();
}