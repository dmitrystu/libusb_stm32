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

/* Bulk-OUT Messages */
#define PC_TO_RDR_ICCPOWERON                   0x62
#define PC_TO_RDR_ICCPOWEROFF                  0x63
#define PC_TO_RDR_GETSLOTSTATUS                0x65
#define PC_TO_RDR_XFRBLOCK                     0x6F
#define PC_TO_RDR_GETPARAMETERS                0x6C
#define PC_TO_RDR_RESETPARAMETERS              0x6D
#define PC_TO_RDR_SETPARAMETERS                0x61
#define PC_TO_RDR_ESCAPE                       0x6B
#define PC_TO_RDR_ICCCLOCK                     0x6E
#define PC_TO_RDR_T0APDU                       0x6A
#define PC_TO_RDR_SECURE                       0x69
#define PC_TO_RDR_MECHANICAL                   0x71
#define PC_TO_RDR_ABORT                        0x72
#define PC_TO_RDR_SETDATARATEANDCLOCKFREQUENCY 0x73

/* Bulk-IN Messages */
#define RDR_TO_PC_DATABLOCK                    0x80
#define RDR_TO_PC_SLOTSTATUS                   0x81
#define RDR_TO_PC_PARAMETERS                   0x82
#define RDR_TO_PC_ESCAPE                       0x83
#define RDR_TO_PC_DATARATEANDCLOCKFREQUENCY    0x84

/* Interrupt-IN Messages */
#define RDR_TO_PC_NOTIFYSLOTCHANGE             0x50
#define RDR_TO_PC_HARDWAREERROR                0x51


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


/* Bulk-Out Messages*/

struct PC_to_RDR_IccPowerOn {
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 bPowerSelect;
    uint8_t                 abRFU[2];
}  __attribute__((packed));

struct PC_to_RDR_IccPowerOff {
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 abRFU[3];
}  __attribute__((packed));

struct PC_to_RDR_GetSlotStatus {
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 abRFU[3];
}  __attribute__((packed));

struct PC_to_RDR_XfrBlock {
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 bSeq;
    uint8_t                 bBWI;
    uint16_t                wLevelParameter;
    uint8_t                 abData[0];
}  __attribute__((packed));

struct PC_to_RDR_GetParameters {
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 abRFU[3];
}  __attribute__((packed));

struct PC_to_RDR_ResetParameters {
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 abRFU[3];
}  __attribute__((packed));

struct PC_to_RDR_SetParameters_T0 {
    //common
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 bProtocolNum;
    uint8_t                 abRFU[2];

    //specific for T=0
    uint8_t                 bmFindexDindex;
    uint8_t                 bmTCCKST0;
    uint8_t                 bGuardTimeT0;
    uint8_t                 bWaitingIntegerT0;
    uint8_t                 bClockStop;
}  __attribute__((packed));

struct PC_to_RDR_SetParameters_T1 {
    //common
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 bProtocolNum;
    uint8_t                 abRFU[2];

    //specific for T=1
    uint8_t                 bmFindexDindex;
    uint8_t                 bmTCCKST1;
    uint8_t                 bGuardTimeT1;
    uint8_t                 bmWaitingIntegersT1;
    uint8_t                 bClockStop;
    uint8_t                 bIFSC;
    uint8_t                 bNadValue;
}  __attribute__((packed));

struct PC_to_RDR_Escape {
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 abRFU[3];
    uint8_t                 abData[0];
}  __attribute__((packed));

struct PC_to_RDR_IccClock {
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 bClockCommand;
    uint8_t                 abRFU[2];
}  __attribute__((packed));

struct PC_to_RDR_T0APDU {
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 bmChanges;
    uint8_t                 bClassGetResponse;
    uint8_t                 bClassEnvelope;
}  __attribute__((packed));

struct PC_to_RDR_Secure {
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 bBWI;
    uint16_t                wLevelParameter;
    uint8_t                 abData[0];
}  __attribute__((packed));

struct PC_to_RDR_Mechanical {
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 bFunction;
    uint8_t                 abRFU[2];
}  __attribute__((packed));

struct PC_to_RDR_Abort {
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 abRFU[3];
}  __attribute__((packed));

struct PC_to_RDR_SetDataRateAndClockFrequency {
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 abRFU[3];
    uint32_t                dwClockFrequency;
    uint32_t                dwDataRate;
}  __attribute__((packed));

/* Bulk-In Messages*/

struct RDR_to_PC_DataBlock {
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 bStatus;
    uint8_t                 bError;
    uint8_t                 bChainParameter;
    uint8_t                 abData[0];
}  __attribute__((packed));

struct RDR_to_PC_SlotStatus {
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 bStatus;
    uint8_t                 bError;
    uint8_t                 bClockStatus;
}  __attribute__((packed));

struct RDR_to_PC_Parameters_T0 {
    //common
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 bStatus;
    uint8_t                 bError;
    uint8_t                 bProtocolNum;

    //specific for T=0
    uint8_t                 bmFindexDindex;
    uint8_t                 bmTCCKST0;
    uint8_t                 bGuardTimeT0;
    uint8_t                 bWaitingIntegerT0;
    uint8_t                 bClockStop;
}  __attribute__((packed));

struct RDR_to_PC_Parameters_T1 {
    //common
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 bStatus;
    uint8_t                 bError;
    uint8_t                 bProtocolNum;

    //specific for T=1
    uint8_t                 bmFindexDindex;
    uint8_t                 bmTCCKST1;
    uint8_t                 bGuardTimeT1;
    uint8_t                 bmWaitingIntegersT1;
    uint8_t                 bClockStop;
    uint8_t                 bIFSC;
    uint8_t                 bNadValue;
}  __attribute__((packed));

struct RDR_to_PC_Escape {
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 bStatus;
    uint8_t                 bError;
    uint8_t                 bRFU;
    uint8_t                 abData[0];
}  __attribute__((packed));

struct RDR_to_PC_DataRateAndClockFrequency {
    uint8_t                 bMessageType;
    uint32_t                dwLength;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 bStatus;
    uint8_t                 bError;
    uint8_t                 bRFU;
    uint32_t                dwClockFrequency;
    uint32_t                dwDataRate;
}  __attribute__((packed));

/* Interrupt-In Messages*/

struct RDR_to_PC_NotifySlotChange {
    uint8_t                 bMessageType;
    uint8_t                 bmSlotICCState[0];
}  __attribute__((packed));

struct RDR_to_PC_NotifySlotChange {
    uint8_t                 bMessageType;
    uint8_t                 bSlot;
    uint8_t                 bSeq;
    uint8_t                 bHardwareErrorCode;
}  __attribute__((packed));

#ifdef __cplusplus
    }
#endif

#endif
