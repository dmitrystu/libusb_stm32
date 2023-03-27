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

#include <stdint.h>
#include <stdbool.h>
#include "stm32_compat.h"
#include "usb.h"

#if defined(USBD_STM32G0B1)

#ifndef USB_PMASIZE
    #pragma message "PMA memory size is not defined. Use 2k by default"
    #define USB_PMASIZE 0x800
#endif

#define USB_EP_SWBUF_TX     USB_EP_DTOG_RX
#define USB_EP_SWBUF_RX     USB_EP_DTOG_TX

#define EP_TOGGLE_SET(epr, bits, mask) *(epr) = (*(epr) ^ (bits)) & (USB_CHEP_REG_MASK | (mask))

#define EP_TX_STALL(epr)    EP_TOGGLE_SET((epr), USB_EP_TX_STALL,                   USB_EP_TX_STTX)
#define EP_RX_STALL(epr)    EP_TOGGLE_SET((epr), USB_EP_RX_STALL,                   USB_EP_RX_STRX)
#define EP_TX_UNSTALL(epr)  EP_TOGGLE_SET((epr), USB_EP_TX_NAK,                     USB_EP_TX_STTX | USB_EP_DTOG_TX)
#define EP_RX_UNSTALL(epr)  EP_TOGGLE_SET((epr), USB_EP_RX_VALID,                   USB_EP_RX_STRX | USB_EP_DTOG_RX)
#define EP_DTX_UNSTALL(epr) EP_TOGGLE_SET((epr), USB_EP_TX_VALID,                   USB_EP_TX_STTX | USB_EP_DTOG_TX | USB_EP_SWBUF_TX)
#define EP_DRX_UNSTALL(epr) EP_TOGGLE_SET((epr), USB_EP_RX_VALID | USB_EP_SWBUF_RX, USB_EP_RX_STRX | USB_EP_DTOG_RX | USB_EP_SWBUF_RX)
#define EP_TX_VALID(epr)    EP_TOGGLE_SET((epr), USB_EP_TX_VALID,                   USB_EP_TX_STTX)
#define EP_RX_VALID(epr)    EP_TOGGLE_SET((epr), USB_EP_RX_VALID,                   USB_EP_RX_STRX)

#define STATUS_VAL(x)   (USBD_HW_BC | (x))

typedef struct {
//    uint16_t    addr;
//    uint16_t    cnt;
    uint32_t    addr_cnt;
} pma_rec;

static inline uint16_t pma_addr(uint32_t addr_cnt) {
    return (addr_cnt & 0xffff);
}

static inline uint16_t pma_cnt(uint32_t addr_cnt) {
    return (addr_cnt >> 16);
}

typedef union pma_table {
    struct {
    pma_rec     tx;
    pma_rec     rx;
    };
    struct {
    pma_rec     tx0;
    pma_rec     tx1;
    };
    struct {
    pma_rec     rx0;
    pma_rec     rx1;
    };
} pma_table;


/** \brief Helper function. Returns pointer to the buffer descriptor table.
 */
inline static pma_table *EPT(uint8_t ep) {
    return (pma_table*)((ep & 0x07) * 8 + USB_DRD_PMAADDR);

}

/** \brief Helper function. Returns pointer to the endpoint control register.
 */
inline static volatile uint16_t *EPR(uint8_t ep) {
    return (uint16_t*)((ep & 0x07) * 4 + USB_BASE);
}


/** \brief Helper function. Returns next available PMA buffer.
 *
 * \param sz uint16_t Requested buffer size.
 * \return uint16_t Buffer address for PMA table.
 * \note PMA buffers grown from top to bottom like stack.
 */
static uint16_t get_next_pma(uint16_t sz) {
    unsigned _result = USB_PMASIZE;
    for (int i = 0; i < 8; i++) {
        pma_table *tbl = EPT(i);
        uint16_t pmaaddr = pma_addr(tbl->rx.addr_cnt);
        if ((pmaaddr) && (pmaaddr < _result)) _result = pmaaddr;
        pmaaddr = pma_addr(tbl->tx.addr_cnt);
        if ((pmaaddr) && (pmaaddr < _result)) _result = pmaaddr;
    }
    return (_result < (0x020 + sz)) ? 0 : (_result - sz);
}

