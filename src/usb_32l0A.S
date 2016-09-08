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

#if !defined (__ASSEMBLER__)
    #define __ASSEMBLER__
#endif
#include "..\inc\usbd_core.h"

#define USB_EPBASE  0x40005C00
#define USB_REGBASE 0x40005C40
#define USB_PMABASE 0x40006000
#define RCC_BASE    0x40021000
#define UID_BASE    0x1FF80050

#define EP_SETUP    0x0800
#define EP_TYPE     0x0600
#define EP_KIND     0x0100
#define EP_ADDR     0x000F

#define EP_RX_CTR   0x8000
#define EP_RX_DTOG  0x4000
#define EP_RX_STAT  0x3000
#define EP_RX_SWBUF 0x0040

#define EP_RX_DIS   0x0000
#define EP_RX_STAL  0x1000
#define EP_RX_NAK   0x2000
#define EP_RX_VAL   0x3000

#define EP_TX_CTR   0x0080
#define EP_TX_DTOG  0x0040
#define EP_TX_STAT  0x0030
#define EP_TX_SWBUF 0x4000

#define EP_TX_DIS   0x0000
#define EP_TX_STAL  0x0010
#define EP_TX_NAK   0x0020
#define EP_TX_VAL   0x0030


#define EP_NOTOG    (EP_RX_CTR | EP_TX_CTR | EP_SETUP | EP_TYPE | EP_KIND | EP_ADDR)

#define TGL_SET(mask, bits)  ((EP_NOTOG | (mask))<<16 | (bits))

    .syntax unified
    .cpu cortex-m0plus
    .text
    .thumb


    .globl  usb_stml0a
    .align  2
usb_stml0a:
    .long   _enable
    .long   _reset
    .long   _connect
    .long   _setaddr
    .long   _ep_config
    .long   _ep_deconfig
    .long   _ep_read
    .long   _ep_write
    .long   _ep_setstall
    .long   _ep_isstalled
    .long   _evt_poll
    .long   _get_serial_desc
    .size   usb_stml0a, . - usb_stml0a


    .thumb_func
    .type _get_serial_desc, %function

/*  uint16_t get_serial_desc (void *buffer)
 *  R0 <- buffer for the string descriptor
 *  descrpitor size -> R0
 */
