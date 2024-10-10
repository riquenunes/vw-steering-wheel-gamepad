#ifndef STEERING_WHEEL_MANAGER_H
#define STEERING_WHEEL_MANAGER_H

#include <TJA1020.hpp>
#include <LIN_master_HardwareSerial_ESP32.h>

class SteeringWheelManager {
public:
  SteeringWheelManager(uint8_t rxPin, uint8_t txPin, uint8_t sleepPin, uint32_t baudRate, uint8_t hornPin);
  byte* readButtonStates();
  void setBacklightsBrightness(uint8_t brightness);
  void flashBacklights(bool isConnected);

private:
  static constexpr uint8_t LIN_LED_CONTROLS_FRAME_ID = 0x0D;
  static constexpr uint8_t LIN_BUTTON_STATE_FRAME_ID = 0x0E;

  static constexpr uint8_t NUM_OF_BUTTONS = 13;
  static constexpr byte linButtonIds[NUM_OF_BUTTONS - 1] = {0x02, 0x03, 0x06, 0x07, 0x09, 0x0A, 0x1A, 0x22, 0x23, 0x28, 0x2A, 0x2B};

  Lin_TJA1020 linBus;
  LIN_Master_HardwareSerial_ESP32 lin;

  uint8_t brightness = 0x00;
  int8_t brightnessDirection = 1;
  unsigned long lastLightUpdateTime = 0;
  static constexpr unsigned long LIGHT_UPDATE_INTERVAL = 5;
  byte buttonStates[NUM_OF_BUTTONS] = {0};
  uint8_t hornPin;
};

#endif