static uint32_t getinfo(void) {
    if (!(RCC->APBENR1 & RCC_APBENR1_USBEN)) return STATUS_VAL(0);
    if (USB_DRD_FS->BCDR & USB_BCDR_DPPU) return STATUS_VAL(USBD_HW_ENABLED | USBD_HW_SPEED_FS);
    return STATUS_VAL(USBD_HW_ENABLED);
}

static void ep_setstall(uint8_t ep, bool stall) {
    volatile uint16_t *reg = EPR(ep);
    /* ISOCHRONOUS endpoint can't be stalled or unstalled */
    if (USB_EP_ISOCHRONOUS == (*reg & USB_EP_TYPE_MASK)) return;
    /* If it's an IN endpoint */
    if (ep & 0x80) {
        /* DISABLED endpoint can't be stalled or unstalled */
        if (USB_EP_TX_DIS == (*reg & USB_EP_TX_STTX)) return;
        if (stall) {
            EP_TX_STALL(reg);
        } else {
            /* if it's a doublebuffered endpoint */
            if ((USB_EP_KIND | USB_EP_BULK) == (*reg & (USB_EP_TYPE_MASK | USB_EP_KIND))) {
                /* set endpoint to VALID and clear DTOG_TX & SWBUF_TX */
                EP_DTX_UNSTALL(reg);
            } else {
                /* set endpoint to NAKED and clear DTOG_TX */
                EP_TX_UNSTALL(reg);
            }
        }
    } else {
        if (USB_EP_RX_DIS == (*reg & USB_EP_RX_STRX)) return;
        if (stall) {
            EP_RX_STALL(reg);
        } else {
            /* if it's a doublebuffered endpoint */
            if ((USB_EP_KIND | USB_EP_BULK) == (*reg & (USB_EP_TYPE_MASK | USB_EP_KIND))) {
                /* set endpoint to VALID, clear DTOG_RX, set SWBUF_RX */
                EP_DRX_UNSTALL(reg);
            } else {
                /* set endpoint to VALID and clear DTOG_RX */
                EP_RX_UNSTALL(reg);
            }
        }
    }
}

static bool ep_isstalled(uint8_t ep) {
    if (ep & 0x80) {
        return (USB_EP_TX_STALL == (USB_EP_TX_STTX & *EPR(ep)));
    } else {
        return (USB_EP_RX_STALL == (USB_EP_RX_STRX & *EPR(ep)));
    }
}

static void enable(bool enable) {
    if (enable) {
        RCC->APBENR1  |=  RCC_APBENR1_USBEN;
        RCC->APBRSTR1 |= RCC_APBRSTR1_USBRST;
        RCC->APBRSTR1 &= ~RCC_APBRSTR1_USBRST;
        USB_DRD_FS->CNTR = USB_CNTR_CTRM | USB_CNTR_RESETM | USB_CNTR_ERRM |
#if !defined(USBD_SOF_DISABLED)
        USB_CNTR_SOFM |
#endif
        USB_CNTR_SUSPM | USB_CNTR_WKUPM;
    } else if (RCC->APBENR1 & RCC_APBENR1_USBEN) {
        USB_DRD_FS->BCDR = 0;
        RCC->APBRSTR1 |= RCC_APBRSTR1_USBRST;
        RCC->APBENR1 &= ~RCC_APBENR1_USBEN;
    }
}

static uint8_t connect(bool connect) {
    uint8_t res;
    USB_DRD_FS->BCDR = USB_BCDR_BCDEN | USB_BCDR_DCDEN;
    if (USB_DRD_FS->BCDR & USB_BCDR_DCDET) {
        USB_DRD_FS->BCDR = USB_BCDR_BCDEN | USB_BCDR_PDEN;
        if (USB_DRD_FS->BCDR & USB_BCDR_PS2DET) {
            res = usbd_lane_unk;
        } else if (USB_DRD_FS->BCDR & USB_BCDR_PDET) {
            USB_DRD_FS->BCDR = USB_BCDR_BCDEN | USB_BCDR_SDEN;
            if (USB_DRD_FS->BCDR & USB_BCDR_SDET) {
                res = usbd_lane_dcp;
            } else {
                res = usbd_lane_cdp;
            }
        } else {
            res = usbd_lane_sdp;
        }
    } else {
        res = usbd_lane_dsc;
    }
    USB_DRD_FS->BCDR = (connect) ? USB_BCDR_DPPU : 0;
    return res;
}

