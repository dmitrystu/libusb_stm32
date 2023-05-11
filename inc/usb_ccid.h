#include <stdint.h>

#ifndef _USB_CCID_H_
#define _USB_CCID_H_
#ifdef __cplusplus
    extern "C" {
#endif

#define USB_CLASS_CCID                   0x0b    /**<\brief Communicational Device class */
#define USB_DTYPE_FUNCTIONAL_DESC   0x21   /**<\brief Functonal descriptor.*/
        
#define ENDPOINT_DIR_IN                    0x80
#define ENDPOINT_DIR_OUT                   0x00
        
#define INTERFACE_ID_CCID                 0

#define CCID_IN_EPADDR       (ENDPOINT_DIR_IN  | 2)

/** Endpoint address of the CCID data OUT endpoint, for host-to-device data transfers. */
#define CCID_OUT_EPADDR      (ENDPOINT_DIR_OUT | 1)

/** Endpoint size in bytes of the CCID data being sent between IN and OUT endpoints. */
#define CCID_EPSIZE          64


#define CCID_CURRENT_SPEC_RELEASE_NUMBER            0x0110
#define CCID_VOLTAGESUPPORT_5V                      0
#define CCID_VOLTAGESUPPORT_3V                      (1 << 0)
#define CCID_VOLTAGESUPPORT_1V8                     (1 << 1)

#define CCID_PROTOCOL_T0                            0
#define CCID_PROTOCOL_T1                            (1 << 0)

#define CCID_ICCSTATUS_PRESENTANDACTIVE             0
#define CCID_ICCSTATUS_PRESENTANDINACTIVE           (1 << 0)
#define CCID_ICCSTATUS_NOICCPRESENT                 (1 << 1)

#define CCID_COMMANDSTATUS_PROCESSEDWITHOUTERROR    0
#define CCID_COMMANDSTATUS_FAILED                   (1 << 6)
#define CCID_COMMANDSTATUS_TIMEEXTENSIONREQUESTED   (1 << 7)

#define CCID_ERROR_NOERROR          0
#define CCID_ERROR_SLOTNOTFOUND     5

#define CCID_ABORT                                  0x1
#define CCID_GET_CLOCK_FREQUENCIES                  0x2
#define CCID_GET_DATA_RATES                         0x3

struct usb_ccid_descriptor {
    uint8_t bLength;                /**<\brief Size of the descriptor, in bytes.*/
    uint8_t bDescriptorType;        /**<\brief IAD descriptor */

    uint16_t                CCID;
    uint8_t                 MaxSlotIndex;
    uint8_t                 VoltageSupport;
    uint32_t                Protocols;
    uint32_t                DefaultClock;
    uint32_t                MaximumClock;
    uint8_t                 NumClockSupported;
    uint32_t                DataRate;
    uint32_t                MaxDataRate;
    uint8_t                 NumDataRatesSupported;
    uint32_t                MaxIFSD;
    uint32_t                SynchProtocols;
    uint32_t                Mechanical;
    uint32_t                Features;
    uint32_t                MaxCCIDMessageLength;
    uint8_t                 ClassGetResponse;
    uint8_t                 ClassEnvelope;
    uint16_t                LcdLayout;
    uint8_t                 PINSupport;
    uint8_t                 MaxCCIDBusySlots;
} __attribute__((packed));

#ifdef __cplusplus
    }
#endif

#endif
