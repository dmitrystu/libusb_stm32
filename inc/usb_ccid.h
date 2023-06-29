/* This file is the part of the Lightweight USB device Stack for STM32 microcontrollers
 * Reference: https://www.usb.org/sites/default/files/DWG_Smart-Card_CCID_Rev110.pdf
 *
 * Copyright ©2023 Filipe Rodrigues <filipepazrodrigues[at]gmail[dot]com>
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
#include <stdint.h>

#ifndef _USB_CCID_H_
#define _USB_CCID_H_
#ifdef __cplusplus
    extern "C" {
#endif

#define USB_CLASS_CCID                   0x0b    /**<\brief Smart Card Device class */
#define USB_DTYPE_CCID_FUNCTIONAL   0x21   /**<\brief Functional descriptor.*/

#define CCID_CURRENT_SPEC_RELEASE_NUMBER            0x0110
#define CCID_VOLTAGESUPPORT_5V                      0
#define CCID_VOLTAGESUPPORT_3V                      (1 << 0)
#define CCID_VOLTAGESUPPORT_1V8                     (1 << 1)

#define CCID_PROTOCOL_T0                            0
#define CCID_PROTOCOL_T1                            (1 << 0)

#define CCID_ICCSTATUS_PRESENTANDACTIVE             0
#define CCID_ICCSTATUS_PRESENTANDINACTIVE           (1 << 0)
#define CCID_ICCSTATUS_NOICCPRESENT                 (1 << 1)

#define CCID_COMMANDSTATUS_PROCESSEDWITHOUTERROR    0
#define CCID_COMMANDSTATUS_FAILED                   (1 << 6)
#define CCID_COMMANDSTATUS_TIMEEXTENSIONREQUESTED   (1 << 7)

#define CCID_ERROR_NOERROR          0
#define CCID_ERROR_SLOTNOTFOUND     5

#define CCID_ABORT                                  0x1
#define CCID_GET_CLOCK_FREQUENCIES                  0x2
#define CCID_GET_DATA_RATES                         0x3

struct usb_ccid_descriptor {
    uint8_t bLength;                /**<\brief Size of the descriptor, in bytes.*/
    uint8_t bDescriptorType;        /**<\brief IAD descriptor */

    uint16_t                bcdCCID;
    uint8_t                 bMaxSlotIndex;
    uint8_t                 bVoltageSupport;
    uint32_t                dwProtocols;
    uint32_t                dwDefaultClock;
    uint32_t                dwMaximumClock;
    uint8_t                 bNumClockSupported;
    uint32_t                dwDataRate;
    uint32_t                dwMaxDataRate;
    uint8_t                 bNumDataRatesSupported;
    uint32_t                dwMaxIFSD;
    uint32_t                dwSynchProtocols;
    uint32_t                dwMechanical;
    uint32_t                dwFeatures;
    uint32_t                dwMaxCCIDMessageLength;
    uint8_t                 bClassGetResponse;
    uint8_t                 bClassEnvelope;
    uint16_t                wLcdLayout;
    uint8_t                 bPINSupport;
    uint8_t                 bMaxCCIDBusySlots;
} __attribute__((packed));

#ifdef __cplusplus
    }
#endif

#endif