static void setaddr (uint8_t addr) {
    USB_DRD_FS->DADDR = USB_DADDR_EF | addr;
}

static bool ep_config(uint8_t ep, uint8_t eptype, uint16_t epsize) {
    volatile uint16_t *reg = EPR(ep);
    pma_table *tbl = EPT(ep);
    /* epsize must be 2-byte aligned */
    epsize = (~0x01U) & (epsize + 1);

    switch (eptype) {
    case USB_EPTYPE_CONTROL:
        *reg = USB_EP_CONTROL | (ep & 0x07);
        break;
    case USB_EPTYPE_ISOCHRONUS:
        *reg = USB_EP_ISOCHRONOUS | (ep & 0x07);
        break;
    case USB_EPTYPE_BULK:
        *reg = USB_EP_BULK | (ep & 0x07);
        break;
    case USB_EPTYPE_BULK | USB_EPTYPE_DBLBUF:
        *reg = USB_EP_BULK | USB_EP_KIND | (ep & 0x07);
        break;
    default:
        *reg = USB_EP_INTERRUPT | (ep & 0x07);
        break;
    }
    /* if it TX or CONTROL endpoint */
    if ((ep & 0x80) || (eptype == USB_EPTYPE_CONTROL)) {
        uint16_t _pma;
        _pma = get_next_pma(epsize);
        if (_pma == 0) return false;
        tbl->tx.addr_cnt = _pma; // _pma | (0 << 16)
        if ((eptype == USB_EPTYPE_ISOCHRONUS) ||
            (eptype == (USB_EPTYPE_BULK | USB_EPTYPE_DBLBUF))) {
            _pma = get_next_pma(epsize);
            if (_pma == 0) return false;
            tbl->tx1.addr_cnt = _pma; // _pma | (0 << 16)
            EP_DTX_UNSTALL(reg);
        } else {
            EP_TX_UNSTALL(reg);
        }
    }
    if (!(ep & 0x80)) {
        uint16_t _rxcnt;
        uint16_t _pma;
        if (epsize > 62) {
            /* using 32-byte blocks. epsize must be 32-byte aligned */
            epsize = (~0x1FU) & (epsize + 0x1FU);
            _rxcnt = 0x8000 - 0x400 + (epsize << 5);
        } else {
            _rxcnt = epsize << 9;
        }
        _pma = get_next_pma(epsize);
        if (_pma == 0) return false;
        tbl->rx.addr_cnt = _pma | (_rxcnt << 16);
        if ((eptype == USB_EPTYPE_ISOCHRONUS) ||
            (eptype == (USB_EPTYPE_BULK | USB_EPTYPE_DBLBUF))) {
            _pma = get_next_pma(epsize);
            if (_pma == 0) return false;
            tbl->rx0.addr_cnt = _pma | (_rxcnt << 16);
            EP_DRX_UNSTALL(reg);
        } else {
            EP_RX_UNSTALL(reg);
        }
    }
    return true;
}

static void ep_deconfig(uint8_t ep) {
    pma_table *ept = EPT(ep);
    *EPR(ep) &= ~USB_CHEP_REG_MASK;
    ept->rx.addr_cnt = 0;
    ept->tx.addr_cnt = 0;
}

static uint16_t pma_read (uint8_t *buf, uint16_t blen, pma_rec *rx) {
    uint32_t *pma = (void*)(USB_DRD_PMAADDR + pma_addr(rx->addr_cnt));
    uint16_t rxcnt = pma_cnt(rx->addr_cnt) & 0x07FF;
    rx->addr_cnt &= ~0x7FF0000;

    if (blen > rxcnt) {
        blen = rxcnt;
    }
    rxcnt = blen;
    uint16_t wcnt = blen >> 2;
    while (wcnt) {
        __UNALIGNED_UINT32_WRITE(buf, *pma);
        wcnt --;
        buf += 4;
        pma++;
    }
    blen &= 0x03;
    switch(blen) {
    default:
    case 0:
        break;
    case 1: {
        uint32_t t = *pma;
        *buf = t & 0xff;
    }
    break;
    case 2: {
        uint32_t t = *pma;
        *buf++ = t & 0xff;
        *buf = (t >> 8) & 0xff;
    }
    break;
    case 3: {
        uint32_t t = *pma;
        *buf++ = t & 0xff;
        *buf++ = (t >> 8) & 0xff;
        *buf = (t >> 16) & 0xff;
    }
    break;
    }
    return rxcnt;
}

