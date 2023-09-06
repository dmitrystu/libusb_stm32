/* This file is the part of the Lightweight USB device Stack for STM32 microcontrollers
 *
 * Copyright ©2023 Nikolay Minaylov <nm29719[at]gmail[dot]com>
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

#ifndef _USB_MSC_BULK_H_
#define _USB_MSC_BULK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**@addtogroup USB_MSC_BULK USB MSC (Bulk-Only) class
 * @brief This module contains USB Device Mass Storage (Bulk-Only) Class definitions.
 * @details This module based on
 *          [USB Mass Storage Class – Bulk Only Transport, Revision 1.0]
 *          (https://www.usb.org/sites/default/files/usbmassbulk_10.pdf)
 * @{*/

/**@name USB MSC class, subclass and protocol definitions
 * @{*/
#define USB_CLASS_MASS_STORAGE          0x08 /**<\brief USB MSC class */
#define MSC_MSC_SUBCLASS_RBC            0x01 /**<\brief Reduced block commands */
#define MSC_MSC_SUBCLASS_SFF8020I_MMC2  0x02 /**<\brief ATAPI (CD/DVD, MMC-2) */
#define MSC_MSC_SUBCLASS_QIC157         0x03 /**<\brief QIC-157 tape (Obsolete) */
#define MSC_MSC_SUBCLASS_UFI            0x04 /**<\brief UFI (floppy) */
#define MSC_MSC_SUBCLASS_SFF8070I       0x05 /**<\brief ATAPI SFF-8070i (Obsolete) */
#define MSC_MSC_SUBCLASS_SCSI           0x06 /**<\brief SCSI transparent (SPC-2, rev. 3+)*/
#define USB_MSC_PROTO_BULK              0x50 /**<\brief Bulk-Only protocol */
/** @}*/

/**@name USB MSC requests
 * @{*/
#define USB_MSC_GET_MAX_LUN 0xFE
#define USB_MSC_RESET       0xFF
/** @}*/

/**@name MSC Command Block Wrapper (CBW)
 * @{*/
#define MSC_CBW_SIG                     0x43425355
#define MSC_CBW_FLAGS_DEVICE_TO_HOST    0x80
/** @}*/

/**@name MSC Command Status Wrapper (CSW)
 * @{*/
#define MSC_CSW_SIG                     0x53425355
#define MSC_CSW_STATUS_OK               0
#define MSC_CSW_STATUS_NOK              1
#define MSC_CSW_STATUS_PHASE_ERROR      2
/** @}*/

/**\brief MSC Command Block Wrapper (CBW) struct */
struct usb_msc_cbw {
    uint32_t dSignature;
    uint32_t dTag;
    uint32_t dDataLength;
    uint8_t bmFlags;
    uint8_t bLUN;
    uint8_t bCBLength;
    uint8_t CB[16];
} __attribute__ ((packed));

/**\brief MSC Command Status Wrapper (CSW) struct */
struct usb_msc_csw {
    uint32_t dSignature;
    uint32_t dTag;
    uint32_t dDataResidue;
    uint8_t bStatus;
} __attribute__ ((packed));

/** @}*/

#if defined(__cplusplus)
}
#endif

#endif /* _USB_MSC_BULK_H_ */
