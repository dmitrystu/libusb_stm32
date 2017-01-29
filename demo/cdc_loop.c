#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "stm32.h"
#include "usb.h"
#include "inc/usb_cdc.h"

#define CDC_EP0_SIZE    0x08
#define CDC_RXD_EP      0x01
#define CDC_TXD_EP      0x82
#define CDC_DATA_SZ     0x40
#define CDC_NTF_EP      0x83
#define CDC_NTF_SZ      0x08
#define CDC_LOOPBACK

struct cdc_config {
    struct usb_config_descriptor        config;
    struct usb_interface_descriptor     comm;
    struct usb_cdc_header_desc          cdc_hdr;
    struct usb_cdc_call_mgmt_desc       cdc_mgmt;
    struct usb_cdc_acm_desc             cdc_acm;
    struct usb_cdc_union_desc           cdc_union;
    struct usb_endpoint_descriptor      comm_ep;
    struct usb_interface_descriptor     data;
    struct usb_endpoint_descriptor      data_eprx;
    struct usb_endpoint_descriptor      data_eptx;
} __attribute__((packed));

static const struct usb_device_descriptor device_desc = {
    .bLength            = sizeof(struct usb_device_descriptor),
    .bDescriptorType    = USB_DTYPE_DEVICE,
    .bcdUSB             = VERSION_BCD(2,0,0),
    .bDeviceClass       = USB_CLASS_CDC,
    .bDeviceSubClass    = USB_SUBCLASS_NONE,
    .bDeviceProtocol    = USB_PROTO_NONE,
    .bMaxPacketSize0    = CDC_EP0_SIZE,
    .idVendor           = 0x0483,
    .idProduct          = 0x5740,
    .bcdDevice          = VERSION_BCD(1,0,0),
    .iManufacturer      = 1,
    .iProduct           = 2,
    .iSerialNumber      = INTSERIALNO_DESCRIPTOR,
    .bNumConfigurations = 1,
};

static const struct cdc_config config_desc = {
    .config = {
        .bLength                = sizeof(struct usb_config_descriptor),
        .bDescriptorType        = USB_DTYPE_CONFIGURATION,
        .wTotalLength           = sizeof(struct cdc_config),
        .bNumInterfaces         = 2,
        .bConfigurationValue    = 1,
        .iConfiguration         = NO_DESCRIPTOR,
        .bmAttributes           = USB_CFG_ATTR_RESERVED | USB_CFG_ATTR_SELFPOWERED,
        .bMaxPower              = USB_CFG_POWER_MA(100),
    },
    .comm = {
        .bLength                = sizeof(struct usb_interface_descriptor),
        .bDescriptorType        = USB_DTYPE_INTERFACE,
        .bInterfaceNumber       = 0,
        .bAlternateSetting      = 0,
        .bNumEndpoints          = 1,
        .bInterfaceClass        = USB_CLASS_CDC,
        .bInterfaceSubClass     = USB_CDC_SUBCLASS_ACM,
        .bInterfaceProtocol     = USB_CDC_PROTO_V25TER,
        .iInterface             = NO_DESCRIPTOR,
    },
    .cdc_hdr = {
        .bFunctionLength        = sizeof(struct usb_cdc_header_desc),
        .bDescriptorType        = USB_DTYPE_CS_INTERFACE,
        .bDescriptorSubType     = USB_DTYPE_CDC_HEADER,
        .bcdCDC                 = VERSION_BCD(1,1,0),
    },
    .cdc_mgmt = {
        .bFunctionLength        = sizeof(struct usb_cdc_call_mgmt_desc),
        .bDescriptorType        = USB_DTYPE_CS_INTERFACE,
        .bDescriptorSubType     = USB_DTYPE_CDC_CALL_MANAGEMENT,
        .bmCapabilities         = 0,
        .bDataInterface         = 1,

    },
    .cdc_acm = {
        .bFunctionLength        = sizeof(struct usb_cdc_acm_desc),
        .bDescriptorType        = USB_DTYPE_CS_INTERFACE,
        .bDescriptorSubType     = USB_DTYPE_CDC_ACM,
        .bmCapabilities         = 0,
    },
    .cdc_union = {
        .bFunctionLength        = sizeof(struct usb_cdc_union_desc),
        .bDescriptorType        = USB_DTYPE_CS_INTERFACE,
        .bDescriptorSubType     = USB_DTYPE_CDC_UNION,
        .bMasterInterface0      = 0,
        .bSlaveInterface0       = 1,
    },
    .comm_ep = {
        .bLength                = sizeof(struct usb_endpoint_descriptor),
        .bDescriptorType        = USB_DTYPE_ENDPOINT,
        .bEndpointAddress       = CDC_NTF_EP,
        .bmAttributes           = USB_EPTYPE_INTERRUPT,
        .wMaxPacketSize         = CDC_NTF_SZ,
        .bInterval              = 0xFF,
    },
    .data = {
        .bLength                = sizeof(struct usb_interface_descriptor),
        .bDescriptorType        = USB_DTYPE_INTERFACE,
        .bInterfaceNumber       = 1,
        .bAlternateSetting      = 0,
        .bNumEndpoints          = 2,
        .bInterfaceClass        = USB_CLASS_CDC_DATA,
        .bInterfaceSubClass     = USB_SUBCLASS_NONE,
        .bInterfaceProtocol     = USB_PROTO_NONE,
        .iInterface             = NO_DESCRIPTOR,
    },
    .data_eprx = {
        .bLength                = sizeof(struct usb_endpoint_descriptor),
        .bDescriptorType        = USB_DTYPE_ENDPOINT,
        .bEndpointAddress       = CDC_RXD_EP,
        .bmAttributes           = USB_EPTYPE_BULK,
        .wMaxPacketSize         = CDC_DATA_SZ,
        .bInterval              = 0x01,
    },
    .data_eptx = {
        .bLength                = sizeof(struct usb_endpoint_descriptor),
        .bDescriptorType        = USB_DTYPE_ENDPOINT,
        .bEndpointAddress       = CDC_TXD_EP,
        .bmAttributes           = USB_EPTYPE_BULK,
        .wMaxPacketSize         = CDC_DATA_SZ,
        .bInterval              = 0x01,
    },
};

