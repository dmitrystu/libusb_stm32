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

#if defined(STM32L052xx) || defined(STM32L053xx) || \
    defined(STM32L062xx) || defined(STM32L063xx) || \
    defined(STM32L072xx) || defined(STM32L073xx) || \
    defined(STM32L082xx) || defined(STM32L083xx) || \
    defined(STM32L432xx) || defined(STM32L433xx) || \
    defined(STM32L442xx) || defined(STM32L443xx) || \
    defined(STM32L452xx) || defined(STM32L462xx) || \
    defined(STM32F042x6) || defined(STM32F048xx) || \
    defined(STM32F070x6) || defined(STM32F070xB) || \
    defined(STM32F072xB) || defined(STM32F078xx) \

    #define USB_EPBASE      0x40005C00
    #define USB_REGBASE     0x40005C40
    #define USB_CNTR        0x00
    #define USB_ISTR        0x04
    #define USB_FNR         0x08
    #define USB_DADDR       0x0C
    #define USB_BTABLE      0x10
    #define USB_BCDR        0x18
    #define USB_PMABASE     0x40006000
    #define RCC_BASE        0x40021000
    #define RCC_APB1RSTR    0x28
    #define RCC_APB1ENR     0x38
    #define UID_BASE        0x1FF80050

#elif defined(STM32L1)
/* common definitions for STM31L100xx STM32L151xx STM32L152xx STM32L162xx */
    #define USB_EPBASE      0x40005C00
    #define USB_REGBASE     0x40005C40
    #define USB_CNTR        0x00
    #define USB_ISTR        0x04
    #define USB_FNR         0x08
    #define USB_DADDR       0x0C
    #define USB_BTABLE      0x10
    #define USB_PMABASE     0x40006000
    #define SYSCFG_BASE     0x40010000
    #define SYSCFG_PMC      0x04
    #define RCC_BASE        0x40023800
    #define RCC_APB1ENR     0x24
    #define RCC_APB1RSTR    0x18
    #define RCC_APB2ENR     0x20
    #if defined(STM32L100xB) || defined(STM32L100xBA) || \
        defined(STM32L151xB) || defined(STM32L151xBA)
    /* Cat.1 and Cat.2 devices */
        #define UID_BASE        0x1FF80050
    #else
        #define UID_BASE        0x1FF800D0
    #endif
#else
    #error Unsupported MCU
#endif


