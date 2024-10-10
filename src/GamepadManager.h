#ifndef GAMEPAD_MANAGER_H
#define GAMEPAD_MANAGER_H

#include <BleGamepad.h>

class GamepadManager {
public:
  GamepadManager(const char* deviceName, const char* manufacturerName);
  void update(const byte* buttonStates);
  bool isConnected();

private:
  static constexpr uint8_t NUM_OF_BUTTONS = 13;
  static constexpr byte gamepadButtonIds[NUM_OF_BUTTONS] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

  BleGamepad bleGamepad;
  byte previousButtonStates[NUM_OF_BUTTONS] = {0};

  void updateButtonState(byte buttonId, bool pressed);
};

#endif
