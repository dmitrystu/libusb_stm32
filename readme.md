### Lightweight USB Device Stack ###

+ Lightweight and fast
+ Event-driven process workflow
+ Completely separated USB hardware driver and usb core
+ Easy to use.

### Supported hardware ###

| HW driver  | Written on | Endpoints |                     Features | MCU series |
|------------|------------|-----------|------------------------------|------------|
| usb_stmv0  | GCC C      | 8         | Internal S/N, Doublebuffered | STM32L0x2 STM32L0x3 STM32L4x2 STM32L4x3 STM32F0x2 STM32F0x8 |
| usb_stmv0a | GCC ASM    | 8         | Internal S/N, Doublebuffered | STM32L0x2 STM32L0x3 STM32L4x2 STM32L4x3 STM32F0x2 STM32F0x8 |
| usb_stmv1  | GCC C      | 8         | Internal S/N, Doublebuffered | STM32L1xx  |
| usb_stmv1a | GCC ASM    | 8         | Internal S/N, Doublebuffered | STM32L1xx  |


1. Single physical endpoint can be used to implement
  + one bi-directional/single-buffer logical endpoint (CONTROL)
  + one mono-directional/double-buffer logical endpoint (BULK OR ISOCHRONOUS)
  + two mono-directional/single-buffer logical endpoints (BULK OR INTERRUPT)

2. At this moment BULK IN endpoint can use both buffers, but it is not **real** doublebuffered.

3. Tested with STM32L052, STM31L100

### Implemented definitions for classes ###
1. USB HID based on [Device Class Definition for Human Interface Devices (HID) Version 1.11](http://www.usb.org/developers/hidpage/HID1_11.pdf)
2. USB DFU based on [USB Device Firmware Upgrade Specification, Revision 1.1] (http://www.usb.org/developers/docs/devclass_docs/DFU_1.1.pdf)
3. USB CDC based on [Class definitions for Communication Devices 1.2] (http://www.usb.org/developers/docs/devclass_docs/CDC1.2_WMC1.1_012011.zip)

### Useful Resources ###
1. [USB Implementers Forum official site] (http://www.usb.org/home)
2. [USB Made Simple] (http://www.usbmadesimple.co.uk/)
3. [LUFA - the Lightweight USB Framework for AVRs.] (https://github.com/abcminiuser/lufa)
4. [Open Source ARM cortex m microcontroller library] (https://github.com/libopencm3/libopencm3)
