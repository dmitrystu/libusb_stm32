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

#ifndef _USB_MIDI_H_
#define _USB_MIDI_H_

#ifdef __cplusplus
    extern "C" {
#endif

/**\addtogroup USB_MIDI USB MIDI class
 * \brief Generic USB MIDI class definitions
 * \details This module based on
 * + [Universal Serial Bus Device Class Definition for MIDI Devices](https://www.usb.org/sites/default/files/midi10.pdf)
 * @{ */

/**\name USB MIDI Class codes
 * @{ */
#define USB_CLASS_MIDI              0x01U   /**<\brief MIDI Device class */
#define USB_MIDI_SUBCLASS_CONTROL   0x01U   /**<\brief Data Interface class */
/** @} */

#define USB_MIDI_SET_CUR            0x01U   /**<\brief Set current setting attribute.*/
#define USB_MIDI_SET_MIN            0x02U   /**<\brief Set minimum setting attribute.*/
#define USB_MIDI_SET_MAX            0x03U   /**<\brief Set maximum setting attribute.*/
#define USB_MIDI_SET_RES            0x04U   /**<\brief Set resolution attribute.*/
#define USB_MIDI_SET_MEM            0x05U   /**<\brief Set memory space attribute.*/
#define USB_MIDI_GET_CUR            0x81U   /**<\brief Get current setting attribute.*/
#define USB_MIDI_GET_MIN            0x82U   /**<\brief Get minimum setting attribute.*/
#define USB_MIDI_GET_MAX            0x83U   /**<\brief Get maximum setting attribute.*/
#define USB_MIDI_GET_RES            0x84U   /**<\brief Get resolution attribute.*/
#define USB_MIDI_GET_MEM            0x85U   /**<\brief Upload a parameter block from a
                                             * particular Entity of the USB-MIDI function.*/
#define USB_MIDI_GET_STAT           0xFFU   /**<\brief Retrieve status information from an
                                             * Entity within the USB-MIDI function.*/

/**\name USB MIDI descriptor types
 * @{ */
#define USB_DTYPE_MIDI_UNDEFINED    0x00U   /**<\brief */
#define USB_DTYPE_MIDI_HEADER       0x01U   /**<\see \ref usb_midi_header_desc */
#define USB_DTYPE_MIDI_IN_JACK      0x02U   /**<\see \ref usb_midi_jack_in_desc */
#define USB_DTYPE_MIDI_OUT_JACK     0x03U   /**<\see \ref usb_midi_jack_out_desc */
#define USB_DTYPE_MIDI_ELEMENT      0x04U   /**<\see \ref usb_midi_element_desc */
#define USB_DTYPE_MIDI_MS_GENERAL   0x01U   /**<\brief */
/** @} */

/**\name USB MIDI Jack types
 * @{ */
#define USB_MIDI_JACK_UNDEFINED     0x00U   /**<\brief Declares undefined Jack */
#define USB_MIDI_JACK_EMBEDDED      0x01U   /**<\brief Declares embedded Jack */
#define USB_MIDI_JACK_EXTERNL       0x02U   /**<\brief Declares external Jack */
/** @} */

/**\name USB MIDI Element capabilities
 * @{ */
#define USB_MIDI_ELEMENT_CUSTOM     0x0001U /**<\brief The Element has unique, undefined features.*/
#define USB_MIDI_ELEMENT_CLOCK      0x0002U /**<\brief MIDI CLOCK messages are supported.*/
#define USB_MIDI_ELEMENT_TIMEDODE   0x0004U /**<\brief Synchronization features are supported.*/
#define USB_MIDI_ELEMENT_MMC        0x0008U /**<\brief MMC messages are supported.*/
#define USB_MIDI_ELEMENT_GM1        0x0010U /**<\brief General MIDI System Level 1 compatibility as
                                             * defined by the MIDI Manufacturers Association.*/
#define USB_MIDI_ELEMENT_GM2        0x0020U /**<\brief General MIDI System Level 2 compatibility as
                                             * defined by the MIDI Manufacturers Association.*/
#define USB_MIDI_ELEMENT_GS         0x0040U /**<\brief GS Format compatibility as defined by Roland Corporation.*/
#define USB_MIDI_ELEMENT_XG         0x0080U /**<\brief XG compatibility as defined by Yamaha Corporation.*/
#define USB_MIDI_ELEMENT_EFX        0x0100U /**<\brief The Element provides an audio effects processor controlled by USB.*/
#define USB_MIDI_ELEMENT_PATCH      0x0200U /**<\brief The Element provides an internal MIDI Patcher or Router.*/
#define USB_MIDI_ELEMENT_DLS1       0x0400U /**<\brief Downloadable Sounds Standard Level 1 compatibility as
                                             * defined by the MIDI Manufacturers Association.*/
#define USB_MIDI_ELEMENT_DLS2       0x0800U /**<\brief Downloadable Sounds Standard Level 1 compatibility as
                                             * defined by the MIDI Manufacturers Association.*/
/** @} */

/**\name USB MIDI Code index numbers
 * @{ */
#define USB_MIDI_CIN_MISC           0x00U   /**<\brief Miscellaneous function codes. Reserved for future extensions.*/
#define USB_MIDI_CIN_CABLE_EVT      0x01U   /**<\brief Cable events. Reserved for future expansion.*/
#define USB_MIDI_CIN_2B_MSG         0x02U   /**<\brief Two-byte System Common messages like MTC, SongSelect, etc.*/
#define USB_MIDI_CIN_3B_MSG         0x03U   /**<\brief Three-byte System Common messages like SPP, etc.*/
#define USB_MIDI_CIN_SYSEX          0x04U   /**<\brief SysEx starts or continues.*/
#define USB_MIDI_CIN_1B_MSG         0x05U   /**<\brief Single-byte System Common Message.*/
#define USB_MIDI_CIN_SYSEX_END1     0x05U   /**<\brief SysEx ends with following single byte.*/
#define USB_MIDI_CIN_SYSEX_END2     0x06U   /**<\brief SysEx ends with following two bytes.*/
#define USB_MIDI_CIN_SYSEX_END3     0x07U   /**<\brief SysEx ends with following three bytes.*/
#define USB_MIDI_CIN_NOTE_OFF       0x08U   /**<\brief Note-off.*/
#define USB_MIDI_CIN_NOTE_ON        0x09U   /**<\brief Note-on.*/
#define USB_MIDI_CIN_PKEY_PRESS     0x0AU   /**<\brief Poly-Key press.*/
#define USB_MIDI_CIN_CTRL_CHANGE    0x0BU   /**<\brief Control change.*/
#define USB_MIDI_CIN_PRGM_CHANGE    0x0CU   /**<\brief Program change.*/
#define USB_MIDI_CIN_CHNL_PRESS     0x0DU   /**<\brief Channel pressure.*/
#define USB_MIDI_CIN_PBEND_CHANGE   0x0EU   /**<\brief PitchBend change.*/
#define USB_MIDI_CIN_SINGLE_BYTE    0x0FU   /**<\brief Single byte.*/
/** @} */


/**\brief Class-Specific MS Interface Header Descriptor
 * \details Header Functional Descriptor marks the beginning of the concatenated set of functional
 * descriptors for the interface. */
struct usb_midi_header_desc {
    uint8_t     bLength;            /**<\brief Size of this descriptor in bytes.*/
    uint8_t     bDescriptorType;    /**<\brief CS_INTERFACE descriptor type.*/
    uint8_t     bDescriptorSubType; /**<\brief MS_HEADER descriptor subtype.*/
    uint16_t    bcdMSC;             /**<\brief MIDIStreaming SubClass Specification Release Number.*/
    uint16_t    wTotalLength;       /**<\brief Total number of bytes returned for the class-specific
                                     * MIDIStreaming interface descriptor.*/
} __attribute__ ((packed));

/**\brief MIDI IN Jack Descriptor */
struct usb_midi_jack_in_desc {
    uint8_t     bLength;            /**<\brief Size of this descriptor in bytes.*/
    uint8_t     bDescriptorType;    /**<\brief CS_INTERFACE descriptor type.*/
    uint8_t     bDescriptorSubType; /**<\brief MIDI_IN_JACK descriptor subtype.*/
    uint8_t     bJackType;          /**<\brief EMBEDDED or EXTERNAL.*/
    uint8_t     bJackID;            /**<\brief Constant uniquely identifying the MIDI IN Jack within
                                     * the USB-MIDI function.*/
    uint8_t     iJack;              /**<\brief Index, describing the MIDI IN Jack.*/
} __attribute__ ((packed));

struct usb_midi_source_pin {
    uint8_t     bSourceID;
    uint8_t     bSourcePin;
} __attribute__ ((packed));

/**\brief MIDI OUT Jack Descriptor */
struct usb_midi_jack_out_desc {
    uint8_t     bLength;                /**<\brief Size of this descriptor in bytes.*/
    uint8_t     bDescriptorType;        /**<\brief CS_INTERFACE descriptor type.*/
    uint8_t     bDescriptorSubType;     /**<\brief MIDI_OUT_JACK descriptor subtype.*/
    uint8_t     bJackType;              /**<\brief EMBEDDED or EXTERNAL.*/
    uint8_t     bJackID;                /**<\brief Constant uniquely identifying the MIDI OUT Jack within
                                         * the USB-MIDI function.*/
    uint8_t     bNrInputPins;           /**<\brief Number of Input Pins of this MIDI OUT Jack */
    uint8_t     baSourceID;
    uint8_t     baSourcePin;
    uint8_t     iJack;                  /**<\brief Index of a string descriptor, describing the MIDI OUT Jack.*/
} __attribute__ ((packed));


struct usb_midi_element_desc {
    uint8_t     bLength;                /**<\brief Size of this descriptor in bytes.*/
    uint8_t     bDescriptorType;        /**<\brief CS_INTERFACE descriptor type.*/
    uint8_t     bDescriptorSubType;     /**<\brief ELEMENT descriptor subtype.*/
    uint8_t     bElementID;
    uint8_t     bNrInputPins;
    uint8_t     baSourceID;
    uint8_t     baSourcePin;
    uint8_t     bNrOutputPins;
    uint8_t     bInTerminalLink;
    uint8_t     bOutTerminalLink;
    uint8_t     bElCapsSize;
    uint16_t    bmElementCaps;
    uint8_t     iElement;
} __attribute__ ((packed));

struct usb_midi_std_ep_descriptor {
    uint8_t     bLength;                /**<\brief Size of the descriptor, in bytes. */
    uint8_t     bDescriptorType;        /**<\brief Endpoint descriptor.*/
    uint8_t     bEndpointAddress;       /**<\brief Logical address of the endpoint within the device for
                                         * the current configuration, including direction mask. */
    uint8_t     bmAttributes;           /**<\brief Endpoint attributes, \ref USB_ENDPOINT_DEF. */
    uint16_t    wMaxPacketSize;         /**<\brief Size of the endpoint bank, in bytes. This indicates the
                                         * maximum packet size that the endpoint can receive at a time. */
    uint8_t     bInterval;              /**<\brief Polling interval in milliseconds for the endpoint.
                                         * Must be reset to 0.*/
    uint8_t     bRefresh;               /**<\brief Reset to 0.*/
    uint8_t     bSyncAddress;           /**<\brief The address o f the endpoint used to communicate
                                         * synchronization information if required by this endpoint.
                                         * Reset to zero.*/
} __attribute__((packed));

struct usb_midi_class_ep_descriptor {
    uint8_t     bLength;                /**<\brief Size of the descriptor, in bytes.*/
    uint8_t     bDescriptorType;        /**<\brief CS_ENDPOINT descriptor.*/
    uint8_t     bDescriptorSubType;     /**<\brief USB_DTYPE_MIDI_EP_GENERAL subtype.*/
    uint8_t     bNumEmbMIDIJack;        /**<\brief Number of Embedded MIDI Jacks.*/
    uint8_t     baAssocJackID[];        /**<\brief Embedded jacks ID's */
} __attribute__((packed));

#ifdef __cplusplus
    }
#endif

#endif /* _USB_MIDI_H_ */
