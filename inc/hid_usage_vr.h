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

#ifndef _USB_HID_USAGE_VR_H_
#define _USB_HID_USAGE_VR_H_

/**\ingroup USB_HID
 * \addtogroup USB_HID_USAGES_VR HID Usage Tables for VR
 * \brief Contains USB HID Usages definitions for VR Control Page
 * \details This module based on
 * + [HID Usage Tables Version 1.12](http://www.usb.org/developers/hidpage/Hut1_12v2.pdf)
 * @{ */

#define HID_PAGE_VR                     0x03

#define HID_VR_BELT                     0x01
#define HID_VR_BODY_SUIT                0x02
#define HID_VR_FLEXTOR                  0x03
#define HID_VR_GLOVE                    0x04
#define HID_VR_HEAD_TRACKER             0x05
#define HID_VR_HEAD_MOUNTED_DISPLAY     0x06
#define HID_VR_HAND_TRACKER             0x07
#define HID_VR_OCULOMETER               0x08
#define HID_VR_VEST                     0x09
#define HID_VR_ANIMATRONIC_DEVICE       0x0A
#define HID_VR_STEREO_ENABLE            0x20
#define HID_VR_DISPLAY_ENABLE           0x21

/** @}  */

#endif