_get_serial_desc:
    push    {r4, r5, lr}
    movs    r1,18               //descriptor size 18 bytes
    strb    r1,[r0]
    movs    r1, #0x03           //DTYPE_STRING
    strb    r1,[r0, #0x01]
    ldr     r5, .L_uid_base     //UID3 this is the serial number
    ldr     r4, .L_fnv1a_offset //FNV1A offset
    ldr     r2, [r5, 0x00]      //UID0
    bl      .L_fnv1a
    ldr     r2, [r5, 0x04]      //UID1
    bl      .L_fnv1a
    ldr     r2, [r5, 0x14]      //UID2
    bl      .L_fnv1a
    movs    r3, #28
.L_gsn_loop:
    movs    r1, r4
    lsrs    r1, r3
    lsls    r1, #28
    lsrs    r1, #28
    adds    r1, #0x30           //'0'
    cmp     r1, #0x3A
    blo     .L_gsn_store
    adds    r1, #0x07           //'A' - '0'
.L_gsn_store:
    adds    r0, #0x02
    strb    r1, [r0]
    lsrs    r1, #0x08
    strb    r1, [r0, #0x01]
    subs    r3, #0x04
    bpl     .L_gsn_loop
    movs    r0, #18
    pop     {r4, r5, pc}

.L_fnv1a:
    ldr     r1, .L_fnv1a_prime       //FNV1A prime
    movs    r3, #0xFF
    ands    r3, r2
    eors    r4, r3
    muls    r4, r1
    lsrs    r2, #8
    movs    r3, #0xFF
    ands    r3, r2
    eors    r4, r3
    muls    r4, r1
    lsrs    r2, #8
    movs    r3, #0xFF
    ands    r3, r2
    eors    r4, r3
    muls    r4, r1
    lsrs    r2, #8
    eors    r4, r2
    muls    r4, r1
    bx      lr

    .align 2
.L_fnv1a_prime:     .long   16777619
.L_fnv1a_offset:    .long   2166136261
.L_uid_base:        .long   UID_BASE

    .size _get_serial_desc, . - _get_serial_desc

    .thumb_func
    .type   _connect, %function
_connect:
    subs    r1, r0, #1
    sbcs    r0, r1
    lsls    r0, #15
    ldr     r1, =USB_REGBASE
    strh    r0, [r1, #0x18]      //USB->BCDR
    bx      lr
    .size   _connect, . - _connect


    .thumb_func
    .type   _setaddr, %function
_setaddr:
    ldr     r1, =USB_REGBASE
    adds    r0, #0x80
    strh    r0, [r1, #0x0C]     //USB->DADDR
    bx      lr
    .size   _setaddr, . - _setaddr

    .thumb_func
    .type   _reset, %function
_reset:
    ldr     r2, =USB_REGBASE
    movs    r0, #0x01           //FRES
    ldrh    r1, [r2]            //USB->CNTR
    orrs    r1, r0
    strh    r1, [r2]            // set FRES
    bics    r1, r0
    strh    r1, [r2]            // clr FRES
    bx      lr
    .size   _reset, . - _reset

    .thumb_func
    .type   _enable, %function
_enable:
    ldr     r1, =USB_REGBASE     //USB->CNTR
    ldr     r2, =RCC_BASE        //RCC
    movs    r3, #0x01
    lsls    r3, #23             //USBEN or USBRST
    tst     r0, r0
    beq     .L_disable
.L_enable:
    ldr     r0, [r2, #0x38]
    orrs    r0, r3
    str     r0, [r2, #0x38]     //RCC->APB1ENR |= USBEN
    ldr     r0, [r2, #0x28]
    orrs    r0, r3
    str     r0, [r2, #0x28]     //RCC->APB1RSTR |= USBRST
    bics    r0, r3
    str     r0, [r2, #0x28]     //RCC->APB1RSTR &= ~USBRST
    movs    r0, #0xBE
    lsls    r0, #0x08           // CTRM | ERRM | WKUPM | SUSPM | RESETM | SOFM
    strh    r0, [r1]            //set USB->CNTR
    bx      lr
.L_disable:
    ldr     r0, [r2, #0x38]
    tst     r0, r3
    beq     .L_enable_end       // usb is disabled
    movs    r0, #0x00
    strh    r0, [r1, #0x18]     //USB->BCDR disable USB I/O
    ldr     r0, [r2, #0x28]
    orrs    r0, r3
    str     r0, [r2, #0x28]     //RCC->APB1RSTR |= USBRST
    ldr     r0, [r2, #0x38]
    bics    r0, r3
    str     r0, [r2, #0x38]     //RCC->APB1ENR &= ~USBEN
.L_enable_end:
    bx      lr
    .size   _enable, . - _enable

    .thumb_func
    .type   _ep_setstall, %function

/*void ep_settall(uint8_t ep, bool stall)
 * in  R0 <- endpoint number
 * in  R1 <- 0 if unstall, !0 if stall
 */
_ep_setstall:
    lsls    r2, r0, #28
    lsrs    r2, #26
    ldr     r3, =USB_EPBASE
    adds    r3, r2          // epr -> r3
    movs    r2, 0x30        // TX_STAT_MASK -> r2
    cmp     r0, #80
    blo     .L_eps_rx
.L_eps_tx:
    ldr     r0, =TGL_SET((EP_TX_STAT | EP_TX_DTOG) , EP_TX_STAL)  //stall TX
    tst     r1, r1
    bne     .L_eps_reg_set
.L_eps_tx_unstall:
    ldrh    r1, [r3]        // *epr -> r1
    lsls    r1, #21
    lsrs    r1, #29         // EPTTYPE | EPKIND mask only
    ldr     r0, =TGL_SET((EP_TX_STAT | EP_TX_DTOG | EP_TX_SWBUF) , EP_TX_VAL) //unstall dblbulk or iso TX (VALID and clr DTOG_TX & SWBUF_TX)
    cmp     r1, #0x01       // if doublebuffered bulk endpoint
    beq     .L_eps_reg_set
    cmp     r1, #0x04       // if isochronous endpoint
    ldr     r0, =TGL_SET((EP_TX_STAT | EP_TX_DTOG) , EP_TX_NAK) // unstall other TX (NAKED + clr DTOG_TX)
    b       .L_eps_reg_set
.L_eps_rx:
    lsls    r2, #8          // RX_STAT_MASK -> R2
    ldr     r0,=TGL_SET((EP_RX_STAT | EP_RX_DTOG) , EP_RX_STAL)  //stall RX
    tst     r1, r1
    bne     .L_eps_reg_set
.L_eps_rx_unstall:
    ldrh    r1, [r3]        // *epr -> r1
    lsls    r1, #21
    lsrs    r1, #29         // EPTTYPE | EPKIND mask only
    ldr     r0, =TGL_SET((EP_RX_STAT | EP_RX_DTOG | EP_RX_SWBUF) , (EP_RX_VAL | EP_RX_SWBUF)) //unstall dblbulk or iso (VALID. clr DTOG_RX set SWBUF_RX)
    cmp     r1, #0x01       // if dblbulk
    beq     .L_eps_reg_set
    cmp     r1, #0x04       // if iso
    beq     .L_eps_reg_set
    ldr     r0, =TGL_SET((EP_RX_STAT | EP_RX_DTOG) , EP_RX_VAL) // unstall other RX (VALID + clr
/* R0 - mask and toggle bits
 * R2 - mask for STAT bits
 * R3 - endpoint register pointer
 */
.L_eps_reg_set:
    ldrh    r1, [r3]        // *epr -> r1
    ands    r2, r1          // check if endpoint disabled
    beq     .L_eps_exit     // do nothing
    eors    r1, r0
    lsrs    r0, #16
    ands    r1, r0
    strh    r1, [r3]
.L_eps_exit:
    bx      lr
    .size   _ep_setstall, . - _ep_setstall


    .thumb_func
    .type   _ep_isstalled, %function
/* bool ep_isstalled(uint8t ep) */
_ep_isstalled:
    ldr     r1, =USB_EPBASE
    lsls    r2, r0, #28
    lsrs    r2, #26
    ldr     r1, [r1, r2]
    lsls    r1, #17
    cmp     r0, #0x80
    bhs     .L_eis_check
    lsls    r1, #8
.L_eis_check:
    lsrs    r1, r1, #28
    subs    r1, #0x01
    subs    r0, r1, #0x01
    sbcs    r1, r1
    rsbs    r0, r1, #0
    bx      lr
    .size  _ep_isstalled, . - _ep_isstalled


    .thumb_func
    .type       _ep_read, %function
/* uint16_t _ep_read(uint8_t ep, void *buf, uint16_t blen)
 * in  R0 <- endpoint
 * in  R1 <- *buffer
 * in  R2 <- length of the buffer
 * out length of the recieved data -> R0
 */
_ep_read:
    push    {r4, r5, lr}
    ldr     r3, =USB_EPBASE
    ldr     r4, =USB_PMABASE
    lsls    r0, #28
    lsrs    r0, #26
    adds    r3, r0          // *EPR -> R3
    lsls    r0, #1
    adds    r4, r0          // *EPT -> R4
    ldrh    r0, [r3]        // reading epr
    lsls    r5, r0, #21
    lsrs    r5, #29
    cmp     r5, #0x04
    beq     .L_epr_iso
    cmp     r5, #0x01
    bne     .L_epr_sngl
.L_epr_dblbulk:
    negs    r0, r0
    lsrs    r0, #7          // ~SW_RX in CF
    b       .L_epr_load_table
.L_epr_iso:
    lsrs    r0, #15         // DTOG_RX passsed to CF
.L_epr_load_table:
    ldrh    r0, [r4, #0]    // R0 rxaddr0
    ldrh    r5, [r4, #2]    // R5 rxcnt0
    bcs     .L_epr_prepare
.L_epr_sngl:
    ldrh    r0, [r4, #4]    // R0 rxaddr1 or rxaddr
    ldrh    r5, [r4, #6]    // R5 rxcnt1 or rxcnt
.L_epr_prepare:
    ldr     r4, =USB_PMABASE
    adds    r0, r4          // R0 now has a physical address
    lsls    r5, #22
    lsrs    r5, #22         // R5 bytes count
    cmp     r2, r5
    blo     .L_epr_read
    mov     r2, r5          // if buffer is larger
.L_epr_read:
    cmp     r2, #1
    blo     .L_epr_read_end
    ldrh    r4, [r0]
    strb    r4, [r1]
    beq     .L_epr_read_end
    lsrs    r4, #8
    strb    r4, [r1, #1]
    adds    r1, #2
    adds    r0, #2
    subs    r2, #2
    bne     .L_epr_read
.L_epr_read_end:
    ldrh    r0, [r3]
    lsls    r1, r0, #21
    lsrs    r1, #29
    cmp     r1, #0x04
    beq     .L_epr_exit     // ep is iso. no needs to set it to valid
    cmp     r1, #0x01
    beq     .L_epr_exit     // ep is dblbulk. no needs to set it to valid
    ldr     r2, =TGL_SET(EP_RX_STAT , EP_RX_VAL)  //0xBF8F3000
    eors    r0, r2
    lsrs    r2, #16
    ands    r0, r2
    strh    r0, [r3]        // set ep to VALID state
.L_epr_exit:
    mov     r0, r5
    pop     {r4, r5, pc}
    .size   _ep_read, . - _ep_read



    .thumb_func
    .type   _ep_write, %function
/* uint16_t ep_write(uint8_t ep, void *buf, uint16_t blen)
 *

 */
_ep_write:
    push    {r2, r4, r5, lr}
    ldr     r3, =USB_EPBASE
    ldr     r4, =USB_PMABASE
    lsls    r0, #28
    lsrs    r0, #26
    adds    r3, r0          // *EPR -> R3
    lsls    r0, #1
    adds    r4, r0          // *EPT -> R4
    ldrh    r0, [r3]        // reading epr
    lsls    r0, #21
    lsrs    r0, #29
    subs    r0, #0x04
    beq     .L_epw_iso
    adds    r0, #0x03
    bne     .L_epw_sngl
.L_epw_dblbulk:
    ldrh    r0, [r3]
    lsrs    r0, #15          // SW_TX in CF
    bcc     .L_epw_sngl
    b       .L_epw_settx1
.L_epw_iso:
    ldrh    r0, [r3]
    lsrs    r0, #7          // DTOG_TX passsed to CF
    bcs     .L_epw_sngl
.L_epw_settx1:
    adds    r4, #0x04
.L_epw_sngl:
    ldrh    r0, [r4, #0]    // R0 txaddr
.L_epw_prepare:
    strh    r2, [r4, #2]    // set txcount
    ldr     r4, =USB_PMABASE
    adds    r0, r4
.L_epw_write:
    cmp     r2, #0x01
    blo     .L_epw_writeend
    ldrb    r4, [r1]
    beq     .L_epw_halfw
    ldrb    r5, [r1, #1]
    lsls    r5, #8
    orrs    r4, r5
    strh    r4, [r0]
    adds    r1, #2
    adds    r0, #2
    subs    r2, #2
    b       .L_epw_write
.L_epw_halfw:
    strh    r4, [r0]
.L_epw_writeend:
    ldrh    r0, [r3]
    lsls    r1, r0, #21
    lsrs    r1, #29
    subs    r1, #0x04
    beq     .L_epw_exit     // ep is iso. no needs to change states
    ldr     r2, =TGL_SET(EP_TX_STAT , EP_TX_VAL) //0x8FBF0030
    adds    r1, #0x03
    bne     .L_epw_setstate
// ep is dblbulk. needs to switch SW_TX
    movs    r2, 0x01
    lsls    r2, #14
    orrs    r0, r2
    ldr     r2, =TGL_SET(EP_TX_SWBUF, 0 ) //0xCF8F0000

.L_epw_setstate:
    eors    r0, r2
    lsrs    r2, #16
    ands    r0, r2
    strh    r0, [r3]
.L_epw_exit:
    pop     {r0, r4, r5, pc}
    .size   _ep_write, .- _ep_write



/* internal function */
/* requester size passed in R2 */
/* result returns in R0 CF=1 if OK*/

_get_next_pma:
    push    {r1, r3, r4, lr}
    movs    r1, #16
    movs    r3, #1
    lsls    r3, #10         //R3 MAX_PMA_SIZE
    ldr     r0, =USB_PMABASE
.L_gnp_chkaddr:
    ldrh    r4, [r0, #0]    //txaddr
    tst     r4, r4
    beq     .L_gnp_nxtaddr
    cmp     r3, r4
    blo     .L_gnp_nxtaddr
    mov     r3, r4
.L_gnp_nxtaddr:
    adds    r0, #4
    subs    r1, #1
    bne     .L_gnp_chkaddr
    subs    r0, r3, r2
    blo     .L_gnp_exit
    cmp     r0, #0x40       //check for the pma table overlap
.L_gnp_exit:
    pop     {r1, r3, r4, pc}



    .size   _get_next_pma, . - _get_next_pma

    .thumb_func
    .type   _ep_config, %function
/* bool ep_config(uint8_t ep, uint8_t eptype, uint16_t epsize)
 * R0 <- ep
 * R1 <- eptype
 * R2 <- epsize
 * result -> R0
 */
_ep_config:
    push    {r4, r5, lr}
    movs    r3, 0x01
    ands    r3, r2
    adds    r2, r3      //R2 -> halfword aligned epsize
    movs    r3, #0x00   //BULK
    cmp     r1, #0x02   // is eptype bulk ?
    beq     .L_epc_settype
    movs    r3, #0x01   //DBLBULK
    cmp     r1, #0x06
    beq     .L_epc_settype
    movs    r3, #0x02   //CONTROL
    cmp     r1, #0x00
    beq     .L_epc_settype
    movs    r3, #0x04   //ISO
    cmp     r1, #0x01
    beq     .L_epc_settype
    movs    r3, #0x06   //INTERRUPT
.L_epc_settype:
    lsls    r3, #8
    lsls    r4, r0, #28
    lsrs    r4, #28
    orrs    r3, r4
    lsls    r4, #2
    ldr     r5, =USB_EPBASE
    strh    r3, [r5, r4]    //setup EPTYPE EPKIND EPADDR
    cmp     r1, #0x00       // is a control ep ?
    beq     .L_epc_setuptx
    cmp     r0, #0x80
    blo     .L_epc_setuprx
.L_epc_setuptx:
    ldr     r5, =USB_PMABASE
    lsls    r4, #1
    adds    r5, r4
    bl      _get_next_pma
    bcc     .L_epc_fail
    strh    r0, [r5, #0]    //store txaddr or txaddr0
    movs    r0, #0x00
    strh    r0, [r5, #2]    //store txcnt
    cmp     r1, #0x06       // is DBLBULK
    beq     .L_epc_txdbl
    ldr     r3, =TGL_SET((EP_TX_STAT | EP_TX_DTOG) , EP_TX_NAK) //set state NAKED , clr DTOG_TX
    cmp     r1, #0x01       // is ISO
    bne     .L_epc_txsetstate   //
.L_epc_txdbl:
    ldr     r3, =TGL_SET((EP_TX_STAT | EP_TX_DTOG | EP_TX_SWBUF) , EP_TX_VAL) //set state VALID clr DTOG_TX & SWBUF_TX
    bl      _get_next_pma
    bcc     .L_epc_fail
    strh    r0, [r5, #4]    //store txaddr1
    movs    r0, #0x00
    strh    r0, [r5, #6]    //store txcnt
.L_epc_txsetstate:
    ldr     r5, =USB_EPBASE
    lsrs    r4, #1
    ldrh    r0, [r5, r4]
    eors    r0, r3
    lsrs    r3, #16
    ands    r0, r3
    strh    r0, [r5, r4]
    cmp     r1, #0x00       //is a control ep ?
    bne     .L_epc_exit
.L_epc_setuprx:
    mov     r3, r2
    cmp     r2, #62
    bls     .L_epc_rxbb
    movs    r3, #0x1F
    ands    r3, r2
    bne     .L_epc_rxaa
    subs    r2, #0x20
.L_epc_rxaa:
    bics    r2, r3
    lsrs    r3, r2, #4
    adds    r3, #0x40
    adds    r2, #0x20
.L_epc_rxbb:
    lsls    r3, #9
    ldr     r5, =USB_PMABASE
    lsls    r4, #1
    adds    r5, r4
    cmp     r1, 0x06    //if dblbulk
    beq     .L_epc_rxdbl
    cmp     r1, 0x01    // iso
    bne     .L_epc_rxsngl
.L_epc_rxdbl:
    bl      _get_next_pma
    bcc     .L_epc_fail
    strh    r0, [r5, #0]    //store rxaddr0
    strh    r3, [r5, #2]    //store rxcnt0
    bl      _get_next_pma
    bcc     .L_epc_fail
    strh    r0, [r5, #4]    //store rxaddr1
    strh    r3, [r5, #6]    //store rxcnt1
    ldr     r3, =TGL_SET((EP_RX_STAT | EP_RX_DTOG | EP_RX_SWBUF) , (EP_RX_VAL | EP_RX_SWBUF)) //0xFFCF3040
    b       .L_epc_rxsetstate
.L_epc_rxsngl:
    bl      _get_next_pma
    bcc     .L_epc_fail
    strh    r0, [r5, #4]    //store rxaddr1 or rxaddr
    strh    r3, [r5, #6]    //store rxcnt1 or rxcnt
    ldr     r3, =TGL_SET((EP_RX_STAT | EP_RX_DTOG) , EP_RX_VAL) //0xFF8F3000
.L_epc_rxsetstate:
    ldr     r5, =USB_EPBASE
    lsrs    r4, #1
    ldrh    r0, [r5, r4]
    eors    r0, r3
    lsrs    r3, #16
    ands    r0, r3
    strh    r0, [r5, r4]
.L_epc_exit:
    movs    r0, #0x01
    pop     {r4, r5, pc}
.L_epc_fail:
    movs    r0, #0x00
    pop     {r4, r5, pc}

    .size   _ep_config, . - _ep_config

    .thumb_func
    .type   _ep_deconfig, %function


/* void ep_deconfig( uint8_t ep)
 * R0 <- ep
 */
_ep_deconfig:
    lsls    r1, r0, #28
    lsrs    r1, #26
    ldr     r2, =USB_EPBASE
    ldr     r3, =USB_PMABASE
    adds    r2, r1
    lsls    r1, #1
    adds    r3, r1
/* clearing endpoint register */
    ldr     r1, =EP_NOTOG
    ldrh    r0, [r2]
    bics    r0, r1
    strh    r0, [r2]
/* clearing PMA data */
    movs    r0, #0x00
    strh    r0, [r3, #0x00]
    strh    r0, [r3, #0x02]
    strh    r0, [r3, #0x04]
    strh    r0, [r3, #0x06]
    bx      lr

    .size   _ep_deconfig, . - _ep_config




#define ISTRSHIFT   8
#define ISTRBIT(bit) ((1 << bit) >> ISTRSHIFT)


    .thumb_func
    .type     _evt_poll, %function
/*void evt_poll(usbd_device *dev, usbd_evt_callback callback)*/
_evt_poll:
    push    {r0, r1, r4, r5}
    ldr     r3, =USB_REGBASE
    ldrh    r0, [r3, #4]        //USB->ISTR -> R2
/* ep_index -> R2 */
    movs    r2, 0x07
    ands    r2, r0
/* checking USB->ISTR for events */
    lsls    r0, #17             //CTRM -> CF
    bcs     .L_ep_ctrm
    lsls    r0, #2              //ERRM -> CF
    bcs     .L_ep_errm
    lsls    r0, #1              //WKUPM -> CF
    bcs     .L_ep_wkupm
    lsls    r0, #1              //SUSPM -> CF
    bcs     .L_ep_suspm
    lsls    r0, #1              //RESETM -> CF
    bcs     .L_ep_resetm
    lsls    r0, #1              //SOFM -> CF
    bcs     .L_ep_sofm
    lsls    r0, #1
    bcs     .L_ep_esofm
    /* exit with no callback */
    pop     {r0, r1, r4 , r5}
    bx      lr

.L_ep_ctrm:
    movs    r3, #0x00
    ldr     r0,=#USB_EPBASE
    lsrs    r0, #2
    adds    r0, r2
    lsls    r0, #2              // R0 ep register address
    ldrh    r4, [r0]            //R4 *USB->EPx
    lsrs    r5, r4, #8         // CTR_TX -> CF
    bcc     .L_ep_ctr_rx
/* CTR_TX event */
    movs    r1, #usbd_evt_eptx
    movs    r5, #0x80
    adds    r2, #0x80           // set endpoint tx
    b       .L_ep_clr_ctr
.L_ep_ctr_rx:
/* CTR_RX  RX or SETUP */
    movs    r1, #usbd_evt_epsetup
    lsls    r5, r4, #21             //SETUP -> CF
    bcs     .L_ep_ctr_evt
    movs    r1, #usbd_evt_eprx
    lsrs    r5, #29                 //EP_TYPE | EP_KIND -> R5 LSB
    cmp     r5, #0x01               //if dblbuf bulk
    bne     .L_ep_ctr_evt
/* if ep is dblbulk RX */
    movs    r3, #EP_RX_SWBUF
.L_ep_ctr_evt:
/* clear CTR_RX */
    movs    r5, #0x80
    lsls    r5, #0x08
.L_ep_clr_ctr:
    bics    r4, r5
    ldr     r5, =EP_NOTOG
    ands    r4, r5
    orrs    r4, r3
    strh    r4, [r0]            // clr CTR flag
    b       .L_ep_callback

.L_ep_errm:
    movs    r1, #usbd_evt_error
    movs    r4, #ISTRBIT(13)
    b      .L_ep_clristr

.L_ep_sofm:
    movs    r1, #usbd_evt_sof
    movs    r4, #ISTRBIT(9)
    b       .L_ep_clristr

.L_ep_esofm:
    movs    r1, #usbd_evt_esof
    movs    r4, #ISTRBIT(8)
    b       .L_ep_clristr

.L_ep_wkupm:
    ldrh    r1, [r3, #0]            //R1 USB->CNTR
    movs    r5, #0x08
    bics    r1, r5                  //clr FSUSP
    strh    r1, [r3, #0]            //USB->CNTR R2
    movs    r1, #usbd_evt_wkup
    movs    r4, #ISTRBIT(12)
    b       .L_ep_clristr

.L_ep_suspm:
    ldrh    r1, [r3, #0]            //R1 USB->CNTR
    movs    r5, #0x08
    orrs    r1, r5                  //set FSUSP
    strh    r1, [r3, #0]            //USB->CNTR R2
    movs    r1, #usbd_evt_susp
    movs    r4, #ISTRBIT(11)
    b       .L_ep_clristr

/* do reset routine */
.L_ep_resetm:
    movs    r1, #7
    ldr     r2, =USB_EPBASE
    ldr     r0, =USB_PMABASE
    ldr     r5, =EP_NOTOG
.L_ep_reset_loop:
    ldrh    r4, [r2]
    bics    r4, r5
    strh    r4, [r2]
    movs    r4, #0
    strh    r4, [r0, #0]
    strh    r4, [r0, #2]
    strh    r4, [r0, #4]
    strh    r4, [r0, #6]
    adds    r2, #4
    adds    r0, #8
    subs    r1, #1
    bpl     .L_ep_reset_loop
    movs    r2, #0x00
    strh    r2, [r3, #0x10]     // 0 -> USB->BTABLE
    movs    r1, #usbd_evt_reset
    movs    r4, #ISTRBIT(10)
.L_ep_clristr:
    lsls    r4, #ISTRSHIFT
    ldrh    r0, [r3, #4]
    bics    r0, r4
    strh    r0, [r3, #4]
.L_ep_callback:
    pop     {r0, r3, r4, r5 }
    bx      r3

    .size   _evt_poll, . - _evt_poll




    .pool

   .end
