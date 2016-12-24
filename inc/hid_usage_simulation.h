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

#ifndef _USB_HID_USAGE_SIMUL_H_
#define _USB_HID_USAGE_SUMUL_H_
#ifdef __cplusplus
    extern "C" {
#endif


/**\ingroup USB_HID
 * \addtogroup USB_HID_USAGES HID Usage Tables for Simulation
 * \brief Contains USB HID Usages definitions for Simulation Controls Page
 * \details This module based on
 * + [HID Usage Tables Version 1.12](http://www.usb.org/developers/hidpage/Hut1_12v2.pdf)
 * @{ */

#define HID_PAGE_SIMULATION             0x02

#define HID_SIMUL_FLIGHT                0x01
#define HID_SIMUL_AUTOMOBILE            0x02
#define HID_SIMUL_TANK                  0x03
#define HID_SIMUL_SPACESHIP             0x04
#define HID_SIMUL_SUBMARINE             0x05
#define HID_SIMUL_SAILING               0x06
#define HID_SIMUL_MOTOCYCLE             0x07
#define HID_SIMUL_SPORTS                0x08
#define HID_SIMUL_AIRPLANE              0x09
#define HID_SIMUL_HELICOPTER            0x0A
#define HID_SIMUL_MAGIC_CARPET          0x0B
#define HID_SIMUL_BICYCLE               0x0C
#define HID_SIMUL_FLIGHT_CONTROL_STICK  0x20
#define HID_SIMUL_FLIGHT_STICK          0x21
#define HID_SIMUL_CYCLIC_CONTROL        0x22
#define HID_SIMUL_CYCLIC_TRIM           0x23
#define HID_SIMUL_FLIGHT_YOKE           0x24
#define HID_SIMUL_TRACK_CONTROL         0x25
#define HID_SIMUL_ALIERON               0xB0
#define HID_SIMUL_ALIERIN_TRIM          0xB1
#define HID_SIMUL_ANTI_TORQUE           0xB2
#define HID_SIMUL_AUTOPILOT_ENABLE      0xB3
#define HID_SIMUL_CHAFF_RELEASE         0xB4
#define HID_SIMUL_COLLECTIVE_CONTROL    0xB5
#define HID_SIMUL_DRIVE_BRAKE           0xB6
#define HID_SIMUL_ELECTR_COUNTERMEAS    0xB7
#define HID_SIMUL_ELEVATOR              0xB8
#define HID_SIMUL_ELEVATOR_TRIM         0xB9
#define HID_SIMUL_RUDDER                0xBA
#define HID_SIMUL_THROTTLE              0xBB
#define HID_SIMUL_FLIGHT_COMM           0xBC
#define HID_SIMUL_FLARE_RELEASE         0xBD
#define HID_SIMUL_LANDING_GEAR          0xBE
#define HID_SIMUL_TOE_BRAKE             0xBF
#define HID_SIMUL_TRIGGER               0xC0
#define HID_SIMUL_WEAPONS_ARM           0xC1
#define HID_SIMUL_WEAPONS_SELECT        0xC2
#define HID_SIMUL_WING_FLAPS            0xC3
#define HID_SIMUL_ACCELERATOR           0xC4
#define HID_SIMUL_BRAKE                 0xC5
#define HID_SIMUL_CLUTCH                0xC6
#define HID_SIMUL_SHIFTER               0xC7
#define HID_SIMUL_STEERING              0xC8
#define HID_SIMUL_TURRET_DIRECTION      0xC9
#define HID_SIMUL_BARREL_ELEVATION      0xCA
#define HID_SIMUL_DRIVE_PLANE           0xCB
#define HID_SIMUL_BALLAST               0xCC
#define HID_SIMUL_BICYCLE_CRANK         0xCD
#define HID_SIMUL_HANDLE_BARS           0xCE
#define HID_SIMUL_FRONT_BRAKE           0xCF
#define HID_SIMUL_REAR_BRAKE            0xD0

/** @}  */

#ifdef __cplusplus
    }
#endif

#endif