static int32_t ep_read(uint8_t ep, void *buf, uint16_t blen) {
    pma_table *tbl = EPT(ep);
    volatile uint16_t *reg = EPR(ep);
    switch (*reg & (USB_EP_RX_STRX | USB_EP_TYPE_MASK | USB_EP_KIND)) {
    /* doublebuffered bulk endpoint */
    case (USB_EP_RX_VALID | USB_EP_BULK | USB_EP_KIND):
        /* switching SWBUF if EP is NAKED */
        switch (*reg & (USB_EP_DTOG_RX | USB_EP_SWBUF_RX)) {
        case 0:
        case (USB_EP_DTOG_RX | USB_EP_SWBUF_RX):
            *reg = (*reg & USB_CHEP_REG_MASK) | USB_EP_SWBUF_RX;
        	break;
        default:
            break;
        }
        if (*reg & USB_EP_SWBUF_RX) {
            return pma_read(buf, blen, &(tbl->rx1));
        } else {
            return pma_read(buf, blen, &(tbl->rx0));
        }
    /* isochronous endpoint */
    case (USB_EP_RX_VALID | USB_EP_ISOCHRONOUS):
        if (*reg & USB_EP_DTOG_RX) {
            return pma_read(buf, blen, &(tbl->rx1));
        } else {
            return pma_read(buf, blen, &(tbl->rx0));
        }
    /* regular endpoint */
    case (USB_EP_RX_NAK | USB_EP_BULK):
    case (USB_EP_RX_NAK | USB_EP_CONTROL):
    case (USB_EP_RX_NAK | USB_EP_INTERRUPT):
        {
        int32_t res = pma_read(buf, blen, &(tbl->rx));
        /* setting endpoint to VALID state */
        EP_RX_VALID(reg);
        return res;
        }
    /* invalid or not ready */
    default:
        return -1;
    }
}

static void pma_write(const uint8_t *buf, uint16_t blen, pma_rec *tx) {
    uint32_t *pma = (void*)(USB_DRD_PMAADDR + pma_addr(tx->addr_cnt));
    //tx->addr_cnt = (blen << 16) | pma_addr(tx->addr_cnt);
    tx->addr_cnt &= 0x0000ffff;
    tx->addr_cnt |= (blen << 16);
    uint16_t wcnt = blen >> 2;
    while (wcnt) {
        *pma++ = __UNALIGNED_UINT32_READ(buf);
        buf += 4;
        wcnt--;
    }
    blen &= 0x3;
    switch(blen) {
    case 1:
        *pma = *buf;
        break;
    case 2:
        *pma = buf[0] | (buf[1] << 8);
        break;
    case 3:
        *pma = buf[0] | (buf[1] << 8) | (buf[2] << 16);
        break;
    case 0:
    default:
        break;
    }
}

static int32_t ep_write(uint8_t ep, const void *buf, uint16_t blen) {
    pma_table *tbl = EPT(ep);
    volatile uint16_t *reg = EPR(ep);
    switch (*reg & (USB_EP_TX_STTX | USB_EP_TYPE_MASK | USB_EP_KIND)) {
    /* doublebuffered bulk endpoint */
    case (USB_EP_TX_NAK   | USB_EP_BULK | USB_EP_KIND):
        if (*reg & USB_EP_SWBUF_TX) {
            pma_write(buf, blen, &(tbl->tx1));
        } else {
            pma_write(buf, blen, &(tbl->tx0));
        }
        *reg = (*reg & USB_CHEP_REG_MASK) | USB_EP_SWBUF_TX;
        break;
    /* isochronous endpoint */
    case (USB_EP_TX_VALID | USB_EP_ISOCHRONOUS):
        if (!(*reg & USB_EP_DTOG_TX)) {
            pma_write(buf, blen, &(tbl->tx1));
        } else {
            pma_write(buf, blen, &(tbl->tx0));
        }
        break;
    /* regular endpoint */
    case (USB_EP_TX_NAK | USB_EP_BULK):
    case (USB_EP_TX_NAK | USB_EP_CONTROL):
    case (USB_EP_TX_NAK | USB_EP_INTERRUPT):
        pma_write(buf, blen, &(tbl->tx));
        EP_TX_VALID(reg);
        break;
    /* invalid or not ready */
    default:
        return -1;
    }
    return blen;
}

