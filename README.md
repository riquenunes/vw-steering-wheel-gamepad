## Volkswagen Steering Wheel Gamepad

This project turns a Volkswagen steering wheel with LIN bus communication into a Bluetooth gamepad for use with various devices (phones, computers, etc.). It reads button presses from the steering wheel, including the horn, and sends them as gamepad events over Bluetooth Low Energy (BLE).

### Features

* Reads button states from a Volkswagen steering wheel via LIN bus.
* Includes support for a dedicated horn button.
* Transmits button presses as a BLE gamepad.
* Controls the steering wheel backlight with multiple brightness levels.
* Designed with reusable components for easy integration into other projects.

### Hardware Requirements

* ESP32 development board
* Volkswagen steering wheel with LIN bus. I tested it with a VW Up! steering wheel, but it should probably work with any PQ24/PQ25 steering wheels
* TJA1020/TJA1021/SIT1021T LIN transceiver
