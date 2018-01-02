/* This file is the part of the Lightweight USB device Stack for STM32 microcontrollers
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

#if defined(STM32L052xx) || defined(STM32L053xx) || \
    defined(STM32L062xx) || defined(STM32L063xx) || \
    defined(STM32L072xx) || defined(STM32L073xx) || \
    defined(STM32L082xx) || defined(STM32L083xx) || \
    defined(STM32L432xx) || defined(STM32L433xx) || \
    defined(STM32L442xx) || defined(STM32L443xx) || \
    defined(STM32L452xx) || defined(STM32L462xx) || \
    defined(STM32F042x6) || defined(STM32F048xx) || \
    defined(STM32F070x6) || defined(STM32F070xB) || \
    defined(STM32F072xB) || defined(STM32F078xx)

    #define USE_STMV0_DRIVER

#elif defined(STM32L1)
    #define USE_STMV1_DRIVER

#elif defined(STM32L476xx)
    #define USE_STMV2_DRIVER

#elif defined(STM32F102x6) || defined(STM32F102xB) || \
      defined(STM32F103x6) || defined(STM32F103xB) || \
      defined(STM32F103xE) || defined(STM32F103xG) || \
      defined(STM32F302x8) || defined(STM32F302xC) || defined(STM32F302xE) || \
      defined(STM32F303xC) || defined(STM32F303xE) || \
      defined(STM32F373xC)

    #define USE_STMV3_DRIVER

#else
    #error Unsupported STM32 family
#endif

#include <stdbool.h>
#include "usbd_core.h"
#if !defined(__ASSEMBLER__)
    #include "usb_std.h"
    #if defined(USE_STMV0_DRIVER) && defined(USBD_ASM_DRIVER)
        extern const struct usbd_driver usb_stmv0a;
        #define usbd_hw usb_stmv0a
    #elif defined(USE_STMV0_DRIVER)
        extern const struct usbd_driver usb_stmv0;
        #define usbd_hw usb_stmv0
    #elif defined(USE_STMV1_DRIVER) && defined(USBD_ASM_DRIVER)
        extern const struct usbd_driver usb_stmv1a;
        #define usbd_hw usb_stmv1a
    #elif defined(USE_STMV1_DRIVER)
        extern const struct usbd_driver usb_stmv1;
        #define usbd_hw usb_stmv1
    #elif defined(USE_STMV2_DRIVER)
        extern const struct usbd_driver usb_stmv2;
        #define usbd_hw usb_stmv2
    #elif defined(USE_STMV3_DRIVER) && defined(USBD_ASM_DRIVER)
        extern const struct usbd_driver usb_stmv3a;
        #define usbd_hw usb_stmv3a
    #elif defined(USE_STMV3_DRIVER)
        extern const struct usbd_driver usb_stmv3;
        #define usbd_hw usb_stmv3
    #endif
#endif

#if defined (__cplusplus)
    }
#endif
#endif //_USB_H_
