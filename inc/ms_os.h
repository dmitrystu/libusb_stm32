#ifndef _MS_OS_H_
#define _MS_OS_H_
/** 
 * Extended Properties OS Feature Descriptor Specification 
 * Extended Compat ID OS Feature Descriptor Specification
 *  v1.0
 */

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

/** Macro to create a unicode char array */
#define STRING_TO_WCHARS(s)	{CAT(u,s)}

/** Macro to return the total byte length of a string as if it were a unicode char array */
#define SIZE_OF_WSTRING(s)	sizeof(CAT(u,s))

/** Total Length of a custom property name (in bytes).
 *
 * This can be hard-coded at 42 for a 'DeviceInterFaceGUIDs' property name.
 */
#define MSOS_DEVGUID_NAME_BLEN  (SIZE_OF_WSTRING("DeviceInterfaceGUIDs"))

/** Total Length of a custom property value (in bytes).
 *
 * This can be hard-coded at 80 for a 'DeviceInterFaceGUIDs' property value.
 */
#define MSOS_DEVGUID_VALUE_BLEN (SIZE_OF_WSTRING("{00000000-0000-0000-0000-000000000000}\0"))

/**
 * \brief windows (winusb) Extended Compat ID OS Feature Descriptor
 * 
 * Stores one or more compatible IDs and subcompatible IDs in device firmware on a per-interface or per-function
 * basis. Windows can then use these values much like class and subclass values to select an appropriate driver.
 * (WinUSB for example)
 */
struct ms_os_compatid_descriptor {

	/**<\brief The length, in bytes, of the complete descriptor (DWORD LE). (40 bytes) */
	uint32_t dwLength;

	/**<\brief The descriptor’s version number, in binary coded decimal (BCD) format. (v1.00) */
	uint16_t bcdVersion;

	/**<\brief The index for extended properties OS descriptors. (always 0x04 for extended compat ID descriptors) */
	uint16_t wIndex;

	/**<\brief The number of custom property sections that follow the header section. (1 property) */
	uint8_t bCount;

	/**<\brief Not used.  fill with zeros. */
	uint8_t _reservedA[7];

	/**<\brief Interface or function that is associated with the IDs in this section */
	uint8_t bInterfaceNumber;

	/**<\brief Not used.  fill with zeros. */
	uint8_t _reservedB[1];

	/**<\brief A fixed string assign by Microsoft. 8 chars. fill extras with zero. (See MSDN) */
	uint8_t chCompatibleID[8];

	/**<\brief A fixed string assign by Microsoft. 8 chars. fill extras with zero. (See MSDN) */
	uint8_t chSubCompatibleID[8];

	/**<\brief Not used.  fill with zeros. */
	uint8_t _reservedC[6];
}__attribute__((packed));

/**
 * \brief windows (winusb) \bDeviceInterfaceGUIDs custom property
 * 
 * This is a DeviceInterfaceGUIDs property section used in \ref wusb_devguid_extprop_feature_descriptor.
 * 
 */
struct wusb_devguid_property {
	/**<\brief The size of this custom properties section, in bytes (136 bytes) */
	uint32_t dwPropertyLength;

	/**<\brief Property data format (7 = Unicode REG_MULTI_SZ) */
	uint32_t dwPropertyType;

	/**<\brief The total length of wPropertyName, in bytes (42) */
	uint16_t wPropertyNameLength;

	/**<\brief The property name, as a NULL-terminated Unicode string (42 bytes) */
	uint16_t wPropertyName[MSOS_DEVGUID_NAME_BLEN / 2];

	/**<\brief The total length of wPropertyData, in bytes (80) */
	uint32_t dwPropertyDataLength;

	/**<\brief (format-dependent) sz = Unicode strings (REG_MULTI_SZ, 76wchars + wnull + wnull = 80 bytes) */
	uint16_t wPropertyData[MSOS_DEVGUID_VALUE_BLEN / 2];

} __attribute__((packed));

/**
 * \brief windows (winusb) \bDeviceInterfaceGUIDs extended property feature descriptor
 * 
 * This is an extended property feature descriptor containing a DeviceInterfaceGUIDs property section.
 * 
 * Store DeviceInterfaceGUIDs in firmware and use them on Windows to locate and open a device.
 * 
 */
struct wusb_devguid_extprop_feature_descriptor {

	/**<\brief The length, in bytes, of the complete extended properties descriptor (DWORD LE). (146 bytes) */
	uint32_t dwLength;

	/**<\brief The descriptor’s version number, in binary coded decimal (BCD) format. */
	uint16_t bcdVersion;

	/**<\brief The index for extended properties OS descriptors. (always 5) */
	uint16_t wIndex;

	/**<\brief The number of custom property sections that follow the header section. (1 property) */
	uint16_t wCount;

	/**<\brief device interface guid custom property */
	struct wusb_devguid_property dev_guid_property;

}__attribute__((packed));

#endif