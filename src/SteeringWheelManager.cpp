#include "SteeringWheelManager.h"
#include <Arduino.h>

#define SKIP_CONSOLE

void debugPrint(const char* format, ...) {
  #ifndef SKIP_CONSOLE
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  #endif
}

SteeringWheelManager::SteeringWheelManager(uint8_t rxPin, uint8_t txPin, uint8_t sleepPin, uint32_t baudRate, uint8_t hornPin) :
  linBus(2, baudRate, rxPin, txPin, sleepPin, Lin_TJA1020::Mode::LowSlope),
  lin(linBus, rxPin, txPin, "LIN_HW"),
  hornPin(hornPin)
{
  lin.begin(baudRate);
  pinMode(hornPin, INPUT_PULLUP);
}

byte* SteeringWheelManager::readButtonStates() {
  uint8_t linFrameData[8];
  lin.resetStateMachine();
  lin.resetError();

  LIN_Master::error_t error = lin.receiveSlaveResponseBlocking(LIN_Master::LIN_V2, LIN_BUTTON_STATE_FRAME_ID, 8, linFrameData);
  if (error != LIN_Master::NO_ERROR) {
    debugPrint("LIN Receive error = 0x%02X\n", error);
    return nullptr;
  }

  for (byte i = 0; i < NUM_OF_BUTTONS - 1; i++) {
    // button state is the second byte of the 0x0E frame
    buttonStates[i] = linFrameData[1] == linButtonIds[i];
  }

  buttonStates[NUM_OF_BUTTONS - 1] = !digitalRead(hornPin);

  return buttonStates;
}

void SteeringWheelManager::setBacklightsBrightness(uint8_t brightness) {
  // for some reason we always need to send a second byte with 0xFF, otherwise the steering wheel stops reporting button states
  uint8_t data[2] = {brightness, 0xFF};
  lin.resetStateMachine();
  lin.resetError();
  LIN_Master::error_t error = lin.sendMasterRequestBlocking(LIN_Master::LIN_V2, LIN_LED_CONTROLS_FRAME_ID, 2, data);
  if (error != LIN_Master::NO_ERROR) {
    debugPrint("LIN Request error = 0x%02X\n", error);
  }
}

void SteeringWheelManager::flashBacklights(bool isConnected) {
  unsigned long currentTime = millis();

  if (!isConnected && (currentTime - lastLightUpdateTime >= LIGHT_UPDATE_INTERVAL)) {
    brightness += brightnessDirection;
    if (brightness >= 0x7F || brightness == 0x00) {
      brightnessDirection = -brightnessDirection;
    }
    setBacklightsBrightness(brightness);
    lastLightUpdateTime = currentTime;
  } else if (isConnected && brightness != 0x00) {
    setBacklightsBrightness(0x00);
    brightness = 0x00;
    brightnessDirection = 1;
  }
}
