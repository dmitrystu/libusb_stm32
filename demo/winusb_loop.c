/* This file is the part of the Lightweight USB device Stack for STM32 microcontrollers
 *
 * Copyright ©2018 Travis Robinson <libusbdotnet[at]gmail[dot]com>
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "usb.h"
#include "ms_os.h"

#ifndef _STM32_WUSB_CONFIG_

// YOUR VENDOR ID
// http://pid.codes/1209/
#define WUSB_VEND_ID 0x1209

// YOUR PRODUCT ID
#define WUSB_PROD_ID 0x0777

// YOUR MANUFACTURER NAME
#define WUSB_MANUFACTURER_STR		"github.TravisRo"

// YOUR PRODUCT NAME
#define WUSB_PRODUCT_STR			"WinUSB Communication Device"

// YOUR DEVICE-INTERFACE-GUID
// NOTE: A '\0' terminator is required!  (This is a multi-sz field)
#define WUSB_DEVICE_INTERFACE_GUID	"{B7705C49-EAC6-4C73-AE94-ACAEF841D599}\0"

#else
#endif

/////////////////////////////////// DEMO ENDPOINT SETUP ////////////////////////////////////
#define WUSB_EP0_MAXPACKET_SIZE	(8)
#define WUSB_EP1_MAXPACKET_SIZE	(64)
#define WUSB_EP1_RX				(0x01)
#define WUSB_EP1_TX				(0x82)

//////////////////////////////////////// VARIABLES ////////////////////////////////////////
// USB device
usbd_device udev;

// USB device buffer (buffer for ep0 rx requests [usbd_ctlreq])
// 32 bytes gives us an extra 24 bytes for an incoming data payload.
// This can bet set as low as 2! (8 bytes to hold the setup
uint32_t wusb_control_buffer[8]; 


// STM32CUBE RTC handle
RTC_HandleTypeDef hrtc;

// DEMO endpoint buffer for loopback
uint8_t fifo[WUSB_EP1_MAXPACKET_SIZE * 4];
uint32_t fpos = 0;

////////////////////////////////////// DEMO PROTOTYPES //////////////////////////////////////
static void cdc_loopback(usbd_device* dev, uint8_t event, uint8_t ep);

//////////////////////////////////////// DESCRIPTORS ////////////////////////////////////////
struct winusb_config {
    struct usb_config_descriptor cfg;
    struct usb_interface_descriptor intf1;
    struct usb_endpoint_descriptor eprx1;
    struct usb_endpoint_descriptor eptx1;
} __attribute__((packed));

static const struct usb_device_descriptor device_desc = {
    .bLength = sizeof(struct usb_device_descriptor),
    .bDescriptorType = USB_DTYPE_DEVICE,
    .bcdUSB = VERSION_BCD(2, 0, 0),
    .bDeviceClass = USB_CLASS_PER_INTERFACE,
    .bDeviceSubClass = USB_SUBCLASS_NONE,
    .bDeviceProtocol = USB_PROTO_NONE,
    .bMaxPacketSize0 = 8,
    .idVendor = WUSB_VEND_ID,
    .idProduct = WUSB_PROD_ID,
    .bcdDevice = VERSION_BCD(1, 0, 0),
    .iManufacturer = 1,
    .iProduct = 2,
    .iSerialNumber = INTSERIALNO_DESCRIPTOR,
    .bNumConfigurations = 1,
};

static const struct winusb_config config_desc = {
    .cfg = {
        .bLength = sizeof(struct usb_config_descriptor),
        .bDescriptorType = USB_DTYPE_CONFIGURATION,
        .wTotalLength = sizeof(struct winusb_config),
        .bNumInterfaces = 1,
        .bConfigurationValue = 1,
        .iConfiguration = NO_DESCRIPTOR,
        .bmAttributes = USB_CFG_ATTR_RESERVED | USB_CFG_ATTR_SELFPOWERED,
        .bMaxPower = USB_CFG_POWER_MA(100),
    },

    .intf1 = {
        .bLength = sizeof(struct usb_interface_descriptor),
        .bDescriptorType = USB_DTYPE_INTERFACE,
        .bInterfaceNumber = 0,
        .bAlternateSetting = 0,
        .bNumEndpoints = 2,
        .bInterfaceClass = USB_CLASS_APP_SPEC,
        .bInterfaceSubClass = 0x01,
        .bInterfaceProtocol = 0x07,
        .iInterface = NO_DESCRIPTOR,
    },
    .eprx1 = {
        .bLength = sizeof(struct usb_endpoint_descriptor),
        .bDescriptorType = USB_DTYPE_ENDPOINT,
        .bEndpointAddress = WUSB_EP1_RX,
        .bmAttributes = USB_EPTYPE_BULK,
        .wMaxPacketSize = WUSB_EP1_MAXPACKET_SIZE,
        .bInterval = 0x00,
    },
    .eptx1 = {
        .bLength = sizeof(struct usb_endpoint_descriptor),
        .bDescriptorType = USB_DTYPE_ENDPOINT,
        .bEndpointAddress = WUSB_EP1_TX,
        .bmAttributes = USB_EPTYPE_BULK,
        .wMaxPacketSize = WUSB_EP1_MAXPACKET_SIZE,
        .bInterval = 0x00,
    },
};

#define MS_VENDOR_CODE 0x20
static const struct usb_string_descriptor ms_os_desc = USB_STRING_DESC("MSFT100\x20");

static const struct usb_string_descriptor lang_desc = USB_ARRAY_DESC(USB_LANGID_ENG_US);
static const struct usb_string_descriptor manuf_desc_en = USB_STRING_DESC(WUSB_MANUFACTURER_STR);
static const struct usb_string_descriptor prod_desc_en = USB_STRING_DESC(WUSB_PRODUCT_STR);

static const struct usb_string_descriptor*const dtable[] = {
    &lang_desc,
    &manuf_desc_en,
    &prod_desc_en,
};

static const struct wusb_devguid_extprop_feature_descriptor devguid_ext_prop_feature_desc = {
    .dwLength = sizeof(struct wusb_devguid_extprop_feature_descriptor),
    .bcdVersion = VERSION_BCD(1,0,0),
    .wIndex = 5,
    .wCount = 1,
    .dev_guid_property = {
        .dwPropertyLength = sizeof(struct wusb_devguid_property),
        .dwPropertyType = 7, // (7 = Unicode REG_MULTI_SZ)
        .wPropertyNameLength = 42,
        .wPropertyName = STRING_TO_WCHARS("DeviceInterfaceGUIDs"),
        .dwPropertyDataLength = 80,
        .wPropertyData = STRING_TO_WCHARS(WUSB_DEVICE_INTERFACE_GUID)
    }
};

static const struct ms_os_compatid_descriptor compatid_desc = {
    .dwLength = sizeof(struct ms_os_compatid_descriptor),
    .bcdVersion = VERSION_BCD(1,0,0),
    .wIndex = 4,
    .bCount = 1,
    ._reservedA = {0, 0, 0, 0, 0, 0, 0},
    .bInterfaceNumber = 0,
    ._reservedB = {0},
    .chCompatibleID = {'W', 'I', 'N', 'U', 'S', 'B', 0, 0},
    .chSubCompatibleID = {0, 0, 0, 0, 0, 0, 0, 0},
    ._reservedC = {0, 0, 0, 0, 0, 0}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////// USB Core callbacks //////////////////////////////////////////////
static usbd_respond wusb_getdesc(usbd_ctlreq* req, void** address, uint16_t* length) {
    const uint8_t dtype = req->wValue >> 8;
    const uint8_t dnumber = req->wValue & 0xFF;
    const void* desc;
    uint16_t len = 0;
    switch (dtype) {
    case USB_DTYPE_DEVICE:
        desc = &device_desc;
        break;
    case USB_DTYPE_CONFIGURATION:
        desc = &config_desc;
        len = sizeof(config_desc);
        break;
    case USB_DTYPE_STRING:
        if (dnumber < 3) {
            desc = dtable[dnumber];
        }
        else if (dnumber == 0xEE) {
            // Microsoft OS String Descriptor
            desc = &ms_os_desc;

            /* MSDN NOTES
            After the operating system requests a Microsoft OS String Descriptor from a device, it creates the following registry key:
            HLKM\SYSTEM\CurrentControlSet\Control\UsbFlags\*vvvvpppprrrrr*

            The operating system creates a registry entry, named osvc, under this registry key that indicates whether the device supports
            Microsoft OS Descriptors. If the device does not provide a valid response the first time that the operating system queries it
            for a Microsoft OS String Descriptor, the operating system will make no further requests for that descriptor.

            [TR] Once it gets a successful enuration, it will make no further requests for it PERIOD.
            [TR] You can change bcdDevice in the device descriptor to get a re-request or delete the UsbFlags key for your dev.
            */
        }
        else {
            return usbd_fail;
        }
        break;
    default:
        return usbd_fail;
    }
    if (len == 0) {
        len = ((struct usb_header_descriptor*)desc)->bLength;
    }
    *address = (void*)desc;
    *length = len;
    return usbd_ack;
}