static const struct usb_string_descriptor lang_desc     = USB_ARRAY_DESC(USB_LANGID_ENG_US);
static const struct usb_string_descriptor manuf_desc_en = USB_STRING_DESC("Open source USB stack for STM32");
static const struct usb_string_descriptor prod_desc_en  = USB_STRING_DESC("CDC Loopback demo");
static const struct usb_string_descriptor *const dtable[] = {
    &lang_desc,
    &manuf_desc_en,
    &prod_desc_en,
};

usbd_device udev;
uint32_t	ubuf[0x20];
uint8_t     dbuf[0x100];

static struct usb_cdc_line_coding cdc_line = {
    .dwDTERate          = 38400,
    .bCharFormat        = USB_CDC_1_STOP_BITS,
    .bParityType        = USB_CDC_NO_PARITY,
    .bDataBits          = 8,
};

static usbd_respond cdc_getdesc (usbd_ctlreq *req, void **address, uint16_t *length) {
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
        } else {
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
};


static usbd_respond cdc_control(usbd_device *dev, usbd_ctlreq *req, usbd_rqc_callback *callback) {
    if (((USB_REQ_RECIPIENT | USB_REQ_TYPE) & req->bmRequestType) != (USB_REQ_INTERFACE | USB_REQ_CLASS)) return usbd_fail;
    switch (req->bRequest) {
    case USB_CDC_SET_CONTROL_LINE_STATE:
        return usbd_ack;
    case USB_CDC_SET_LINE_CODING:
        memmove( req->data, &cdc_line, sizeof(cdc_line));
        return usbd_ack;
    case USB_CDC_GET_LINE_CODING:
        dev->status.data_ptr = &cdc_line;
        dev->status.data_count = sizeof(cdc_line);
        return usbd_ack;
    default:
        return usbd_fail;
    }
}


static void cdc_rxonly (usbd_device *dev, uint8_t event, uint8_t ep) {
    usbd_ep_read(dev, ep, dbuf, CDC_DATA_SZ);
}

static void cdc_txonly(usbd_device *dev, uint8_t event, uint8_t ep) {
    uint8_t _t = dev->driver->frame_no();
    memset(dbuf, _t, CDC_DATA_SZ);   
    usbd_ep_write(dev, ep, dbuf, CDC_DATA_SZ);

}


