/* This file is the part of the LUS32 project
 *
 * Copyright ©2016 Dmitry Filimonchuk <dmitrystu[at]gmail[dot]com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _USB_HID_USAGE_DESKTOP_H_
#define _USB_HID_USAGE_DESKTOP_H_
#ifdef __cplusplus
    extern "C" {
#endif


/**\ingroup USB_HID
 * \addtogroup USB_HID_USAGES_DESKTOP HID Usage Tables for Desktop
 * \brief Contains USB HID Usages definitions for Generic Desktop Page
 * \details This module based on
 * + [HID Usage Tables Version 1.12](http://www.usb.org/developers/hidpage/Hut1_12v2.pdf)
 * @{ */

#define HID_PAGE_DESKTOP                0x01

#define HID_DESKTOP_POINTER             0x01
#define HID_DESKTOP_MOUSE               0x02
#define HID_DESKTOP_JOYSTICK            0x04
#define HID_DESKTOP_GAMEPAD             0x05
#define HID_DESKTOP_KEYBOARD            0x06
#define HID_DESKTOP_KEYPAD              0x07
#define HID_DESKTOP_MULTIAXIS           0x08
#define HID_DESKTOP_TABLET              0x09
#define HID_DESKTOP_X                   0x30
#define HID_DESKTOP_Y                   0x31
#define HID_DESKTOP_Z                   0x32
#define HID_DESKTOP_RX                  0x33
#define HID_DESKTOP_RY                  0x34
#define HID_DESKTOP_RZ                  0x35
#define HID_DESKTOP_SLIDER              0x36
#define HID_DESKTOP_DIAL                0x37
#define HID_DESKTOP_WHEEL               0x38
#define HID_DESKTOP_HAT_SWITCH          0x39
#define HID_DESKTOP_COUNTEDBUF          0x3A
#define HID_DESKTOP_BYTECOUNT           0x3B
#define HID_DESKTOP_MOTION_WAKEUP       0x3C
#define HID_DESKTOP_START               0x3D
#define HID_DESKTOP_SELECT              0x3C
#define HID_DESKTOP_VX                  0x40
#define HID_DESKTOP_VY                  0x41
#define HID_DESKTOP_VZ                  0x42
#define HID_DESKTOP_VBRX                0x43
#define HID_DESKTOP_VBRY                0x44
#define HID_DESKTOP_VBRZ                0x45
#define HID_DESKTOP_VNO                 0x46
#define HID_DESKTOP_FEATURE_NOTIFY      0x47
#define HID_DESKTOP_RESOLUTION_MULTIPLY 0x48
#define HID_DESKTOP_SYS_CONTROL         0x80
#define HID_DESKTOP_SYS_PWR_DOWN        0x81
#define HID_DESKTOP_SYS_SLEEP           0x82
#define HID_DESKTOP_SYS_WAKEUP          0x83
#define HID_DESKTOP_SYS_CONTEXT_MENU    0x84
#define HID_DESKTOP_SYS_MAIN_MENU       0x85
#define HID_DESKTOP_SYS_APP_MENU        0x86
#define HID_DESKTOP_SYS_MENU_HELP       0x87
#define HID_DESKTOP_SYS_MENU_EXIT       0x88
#define HID_DESKTOP_SYS_MENU_SELECT     0x89
#define HID_DESKTOP_SYS_MENU_RIGHT      0x8A
#define HID_DESKTOP_SYS_MENU_LEFT       0x8B
#define HID_DESKTOP_SYS_MENU_UP         0x8C
#define HID_DESKTOP_SYS_MENU_DOWN       0x8D
#define HID_DESKTOP_SYS_RESTART_COLD    0x8E
#define HID_DESKTOP_SYS_RESTART_WARM    0x8F
#define HID_DESKTOP_DPAD_UP             0x90
#define HID_DESKTOP_DPAD_DOWN           0x91
#define HID_DESKTOP_DPAD_RIGHT          0x92
#define HID_DESKTOP_DPAD_LEFT           0x93
#define HID_DESKTOP_SYS_DOCK            0xA0
#define HID_DESKTOP_SYS_UNDOCK          0xA1
#define HID_DESKTOP_SYS_STARTUP         0xA2
#define HID_DESKTOP_SYS_BREAK           0xA3
#define HID_DESKTOP_SYS_DBG_BREAK       0xA4
#define HID_DESKTOP_APP_BREAK           0xA5
#define HID_DESKTOP_APP_DBG_BREAK       0xA6
#define HID_DESKTOP_SYS_SPKR_MUTE       0xA7
#define HID_DESKTOP_SYS_HIBERNATE       0xA8
#define HID_DESKTOP_SYS_DISP_INVERT     0xB0
#define HID_DESKTOP_SYS_DISP_INT        0xB1
#define HID_DESKTOP_SYS_DISP_EXT        0xB2
#define HID_DESKTOP_SYS_DISP_BOTH       0xB3
#define HID_DESKTOP_SYS_DISP_DUAL       0xB4
#define HID_DESKTOP_SYS_DISP_TOGGLE     0xB5
#define HID_DESKTOP_SYS_DISP_SWAP       0xB6
#define HID_DESKTOP_SYS_DISP_AUTOSCALE  0xB7

/** @}  */

#ifdef __cplusplus
    }
#endif

#endif

