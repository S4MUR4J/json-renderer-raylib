#include "input_manager.h"

#include "raylib.h"

auto InputManager::updateInput() -> void {
  if (IsKeyPressed((KEY_E))) {
    triggerEvent(InputEvent::TOGGLE_CAMERA_MODE);
  }
}

// ReSharper disable once CppMemberFunctionMayBeConst
auto InputManager::triggerEvent(const InputEvent event) -> void {
  if (_eventCallback) {
    _eventCallback(event);
  }
}