static void cdc_loopback (usbd_device *dev, uint8_t event, uint8_t ep) {
#define WAIT_TX     0x01
#define WAIT_RX     0x02
    static uint16_t rpos = 0;
    static uint8_t  flags = WAIT_RX;
    int _t;
    switch (event) {
read_delayed:
    case usbd_evt_eprx:
        if (rpos > (sizeof(dbuf) - CDC_DATA_SZ)) {
            /* buffer overflow. stop accepting data */
            flags &= ~WAIT_RX;
        } else {
            _t = usbd_ep_read(dev, CDC_RXD_EP, &dbuf[rpos], CDC_DATA_SZ);
            if (_t > 0) {
                rpos += _t;
            }
        }
        if (flags & WAIT_TX) break;
        flags |= WAIT_TX;
    case usbd_evt_eptx:
        if (rpos > 0) {
            _t = (rpos > CDC_DATA_SZ) ? CDC_DATA_SZ : rpos;
            _t = usbd_ep_write(dev, CDC_TXD_EP, &dbuf[0], _t);
            memmove(&dbuf[0], &dbuf[_t], (rpos - _t));
            rpos -= _t;
        } else {
            flags &= ~WAIT_TX;
            if (flags & WAIT_RX) break;
            flags |= WAIT_RX;
            goto read_delayed;
        }
    default:
        break;
    }
}

static usbd_respond cdc_setconf (usbd_device *dev, uint8_t cfg) {
    switch (cfg) {
    case 0:
        /* deconfiguring device */
        usbd_ep_deconfig(dev, CDC_RXD_EP);
        usbd_ep_deconfig(dev, CDC_TXD_EP);
        usbd_ep_deconfig(dev, CDC_NTF_EP);
        usbd_reg_endpoint(dev, CDC_RXD_EP, 0);
        usbd_reg_endpoint(dev, CDC_TXD_EP, 0);
        return usbd_ack;
    case 1:
        /* configuring device */
        usbd_ep_config(dev, CDC_RXD_EP, USB_EPTYPE_BULK | USB_EPTYPE_DBLBUF, CDC_DATA_SZ);
        usbd_ep_config(dev, CDC_TXD_EP, USB_EPTYPE_BULK | USB_EPTYPE_DBLBUF, CDC_DATA_SZ);
        usbd_ep_config(dev, CDC_NTF_EP, USB_EPTYPE_INTERRUPT, CDC_NTF_SZ);
#if defined(CDC_LOOPBACK)
        usbd_reg_endpoint(dev, CDC_RXD_EP, cdc_loopback);
        usbd_reg_endpoint(dev, CDC_TXD_EP, cdc_loopback);
#else
        usbd_reg_endpoint(dev, CDC_RXD_EP, cdc_rxonly);
        usbd_reg_endpoint(dev, CDC_TXD_EP, cdc_txonly);
        usbd_ep_write(dev, CDC_TXD_EP, 0, 0);
#endif
        return usbd_ack;
    default:
        return usbd_fail;
    }
}

static void cdc_init_usbd(void) {
    usbd_init(&udev, &usbd_hw, CDC_EP0_SIZE, ubuf, sizeof(ubuf));
    usbd_reg_config(&udev, cdc_setconf);
    usbd_reg_control(&udev, cdc_control);
    usbd_reg_descr(&udev, cdc_getdesc);
}

static void cdc_init_rcc(void) {
    BST(RCC->APB1ENR, RCC_APB1ENR_PWREN);
    BMD(PWR->CR, PWR_CR_VOS, PWR_CR_VOS_0);
    WBC(PWR->CSR, PWR_CSR_VOSF);
    /* set FLASH latency to 1 */
#if defined(STM32L1)
    BST(FLASH->ACR, FLASH_ACR_ACC64);
#endif
    BST(FLASH->ACR, FLASH_ACR_LATENCY);
    /* set PLL clock HSI * 6/4 (24 MHz) */
    BMD(RCC->CFGR, RCC_CFGR_PLLDIV | RCC_CFGR_PLLMUL | RCC_CFGR_PLLSRC, RCC_CFGR_PLLDIV3 | RCC_CFGR_PLLMUL6);
    BST(RCC->CR, RCC_CR_HSION);
    WBS(RCC->CR, RCC_CR_HSIRDY);
    BST(RCC->CR, RCC_CR_PLLON);
    WBS(RCC->CR, RCC_CR_PLLRDY);
    /* switch clock to PLL */
    BMD(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
    WVL(RCC->CFGR, RCC_CFGR_SWS, RCC_CFGR_SWS_PLL);
}

void __libc_init_array(void) {

}

void SystemInit(void) {
    cdc_init_rcc();
}


void main(void) {
    cdc_init_usbd();
    usbd_control(&udev, usbd_cmd_enable);
    usbd_control(&udev, usbd_cmd_connect);
    while(1) {
    usbd_poll(&udev);
    }
}
