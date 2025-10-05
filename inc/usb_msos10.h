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

#ifndef _USB_MSOS10_H_
#define _USB_MSOS10_H_

#ifdef __cplusplus
    extern "C" {
#endif


#define USB_MS_INDEX                0xEE    // MS OS string descriptor index
#define USB_MS_GET_DESCRIPTOR       0x69


/// @brief MS OS String descriptor
struct usb_msos_descriptor {
    uint8_t     bLength;            //< Size of the descriptor in bytes
    uint8_t     bDescriptorType;    //< USB_DTYPE_STRING
    uint16_t    qwSignature[7];     //< Signature field 'MSFT100'
    uint8_t     bMS_VendorCode;     //< Vendor Code
    uint8_t     bPad;               //< Pad field (0x00)
} __attribute__((packed));

#define USB_MS_MSFT100   {0x004D, 0x0053, 0x0046, 0x0054, 0x0031, 0x0030, 0x0030}



struct usb_ms_extcompatid_header {
    uint32_t    dwLength;           //< The length of the entire descriptor,
                                    //  including the header section. Windows
                                    //  uses this value to retrieve the complete
                                    //  descriptor.
    uint16_t    bcdVersion;
    uint16_t    wIndex;             //< An index that identifies the particular
                                    //  OS feature descriptor
    uint8_t     bCount;             //< Number of the Extended compat functions
    uint8_t     baReserved[7];      //< Reserved. Must be 0
} __attribute__((packed));

#define USB_MS_GENRE_ID             0x01 //< Genre ID descriptor
#define USB_MS_EXTCOMAPT_ID         0x04 //< Extended compat ID descriptor
#define USB_MS_EXTPROPERTY_ID       0x05 //< Extended property ID descriptor

struct usb_ms_extcompatid_function {
    uint8_t     bFirstInterfaceNum;
    uint8_t     bReserved;          //< Reserved. Set this value to 0x01.
    uint8_t     baCompatibleID[8];
    uint8_t     baSubCompatibleID[8];
    uint8_t     baReserved[6];      //< Reserved. Fill this value with NULLs.
} __attribute__((packed));

#define USB_MS_COMPID_NONE      {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
#define USB_MS_COMPID_RNDIS     {0x52, 0x4E, 0x44, 0x49, 0x53, 0x00, 0x00, 0x00}
#define USB_MS_COMPID_PTP       {0x50, 0x54, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00}
#define USB_MS_COMPID_MTP       {0x4D, 0x54, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00}
#define USB_MS_COMPID_XUSB20    {0x58, 0x55, 0x53, 0x42, 0x32, 0x30, 0x00, 0x00}
#define USB_MS_COMPID_BLUETOOTH {0x42, 0x4C, 0x55, 0x54, 0x55, 0x54, 0x48, 0x00}
#define USB_MS_COMPID_WINUSB    {'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00}
#define USB_MS_COMPID_LIBUSB0   {'L', 'I', 'B', 'U', 'S', 'B', '0', 0x00}
#define USB_MS_COMPID_LIBUSBK   {'L', 'I', 'B', 'U', 'S', 'B', 'K', 0x00}
#define USB_MS_SUBCOMPID_BT11   {0x31, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
#define USB_MS_SUBCOMPID_BT12   {0x31, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
#define USB_MS_SUBCOMPID_BTEDR  {0x45, 0x44, 0x52, 0x00, 0x00, 0x00, 0x00, 0x00}


#define USB_MS_PTYPE_RESERVED   0x00    //<
#define USB_MS_PTYPE_REGSZ      0x01    //< NULL-terminated Unicode String (REG_SZ)
#define USB_MS_PTYPE_REGEXSZ    0x02    //< NULL-terminated Unicode String that
                                        //  includes environment variables (REG_EXPAND_SZ)
#define USB_MS_PTYPE_REGBINARY  0x03    //< Free-form binary (REG_BINARY)
#define USB_MS_PTYPE_REGDWLE    0x04    //< A little-endian 32-bit integer (REG_DWORD_LITTLE_ENDIAN)
#define USB_MS_PTYPE_REGDWBE    0x05    //< A big-endian 32-bit integer (REG_DWORD_BIG_ENDIAN)
#define USB_MS_PTYPE_REGLINK    0x06    //< A NULL-terminated Unicode string that contains a symbolic link (REG_LINK)
#define USB_MS_PTYPE_REGMULTISZ 0x07    //< Multiple NULL-terminated Unicode strings (REG_MULTI_SZ)

#define USB_MS_PNAME_IFACEGUID  u"DeviceInterfaceGUID"


struct usb_ms_extproperty_header {
    uint32_t    dwLength;
    uint16_t    bcdVersion;
    uint16_t    wIndex;
    uint16_t    wCount;
} __attribute__((packed));

struct usb_ms_extproperty_name {
    uint32_t    dwSize;
    uint32_t    dwDataType;
    uint16_t    wNameLength;
    uint16_t    wName[];
} __attribute__((packed));

struct usb_ms_extproperty_data {
    uint32_t    dwDataLength;
    uint8_t     baData[];
} __attribute__((packed));

#define construct_ms_propu_desc(id, name, prop) \
struct {\
    uint32_t dwSize;\
    uint32_t dwDataType;\
    uint16_t wNameLength;\
    uint16_t wName[sizeof(name)/2];\
    uint32_t dwDataLength;\
    uint16_t baData[sizeof(prop)/2];\
} __attribute__((packed)) id

#define construct_ms_propb_desc(id, name, prop) \
struct {\
    uint32_t dwSize;\
    uint32_t dwDataType;\
    uint16_t wNameLength;\
    uint16_t wName[sizeof(name)/2];\
    uint32_t dwDataLength;\
    uint8_t  baData[sizeof(prop)];\
} __attribute__((packed)) id

#define construct_ms_propi_desc(id, name, prop) \
struct {\
    uint32_t dwSize;\
    uint32_t dwDataType;\
    uint16_t wNameLength;\
    uint16_t wName[sizeof(name)];\
    uint32_t dwDataLength;\
    uint32_t baData;\
} __attribute__((packed)) id




#ifdef __cplusplus
    }
#endif

#endif /* _USB_MSOS10_H_ */
