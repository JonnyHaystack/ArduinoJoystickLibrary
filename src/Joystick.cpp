/*
  Joystick.cpp

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

#include "Joystick.h"

#if defined(_USING_DYNAMIC_HID)

#define JOYSTICK_REPORT_ID_INDEX 7
#define JOYSTICK_AXIS_MINIMUM 0
#define JOYSTICK_AXIS_MAXIMUM 65535
#define JOYSTICK_SIMULATOR_MINIMUM 0
#define JOYSTICK_SIMULATOR_MAXIMUM 65535

#define JOYSTICK_INCLUDE_X_AXIS B00000001
#define JOYSTICK_INCLUDE_Y_AXIS B00000010
#define JOYSTICK_INCLUDE_Z_AXIS B00000100
#define JOYSTICK_INCLUDE_RX_AXIS B00001000
#define JOYSTICK_INCLUDE_RY_AXIS B00010000
#define JOYSTICK_INCLUDE_RZ_AXIS B00100000

#define JOYSTICK_INCLUDE_RUDDER B00000001
#define JOYSTICK_INCLUDE_THROTTLE B00000010
#define JOYSTICK_INCLUDE_ACCELERATOR B00000100
#define JOYSTICK_INCLUDE_BRAKE B00001000
#define JOYSTICK_INCLUDE_STEERING B00010000

// clang-format off

PROGMEM const uint8_t Joystick_::_descriptor[] = {
	0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
	0x09, 0x05,        // Usage (Game Pad)
	0xA1, 0x01,        // Collection (Application)
	0x85, _report_id,  //   Report ID (Default 3)
	0x05, 0x01,        //   Usage Page (Generic Desktop Ctrls)
	0x09, 0x30,        //   Usage (X)
	0x09, 0x31,        //   Usage (Y)
	0x09, 0x32,        //   Usage (Z)
	0x09, 0x35,        //   Usage (Rz)
	0x09, 0x33,        //   Usage (Rx)
	0x09, 0x34,        //   Usage (Ry)
	0x15, 0x00,        //   Logical Minimum (0)
	0x27, 0xFF, 0xFF, 0x00, 0x00,  //   Logical Maximum (65534)
	0x95, 0x06,        //   Report Count (6)
	0x75, 0x10,        //   Report Size (16)
	0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x05, 0x01,        //   Usage Page (Generic Desktop Ctrls)
	0x09, 0x39,        //   Usage (Hat switch)
	0x15, 0x01,        //   Logical Minimum (1)
	0x25, 0x08,        //   Logical Maximum (8)
	0x35, 0x00,        //   Physical Minimum (0)
	0x46, 0x3B, 0x01,  //   Physical Maximum (315)
	0x95, 0x01,        //   Report Count (1)
	0x75, 0x08,        //   Report Size (8)
	0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x05, 0x09,        //   Usage Page (Button)
	0x19, 0x01,        //   Usage Minimum (0x01)
	0x29, 0x10,        //   Usage Maximum (0x10)
	0x15, 0x00,        //   Logical Minimum (0)
	0x25, 0x01,        //   Logical Maximum (1)
	0x95, 0x10,        //   Report Count (16)
	0x75, 0x01,        //   Report Size (1)
	0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0xC0,              // End Collection
	0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
	0x09, 0x06,        // Usage (Keyboard)
	0xA1, 0x01,        // Collection (Application)
	0x85, 0x02,        //   Report ID (2)
	0x05, 0x07,        //   Usage Page (Kbrd/Keypad)
	0x19, 0xE0,        //   Usage Minimum (0xE0)
	0x29, 0xE7,        //   Usage Maximum (0xE7)
	0x15, 0x00,        //   Logical Minimum (0)
	0x25, 0x01,        //   Logical Maximum (1)
	0x95, 0x08,        //   Report Count (8)
	0x75, 0x01,        //   Report Size (1)
	0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x95, 0x01,        //   Report Count (1)
	0x75, 0x08,        //   Report Size (8)
	0x81, 0x01,        //   Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x05, 0x08,        //   Usage Page (LEDs)
	0x19, 0x01,        //   Usage Minimum (Num Lock)
	0x29, 0x05,        //   Usage Maximum (Kana)
	0x95, 0x05,        //   Report Count (5)
	0x75, 0x01,        //   Report Size (1)
	0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0x95, 0x01,        //   Report Count (1)
	0x75, 0x03,        //   Report Size (3)
	0x91, 0x01,        //   Output (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0x05, 0x07,        //   Usage Page (Kbrd/Keypad)
	0x19, 0x00,        //   Usage Minimum (0x00)
	0x2A, 0xFF, 0x00,  //   Usage Maximum (0xFF)
	0x15, 0x00,        //   Logical Minimum (0)
	0x26, 0xFF, 0x00,  //   Logical Maximum (255)
	0x95, 0x06,        //   Report Count (6)
	0x75, 0x08,        //   Report Size (8)
	0x81, 0x00,        //   Input (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0xC0,              // End Collection
}; // 138 bytes

// clang-format on

Joystick_::Joystick_() {}

void Joystick_::begin() {
    // Register HID Report Descriptor
    DynamicHIDSubDescriptor *node =
        new DynamicHIDSubDescriptor(_descriptor, sizeof(_descriptor), true);
    DynamicHID().AppendDescriptor(node);

    // Initialize Joystick State
    resetInputs();
}

void Joystick_::end() {
    resetInputs();
}

bool Joystick_::ready() {
    return DynamicHID().SendSpace() > sizeof(gamepad_report_t);
}

void Joystick_::sendState() {
    while (!ready()) {}

    DynamicHID().SendReport(_report_id, &_report, sizeof(gamepad_report_t));
}

void Joystick_::resetInputs() {
    releaseAllButtons();
    setLeftXAxis(128);
    setLeftYAxis(128);
    setRightXAxis(128);
    setRightYAxis(128);
    setLeftTrigger(0);
    setRightTrigger(0);
}

void Joystick_::pressButton(uint8_t button) {
    bitSet(_report.buttons, button);
}

void Joystick_::releaseButton(uint8_t button) {
    bitClear(_report.buttons, button);
}

void Joystick_::setButton(uint8_t button, bool pressed) {
    if (pressed) {
        pressButton(button);
    } else {
        releaseButton(button);
    }
}

void Joystick_::releaseAllButtons() {
    setButtons(0);
}

void Joystick_::setButtons(uint16_t buttons) {
    _report.buttons = buttons;
}

void Joystick_::setLeftXAxis(uint8_t value) {
    _report.x = value * 257;
}

void Joystick_::setLeftYAxis(uint8_t value) {
    _report.y = value * 257;
}

void Joystick_::setRightXAxis(uint8_t value) {
    _report.rx = value * 257;
}

void Joystick_::setRightYAxis(uint8_t value) {
    _report.ry = value * 257;
}

void Joystick_::setLeftTrigger(uint8_t value) {
    _report.z = value * 257;
}

void Joystick_::setRightTrigger(uint8_t value) {
    _report.rz = value * 257;
}

void Joystick_::setHatSwitch(gamepad_hat_t direction) {
    _report.hat = direction;
}

void Joystick_::setHatSwitch(bool left, bool right, bool down, bool up) {
    _report.hat = getHatDirection(left, right, down, up);
}

gamepad_hat_t Joystick_::getHatDirection(bool left, bool right, bool down, bool up) {
    gamepad_hat_t angle = HAT_CENTERED;
    if (right && !left) {
        angle = HAT_RIGHT;
        if (down)
            angle = HAT_DOWN_RIGHT;
        if (up)
            angle = HAT_UP_RIGHT;
    } else if (left && !right) {
        angle = HAT_LEFT;
        if (down)
            angle = HAT_DOWN_LEFT;
        if (up)
            angle = HAT_UP_LEFT;
    } else if (down && !up) {
        angle = HAT_DOWN;
    } else if (up && !down) {
        angle = HAT_UP;
    }
    return angle;
}

#endif
