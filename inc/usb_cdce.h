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

/** \ingroup USB_CDC
 *  \addtogroup USB_CDC_ECM USB CDC ECM subclass
 *  \brief USB CDC ECM subclass definitions
 *  \details Includes following subclasses
 * + Ethernet Control Model
 * @{ */

#ifndef _USB_CDC_ECM_H_
#define _USB_CDC_ECM_H_

#ifdef __cplusplus
    extern "C" {
#endif


/**\name Communications Class Subclass Codes
 * @{ */
#define USB_CDC_SUBCLASS_ETH                0x06 /**< Ethernet Networking Control Model */
 /* @} */

/**\name CDC ECM subclass specific Functional Descriptors codes
 * @{ */
#define USB_DTYPE_CDC_ETHERNET              0x0F /**< Ethernet Networking Functional Descriptor*/
/** @} */    	

/**\name CDC ECM subclass specific requests
 * @{ */
#define USB_CDC_SET_ETH_MULTICAST_FILTERS   0x40 /**<  */
#define USB_CDC_SET_ETH_PM_PATTERN_FILTER   0x41 /**<  */
#define USB_CDC_GET_ETH_PM_PATTERN_FILTER   0x42 /**<  */
#define USB_CDC_SET_ETH_PACKET_FILTER       0x43 /**< Sets device filter for running a network analyzer application on the host machine */
#define USB_CDC_GET_ETH_STATISTIC           0x44 /**< Retrieves Ethernet device statistics such as frames transmitted, frames received, and bad frames received. */
/** @} */


/**\brief Ethernet Networking Functional Descriptor
 * \details describes the operational modes supported by the
 * Communications Class interface, as defined in Section 3.4, with the SubClass code of Ethernet
 * Networking Control. It can only occur within the class-specific portion of an Interface descriptor.
 */
struct usb_cdc_ether_desc {
    uint8_t     bFunctionLength;				/**< Size of this functional descriptor, in bytes. */
    uint8_t     bDescriptorType;				/**< CS_INTERFACE descriptor type. \see \ref USB_DTYPE_CS_INTERFACE */
    uint8_t     bDescriptorSubType;				/**< Ethernet Networking Functional Descriptor. \ref USB_DTYPE_CDC_ETHERNET */
    uint8_t     iMACAddress;					/**< Index of string descriptor that holds the 48bit Ethernet MAC address. */
    uint32_t    bmEthernetStatistics;			/**< Indicates which Ethernet statistics functions the device collects. */
    uint16_t    wMaxSegmentSize;				/**< The maximum segment size that the Ethernet device is capable of supporting. */
    uint16_t    wNumberMCFilters;				/**< Contains the number of multicast filters that can be configured by the host. */
    uint8_t     bNumberPowerFilters;			/**< Contains the number of pattern filters that are available for causing wake-up of the host. */
} __attribute__ ((packed));




/** @} */


#ifdef __cplusplus
    }
#endif

#endif /* _USB_CDC_ECM_H_ */    	