static uint16_t get_frame (void) {
    return USB_DRD_FS->FNR & USB_FNR_FN;
}

static void evt_poll(usbd_device *dev, usbd_evt_callback callback) {
    uint8_t _ev, _ep;
    uint16_t _istr = USB_DRD_FS->ISTR;
    _ep = _istr & USB_ISTR_IDN;
    if (_istr & USB_ISTR_CTR) {
        volatile uint16_t *reg = EPR(_ep);
        if (*reg & USB_EP_VTTX) {
            *reg &= (USB_CHEP_REG_MASK ^ USB_EP_VTTX);
            _ep |= 0x80;
            _ev = usbd_evt_eptx;
        } else {
            *reg &= (USB_CHEP_REG_MASK ^ USB_EP_VTRX);
            _ev = (*reg & USB_EP_SETUP) ? usbd_evt_epsetup : usbd_evt_eprx;
        }
    } else if (_istr & USB_ISTR_RESET) {
        USB_DRD_FS->ISTR &= ~USB_ISTR_RESET;
        for (int i = 0; i < 8; i++) {
            ep_deconfig(i);
        }
        _ev = usbd_evt_reset;
#if !defined(USBD_SOF_DISABLED)
    } else if (_istr & USB_ISTR_SOF) {
        _ev = usbd_evt_sof;
        USB_DRD_FS->ISTR &= ~USB_ISTR_SOF;
#endif
    } else if (_istr & USB_ISTR_WKUP) {
        _ev = usbd_evt_wkup;
        USB_DRD_FS->CNTR &= ~USB_CNTR_SUSPEN;
        USB_DRD_FS->ISTR &= ~USB_ISTR_WKUP;
    } else if (_istr & USB_ISTR_SUSP) {
        _ev = usbd_evt_susp;
        USB_DRD_FS->CNTR |= USB_CNTR_SUSPEN;
        USB_DRD_FS->ISTR &= ~USB_ISTR_SUSP;
    } else if (_istr & USB_ISTR_ERR) {
        USB_DRD_FS->ISTR &= ~USB_ISTR_ERR;
        _ev = usbd_evt_error;
    } else {
        return;
    }
    callback(dev, _ev, _ep);
}

static uint32_t fnv1a32_turn (uint32_t fnv, uint32_t data ) {
    for (int i = 0; i < 4 ; i++) {
        fnv ^= (data & 0xFF);
        fnv *= 16777619;
        data >>= 8;
    }
    return fnv;
}

static uint16_t get_serialno_desc(void *buffer) {
    struct  usb_string_descriptor *dsc = buffer;
    uint16_t *str = dsc->wString;
    uint32_t fnv = 2166136261;
    fnv = fnv1a32_turn(fnv, *(uint32_t*)(UID_BASE + 0x00));
    fnv = fnv1a32_turn(fnv, *(uint32_t*)(UID_BASE + 0x04));
    fnv = fnv1a32_turn(fnv, *(uint32_t*)(UID_BASE + 0x14));
    for (int i = 28; i >= 0; i -= 4 ) {
        uint16_t c = (fnv >> i) & 0x0F;
        c += (c < 10) ? '0' : ('A' - 10);
        *str++ = c;
    }
    dsc->bDescriptorType = USB_DTYPE_STRING;
    dsc->bLength = 18;
    return 18;
}

 __attribute__((externally_visible)) const struct usbd_driver usbd_devfs = {
    getinfo,
    enable,
    connect,
    setaddr,
    ep_config,
    ep_deconfig,
    ep_read,
    ep_write,
    ep_setstall,
    ep_isstalled,
    evt_poll,
    get_frame,
    get_serialno_desc,
};

#endif //USBD_STM32L052
