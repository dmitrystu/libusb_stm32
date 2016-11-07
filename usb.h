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

#if defined(STM32L0)
    #if defined(FORCE_C_DRIVER)
        #define USE_STMV0_DRIVER
    #elif defined(FORCE_ASM_DRIVER)
        #define USE_STMV0A_DRIVER
    #elif defined(STM32L052xx)
        #define USE_STMV0A_DRIVER
    #else
        #define USE_STMV0_DRIVER
    #endif
#elif defined(STM32L1)
    #if defined(FORCE_C_DRIVER)
        #define USE_STMV1_DRIVER
    #elif defined(FORCE_ASM_DRIVER)
        #define USE_STMV1A_DRIVER
    #elif defined(STM32L100xC)
        #define USE_STMV1A_DRIVER
    #else
        #define USE_STMV1_DRIVER
    #endif
#else
    #error "No supported MCU family selected"
#endif

#include "inc/usbd_core.h"
#if !defined(__ASSEMBLER__)
    #include "inc/usb_std.h"
    #if defined(USE_STMV0A_DRIVER)
        extern const struct usbd_driver usb_stmv0a;
        #define usbd_hw usb_stmv0a
    #elif defined(USE_STMV0_DRIVER)
        extern const struct usbd_driver usb_stmv0;
        #define usbd_hw usb_stmv0
    #elif defined(USE_STMV1_DRIVER)
        extern const struct usbd_driver usb_stmv1;
        #define usbd_hw usb_stmv1
    #elif defined(USE_STMV1A_DRIVER)
        extern const struct usbd_driver usb_stmv1a;
        #define usbd_hw usb_stmv1a
    #endif
#endif

#if defined (__cplusplus)
    }
#endif
#endif //_USB_H_