static usbd_respond wusb_control(usbd_device* dev, usbd_ctlreq* req, usbd_rqc_callback* callback) {

    if ((req->bmRequestType == (USB_REQ_DEVTOHOST | USB_REQ_VENDOR | USB_REQ_DEVICE)) ||
        (req->bmRequestType == (USB_REQ_DEVTOHOST | USB_REQ_VENDOR | USB_REQ_INTERFACE))) {
        if (req->bRequest == MS_VENDOR_CODE) {
            switch (req->wIndex) {

            case 0x04: // Compatible ID Feature Descriptor
                // NOTE: data_ptr and data_count are the same as the address and length params
                // in the get descriptor request.
                dev->status.data_ptr = (void*)&compatid_desc;
                dev->status.data_count = sizeof(compatid_desc);
                return usbd_ack;

            case 0x05: // Microsoft Extended Properties Feature Descriptor
                dev->status.data_ptr = (void*)&devguid_ext_prop_feature_desc;
                dev->status.data_count = sizeof(devguid_ext_prop_feature_desc);
                return usbd_ack;

            default: ;
            }
        }
    }

    return usbd_fail;
}



static usbd_respond wusb_setconf(usbd_device* dev, uint8_t cfg) {
    switch (cfg) {
    case 0:
        /* deconfiguring device */
        usbd_ep_deconfig(dev, WUSB_EP1_TX);
        usbd_ep_deconfig(dev, WUSB_EP1_RX);
        usbd_reg_endpoint(dev, WUSB_EP1_RX, 0);
        usbd_reg_endpoint(dev, WUSB_EP1_TX, 0);
        return usbd_ack;
    case 1:
        /* configuring device */
        usbd_ep_config(dev, WUSB_EP1_RX, USB_EPTYPE_BULK | USB_EPTYPE_DBLBUF, WUSB_EP1_MAXPACKET_SIZE);
        usbd_ep_config(dev, WUSB_EP1_TX, USB_EPTYPE_BULK | USB_EPTYPE_DBLBUF, WUSB_EP1_MAXPACKET_SIZE);

        usbd_reg_endpoint(dev, WUSB_EP1_RX, cdc_loopback);
        usbd_reg_endpoint(dev, WUSB_EP1_TX, cdc_loopback);

        usbd_ep_write(dev, WUSB_EP1_TX, 0, 0);
        return usbd_ack;
    default:
        return usbd_fail;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////// DEMO MAIN //////////////////////////////////////////////////
static void cdc_loopback(usbd_device* dev, uint8_t event, uint8_t ep) {
	int _t;
	switch (event) {
	case usbd_evt_eptx:
		_t = usbd_ep_write(dev,
		                   WUSB_EP1_TX,
		                   &fifo[0],
		                   (fpos < WUSB_EP1_MAXPACKET_SIZE) ? fpos : WUSB_EP1_MAXPACKET_SIZE);
		if (_t > 0) {
			memmove(&fifo[0], &fifo[_t], fpos - _t);
			fpos -= _t;
		}
	case usbd_evt_eprx:
		if (fpos < (sizeof(fifo) - WUSB_EP1_MAXPACKET_SIZE)) {
			_t = usbd_ep_read(dev, WUSB_EP1_RX, &fifo[fpos], WUSB_EP1_MAXPACKET_SIZE);
			if (_t > 0) {
				fpos += _t;
			}
		}
	default:
		break;
	}
}

static void wusb_init_usbd(void) {

    usbd_init(&udev, &usbd_hw, WUSB_EP0_MAXPACKET_SIZE, wusb_control_buffer, sizeof(wusb_control_buffer));
    usbd_reg_config(&udev, wusb_setconf);
    usbd_reg_control(&udev, wusb_control);
    usbd_reg_descr(&udev, wusb_getdesc);
}

#if defined(WUSB_USE_IRQ)
#if defined(STM32L052xx)
#define USB_HANDLER     USB_IRQHandler
#define USB_NVIC_IRQ    USB_IRQn
#elif defined(STM32L100xC)
#define USB_HANDLER     USB_LP_IRQHandler
#define USB_NVIC_IRQ    USB_LP_IRQn
#elif defined(STM32L476xx)
#define USB_HANDLER     OTG_FS_IRQHandler
#define USB_NVIC_IRQ    OTG_FS_IRQn
#elif defined(STM32F103x6)
#define USB_HANDLER     USB_LP_CAN1_RX0_IRQHandler
#define USB_NVIC_IRQ    USB_LP_CAN1_RX0_IRQn
#elif defined(STM32F103xE)
#define USB_HANDLER     USB_LP_CAN1_RX0_IRQHandler
#define USB_NVIC_IRQ    USB_LP_CAN1_RX0_IRQn
#elif defined(STM32F429xx)
#define USB_HANDLER     OTG_FS_IRQHandler
#define USB_NVIC_IRQ    OTG_FS_IRQn
#else
#error Not supported
#endif
#endif

void USB_HANDLER(void) {
    usbd_poll(&udev);
}

#ifdef CUBE_CALLS_MAIN
	void wusb_main(void) {
#else
	void main(void) {
#endif
    wusb_init_usbd();

#ifdef USB_NVIC_IRQ
    NVIC_EnableIRQ(USB_NVIC_IRQ);
#endif
    usbd_enable(&udev, true);
    usbd_connect(&udev, true);
    uint32_t curTick = HAL_GetTick();
    while (true) {

#ifndef USB_NVIC_IRQ
		usbd_poll(&udev);
#endif

        const uint32_t nextTick = HAL_GetTick();
        if (curTick + 1000 < nextTick) {
            curTick = nextTick;
            HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
        }
#ifdef USB_NVIC_IRQ
        __WFI();
#endif
    }
}
