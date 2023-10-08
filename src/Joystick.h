/*
  Joystick.h

  Copyright (c) 2015-2017, Matthew Heironimus

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef JOYSTICK_h
#define JOYSTICK_h

#include "DynamicHID/DynamicHID.h"

#if ARDUINO < 10606
#error The Joystick library requires Arduino IDE 1.6.6 or greater. Please update your IDE.
#endif // ARDUINO < 10606

#if ARDUINO > 10606
#if !defined(USBCON)
#error The Joystick library can only be used with a USB MCU (e.g. Arduino Leonardo, Arduino Micro, etc.).
#endif // !defined(USBCON)
#endif // ARDUINO > 10606

#if !defined(_USING_DYNAMIC_HID)

#warning "Using legacy HID core (non pluggable)"

#else // !defined(_USING_DYNAMIC_HID)

//================================================================================
//  Joystick (Gamepad)

#define JOYSTICK_DEFAULT_REPORT_ID         0x03
#define JOYSTICK_DEFAULT_BUTTON_COUNT        32
#define JOYSTICK_DEFAULT_AXIS_MINIMUM         0
#define JOYSTICK_DEFAULT_AXIS_MAXIMUM      1023
#define JOYSTICK_DEFAULT_SIMULATOR_MINIMUM    0
#define JOYSTICK_DEFAULT_SIMULATOR_MAXIMUM 1023
#define JOYSTICK_DEFAULT_HATSWITCH_COUNT      2
#define JOYSTICK_HATSWITCH_COUNT_MAXIMUM      2
#define JOYSTICK_HATSWITCH_RELEASE           -1
#define JOYSTICK_TYPE_JOYSTICK             0x04
#define JOYSTICK_TYPE_GAMEPAD              0x05
#define JOYSTICK_TYPE_MULTI_AXIS           0x08

typedef enum {
  HAT_CENTERED = 0,
  HAT_UP = 1,
  HAT_UP_RIGHT = 2,
  HAT_RIGHT = 3,
  HAT_DOWN_RIGHT = 4,
  HAT_DOWN = 5,
  HAT_DOWN_LEFT = 6,
  HAT_LEFT = 7,
  HAT_UP_LEFT = 8,
} gamepad_hat_t;

typedef struct {
    uint16_t x; // X value of left analog stick
    uint16_t y; // Y value of left analog stick
    uint16_t z; // Value of analog left trigger
    uint16_t rz; // Value of analog right trigger
    uint16_t rx; // X value of right analog stick
    uint16_t ry; // Y value of right analog stick
    uint8_t hat; // Position value of the DPad/hat switch
    uint16_t buttons; // Buttons mask for currently pressed buttons
} gamepad_report_t;

class Joystick_ {
  public:
    Joystick_();

    void begin();
    void end();
    bool ready();
    void resetInputs();
    void sendState();
    
    void pressButton(uint8_t button);
    void releaseButton(uint8_t button);
    void setButton(uint8_t button, bool pressed);
    void setButtons(uint16_t buttons);
    void releaseAllButtons();

    void setLeftXAxis(uint8_t value);
    void setLeftYAxis(uint8_t value);
    void setRightXAxis(uint8_t value);
    void setRightYAxis(uint8_t value);
    void setLeftTrigger(uint8_t value);
    void setRightTrigger(uint8_t value);
    void setHatSwitch(gamepad_hat_t direction);
    void setHatSwitch(bool left, bool right, bool down, bool up);

  protected:
    static const uint8_t _report_id = JOYSTICK_DEFAULT_REPORT_ID;
    static const uint8_t _descriptor[];

    gamepad_report_t _report;

  private:
    static gamepad_hat_t getHatDirection(bool left, bool right, bool down, bool up);
};

#endif // !defined(_USING_DYNAMIC_HID)
#endif // JOYSTICK_h
