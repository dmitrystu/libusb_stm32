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

#ifndef _USB_STD_H_
#define _USB_STD_H_
#if defined(__cplusplus)
extern "C" {
#endif

/**\addtogroup USB_STD USB Standard
 * \brief This module contains generic USB device framework definitions
 * \details This module based on
 * + Chapter 9 of the [Universal Serial Bus Specification Revision 2.0](http://www.usb.org/developers/docs/usb20_docs/usb_20_080416.zip)
 * + [LUFA - the Lightweight USB Framework for AVRs.](https://github.com/abcminiuser/lufa)
 * @{
 *\name Utility functional macros
 * @{ */
/** Macro to encode major/minor/version number into BCD code
 * \param maj Major version
 * \param min Minor version
 * \param rev Revision
 */
#define VERSION_BCD(maj, min, rev)  (((maj & 0xFF) << 8) | ((min & 0x0F) << 4) | (rev & 0x0F))

/** Macro to create \ref usb_string_descriptor from array of characters */
#define USB_STRING_DESC(...)        {.bLength = 2 + sizeof((uint16_t[]){__VA_ARGS__}), .bDescriptorType = USB_DTYPE_STRING, .wString = {__VA_ARGS__}}

/**\brief Macro to */
#define USB_CFG_POWER_MA(mA)        ((mA) >> 1)
/** @} */

/**\name USB device configuration definitions
 * @{ */
#define USB_CFG_ATTR_RESERVED       0x80
#define USB_CFG_ATTR_SELFPOWERED    0x40
/** @} */

/** \anchor USB_ENDPOINT_DEF
 *  \name USB endpoint attributes definitions
 * @{ */
#define USB_EPTYPE_CONTROL          0x00
#define USB_EPTYPE_ISOCHRONUS       0x01
#define USB_EPTYPE_BULK             0x02
#define USB_EPTYPE_INTERRUPT        0x03
#define USB_EPATTR_NO_SYNC          0x00
#define USB_EPATTR_ASYNC            0x04
#define USB_EPATTR_ADAPTIVE         0x08
#define USB_EPATTR_SYNC             0x0C
#define USB_EPUSAGE_DATA            0x00
#define USB_EPUSAGE_FEEDBACK        0x10
#define USB_EPUSAGE_IMP_FEEDBACK    0x20
/** @} */

/**\name Special string descriptor indexes
 * @{ */
#define NO_DESCRIPTOR               0x00    /**< \brief Indicates that a given string descriptor doesn't exists in the device */
#define INTSERIALNO_DESCRIPTOR      0xFE    /**< \brief Indicates that a given string descriptor is a internal serial number provided by hardware driver */
/** @} */

/**\name USB class definitions
 * @{ */
#define USB_CLASS_PER_INTERFACE     0x00 /**< Class defined on interface level */
#define USB_SUBCLASS_NONE           0x00
#define USB_PROTO_NONE              0x00
#define USB_CLASS_AUDIO             0x01 /**< Interface belongs to the Audio device class. */
#define USB_CLASS_PHYSICAL          0x05 /**< Interface belongs to the Physical device class. */
#define USB_CLASS_STILL_IMAGE       0x06 /**< Interface belongs to the Still Imaging device class. */
#define USB_CLASS_PRINTER           0x07 /**< Interface belongs to the Printer device class. */
#define USB_CLASS_MASS_STORAGE      0x08 /**< Interface belongs to the Mass Storage device class. */
#define USB_CLASS_HUB               0x09 /**< Device belongs to the HUB device class. */
#define USB_CLASS_CSCID             0x0B /**< Interface belongs to the Smart Card device class. */
#define USB_CLASS_CONTENT_SEC       0x0D /**< Interface belongs to the Content Security device class. */
#define USB_CLASS_VIDEO             0x0E /**< Interface belongs to the Video device class. */
#define USB_CLASS_HEALTHCARE        0x0F /**< Interface belongs to the Personal Healthcare device class. */
#define USB_CLASS_AV                0x10 /**< Interface belongs to the Audio/Video device class. */
#define USB_CLASS_BILLBOARD         0x11 /**< Device belongs to the Billboard device class. */
#define USB_CLASS_CBRIDGE           0x12 /**< Interface belongs to the USB Type-C Bridge device class. */
#define USB_CLASS_DIAGNOSTIC        0xDC /**< Device/Interface belongs to the Diagnostic device class. */
#define USB_CLASS_WIRELESS          0xE0 /**< Interface belongs to the Wireless controller class. */
#define USB_CLASS_MISC              0xEF /**< Device/Interface belongs to the Miscellanious device class. */
#define USB_CLASS_APP_SPEC          0xFE /**< Interface belongs to the Application Specific class. */
#define USB_CLASS_VENDOR            0xFF /**< Device belongs to a vendor specific class. */
#define USB_SUBCLASS_VENDOR         0xFF /**< Subclass belongs to a vendor specific subclass. */
#define USB_PROTO_VENDOR            0xFF /**< Protocol belongs to a vendor specific protocol. */
/** @} */

/**\name USB Standard descriptor types
 * @{ */
#define USB_DTYPE_DEVICE            0x01 /**< Indicates that the descriptor is a \ref usb_device_descriptor*/
#define USB_DTYPE_CONFIGURATION     0x02 /**< Indicates that the descriptor is a \ref usb_config_descriptor */
#define USB_DTYPE_STRING            0x03 /**< Indicates that the descriptor is a \ref usb_string_descriptor */
#define USB_DTYPE_INTERFACE         0x04 /**< Indicates that the descriptor is a \ref usb_interface_descriptor */
#define USB_DTYPE_ENDPOINT          0x05 /**< Indicates that the descriptor is an endpoint descriptor. */
#define USB_DTYPE_QUALIFIER         0x06 /**< Indicates that the descriptor is a \ref usb_qualifier_descriptor */
#define USB_DTYPE_OTHER             0x07 /**< Indicates that the descriptor is of other type. */
#define USB_DTYPE_INTERFACEPOWER    0x08 /**< Indicates that the descriptor is an interface power descriptor. */
#define USB_DTYPE_OTG               0x09 /**< Indicates that the descroptor is an OTG descriptor */
#define USB_DTYPE_DEBUG             0x0A /**< Indicates that the descriptor is a Debug descriptor */
#define USB_DTYPE_INTERFASEASSOC    0x0B /**< Indicates that the descriptor is an interface association descriptor. */
#define USB_DTYPE_CS_INTERFACE      0x24 /**< Indicates that the descriptor is a class specific interface descriptor. */
#define USB_DTYPE_CS_ENDPOINT       0x25 /**< Indicates that the descriptor is a class specific endpoint descriptor. */
/** @} */

/**\name USB Standard requests
 * @{ */
#define USB_STD_GET_STATUS          0x00 /**< This request returns status for the specified recipient */
#define USB_STD_CLEAR_FEATURE       0x01 /**< This request is used to clear or disable a specific feature */
#define USB_STD_SET_FEATURE         0x03 /**< This request is used to set or enable a specific feature */
#define USB_STD_SET_ADDRESS         0x05 /**< This request sets the device address for all future device accesses */
#define USB_STD_GET_DESCRIPTOR      0x06 /**< This request returns the specified descriptor if the descriptor exists */
#define USB_STD_SET_DESCRIPTOR      0x07 /**< This request is optional and may be used to update existing descriptors or new descriptors may be added */
#define USB_STD_GET_CONFIG          0x08 /**< This request returns the current device configuration value */
#define USB_STD_SET_CONFIG          0x09 /**< This request sets the device configuration */
#define USB_STD_GET_INTERFACE       0x0A /**< This request returns the selected alternate setting for the specified interface */
#define USB_STD_SET_INTERFACE       0x0B /**< This request allows the host to select an alternate setting for the specified interface */
#define USB_STD_SYNCH_FRAME         0x0C /**< This request is used to set and then report an endpoint's synchronization frame */
/** @} */

/** \brief USB standard LANGID codes */
enum usb_std_langid_codes {
    USB_LANGID_AFR      = 0x0436,   /**< Afrikaans */
    USB_LANGID_SQI      = 0x041c,   /**< Albanian */
    USB_LANGID_ARA_SA   = 0x0401,   /**< Arabic (Saudi Arabia) */
    USB_LANGID_ARA_IQ   = 0x0801,   /**< Arabic (Iraq) */
    USB_LANGID_ARA_EG   = 0x0c01,   /**< Arabic (Egypt) */
    USB_LANGID_ARA_LY   = 0x1001,   /**< Arabic (Libya) */
    USB_LANGID_ARA_DZ   = 0x1401,   /**< Arabic (Algeria) */
    USB_LANGID_ARA_MA   = 0x1801,   /**< Arabic (Morocco) */
    USB_LANGID_ARA_TN   = 0x1c01,   /**< Arabic (Tunisia) */
    USB_LANGID_ARA_OM   = 0x2001,   /**< Arabic (Oman) */
    USB_LANGID_ARA_YE   = 0x2401,   /**< Arabic (Yemen) */
    USB_LANGID_ARA_SY   = 0x2801,   /**< Arabic (Syria) */
    USB_LANGID_ARA_JO   = 0x2c01,   /**< Arabic (Jordan) */
    USB_LANGID_ARA_LB   = 0x3001,   /**< Arabic (Lebanon) */
    USB_LANGID_ARA_KW   = 0x3401,   /**< Arabic (Kuwait) */
    USB_LANGID_ARA_AE   = 0x3801,   /**< Arabic (U.A.E.) */
    USB_LANGID_ARA_BH   = 0x3c01,   /**< Arabic (Bahrain) */
    USB_LANGID_ARA_QA   = 0x4001,   /**< Arabic (Qatar) */
    USB_LANGID_HYE      = 0x042b,   /**< Armenian */
    USB_LANGID_ASM      = 0x044d,   /**< Assamese */
    USB_LANGID_AZE_LAT  = 0x042c,   /**< Azeri (Latin) */
    USB_LANGID_AZE_CYR  = 0x082c,   /**< Azeri (Cyrillic) */
    USB_LANGID_EUS      = 0x042d,   /**< Basque */
    USB_LANGID_BEL      = 0x0423,   /**< Belarussian */
    USB_LANGID_BEN      = 0x0445,   /**< Bengali */
    USB_LANGID_BUL      = 0x0402,   /**< Bulgarian */
    USB_LANGID_MYA      = 0x0455,   /**< Burmese */
    USB_LANGID_CAT      = 0x0403,   /**< Catalan */
    USB_LANGID_ZHO_TW   = 0x0404,   /**< Chinese (Taiwan) */
    USB_LANGID_ZHO_CN   = 0x0804,   /**< Chinese (PRC) */
    USB_LANGID_ZHO_HK   = 0x0c04,   /**< Chinese (Hong Kong SAR, PRC) */
    USB_LANGID_ZHO_SG   = 0x1004,   /**< Chinese (Singapore) */
    USB_LANGID_ZHO_MO   = 0x1404,   /**< Chinese (Macau SAR) */
    USB_LANGID_HRV      = 0x041a,   /**< Croatian */
    USB_LANGID_CZE      = 0x0405,   /**< Czech */
    USB_LANGID_DAN      = 0x0406,   /**< Danish */
    USB_LANGID_NLD_NL   = 0x0413,   /**< Dutch (Netherlands) */
    USB_LANGID_NLD_BE   = 0x0813,   /**< Dutch (Belgium) */
    USB_LANGID_ENG_US   = 0x0409,   /**< English (United States) */
    USB_LANGID_ENG_UK   = 0x0809,   /**< English (United Kingdom) */
    USB_LANGID_ENG_AU   = 0x0c09,   /**< English (Australian) */
    USB_LANGID_ENG_CA   = 0x1009,   /**< English (Canadian) */
    USB_LANGID_ENG_NZ   = 0x1409,   /**< English (New Zealand) */
    USB_LANGID_ENG_IE   = 0x1809,   /**< English (Ireland) */
    USB_LANGID_ENG_ZA   = 0x1c09,   /**< English (South Africa) */
    USB_LANGID_ENG_JM   = 0x2009,   /**< English (Jamaica) */
    USB_LANGID_ENG_CAR  = 0x2409,   /**< English (Caribbean) */
    USB_LANGID_ENG_BZ   = 0x2809,   /**< English (Belize) */
    USB_LANGID_ENG_TH   = 0x2c09,   /**< English (Trinidad) */
    USB_LANGID_ENG_ZW   = 0x3009,   /**< English (Zimbabwe) */
    USB_LANGID_ENG_PH   = 0x3409,   /**< English (Philippines) */
    USB_LANGID_EST      = 0x0425,   /**< Estonian */
    USB_LANGID_FAO      = 0x0438,   /**< Faeroese */
    USB_LANGID_FAS      = 0x0429,   /**< Farsi */
    USB_LANGID_FIN      = 0x040b,   /**< Finnish */
    USB_LANGID_FRA      = 0x040c,   /**< French (Standard) */
    USB_LANGID_FRA_BE   = 0x080c,   /**< French (Belgian) */
    USB_LANGID_FRA_CA   = 0x0c0c,   /**< French (Canadian) */
    USB_LANGID_FRA_SZ   = 0x100c,   /**< French (Switzerland) */
    USB_LANGID_FRA_LU   = 0x140c,   /**< French (Luxembourg) */
    USB_LANGID_FRA_MC   = 0x180c,   /**< French (Monaco) */
    USB_LANGID_KAT      = 0x0437,   /**< Georgian */
    USB_LANGID_DEU      = 0x0407,   /**< German (Standard) */
    USB_LANGID_DEU_SZ   = 0x0807,   /**< German (Switzerland) */
    USB_LANGID_DEU_AT   = 0x0c07,   /**< German (Austria) */
    USB_LANGID_DEU_LU   = 0x1007,   /**< German (Luxembourg) */
    USB_LANGID_DEU_LI   = 0x1407,   /**< German (Liechtenstein) */
    USB_LANGID_ELL      = 0x0408,   /**< Greek */
    USB_LANGID_GUJ      = 0x0447,   /**< Gujarati */
    USB_LANGID_HEB      = 0x040d,   /**< Hebrew */
    USB_LANGID_HIN      = 0x0439,   /**< Hindi */
    USB_LANGID_HUN      = 0x040e,   /**< Hungarian */
    USB_LANGID_ISL      = 0x040f,   /**< Icelandic */
    USB_LANGID_IND      = 0x0421,   /**< Indonesian */
    USB_LANGID_ITA      = 0x0410,   /**< Italian (Standard) */
    USB_LANGID_ITA_SZ   = 0x0810,   /**< Italian (Switzerland) */
    USB_LANGID_JPN      = 0x0411,   /**< Japanese */
    USB_LANGID_KAN      = 0x044b,   /**< Kannada */
    USB_LANGID_KAS      = 0x0860,   /**< Kashmiri (India) */
    USB_LANGID_KAZ      = 0x043f,   /**< Kazakh */
    USB_LANGID_KOK      = 0x0457,   /**< Konkani */
    USB_LANGID_KOR      = 0x0412,   /**< Korean */
    USB_LANGID_KOR_JOH  = 0x0812,   /**< Korean (Johab) */
    USB_LANGID_LAV      = 0x0426,   /**< Latvian */
    USB_LANGID_LIT      = 0x0427,   /**< Lithuanian */
    USB_LANGID_LIT_CLS  = 0x0827,   /**< Lithuanian (Classic) */
    USB_LANGID_MKD      = 0x042f,   /**< Macedonian */
    USB_LANGID_MSA      = 0x043e,   /**< Malay (Malaysian) */
    USB_LANGID_MSA_BN   = 0x083e,   /**< Malay (Brunei Darussalam) */
    USB_LANGID_MAL      = 0x044c,   /**< Malayalam */
    USB_LANGID_MNI      = 0x0458,   /**< Manipuri */
    USB_LANGID_MAR      = 0x044e,   /**< Marathi */
    USB_LANGID_NEP      = 0x0861,   /**< Nepali (India) */
    USB_LANGID_NOB      = 0x0414,   /**< Norwegian (Bokmal) */
    USB_LANGID_NNO      = 0x0814,   /**< Norwegian (Nynorsk) */
    USB_LANGID_ORI      = 0x0448,   /**< Oriya */
    USB_LANGID_POL      = 0x0415,   /**< Polish */
    USB_LANGID_POR_BR   = 0x0416,   /**< Portuguese (Brazil) */
    USB_LANGID_POR      = 0x0816,   /**< Portuguese (Standard) */
    USB_LANGID_PAN      = 0x0446,   /**< Punjabi */
    USB_LANGID_RON      = 0x0418,   /**< Romanian */
    USB_LANGID_RUS      = 0x0419,   /**< Russian */
    USB_LANGID_SAN      = 0x044f,   /**< Sanskrit */
    USB_LANGID_SRB_CYR  = 0x0c1a,   /**< Serbian (Cyrillic) */
    USB_LANGID_SRB_LAT  = 0x081a,   /**< Serbian (Latin) */
    USB_LANGID_SND      = 0x0459,   /**< Sindhi */
    USB_LANGID_SLK      = 0x041b,   /**< Slovak */
    USB_LANGID_SLV      = 0x0424,   /**< Slovenian */
    USB_LANGID_SPA      = 0x040a,   /**< Spanish (Traditional Sort) */
    USB_LANGID_SPA_MX   = 0x080a,   /**< Spanish (Mexican) */
    USB_LANGID_SPA_MDN  = 0x0c0a,   /**< Spanish (Modern Sort) */
    USB_LANGID_SPA_GT   = 0x100a,   /**< Spanish (Guatemala) */
    USB_LANGID_SPA_CR   = 0x140a,   /**< Spanish (Costa Rica) */
    USB_LANGID_SPA_PA   = 0x180a,   /**< Spanish (Panama) */
    USB_LANGID_SPA_DO   = 0x1c0a,   /**< Spanish (Dominican Republic) */
    USB_LANGID_SPA_VE   = 0x200a,   /**< Spanish (Venezuela) */
    USB_LANGID_SPA_CO   = 0x240a,   /**< Spanish (Colombia) */
    USB_LANGID_SPA_PE   = 0x280a,   /**< Spanish (Peru) */
    USB_LANGID_SPA_AR   = 0x2c0a,   /**< Spanish (Argentina) */
    USB_LANGID_SPA_EC   = 0x300a,   /**< Spanish (Ecuador) */
    USB_LANGID_SPA_CL   = 0x340a,   /**< Spanish (Chile) */
    USB_LANGID_SPA_UY   = 0x380a,   /**< Spanish (Uruguay) */
    USB_LANGID_SPA_PY   = 0x3c0a,   /**< Spanish (Paraguay) */
    USB_LANGID_SPA_BO   = 0x400a,   /**< Spanish (Bolivia) */
    USB_LANGID_SPA_SV   = 0x440a,   /**< Spanish (El Salvador) */
    USB_LANGID_SPA_HN   = 0x480a,   /**< Spanish (Honduras) */
    USB_LANGID_SPA_NI   = 0x4c0a,   /**< Spanish (Nicaragua) */
    USB_LANGID_SPA_PR   = 0x500a,   /**< Spanish (Puerto Rico) */
    USB_LANGID_NSO      = 0x0430,   /**< Sutu, Sotho. */
    USB_LANGID_SWA      = 0x0441,   /**< Swahili (Kenya) */
    USB_LANGID_SWE      = 0x041d,   /**< Swedish */
    USB_LANGID_SWE_FI   = 0x081d,   /**< Swedish (Finland) */
    USB_LANGID_TAM      = 0x0449,   /**< Tamil */
    USB_LANGID_TAT      = 0x0444,   /**< Tatar (Tatarstan) */
    USB_LANGID_TEL      = 0x044a,   /**< Telugu */
    USB_LANGID_THA      = 0x041e,   /**< Thai */
    USB_LANGID_TUR      = 0x041f,   /**< Turkish */
    USB_LANGIG_UKR      = 0x0422,   /**< Ukrainian */
    USB_LANGID_URD_PK   = 0x0420,   /**< Urdu (Pakistan) */
    USB_LANGID_URD_IN   = 0x0820,   /**< Urdu (India) */
    USB_LANGID_UZB_LAT  = 0x0443,   /**< Uzbek (Latin) */
    USB_LANGID_UZB_CYR  = 0x0843,   /**< Uzbek (Cyrillic) */
    USB_LANGID_VIE      = 0x042a,   /**< Vietnamese. */
};

/** \brief common USB descriptor header */
struct usb_header_descriptor {
    uint8_t bLength;                /**< Size of the descriptor, in bytes. */
    uint8_t bDescriptorType;        /**< Type of the descriptor. */
} __attribute__((packed));

/** \brief Represents a USB device descriptor
 *  \details A device descriptor describes general information about a USB device. It includes information that applies
 *           globally to the device and all of the device’s configurations. A USB device has only one device descriptor.
 *           A high-speed capable device that has different device information for full-speed and high-speed must also
 *           have a \ref usb_qualifier_descriptor
 */
struct usb_device_descriptor {
    uint8_t  bLength;               /**< Size of the descriptor, in bytes. */
    uint8_t  bDescriptorType;       /**< Type of the descriptor, must be a \ref USB_DTYPE_DEVICE. */
    uint16_t bcdUSB;                /**< BCD of the supported USB specification. \ref VERSION_BCD utility macro. */
    uint8_t  bDeviceClass;          /**< USB device class. */
    uint8_t  bDeviceSubClass;       /**< USB device subclass. */
    uint8_t  bDeviceProtocol;       /**< USB device protocol. */
    uint8_t  bMaxPacketSize0;       /**< Size of the control (address 0) endpoint's bank in bytes. */
    uint16_t idVendor;              /**< Vendor ID for the USB product. */
    uint16_t idProduct;             /**< Unique product ID for the USB product. */
    uint16_t bcdDevice;             /**< Product release (version) number. \ref VERSION_BCD utility macro. */
    uint8_t  iManufacturer;         /**< String index for the manufacturer's name. */
    uint8_t  iProduct;              /**< String index for the product name/details. */
    uint8_t  iSerialNumber;         /**< String index for the product serial number, \ref INTSERIALNO_DESCRIPTOR can be used*/
    uint8_t  bNumConfigurations;    /**< Total number of configurations supported by the device. */
} __attribute__((packed));

/** \brief USB device qualifier descriptor
 *  \details The device_qualifier descriptor describes information about a high-speed capable device that would
 *           change if the device were operating at the other speed. For example, if the device is currently operating
 *           at full-speed, the device qualifier returns information about how it would operate at high-speed and vice-versa.
 */
struct usb_qualifier_descriptor {
    uint8_t  bLength;               /**< Size of the descriptor, in bytes. */
    uint8_t  bDescriptorType;       /**< Type of the descriptor, must be a \ref USB_DTYPE_QUALIFIER. */
    uint16_t bcdUSB;                /**< BCD of the supported USB specification. \ref VERSION_BCD utility macro. */
    uint8_t  bDeviceClass;          /**< USB device class. */
    uint8_t  bDeviceSubClass;       /**< USB device subclass. */
    uint8_t  bDeviceProtocol;       /**< USB device protocol. */
    uint8_t  bMaxPacketSize0;       /**< Size of the control (address 0) endpoint's bank in bytes. */
    uint8_t  bNumConfigurations;    /**< Total number of configurations supported by the device. */
    uint8_t  bReserved;             /**< Reserved for future use, must be 0. */
} __attribute__((packed));
/** \brief USB device configuration descriptor
 *  \details The configuration descriptor describes information about a specific device configuration. The descriptor
 *           contains a bConfigurationValue field with a value that, when used as a parameter to the SetConfiguration()
 *           request, causes the device to assume the described configuration.
 */
struct usb_config_descriptor {
    uint8_t  bLength;               /**< Size of the descriptor, in bytes. */
    uint8_t  bDescriptorType;       /**< Type of the descriptor, must be a \ref USB_DTYPE_CONFIGURATION. */
    uint16_t wTotalLength;          /**< Size of the configuration descriptor header, and all sub descriptors inside the configuration. */
    uint8_t  bNumInterfaces;        /**< Total number of interfaces in the configuration. */
    uint8_t  bConfigurationValue;   /**< Configuration index of the current configuration. */
    uint8_t  iConfiguration;        /**< Index of a string descriptor describing the configuration. */
    uint8_t  bmAttributes;          /**< Configuration attributes, comprised of a mask of \c USB_CONFIG_ATTR_* masks. On all devices, this should include USB_CONFIG_ATTR_RESERVED at a minimum. */
    uint8_t  bMaxPower;             /**< Maximum power consumption of the device while in the current configuration, calculated by the \ref USB_CFG_POWER_MA() macro. */
} __attribute__((packed));
/** \brief USB interface descriptor
 *  \details The interface descriptor describes a specific interface within a configuration. A configuration provides one or more interfaces,
 *           each with zero or more endpoint descriptors describing a unique set of endpoints within the configuration.
 */
struct usb_interface_descriptor {
    uint8_t bLength;                /**< Size of the descriptor, in bytes. */
    uint8_t bDescriptorType;        /**< Type of the descriptor, must be \ref USB_DTYPE_INTERFACE */
    uint8_t bInterfaceNumber;       /**< Index of the interface in the current configuration. */
    uint8_t bAlternateSetting;      /**< Alternate setting for the interface number. */
    uint8_t bNumEndpoints;          /**< Total number of endpoints in the interface. */
    uint8_t bInterfaceClass;        /**< Interface class ID. */
    uint8_t bInterfaceSubClass;     /**< Interface subclass ID. */
    uint8_t bInterfaceProtocol;     /**< Interface protocol ID. */
    uint8_t iInterface;             /**< Index of the string descriptor describing the interface. */
} __attribute__((packed));
struct usb_iad_descriptor {
    uint8_t bLength;                /**< Size of the descriptor, in bytes. */
    uint8_t bDescriptorType;        /**< Type of the descriptor, either a value in */
    uint8_t bFirstInterface;        /**< Index of the first associated interface. */
    uint8_t bInterfaceCount;        /**< Total number of associated interfaces. */
    uint8_t bFunctionClass;         /**< Interface class ID. */
    uint8_t bFunctionSubClass;      /**< Interface subclass ID. */
    uint8_t bFunctionProtocol;      /**< Interface protocol ID. */
    uint8_t iFunction;              /**< Index of the string descriptor describing the interface association. */
} __attribute__((packed));
/** \brief USB endpoint descriptor
 *  \details This descriptor contains the information required by the host to determine the bandwidth requirements of each endpoint.
 */
struct usb_endpoint_descriptor {
    uint8_t  bLength;               /**< Size of the descriptor, in bytes. */
    uint8_t  bDescriptorType;       /**< Type of the descriptor, must be \ref USB_DTYPE_ENDPOINT */
    uint8_t  bEndpointAddress;      /**< Logical address of the endpoint within the device for the current configuration, including direction mask. */
    uint8_t  bmAttributes;          /**< Endpoint attributes, \ref USB_ENDPOINT_DEF. */
    uint16_t wMaxPacketSize;        /**< Size of the endpoint bank, in bytes. This indicates the maximum packet size that the endpoint can receive at a time. */
    uint8_t  bInterval;             /**< Polling interval in milliseconds for the endpoint if it is an INTERRUPT or ISOCHRONOUS type. */
} __attribute__((packed));

/** \brief USB string descriptor
 *  \details String descriptors are referenced by their one-based index number. A string descriptor contains one or more not NULL-terminated Unicode strings.
 *  \note String descriptors are optional. if a device does not support string descriptors, all references to string descriptors within device, configuration,
 *        and interface descriptors must be reset to zero.
 */
struct usb_string_descriptor {
    uint8_t  bLength;               /**< Size of the descriptor, in bytes. */
    uint8_t  bDescriptorType;       /**< Type of the descriptor, must be \ref USB_DTYPE_STRING */
    uint16_t wString[];             /**< String data, as unicode characters (alternatively, array of \ref USB_STD_LANGIDS ). */
} __attribute__((packed));

struct usb_debug_descriptor {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDebugInEndpoint;      /**< Endpoint number of the Debug Data IN endpoint. This is a Bulk-type endpoint with a maximum packet size of 8 bytes.  */
    uint8_t  bDebugOutEndpoint;     /**< Endpoint number of the Debug Data OUTendpoint. This is a Bulk-type endpoint with a maximum packet size of 8 bytes.  */
} __attribute__((packed));


/** @} */

#if defined (__cplusplus)
}
#endif
#endif //_USB_STD_H_
