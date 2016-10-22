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

/** \file usbd_core.h
 * \brief Core and hardware driver framework.
 * \author Dmitry Filimonchuk <dmitrystu[at]gmail[dot]com>
 * \version 1.0
 * \copyright Apache License, Version 2.0
 */

#ifndef _USBD_CORE_H_
#define _USBD_CORE_H_
#if defined(__cplusplus)
    extern "C" {
#endif

/** \addtogroup USBD_CORE USB device core
 * \brief Contains core and hardware driver framework definitions
 * @{ */
#define USB_EPTYPE_DBLBUF       0x04        /**< indicates a doublebuffered endpoint (bulk endpoint only) */
#define USB_EPDIR_IN            0x00        /**< indicates host-to-device endpoint direction  */
#define USB_EPDIR_OUT           0x80        /**< indicates device-to-host endpoint direction */


/** \name bmRequestType bitmapped field
 * @{ */
#define USB_REQ_DIRECTION       (1 << 7)
#define USB_REQ_HOSTTODEV       (0 << 7)
#define USB_REQ_DEVTOHOST       (1 << 7)
#define USB_REQ_TYPE            (3 << 5)
#define USB_REQ_STANDARD        (0 << 5)
#define USB_REQ_CLASS           (1 << 5)
#define USB_REQ_VENDOR          (2 << 5)
#define USB_REQ_RECIPIENT       (3 << 0)
#define USB_REQ_DEVICE          (0 << 0)
#define USB_REQ_INTERFACE       (1 << 0)
#define USB_REQ_ENDPOINT        (2 << 0)
#define USB_REQ_OTHER           (3 << 0)
/** @} */


#if defined(__ASSEMBLER__)
    #define usbd_evt_reset      0
    #define usbd_evt_sof        1
    #define usbd_evt_susp       2
    #define usbd_evt_wkup       3
    #define usbd_evt_eptx       4
    #define usbd_evt_eprx       5
    #define usbd_evt_epsetup    6
    #define usbd_evt_error      7
    #define usbd_evt_esof       8
#else

/** USB device events */
enum usbd_evt {
    usbd_evt_reset,             /**< Reset */
    usbd_evt_sof,               /**< Start Of Frame */
    usbd_evt_susp,              /**< Suspend */
    usbd_evt_wkup,              /**< Wakeup */
    usbd_evt_eptx,              /**< Transmit completed */
    usbd_evt_eprx,              /**< Data packet received */
    usbd_evt_epsetup,           /**< Setup packet received */
    usbd_evt_error,             /**< Data error */
    usbd_evt_esof,              /**< Missed SOF */
    usbd_evt_count, /* this is trick to count qty */
};

/** USB device machine state */
enum usbd_machine_state {
    usbd_state_disabled,
    usbd_state_disconnected,
    usbd_state_default,         /**< Default */
    usbd_state_addressed,       /**< Addressed */
    usbd_state_configured,      /**< Configured */
};

/** USB device control endpoint machine state */
enum usbd_ctl_state {
    usbd_ctl_idle,              /**< Idle. Awaiting for SETUP packet */
    usbd_ctl_rxdata,            /**< RX. Receiving DATA-OUT payload */
    usbd_ctl_txdata,            /**< TX. Transmitting DATA-IN payload */
    usbd_ctl_ztxdata,           /**< TX. Transmitting DATA-IN payload. Zero length packet maybe required. */
    usbd_ctl_lastdata,          /**< TX. Last DATA-IN packed passed to buffer. Awaiting for the TX completion */
    usbd_ctl_statusin,          /**< STATUS-IN stage */
    usbd_ctl_statusout,         /**< STATUS-OUT stage */
};

/** Asynchronous device control commands  */
enum usbd_commands {
    usbd_cmd_enable,            /**< Enables device */
    usbd_cmd_disable,           /**< Disables device */
    usbd_cmd_connect,           /**< Connects device to host */
    usbd_cmd_disconnect,        /**< Disconnects device from host */
    usbd_cmd_reset,             /**< Resets device */
};

/* Reporting status results */
typedef enum _usbd_respond {
    usbd_fail,                  /**< Function has an error, STALLPID will be issued */
    usbd_ack,                   /**< Function completes request accepted ZLP or data will be send */
    usbd_nak,                   /**< Function is busy. NAK handshake */
} usbd_respond;

typedef struct _usbd_device usbd_device;
typedef struct _usbd_ctlreq usbd_ctlreq;
typedef struct _usbd_status usbd_status;

/**\name USB Device user callbacks function prototypes
 * @{ */
 /** Generic USB device event callback for events and endpoints processing
  * \param[in] dev pointer to USB device
  * \param event \ref usbd_evt "USB event"
  * \param ep active endpoint number
  * \note endpoints with same indexes i.e. 0x01 and 0x81 shares same callback.
  */
typedef void (*usbd_evt_callback)(usbd_device *dev, uint8_t event, uint8_t ep);

/** USB control transfer completed callback.
 * \param[in] dev pointer to USB device
 * \param[in] req pointer to usb request structure
 * \note When this callback will be completed usbd_device#complete_callback will be reseted to NULL
 */
typedef void (*usbd_ctl_complete)(usbd_device *dev, usbd_ctlreq *req);

/** USB control callback.
 * \details Uses for the control request processing.
 *          Some requests will be handled by core if callback don't process it (returns FALSE). If request was not processed STALL PID will be issued.
 *          - GET_CONFIGURATION
 *          - SET_CONFIGURATION (passes to \ref usbd_cfg_callback)
 *          - GET_DESCRIPTOR (passes to \ref usbd_dsc_callback)
 *          - GET_STATUS
 *          - SET_FEATURE, CLEAR_FEATURE (endpoints only)
 *          - SET_ADDRESS
 * \param[in] dev points to USB device
 * \param[in] req points to usb control request
 * \param[out] *callback \ref usbd_ctl_complete "pointer to USB control transfer completed callback", default is NULL (no callback)
 * \return usbd_respond status.
 */
typedef usbd_respond (*usbd_ctl_callback)(usbd_device *dev, usbd_ctlreq *req, usbd_ctl_complete *callback);

/** USB get descriptor callback
 * \details Called when GET_DESCRIPTOR request issued
 * \param[in] req pointer to usb control request structure
 * \param[in,out] address pointer to the descriptor in memory. Points to req->data by default. You can use this buffer.
 * \param[in,out] dsize descriptor size. req->data buffer size by default.
 * \return TRUE if you passed the correct descriptor, FALSE otherwise.
 */
typedef bool (*usbd_dsc_callback)(usbd_ctlreq *req, void **address, uint16_t *dsize);

/** USB set configuration callback
 * \details called when SET_CONFIGURATION request issued
 * \param[in] dev pointer to USB device
 * \param[in] cfg configuration number.
 * \note if config is 0 device endpoints should be de-configured
 * \return TRUE if success
 */
typedef bool (*usbd_cfg_callback)(usbd_device *dev, uint8_t cfg);

/** @} */

/**\name USB Hardware driver API function prototypes
 * @{ */

/** Enables or disables USB hardware
 * \param enable Enables USB when TRUE disables otherwise
 */
typedef void (*usbd_hw_enable)(bool enable);

/** Resets USB hardware */
typedef void (*usbd_hw_reset)(void);

/** Connects or disconnects USB hardware to/from usb host
 * \param connect Connects USB to host if TRUE, disconnects otherwise
 */
typedef void (*usbd_hw_connect)(bool connect);

/** Sets USB hardware address
 * \param address USB address
 */
typedef void (*usbd_hw_setaddr)(uint8_t address);

/** Configures endpoint
 * \param ep endpoint address. Use USB_EPDIR_ macros to set endpoint direction
 * \param eptype endpoint type. Use USB_EPTYPE_* macros.
 * \param epsize endpoint size in bytes
 * \return TRUE if success
 */
typedef bool (*usbd_hw_ep_config)(uint8_t ep, uint8_t eptype, uint16_t epsize);

/** De-configures, cleans and disables endpoint
 * \param ep endpoint index
 * \note if you have two one-direction single-buffered endpoints with same index (i.e. 0x02 and 0x82) both will be deconfigured.
 */
typedef void (*usbd_hw_ep_deconfig)(uint8_t ep);

/** Reads data from OUT or control endpoint
 * \param ep endpoint index, should belong to OUT or CONTROL endpoint.
 * \param buf pointer to read buffer
 * \param blen size of the read buffer in bytes
 * \return size of the actually received data
 */
typedef uint16_t (*usbd_hw_ep_read)(uint8_t ep, void *buf, uint16_t blen);

/** Writes data to IN or control endpoint
 * \param ep endpoint index, hould belong to IN or CONTROL endpoint
 * \param buf pointer to data buffer
 * \param blen size of data will be written
 * \return number of written bytes
 */
typedef uint16_t (*usbd_hw_ep_write)(uint8_t ep, void *buf, uint16_t blen);

/** Stalls and unstalls endpoint
 * \param ep endpoint address
 * \param stall endpoint will be stalled if TRUE and unstalled otherwise.
 * \note Has no effect on inactive endpoints.
 */
typedef void (*usbd_hw_ep_setstall)(uint8_t ep, bool stall);

/** Checks endpoint for stalled state
 * \param ep endpoint address
 * \return TRUE if endpoint is stalled
 */
typedef bool (*usbd_hw_ep_isstalled)(uint8_t ep);

/** Polls USB hardware for the events
 * \param[in] dev pointer to usb device structure
 * \param drv_callback callback to event processing subroutine
 */
typedef void (*usbd_hw_poll)(usbd_device *dev, usbd_evt_callback drv_callback);

/** Gets frame number from usb hardware
 */
typedef uint16_t (*usbd_hw_get_frameno)(void);


/** Makes a string descriptor contains unique serial number from hardware ID's
 * \param[in] buffer pointer to buffer for the descriptor
 * \return of the descriptor in bytes
 */
typedef uint16_t (*usbd_hw_get_serialno)(void *buffer);

/** @} */

/** Represents generic USB control request */
struct _usbd_ctlreq {
    uint8_t     bmRequestType;  /**< This bitmapped field identifies the characteristics of the specific request. */
    uint8_t     bRequest;       /**< This field specifies the particular request. */
    uint16_t    wValue;         /**< It is used to pass a parameter to the device, specific to the request. */
    uint16_t    wIndex;         /**< It is used to pass a parameter to the device, specific to the request. */
    uint16_t    wLength;        /**< This field specifies the length of the data transferred during the second phase of the control transfer */
    uint8_t     data[];         /**< Request data payload */
};


/** USB device status data for control endpoint */
struct _usbd_status {
    void        *data_buf;
    void        *data_ptr;      /**< Pointer to control endpoint current data buffer */
    uint16_t    data_count;     /**< Control endpoint data counter */
    uint16_t    data_maxsize;   /**< Size of the data buffer for control endpoint */
    uint8_t     ep0size;        /**< Size of the control endpoint */
    uint8_t     device_cfg;     /**< Current device configuration ID */
    uint8_t     device_state;   /**< Current \ref usbd_machine_state */
    uint8_t     control_state;  /**< Current \ref usbd_ctl_state */
};

/** Structure represents a hardware USB driver call table */
struct usbd_driver {
    usbd_hw_enable          enable;
    usbd_hw_reset           reset;
    usbd_hw_connect         connect;
    usbd_hw_setaddr         setaddr;
    usbd_hw_ep_config       ep_config;
    usbd_hw_ep_deconfig     ep_deconfig;
    usbd_hw_ep_read         ep_read;
    usbd_hw_ep_write        ep_write;
    usbd_hw_ep_setstall     ep_setstall;
    usbd_hw_ep_isstalled    ep_isstalled;
    usbd_hw_poll            poll;
    usbd_hw_get_frameno     frame_no;
    usbd_hw_get_serialno    get_serialno_desc;
};

/** Structure represents a USB device data. No other data used by USB core and driver
 *  \note use helper \ref usbd_device typedef
 *  \note structure must be aligned
 */
struct _usbd_device {
    const struct usbd_driver    *driver;
    usbd_ctl_callback           control_callback;
    usbd_ctl_complete           complete_callback;
    usbd_cfg_callback           config_callback;
    usbd_dsc_callback           descriptor_callback;
    usbd_evt_callback           events[usbd_evt_count];     /**< events callbacks array */
    usbd_evt_callback           endpoint[8];                /**< endpoint callbacks array for tx, rx and setup events */
    usbd_status                 status;
};

/** Initializes device structure
 * \param dev USB device that will be initialized
 * \param drv Pointer to hardware driver
 * \param ep0size Control endpoint 0 size
 * \param buffer Pointer to control request data buffer (32-bit aligned)
 * \param bsize Size of the data buffer
 */
void usbd_init(usbd_device *dev, const struct usbd_driver *drv, const uint8_t ep0size, uint32_t *buffer, const uint16_t bsize);

/** Polls USB for events
 * \param dev Pointer to device structure
 * \note can be called as from main routine as from USB interrupt
 */
void usbd_poll(usbd_device *dev);

/** Asynchronous device control
 * \param dev USB device
 * \param cmd control command
 */
void usbd_control(usbd_device *dev, enum usbd_commands cmd);


/** \name API macro functions
 * @{ */

/** Macro to register control callback
 * \param dev pointer to \ref usbd_device structure
 * \param cb pointer to user \ref usbd_ctl_callback
 */
#define usbd_reg_control(dev, cb) (dev)->control_callback = (cb)

/** Macro to register set configuration callback
 * \param dev pointer to \ref usbd_device structire
 * \param cb pointer to user \ref usbd_ctl_callback
 */
#define usbd_reg_config(dev, cb) (dev)->config_callback = (cb)

/** Macro to register GET_DESCRIPTOR callback
 * \param dev USB device
 * \param cb callback
 */
#define usbd_reg_descr(dev, cb) (dev)->descriptor_callback = (cb)

/** Macro to register endpoint callback
 * \param dev pointer to \ref usbd_device structure
 * \param ep endpoint index
 * \param cb pointer to user \ref usbd_evt_callback callback for endpoint events
 */
#define usbd_reg_endpoint(dev, ep, cb) (dev)->endpoint[(ep) & 0x07] = (cb)

/** Macro to registers event callback
 * \param dev pointer to \ref usbd_device structure
 * \param evt device \ref usbd_evt "event" wants to be registered
 * \param cb pointer to user \ref usbd_evt_callback for this event
 */
#define usbd_reg_event(dev, evt, cb) (dev)->events[(evt)] = (cb)

/** Macro to configure endpoint
 * \param dev pointer to \ref usbd_device structure
 * \copydetails usbd_hw_ep_config
 */
#define usbd_ep_config(dev, ep, eptype, epsize) (dev)->driver->ep_config((ep), (eptype), (epsize))

/** Macro to deconfigure endpoint
 * \param dev pointer to \ref usbd_device structure
 * \copydetails usbd_hw_ep_deconfig
 */
#define usbd_ep_deconfig(dev, ep) (dev)->driver->ep_deconfig(ep)

/** Macro to write data to endpoint
 * \param dev pointer to \ref usbd_device structure
 * \copydetails usbd_hw_ep_write
 */
#define usbd_ep_write(dev, ep, buf, blen) (dev)->driver->ep_write((ep), (buf), (blen))

/** Macro to read data from endpoint
 * \param dev pointer to \ref usbd_device structure
 * \copydetails usbd_hw_ep_read
 */
#define usbd_ep_read(dev, ep, buffer, length) (dev)->driver->ep_read((ep), (buf), (blen))

/** Macro to stall endpoint
 * \param dev pointer to \ref usbd_device structure
 * \param ep endpoint address
 */
#define usbd_ep_stall(dev, ep) (dev)->driver->ep_setstall((ep), 1)

/** Macro to unstall endpoint
 * \param dev pointer to \ref usbd_device structure
 * \param ep endpoint address
 */
#define usbd_ep_unstall(dev, ep) (dev)->driver->ep_setstall((ep), 0)

/** @} */


#endif //(__ASSEMBLER__)

/**@} */


#if defined(__cplusplus)
    }
#endif
#endif //_USBD_STD_H_
