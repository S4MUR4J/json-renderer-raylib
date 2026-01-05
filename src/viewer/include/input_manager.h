#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
#include <functional>

enum class InputEvent {
  TOGGLE_CAMERA_MODE,
  RELOAD_SCENE_REQUESTED,
};

class InputManager {
 public:
  using EventCallback = std::function<void(InputEvent)>;

  InputManager() = default;

  auto updateInput() -> void;
  void setEventCallback(const EventCallback& callback) {
    _eventCallback = callback;
  }

 private:
  auto triggerEvent(InputEvent event) -> void;

  EventCallback _eventCallback;
};

#endif /* INPUT_MANAGER_H */
