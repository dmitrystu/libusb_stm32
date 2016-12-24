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

#ifndef _USB_HID_H_
#define _USB_HID_H_
#ifdef __cplusplus
    extern "C" {
#endif


/**\addtogroup USB_HID USB HID class
 * \brief This module contains USB Human Interface Devices class definitions
 * \details This module based on
 * + [Device Class Definition for Human Interface Devices (HID) Version 1.11](http://www.usb.org/developers/hidpage/HID1_11.pdf)
 * + [LUFA - the Lightweight USB Framework for AVRs.](https://github.com/abcminiuser/lufa)
 * @{ */

/**\name USB HID class code */
#define USB_CLASS_HID               0x03 /**< Interface belongs to the Human Interface device class */

/**\name USB HID subclass codes
 * @{ */
#define USB_HID_SUBCLASS_NONBOOT    0x00
#define USB_HID_SUBCLASS_BOOT       0x01
/** @} */

/**\name USB HID protocol codes
 * @{ */
#define USB_HID_PROTO_NONBOOT       0x00
#define USB_HID_PROTO_KEYBOARD      0x01
#define USB_HID_PROTO_MOUSE         0x02
/** @} */

#define USB_HID_REPORT_IN           0 /**< \brief Indicates that the item is an IN report type. */
#define USB_HID_REPORT_OUT          1 /**< \brief Indicates that the item is an OUT report type. */
#define USB_HID_REPORT_FEATURE      2 /**< \brief Indicates that the item is a FEATURE report type. */


/**\name USB HID class-specified requests
 * @{ */
#define USB_HID_GETREPORT  			0x01 /**< Request to get the current HID report from the device. */
#define USB_HID_GETIDLE    			0x02 /**< Request to get the current device idle count. */
#define USB_HID_GETPROTOCOL			0x03 /**< Request to get the current HID report protocol mode. */
#define USB_HID_SETREPORT  			0x09 /**< Request to set the current HID report to the device. */
#define USB_HID_SETIDLE    			0x0A /**< Request to set the device's idle count. */
#define USB_HID_SETPROTOCOL			0x0B /**< Request to set the current HID report protocol mode. */
/** @} */

/**\name USB HID class-specified descriptor types
 * @{ */
#define	USB_DTYPE_HID           	0x21 /**< Descriptor header type value, to indicate a HID class HID descriptor. */
#define	USB_DTYPE_HID_REPORT     	0x22 /**< Descriptor header type value, to indicate a HID class HID report descriptor. */
/** @} */

/**\name USB HID country codes
 * @{ */
#define USB_HID_COUNTRY_NONE 		0 	/**< Not supported */
#define USB_HID_COUNTRY_AR   		1 	/**< Arabic */
#define USB_HID_COUNTRY_BE   		2 	/**< Belgian */
#define USB_HID_COUNTRY_CA_BI		3 	/**< Canadian-Bilingual */
#define USB_HID_COUNTRY_CA_FR		4 	/**< Canadian-French */
#define USB_HID_COUNTRY_CZ   		5 	/**< Czech Republic */
#define USB_HID_COUNTRY_DK   		6 	/**< Danish */
#define USB_HID_COUNTRY_FI   		7 	/**< Finnish */
#define USB_HID_COUNTRY_FR   		8 	/**< French */
#define USB_HID_COUNTRY_DE   		9 	/**< German */
#define USB_HID_COUNTRY_GR   		10	/**< Greek */
#define USB_HID_COUNTRY_HEB  		11	/**< Hebrew */
#define USB_HID_COUNTRY_HU   		12	/**< Hungary */
#define USB_HID_COUNTRY_ISO  		13	/**< International (ISO) */
#define USB_HID_COUNTRY_IT   		14	/**< Italian */
#define USB_HID_COUNTRY_JP   		15	/**< Japan (Katakana) */
#define USB_HID_COUNTRY_KR   		16	/**< Korean */
#define USB_HID_COUNTRY_LAT  		17	/**< Latin American */
#define USB_HID_COUNTRY_NL   		18	/**< Netherlands/Dutch */
#define USB_HID_COUNTRY_NO   		19	/**< Norwegian */
#define USB_HID_COUNTRY_PER  		20	/**< Persian (Farsi) */
#define USB_HID_COUNTRY_PL   		21	/**< Poland */
#define USB_HID_COUNTRY_PO   		22	/**< Portuguese */
#define USB_HID_COUNTRY_RU   		23	/**< Russia */
#define USB_HID_COUNTRY_SK   		24	/**< Slovakia */
#define USB_HID_COUNTRY_ES   		25	/**< Spanish */
#define USB_HID_COUNTRY_SE   		26	/**< Swedish */
#define USB_HID_COUNTRY_CH_FR		26	/**< Swiss-French */
#define USB_HID_COUNTRY_CH_DE		27	/**< Swiss-German */
#define USB_HID_COUNTRY_CH   		29	/**< Switzerland */
#define USB_HID_COUNTRY_TW   		30	/**< Taiwan */
#define USB_HID_COUNTRY_TR_Q 		31	/**< Turkish-Q */
#define USB_HID_COUNTRY_UK   		32	/**< UK */
#define USB_HID_COUNTRY_US   		33	/**< US */
#define USB_HID_COUNTRY_YU   		34	/**< Yugoslavia */
#define USB_HID_COUNTRY_TR_F 		35	/**< Turkish-F */
/** @} */

/** \brief USB HID functional descriptor */
struct usb_hid_descriptor {
    uint8_t     bLength;            /**< Size of the descriptor, in bytes. */
    uint8_t     bDescriptorType;    /**< Type of the descriptor, set to \ref USB_DTYPE_HID */
	uint16_t    bcdHID;             /**< BCD encoded version that the HID descriptor and device complies to. \ref VERSION_BCD() */
    uint8_t     bCountryCode;       /**< Country code of the localized device, or zero if universal. */
	uint8_t     bNumDescriptors;    /**< Total number of HID report descriptors for the interface. */
	uint8_t     bDescriptorType0;   /**< 1'st HID report descriptor type, set to \ref USB_DTYPE_HID_REPORT */
	uint16_t    wDescriptorLength0; /**< 1'sr HID report descriptor length in bytes. */
} __attribute__((packed));

/**\brief USB HID report descriptor */
struct usb_hid_report_descriptor {
	uint8_t     bDescriptorType;   /**< Type of HID report, set to \ref USB_DTYPE_HID_REPORT */
    uint16_t    wDescriptorLength; /**< Length of the associated HID report descriptor, in bytes. */
} __attribute__((packed));


	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
            #define CONCAT(x, y)            x ## y
            #define CONCAT_EXPANDED(x, y)   CONCAT(x, y)

			#define HID_RI_DATA_SIZE_MASK                   0x03
			#define HID_RI_TYPE_MASK                        0x0C
			#define HID_RI_TAG_MASK                         0xF0

			#define HID_RI_TYPE_MAIN                        0x00
			#define HID_RI_TYPE_GLOBAL                      0x04
			#define HID_RI_TYPE_LOCAL                       0x08

			#define HID_RI_DATA_BITS_0                      0x00
			#define HID_RI_DATA_BITS_8                      0x01
			#define HID_RI_DATA_BITS_16                     0x02
			#define HID_RI_DATA_BITS_32                     0x03
			#define HID_RI_DATA_BITS(DataBits)              CONCAT_EXPANDED(HID_RI_DATA_BITS_, DataBits)

			#define _HID_RI_ENCODE_0(Data)
			#define _HID_RI_ENCODE_8(Data)                  , (Data & 0xFF)
			#define _HID_RI_ENCODE_16(Data)                 _HID_RI_ENCODE_8(Data)  _HID_RI_ENCODE_8(Data >> 8)
			#define _HID_RI_ENCODE_32(Data)                 _HID_RI_ENCODE_16(Data) _HID_RI_ENCODE_16(Data >> 16)
			#define _HID_RI_ENCODE(DataBits, ...)           CONCAT_EXPANDED(_HID_RI_ENCODE_, DataBits(__VA_ARGS__))

			#define _HID_RI_ENTRY(Type, Tag, DataBits, ...) (Type | Tag | HID_RI_DATA_BITS(DataBits)) _HID_RI_ENCODE(DataBits, (__VA_ARGS__))
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
		/** \name HID Input, Output and Feature Report Descriptor Item Flags */
		//@{
			#define HID_IOF_CONSTANT                        (1 << 0)
			#define HID_IOF_DATA                            (0 << 0)
			#define HID_IOF_VARIABLE                        (1 << 1)
			#define HID_IOF_ARRAY                           (0 << 1)
			#define HID_IOF_RELATIVE                        (1 << 2)
			#define HID_IOF_ABSOLUTE                        (0 << 2)
			#define HID_IOF_WRAP                            (1 << 3)
			#define HID_IOF_NO_WRAP                         (0 << 3)
			#define HID_IOF_NON_LINEAR                      (1 << 4)
			#define HID_IOF_LINEAR                          (0 << 4)
			#define HID_IOF_NO_PREFERRED_STATE              (1 << 5)
			#define HID_IOF_PREFERRED_STATE                 (0 << 5)
			#define HID_IOF_NULLSTATE                       (1 << 6)
			#define HID_IOF_NO_NULL_POSITION                (0 << 6)
			#define HID_IOF_VOLATILE                        (1 << 7)
			#define HID_IOF_NON_VOLATILE                    (0 << 7)
			#define HID_IOF_BUFFERED_BYTES                  (1 << 8)
			#define HID_IOF_BITFIELD                        (0 << 8)
		//@}

		/** \name HID Report Descriptor Item Macros */
		//@{
			#define HID_RI_INPUT(DataBits, ...)             _HID_RI_ENTRY(HID_RI_TYPE_MAIN  , 0x80, DataBits, __VA_ARGS__)
			#define HID_RI_OUTPUT(DataBits, ...)            _HID_RI_ENTRY(HID_RI_TYPE_MAIN  , 0x90, DataBits, __VA_ARGS__)
			#define HID_RI_COLLECTION(DataBits, ...)        _HID_RI_ENTRY(HID_RI_TYPE_MAIN  , 0xA0, DataBits, __VA_ARGS__)
			#define HID_RI_FEATURE(DataBits, ...)           _HID_RI_ENTRY(HID_RI_TYPE_MAIN  , 0xB0, DataBits, __VA_ARGS__)
			#define HID_RI_END_COLLECTION(DataBits, ...)    _HID_RI_ENTRY(HID_RI_TYPE_MAIN  , 0xC0, DataBits, __VA_ARGS__)
			#define HID_RI_USAGE_PAGE(DataBits, ...)        _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x00, DataBits, __VA_ARGS__)
			#define HID_RI_LOGICAL_MINIMUM(DataBits, ...)   _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x10, DataBits, __VA_ARGS__)
			#define HID_RI_LOGICAL_MAXIMUM(DataBits, ...)   _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x20, DataBits, __VA_ARGS__)
			#define HID_RI_PHYSICAL_MINIMUM(DataBits, ...)  _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x30, DataBits, __VA_ARGS__)
			#define HID_RI_PHYSICAL_MAXIMUM(DataBits, ...)  _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x40, DataBits, __VA_ARGS__)
			#define HID_RI_UNIT_EXPONENT(DataBits, ...)     _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x50, DataBits, __VA_ARGS__)
			#define HID_RI_UNIT(DataBits, ...)              _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x60, DataBits, __VA_ARGS__)
			#define HID_RI_REPORT_SIZE(DataBits, ...)       _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x70, DataBits, __VA_ARGS__)
			#define HID_RI_REPORT_ID(DataBits, ...)         _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x80, DataBits, __VA_ARGS__)
			#define HID_RI_REPORT_COUNT(DataBits, ...)      _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x90, DataBits, __VA_ARGS__)
			#define HID_RI_PUSH(DataBits, ...)              _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0xA0, DataBits, __VA_ARGS__)
			#define HID_RI_POP(DataBits, ...)               _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0xB0, DataBits, __VA_ARGS__)
			#define HID_RI_USAGE(DataBits, ...)             _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x00, DataBits, __VA_ARGS__)
			#define HID_RI_USAGE_MINIMUM(DataBits, ...)     _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x10, DataBits, __VA_ARGS__)
			#define HID_RI_USAGE_MAXIMUM(DataBits, ...)     _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x20, DataBits, __VA_ARGS__)
		//@}




/** @}  */

#ifdef __cplusplus
    }
#endif

#endif

