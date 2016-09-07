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


#ifndef _USB_H_
#define _USB_H_
#if defined(__cplusplus)
    extern "C" {
#endif


#include "inc\usbd_core.h"
#include "inc\usb_std.h"


#if defined(STM32L0)
    extern const struct usbd_driver usb_stml0a;
    #define usb_hw_driver usb_stml0a
#else
    #error "No supported MCU family selected"
#endif



#if defined (__cplusplus)
    }
#endif
#endif //_USB_H_
