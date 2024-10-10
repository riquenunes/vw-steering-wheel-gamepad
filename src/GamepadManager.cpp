#include "GamepadManager.h"

GamepadManager::GamepadManager(const char* deviceName, const char* manufacturerName) :
  bleGamepad(deviceName, manufacturerName) {
  BleGamepadConfiguration bleGamepadConfig;
  bleGamepadConfig.setButtonCount(NUM_OF_BUTTONS);
  bleGamepadConfig.setAutoReport(false);
  bleGamepadConfig.setControllerType(CONTROLLER_TYPE_GAMEPAD);
  bleGamepad.begin(&bleGamepadConfig);
}

void GamepadManager::update(const byte* buttonStates) {
  for (byte i = 0; i < NUM_OF_BUTTONS; i++) {
    if (buttonStates[i] != previousButtonStates[i]) {
      updateButtonState(gamepadButtonIds[i], buttonStates[i]);
    }
  }

  if (memcmp(buttonStates, previousButtonStates, NUM_OF_BUTTONS) != 0) {
    memcpy(previousButtonStates, buttonStates, NUM_OF_BUTTONS);
    bleGamepad.sendReport();
  }
}

bool GamepadManager::isConnected() {
  return bleGamepad.isConnected();
}

void GamepadManager::updateButtonState(byte buttonId, bool pressed) {
  if (pressed) {
    bleGamepad.press(buttonId);
  } else {
    bleGamepad.release(buttonId);
  }
}
