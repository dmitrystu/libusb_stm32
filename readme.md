### Lightweight USB Device Stack ###

+ Lightweight and fast
+ Event-driven process workflow
+ Completely separated USB hardware driver and middleware
+ Easy to use.

### Supported hardware ###

| MCU series | Driver Name | Written on | Endpoints (1) | Internal S/N | Doublebuffered transfer   |
| ---------- | ----------- | ---------- | ------------- |------------- | ------------------------- |
| STM32L0/F0 | usb_stml0a  | GCC ASM    |             8 | FNV1A 32bit  | ISO, BULK OUT, BULK IN (2)|
| STM32L0/F0 | usb_stmv0   | C          |             8 | FNV1A 32bit  | ISO, BULK OUT, BULK IN (2)|


1. Single physicsl endpoint can be used to implement
  + one bi-directional/single-buffer logical endpoint (CONTROL)
  + one mono-directional/double-buffer logical endpoint (BULK OR ISOCHRONOUS)
  + two mono-directional/single-buffer logical endpoints (BULK OR INTERRUPT)

2. At this moment BULK IN endpoint can use both buffers, but it is not **real** doublebuffered.

### Implemented definitions for classes ###
1. USB HID based on [Device Class Definition for Human Interface Devices (HID) Version 1.11](http://www.usb.org/developers/hidpage/HID1_11.pdf)
2. USB DFU based on [USB Device Firmware Upgrade Specification, Revision 1.1] (http://www.usb.org/developers/docs/devclass_docs/DFU_1.1.pdf)
3. USB CDC based on [Class definitions for Communication Devices 1.2] (http://www.usb.org/developers/docs/devclass_docs/CDC1.2_WMC1.1_012011.zip)

### Useful Recources ###
1. [USB Implementers Forum official site] (http://www.usb.org/home)
2. [USB Made Simple] (http://www.usbmadesimple.co.uk/)
3. [LUFA - the Lightweight USB Framework for AVRs.] (https://github.com/abcminiuser/lufa)
4. [Open Source ARM cortex m microcontroller library] (https://github.com/libopencm3/libopencm3)
