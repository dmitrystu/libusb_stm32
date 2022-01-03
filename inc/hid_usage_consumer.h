/* This file is the part of the Lightweight USB device Stack for STM32 microcontrollers
 *
 * Copyright ©2016 Dmitry Filimonchuk <dmitrystu[at]gmail[dot]com>
 * Copyright ©2021 Nikolay Minaylov <nm29719@gmail.com>
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

#ifndef _USB_HID_USAGE_CONSUMER_H_
#define _USB_HID_USAGE_CONSUMER_H_

/**\ingroup USB_HID
 * \addtogroup USB_HID_USAGES_CONSUMER HID Usage Tables for Consumer Control
 * \brief Contains USB HID Usages definitions for Consumer Control Page
 * \details This module based on
 * + [HID Usage Tables Version 1.12](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf)
 * @{ */

#define HID_PAGE_CONSUMER 0x0C

#define HID_CONSUMER_UNASSIGNED                             0x00
#define HID_CONSUMER_CONTROL                                0x01    /**<\brief CA */

#define HID_CONSUMER_NUMERIC_KEY_PAD                        0x02    /**<\brief NARY */
#define HID_CONSUMER_PROGRAMMABLE_BUTTONS                   0x03    /**<\brief NARY */
#define HID_CONSUMER_MICROPHONE                             0x04    /**<\brief CA */
#define HID_CONSUMER_HEADPHONE                              0x05    /**<\brief CA */
#define HID_CONSUMER_GRAPHIC_EQUALIZER                      0x06    /**<\brief CA */

#define HID_CONSUMER_PLUS_10                                0x20    /**<\brief OSC */
#define HID_CONSUMER_PLUS_100                               0x21    /**<\brief OSC */
#define HID_CONSUMER_AM_PM                                  0x22    /**<\brief OSC */

#define HID_CONSUMER_POWER                                  0x30    /**<\brief OOC */
#define HID_CONSUMER_RESET                                  0x31    /**<\brief OSC */
#define HID_CONSUMER_SLEEP                                  0x32    /**<\brief OSC */
#define HID_CONSUMER_SLEEP_AFTER                            0x33    /**<\brief OSC */
#define HID_CONSUMER_SLEEP_MODE                             0x34    /**<\brief RTC */
#define HID_CONSUMER_ILLUMINATION                           0x35    /**<\brief OOC */

#define HID_CONSUMER_FUNCTION_BUTTONS                       0x36    /**<\brief NARY */
#define HID_CONSUMER_MENU                                   0x40    /**<\brief OOC */
#define HID_CONSUMER_MENU_PICK                              0x41    /**<\brief OSC */
#define HID_CONSUMER_MENU_UP                                0x42    /**<\brief OSC */
#define HID_CONSUMER_MENU_DOWN                              0x43    /**<\brief OSC */
#define HID_CONSUMER_MENU_LEFT                              0x44    /**<\brief OSC */
#define HID_CONSUMER_MENU_RIGHT                             0x45    /**<\brief OSC */
#define HID_CONSUMER_MENU_ESCAPE                            0x46    /**<\brief OSC */
#define HID_CONSUMER_MENU_VALUE_INCREASE                    0x47    /**<\brief OSC */
#define HID_CONSUMER_MENU_VALUE_DECREASE                    0x48    /**<\brief OSC */
#define HID_CONSUMER_DATA_ON_SCREEN                         0x60    /**<\brief OOC */
#define HID_CONSUMER_CLOSED_CAPTION                         0x61    /**<\brief OOC */
#define HID_CONSUMER_CLOSED_CAPTION_SELECT                  0x62    /**<\brief OSC */
#define HID_CONSUMER_VCR_TV                                 0x63    /**<\brief OOC */
#define HID_CONSUMER_BROADCAST_MODE                         0x64    /**<\brief OSC */
#define HID_CONSUMER_SNAPSHOT                               0x65    /**<\brief OSC */
#define HID_CONSUMER_STILL                                  0x66    /**<\brief OSC */

#define HID_CONSUMER_SELECTION                              0x80    /**<\brief NARY */
#define HID_CONSUMER_ASSIGN_SELECTION                       0x81    /**<\brief OSC */
#define HID_CONSUMER_MODE_STEP                              0x82    /**<\brief OSC */
#define HID_CONSUMER_RECALL_LAST                            0x83    /**<\brief OSC */
#define HID_CONSUMER_ENTER_CHANNEL                          0x84    /**<\brief OSC */
#define HID_CONSUMER_ORDER_MOVIE                            0x85    /**<\brief OSC */
#define HID_CONSUMER_CHANNEL                                0x86    /**<\brief LC */

#define HID_CONSUMER_MEDIA_SELECTION                        0x87    /**<\brief NARY */
#define HID_CONSUMER_MEDIA_SELECT_COMPUTER                  0x88    /**<\brief SEL */
#define HID_CONSUMER_MEDIA_SELECT_TV                        0x89    /**<\brief SEL */
#define HID_CONSUMER_MEDIA_SELECT_WWW                       0x8A    /**<\brief SEL */
#define HID_CONSUMER_MEDIA_SELECT_DVD                       0x8B    /**<\brief SEL */
#define HID_CONSUMER_MEDIA_SELECT_TELEPHONE                 0x8C    /**<\brief SEL */
#define HID_CONSUMER_MEDIA_SELECT_PROGRAM_GUIDE             0x8D    /**<\brief SEL */
#define HID_CONSUMER_MEDIA_SELECT_VIDEO_PHONE               0x8E    /**<\brief SEL */
#define HID_CONSUMER_MEDIA_SELECT_GAMES                     0x8F    /**<\brief SEL */
#define HID_CONSUMER_MEDIA_SELECT_MESSAGES                  0x90    /**<\brief SEL */
#define HID_CONSUMER_MEDIA_SELECT_CD                        0x91    /**<\brief SEL */
#define HID_CONSUMER_MEDIA_SELECT_VCR                       0x92    /**<\brief SEL */
#define HID_CONSUMER_MEDIA_SELECT_TUNER                     0x93    /**<\brief SEL */
#define HID_CONSUMER_QUIT                                   0x94    /**<\brief OSC */
#define HID_CONSUMER_HELP                                   0x95    /**<\brief OOC */
#define HID_CONSUMER_MEDIA_SELECT_TAPE                      0x96    /**<\brief SEL */
#define HID_CONSUMER_MEDIA_SELECT_CABLE                     0x97    /**<\brief SEL */
#define HID_CONSUMER_MEDIA_SELECT_SATELLITE                 0x98    /**<\brief SEL */
#define HID_CONSUMER_MEDIA_SELECT_SECURITY                  0x99    /**<\brief SEL */
#define HID_CONSUMER_MEDIA_SELECT_HOME                      0x9A    /**<\brief SEL */
#define HID_CONSUMER_MEDIA_SELECT_CALL                      0x9B    /**<\brief SEL */
#define HID_CONSUMER_CHANNEL_INCREMENT                      0x9C    /**<\brief OSC */
#define HID_CONSUMER_CHANNEL_DECREMENT                      0x9D    /**<\brief OSC */
#define HID_CONSUMER_MEDIA_SELECT_SAP                       0x9E    /**<\brief SEL */

#define HID_CONSUMER_VCR_PLUS                               0xA0    /**<\brief OSC */
#define HID_CONSUMER_ONCE                                   0xA1    /**<\brief OSC */
#define HID_CONSUMER_DAILY                                  0xA2    /**<\brief OSC */
#define HID_CONSUMER_WEEKLY                                 0xA3    /**<\brief OSC */
#define HID_CONSUMER_MONTHLY                                0xA4    /**<\brief OSC */

#define HID_CONSUMER_PLAY                                   0xB0    /**<\brief OOC */
#define HID_CONSUMER_PAUSE                                  0xB1    /**<\brief OOC */
#define HID_CONSUMER_RECORD                                 0xB2    /**<\brief OOC */
#define HID_CONSUMER_FAST_FORWARD                           0xB3    /**<\brief OOC */
#define HID_CONSUMER_REWIND                                 0xB4    /**<\brief OOC */
#define HID_CONSUMER_SCAN_NEXT_TRACK                        0xB5    /**<\brief OSC */
#define HID_CONSUMER_SCAN_PREVIOUS_TRACK                    0xB6    /**<\brief OSC */
#define HID_CONSUMER_STOP                                   0xB7    /**<\brief OSC */
#define HID_CONSUMER_EJECT                                  0xB8    /**<\brief OSC */
#define HID_CONSUMER_RANDOM_PLAY                            0xB9    /**<\brief OOC */
#define HID_CONSUMER_SELECT_DISC                            0xBA    /**<\brief NARY */
#define HID_CONSUMER_ENTER_DISC                             0xBB    /**<\brief MC */
#define HID_CONSUMER_REPEAT                                 0xBC    /**<\brief OSC */
#define HID_CONSUMER_TRACKING                               0xBD    /**<\brief LC */
#define HID_CONSUMER_TRACK_NORMAL                           0xBE    /**<\brief OSC */
#define HID_CONSUMER_SLOW_TRACKING                          0xBF    /**<\brief LC */
#define HID_CONSUMER_FRAME_FORWARD                          0xC0    /**<\brief RTC */
#define HID_CONSUMER_FRAME_BACK                             0xC1    /**<\brief RTC */
#define HID_CONSUMER_MARK                                   0xC2    /**<\brief OSC */
#define HID_CONSUMER_CLEAR_MARK                             0xC3    /**<\brief OSC */
#define HID_CONSUMER_REPEAT_FROM_MARK                       0xC4    /**<\brief OOC */
#define HID_CONSUMER_RETURN_TO_MARK                         0xC5    /**<\brief OSC */
#define HID_CONSUMER_SEARCH_MARK_FORWARD                    0xC6    /**<\brief OSC */
#define HID_CONSUMER_SEARCH_MARK_BACKWARDS                  0xC7    /**<\brief OSC */
#define HID_CONSUMER_COUNTER_RESET                          0xC8    /**<\brief OSC */
#define HID_CONSUMER_SHOW_COUNTER                           0xC9    /**<\brief OSC */
#define HID_CONSUMER_TRACKING_INCREMENT                     0xCA    /**<\brief RTC */
#define HID_CONSUMER_TRACKING_DECREMENT                     0xCB    /**<\brief RTC */
#define HID_CONSUMER_STOP_EJECT                             0xCC    /**<\brief OSC */
#define HID_CONSUMER_PLAY_PAUSE                             0xCD    /**<\brief OSC */
#define HID_CONSUMER_PLAY_SKIP                              0xCE    /**<\brief OSC */

#define HID_CONSUMER_VOLUME                                 0xE0    /**<\brief LC */
#define HID_CONSUMER_BALANCE                                0xE1    /**<\brief LC */
#define HID_CONSUMER_MUTE                                   0xE2    /**<\brief OOC */
#define HID_CONSUMER_BASS                                   0xE3    /**<\brief LC */
#define HID_CONSUMER_TREBLE                                 0xE4    /**<\brief LC */
#define HID_CONSUMER_BASS_BOOST                             0xE5    /**<\brief OOC */
#define HID_CONSUMER_SURROUND_MODE                          0xE6    /**<\brief OSC */
#define HID_CONSUMER_LOUDNESS                               0xE7    /**<\brief OOC */
#define HID_CONSUMER_MPX                                    0xE8    /**<\brief OOC */
#define HID_CONSUMER_VOLUME_INCREMENT                       0xE9    /**<\brief RTC */
#define HID_CONSUMER_VOLUME_DECREMENT                       0xEA    /**<\brief RTC */

#define HID_CONSUMER_SPEED_SELECT                           0xF0    /**<\brief OSC */
#define HID_CONSUMER_PLAYBACK_SPEED                         0xF1    /**<\brief NARY */
#define HID_CONSUMER_STANDARD_PLAY                          0xF2    /**<\brief SEL */
#define HID_CONSUMER_LONG_PLAY                              0xF3    /**<\brief SEL */
#define HID_CONSUMER_EXTENDED_PLAY                          0xF4    /**<\brief SEL */
#define HID_CONSUMER_SLOW                                   0xF5    /**<\brief OSC */

#define HID_CONSUMER_FAN_ENABLE                             0x100   /**<\brief OOC */
#define HID_CONSUMER_FAN_SPEED                              0x101   /**<\brief LC */
#define HID_CONSUMER_LIGHT_ENABLE                           0x102   /**<\brief OOC */
#define HID_CONSUMER_LIGHT_ILLUMINATION_LEVEL               0x103   /**<\brief LC */
#define HID_CONSUMER_CLIMATE_CONTROL_ENABLE                 0x104   /**<\brief OOC */
#define HID_CONSUMER_ROOM_TEMPERATURE                       0x105   /**<\brief LC */
#define HID_CONSUMER_SECURITY_ENABLE                        0x106   /**<\brief OOC */
#define HID_CONSUMER_FIRE_ALARM                             0x107   /**<\brief OSC */
#define HID_CONSUMER_POLICE_ALARM                           0x108   /**<\brief OSC */
#define HID_CONSUMER_PROXIMITY                              0x109   /**<\brief LC */
#define HID_CONSUMER_MOTION                                 0x10A   /**<\brief OSC */
#define HID_CONSUMER_DURESS_ALARM                           0x10B   /**<\brief OSC */
#define HID_CONSUMER_HOLDUP_ALARM                           0x10C   /**<\brief OSC */
#define HID_CONSUMER_MEDICAL_ALARM                          0x10D   /**<\brief OSC */

#define HID_CONSUMER_BALANCE_RIGHT                          0x150   /**<\brief RTC */
#define HID_CONSUMER_BALANCE_LEFT                           0x151   /**<\brief RTC */
#define HID_CONSUMER_BASS_INCREMENT                         0x152   /**<\brief RTC */
#define HID_CONSUMER_BASS_DECREMENT                         0x153   /**<\brief RTC */
#define HID_CONSUMER_TREBLE_INCREMENT                       0x154   /**<\brief RTC */
#define HID_CONSUMER_TREBLE_DECREMENT                       0x155   /**<\brief RTC */

#define HID_CONSUMER_SPEAKER_SYSTEM                         0x160   /**<\brief CL */
#define HID_CONSUMER_CHANNEL_LEFT                           0x161   /**<\brief CL */
#define HID_CONSUMER_CHANNEL_RIGHT                          0x162   /**<\brief CL */
#define HID_CONSUMER_CHANNEL_CENTER                         0x163   /**<\brief CL */
#define HID_CONSUMER_CHANNEL_FRONT                          0x164   /**<\brief CL */
#define HID_CONSUMER_CHANNEL_CENTER_FRONT                   0x165   /**<\brief CL */
#define HID_CONSUMER_CHANNEL_SIDE                           0x166   /**<\brief CL */
#define HID_CONSUMER_CHANNEL_SURROUND                       0x167   /**<\brief CL */
#define HID_CONSUMER_CHANNEL_LOW_FREQUENCY_ENHANCEMENT      0x168   /**<\brief CL */
#define HID_CONSUMER_CHANNEL_TOP                            0x169   /**<\brief CL */
#define HID_CONSUMER_CHANNEL_UNKNOWN                        0x16A   /**<\brief CL */

#define HID_CONSUMER_SUB_CHANNEL                            0x170   /**<\brief LC */
#define HID_CONSUMER_SUB_CHANNEL_INCREMENT                  0x171   /**<\brief OSC */
#define HID_CONSUMER_SUB_CHANNEL_DECREMENT                  0x172   /**<\brief OSC */
#define HID_CONSUMER_ALTERNATE_AUDIO_INCREMENT              0x173   /**<\brief OSC */
#define HID_CONSUMER_ALTERNATE_AUDIO_DECREMENT              0x174   /**<\brief OSC */

#define HID_CONSUMER_APPLICATION_LAUNCH_BUTTONS             0x180   /**<\brief NARY */
#define HID_CONSUMER_AL_LAUNCH_BUTTON_CONFIGURATION_TOOL    0x181   /**<\brief SEL */
#define HID_CONSUMER_AL_PROGRAMMABLE_BUTTON_CONFIGURATION   0x182   /**<\brief SEL */
#define HID_CONSUMER_AL_CONSUMER_CONTROL_CONFIGURATION      0x183   /**<\brief SEL */
#define HID_CONSUMER_AL_WORD_PROCESSOR                      0x184   /**<\brief SEL */
#define HID_CONSUMER_AL_TEXT_EDITOR                         0x185   /**<\brief SEL */
#define HID_CONSUMER_AL_SPREADSHEET                         0x186   /**<\brief SEL */
#define HID_CONSUMER_AL_GRAPHICS_EDITOR                     0x187   /**<\brief SEL */
#define HID_CONSUMER_AL_PRESENTATION_APP                    0x188   /**<\brief SEL */
#define HID_CONSUMER_AL_DATABASE_APP                        0x189   /**<\brief SEL */
#define HID_CONSUMER_AL_EMAIL_READER                        0x18A   /**<\brief SEL */
#define HID_CONSUMER_AL_NEWSREADER                          0x18B   /**<\brief SEL */
#define HID_CONSUMER_AL_VOICEMAIL                           0x18C   /**<\brief SEL */
#define HID_CONSUMER_AL_CONTACTS_ADDRESS_BOOK               0x18D   /**<\brief SEL */
#define HID_CONSUMER_AL_CALENDAR_SCHEDULE                   0x18E   /**<\brief SEL */
#define HID_CONSUMER_AL_TASK_PROJECT_MANAGER                0x18F   /**<\brief SEL */
#define HID_CONSUMER_AL_LOG_JOURNAL_TIMECARD                0x190   /**<\brief SEL */
#define HID_CONSUMER_AL_CHECKBOOK_FINANCE                   0x191   /**<\brief SEL */
#define HID_CONSUMER_AL_CALCULATOR                          0x192   /**<\brief SEL */
#define HID_CONSUMER_AL_A_V_CAPTURE_PLAYBACK                0x193   /**<\brief SEL */
#define HID_CONSUMER_AL_LOCAL_MACHINE_BROWSER               0x194   /**<\brief SEL */
#define HID_CONSUMER_AL_LAN_WAN_BROWSER                     0x195   /**<\brief SEL */
#define HID_CONSUMER_AL_INTERNET_BROWSER                    0x196   /**<\brief SEL */
#define HID_CONSUMER_AL_REMOTE_NETWORKING_ISP_CONNECT       0x197   /**<\brief SEL */
#define HID_CONSUMER_AL_NETWORK_CONFERENCE                  0x198   /**<\brief SEL */
#define HID_CONSUMER_AL_NETWORK_CHAT                        0x199   /**<\brief SEL */
#define HID_CONSUMER_AL_TELEPHONY_DIALER                    0x19A   /**<\brief SEL */
#define HID_CONSUMER_AL_LOGON                               0x19B   /**<\brief SEL */
#define HID_CONSUMER_AL_LOGOFF                              0x19C   /**<\brief SEL */
#define HID_CONSUMER_AL_LOGON_LOGOFF                        0x19D   /**<\brief SEL */
#define HID_CONSUMER_AL_TERMINAL_LOCK_SCREENSAVER           0x19E   /**<\brief SEL */
#define HID_CONSUMER_AL_CONTROL_PANEL                       0x19F   /**<\brief SEL */
#define HID_CONSUMER_AL_COMMAND_LINE_PROCESSOR_RUN          0x1A0   /**<\brief SEL */
#define HID_CONSUMER_AL_PROCESS_TASK_MANAGER                0x1A1   /**<\brief SEL */
#define HID_CONSUMER_AL_SELECT_TASK_APPLICATION             0x1A2   /**<\brief SEL */
#define HID_CONSUMER_AL_NEXT_TASK_APPLICATION               0x1A3   /**<\brief SEL */
#define HID_CONSUMER_AL_PREVIOUS_TASK_APPLICATION           0x1A4   /**<\brief SEL */
#define HID_CONSUMER_AL_PREEMPTIVE_HALT_TASK_APPLICATION    0x1A5   /**<\brief SEL */
#define HID_CONSUMER_AL_INTEGRATED_HELP_CENTER              0x1A6   /**<\brief SEL */
#define HID_CONSUMER_AL_DOCUMENTS                           0x1A7   /**<\brief SEL */
#define HID_CONSUMER_AL_THESAURUS                           0x1A8   /**<\brief SEL */
#define HID_CONSUMER_AL_DICTIONARY                          0x1A9   /**<\brief SEL */
#define HID_CONSUMER_AL_DESKTOP                             0x1AA   /**<\brief SEL */
#define HID_CONSUMER_AL_SPELL_CHECK                         0x1AB   /**<\brief SEL */
#define HID_CONSUMER_AL_GRAMMAR_CHECK                       0x1AC   /**<\brief SEL */
#define HID_CONSUMER_AL_WIRELESS_STATUS                     0x1AD   /**<\brief SEL */
#define HID_CONSUMER_AL_KEYBOARD_LAYOUT                     0x1AE   /**<\brief SEL */
#define HID_CONSUMER_AL_VIRUS_PROTECTION                    0x1AF   /**<\brief SEL */
#define HID_CONSUMER_AL_ENCRYPTION                          0x1B0   /**<\brief SEL */
#define HID_CONSUMER_AL_SCREEN_SAVER                        0x1B1   /**<\brief SEL */
#define HID_CONSUMER_AL_ALARMS                              0x1B2   /**<\brief SEL */
#define HID_CONSUMER_AL_CLOCK                               0x1B3   /**<\brief SEL */
#define HID_CONSUMER_AL_FILE_BROWSER                        0x1B4   /**<\brief SEL */
#define HID_CONSUMER_AL_POWER_STATUS                        0x1B5   /**<\brief SEL */
#define HID_CONSUMER_AL_IMAGE_BROWSER                       0x1B6   /**<\brief SEL */
#define HID_CONSUMER_AL_AUDIO_BROWSER                       0x1B7   /**<\brief SEL */
#define HID_CONSUMER_AL_MOVIE_BROWSER                       0x1B8   /**<\brief SEL */
#define HID_CONSUMER_AL_DIGITAL_RIGHTS_MANAGER              0x1B9   /**<\brief SEL */
#define HID_CONSUMER_AL_DIGITAL_WALLET                      0x1BA   /**<\brief SEL */
#define HID_CONSUMER_AL_INSTANT_MESSAGING                   0x1BC   /**<\brief SEL */
#define HID_CONSUMER_AL_OEM_FEATURES_TIPS_TUTORIAL_BROWSER  0x1BD   /**<\brief SEL */
#define HID_CONSUMER_AL_OEM_HELP                            0x1BE   /**<\brief SEL */
#define HID_CONSUMER_AL_ONLINE_COMMUNITY                    0x1BF   /**<\brief SEL */
#define HID_CONSUMER_AL_ENTERTAINMENT_CONTENT_BROWSER       0x1C0   /**<\brief SEL */
#define HID_CONSUMER_AL_ONLINE_SHOPPING_BROWSER             0x1C1   /**<\brief SEL */
#define HID_CONSUMER_AL_SMARTCARD_INFORMATION_HELP          0x1C2   /**<\brief SEL */
#define HID_CONSUMER_AL_MARKET_MONITOR_FINANCE_BROWSER      0x1C3   /**<\brief SEL */
#define HID_CONSUMER_AL_CUSTOMIZED_CORPORATE_NEWS_BROWSER   0x1C4   /**<\brief SEL */
#define HID_CONSUMER_AL_ONLINE_ACTIVITY_BROWSER             0x1C5   /**<\brief SEL */
#define HID_CONSUMER_AL_RESEARCH_SEARCH_BROWSER             0x1C6   /**<\brief SEL */
#define HID_CONSUMER_AL_AUDIO_PLAYER                        0x1C7   /**<\brief SEL */

#define HID_CONSUMER_GENERIC_GUI_APPLICATION_CONTROLS       0x200   /**<\brief NARY */
#define HID_CONSUMER_AC_NEW                                 0x201   /**<\brief SEL */
#define HID_CONSUMER_AC_OPEN                                0x202   /**<\brief SEL */
#define HID_CONSUMER_AC_CLOSE                               0x203   /**<\brief SEL */
#define HID_CONSUMER_AC_EXIT                                0x204   /**<\brief SEL */
#define HID_CONSUMER_AC_MAXIMIZE                            0x205   /**<\brief SEL */
#define HID_CONSUMER_AC_MINIMIZE                            0x206   /**<\brief SEL */
#define HID_CONSUMER_AC_SAVE                                0x207   /**<\brief SEL */
#define HID_CONSUMER_AC_PRINT                               0x208   /**<\brief SEL */
#define HID_CONSUMER_AC_PROPERTIES                          0x209   /**<\brief SEL */
#define HID_CONSUMER_AC_UNDO                                0x21A   /**<\brief SEL */
#define HID_CONSUMER_AC_COPY                                0x21B   /**<\brief SEL */
#define HID_CONSUMER_AC_CUT                                 0x21C   /**<\brief SEL */
#define HID_CONSUMER_AC_PASTE                               0x21D   /**<\brief SEL */
#define HID_CONSUMER_AC_SELECT_ALL                          0x21E   /**<\brief SEL */
#define HID_CONSUMER_AC_FIND                                0x21F   /**<\brief SEL */
#define HID_CONSUMER_AC_FIND_AND_REPLACE                    0x220   /**<\brief SEL */
#define HID_CONSUMER_AC_SEARCH                              0x221   /**<\brief SEL */
#define HID_CONSUMER_AC_GO_TO                               0x222   /**<\brief SEL */
#define HID_CONSUMER_AC_HOME                                0x223   /**<\brief SEL */
#define HID_CONSUMER_AC_BACK                                0x224   /**<\brief SEL */
#define HID_CONSUMER_AC_FORWARD                             0x225   /**<\brief SEL */
#define HID_CONSUMER_AC_STOP                                0x226   /**<\brief SEL */
#define HID_CONSUMER_AC_REFRESH                             0x227   /**<\brief SEL */
#define HID_CONSUMER_AC_PREVIOUS_LINK                       0x228   /**<\brief SEL */
#define HID_CONSUMER_AC_NEXT_LINK                           0x229   /**<\brief SEL */
#define HID_CONSUMER_AC_BOOKMARKS                           0x22A   /**<\brief SEL */
#define HID_CONSUMER_AC_HISTORY                             0x22B   /**<\brief SEL */
#define HID_CONSUMER_AC_SUBSCRIPTIONS                       0x22C   /**<\brief SEL */
#define HID_CONSUMER_AC_ZOOM_IN                             0x22D   /**<\brief SEL */
#define HID_CONSUMER_AC_ZOOM_OUT                            0x22E   /**<\brief SEL */
#define HID_CONSUMER_AC_ZOOM                                0x22F   /**<\brief LC */
#define HID_CONSUMER_AC_FULL_SCREEN_VIEW                    0x230   /**<\brief SEL */
#define HID_CONSUMER_AC_NORMAL_VIEW                         0x231   /**<\brief SEL */
#define HID_CONSUMER_AC_VIEW_TOGGLE                         0x232   /**<\brief SEL */
#define HID_CONSUMER_AC_SCROLL_UP                           0x233   /**<\brief SEL */
#define HID_CONSUMER_AC_SCROLL_DOWN                         0x234   /**<\brief SEL */
#define HID_CONSUMER_AC_SCROLL                              0x235   /**<\brief LC */
#define HID_CONSUMER_AC_PAN_LEFT                            0x236   /**<\brief SEL */
#define HID_CONSUMER_AC_PAN_RIGHT                           0x237   /**<\brief SEL */
#define HID_CONSUMER_AC_PAN                                 0x238   /**<\brief LC */
#define HID_CONSUMER_AC_NEW_WINDOW                          0x239   /**<\brief SEL */
#define HID_CONSUMER_AC_TILE_HORIZONTALLY                   0x23A   /**<\brief SEL */
#define HID_CONSUMER_AC_TILE_VERTICALLY                     0x23B   /**<\brief SEL */
#define HID_CONSUMER_AC_FORMAT                              0x23C   /**<\brief SEL */
#define HID_CONSUMER_AC_EDIT                                0x23D   /**<\brief SEL */
#define HID_CONSUMER_AC_BOLD                                0x23E   /**<\brief SEL */
#define HID_CONSUMER_AC_ITALICS                             0x23F   /**<\brief SEL */
#define HID_CONSUMER_AC_UNDERLINE                           0x240   /**<\brief SEL */
#define HID_CONSUMER_AC_STRIKETHROUGH                       0x241   /**<\brief SEL */
#define HID_CONSUMER_AC_SUBSCRIPT                           0x242   /**<\brief SEL */
#define HID_CONSUMER_AC_SUPERSCRIPT                         0x243   /**<\brief SEL */
#define HID_CONSUMER_AC_ALL_CAPS                            0x244   /**<\brief SEL */
#define HID_CONSUMER_AC_ROTATE                              0x245   /**<\brief SEL */
#define HID_CONSUMER_AC_RESIZE                              0x246   /**<\brief SEL */
#define HID_CONSUMER_AC_FLIP_HORIZONTAL                     0x247   /**<\brief SEL */
#define HID_CONSUMER_AC_FLIP_VERTICAL                       0x248   /**<\brief SEL */
#define HID_CONSUMER_AC_MIRROR_HORIZONTAL                   0x249   /**<\brief SEL */
#define HID_CONSUMER_AC_MIRROR_VERTICAL                     0x24A   /**<\brief SEL */
#define HID_CONSUMER_AC_FONT_SELECT                         0x24B   /**<\brief SEL */
#define HID_CONSUMER_AC_FONT_COLOR                          0x24C   /**<\brief SEL */
#define HID_CONSUMER_AC_FONT_SIZE                           0x24D   /**<\brief SEL */
#define HID_CONSUMER_AC_JUSTIFY_LEFT                        0x24E   /**<\brief SEL */
#define HID_CONSUMER_AC_JUSTIFY_CENTER_H                    0x24F   /**<\brief SEL */
#define HID_CONSUMER_AC_JUSTIFY_RIGHT                       0x250   /**<\brief SEL */
#define HID_CONSUMER_AC_JUSTIFY_BLOCK_H                     0x251   /**<\brief SEL */
#define HID_CONSUMER_AC_JUSTIFY_TOP                         0x252   /**<\brief SEL */
#define HID_CONSUMER_AC_JUSTIFY_CENTER_V                    0x253   /**<\brief SEL */
#define HID_CONSUMER_AC_JUSTIFY_BOTTOM                      0x254   /**<\brief SEL */
#define HID_CONSUMER_AC_JUSTIFY_BLOCK_V                     0x255   /**<\brief SEL */
#define HID_CONSUMER_AC_INDENT_DECREASE                     0x256   /**<\brief SEL */
#define HID_CONSUMER_AC_INDENT_INCREASE                     0x257   /**<\brief SEL */
#define HID_CONSUMER_AC_NUMBERED_LIST                       0x258   /**<\brief SEL */
#define HID_CONSUMER_AC_RESTART_NUMBERING                   0x259   /**<\brief SEL */
#define HID_CONSUMER_AC_BULLETED_LIST                       0x25A   /**<\brief SEL */
#define HID_CONSUMER_AC_PROMOTE                             0x25B   /**<\brief SEL */
#define HID_CONSUMER_AC_DEMOTE                              0x25C   /**<\brief SEL */
#define HID_CONSUMER_AC_YES                                 0x25D   /**<\brief SEL */
#define HID_CONSUMER_AC_NO                                  0x25E   /**<\brief SEL */
#define HID_CONSUMER_AC_CANCEL                              0x25F   /**<\brief SEL */
#define HID_CONSUMER_AC_CATALOG                             0x260   /**<\brief SEL */
#define HID_CONSUMER_AC_BUY_CHECKOUT                        0x261   /**<\brief SEL */
#define HID_CONSUMER_AC_ADD_TO_CART                         0x262   /**<\brief SEL */
#define HID_CONSUMER_AC_EXPAND                              0x263   /**<\brief SEL */
#define HID_CONSUMER_AC_EXPAND_ALL                          0x264   /**<\brief SEL */
#define HID_CONSUMER_AC_COLLAPSE                            0x265   /**<\brief SEL */
#define HID_CONSUMER_AC_COLLAPSE_ALL                        0x266   /**<\brief SEL */
#define HID_CONSUMER_AC_PRINT_PREVIEW                       0x267   /**<\brief SEL */
#define HID_CONSUMER_AC_PASTE_SPECIAL                       0x268   /**<\brief SEL */
#define HID_CONSUMER_AC_INSERT_MODE                         0x269   /**<\brief SEL */
#define HID_CONSUMER_AC_DELETE                              0x26A   /**<\brief SEL */
#define HID_CONSUMER_AC_LOCK                                0x26B   /**<\brief SEL */
#define HID_CONSUMER_AC_UNLOCK                              0x26C   /**<\brief SEL */
#define HID_CONSUMER_AC_PROTECT                             0x26D   /**<\brief SEL */
#define HID_CONSUMER_AC_UNPROTECT                           0x26E   /**<\brief SEL */
#define HID_CONSUMER_AC_ATTACH_COMMENT                      0x26F   /**<\brief SEL */
#define HID_CONSUMER_AC_DELETE_COMMENT                      0x270   /**<\brief SEL */
#define HID_CONSUMER_AC_VIEW_COMMENT                        0x271   /**<\brief SEL */
#define HID_CONSUMER_AC_SELECT_WORD                         0x272   /**<\brief SEL */
#define HID_CONSUMER_AC_SELECT_SENTENCE                     0x273   /**<\brief SEL */
#define HID_CONSUMER_AC_SELECT_PARAGRAPH                    0x274   /**<\brief SEL */
#define HID_CONSUMER_AC_SELECT_COLUMN                       0x275   /**<\brief SEL */
#define HID_CONSUMER_AC_SELECT_ROW                          0x276   /**<\brief SEL */
#define HID_CONSUMER_AC_SELECT_TABLE                        0x277   /**<\brief SEL */
#define HID_CONSUMER_AC_SELECT_OBJECT                       0x278   /**<\brief SEL */
#define HID_CONSUMER_AC_REDO_REPEAT                         0x279   /**<\brief SEL */
#define HID_CONSUMER_AC_SORT                                0x27A   /**<\brief SEL */
#define HID_CONSUMER_AC_SORT_ASCENDING                      0x27B   /**<\brief SEL */
#define HID_CONSUMER_AC_SORT_DESCENDING                     0x27C   /**<\brief SEL */
#define HID_CONSUMER_AC_FILTER                              0x27D   /**<\brief SEL */
#define HID_CONSUMER_AC_SET_CLOCK                           0x27E   /**<\brief SEL */
#define HID_CONSUMER_AC_VIEW_CLOCK                          0x27F   /**<\brief SEL */
#define HID_CONSUMER_AC_SELECT_TIME_ZONE                    0x280   /**<\brief SEL */
#define HID_CONSUMER_AC_EDIT_TIME_ZONES                     0x281   /**<\brief SEL */
#define HID_CONSUMER_AC_SET_ALARM                           0x282   /**<\brief SEL */
#define HID_CONSUMER_AC_CLEAR_ALARM                         0x283   /**<\brief SEL */
#define HID_CONSUMER_AC_SNOOZE_ALARM                        0x284   /**<\brief SEL */
#define HID_CONSUMER_AC_RESET_ALARM                         0x285   /**<\brief SEL */
#define HID_CONSUMER_AC_SYNCHRONIZE                         0x286   /**<\brief SEL */
#define HID_CONSUMER_AC_SEND_RECEIVE                        0x287   /**<\brief SEL */
#define HID_CONSUMER_AC_SEND_TO                             0x288   /**<\brief SEL */
#define HID_CONSUMER_AC_REPLY                               0x289   /**<\brief SEL */
#define HID_CONSUMER_AC_REPLY_ALL                           0x28A   /**<\brief SEL */
#define HID_CONSUMER_AC_FORWARD_MSG                         0x28B   /**<\brief SEL */
#define HID_CONSUMER_AC_SEND                                0x28C   /**<\brief SEL */
#define HID_CONSUMER_AC_ATTACH_FILE                         0x28D   /**<\brief SEL */
#define HID_CONSUMER_AC_UPLOAD                              0x28E   /**<\brief SEL */
#define HID_CONSUMER_AC_DOWNLOAD_SAVE_TARGET_AS             0x28F   /**<\brief SEL */
#define HID_CONSUMER_AC_SET_BORDERS                         0x290   /**<\brief SEL */
#define HID_CONSUMER_AC_INSERT_ROW                          0x291   /**<\brief SEL */
#define HID_CONSUMER_AC_INSERT_COLUMN                       0x292   /**<\brief SEL */
#define HID_CONSUMER_AC_INSERT_FILE                         0x293   /**<\brief SEL */
#define HID_CONSUMER_AC_INSERT_PICTURE                      0x294   /**<\brief SEL */
#define HID_CONSUMER_AC_INSERT_OBJECT                       0x295   /**<\brief SEL */
#define HID_CONSUMER_AC_INSERT_SYMBOL                       0x296   /**<\brief SEL */
#define HID_CONSUMER_AC_SAVE_AND_CLOSE                      0x297   /**<\brief SEL */
#define HID_CONSUMER_AC_RENAME                              0x298   /**<\brief SEL */
#define HID_CONSUMER_AC_MERGE                               0x299   /**<\brief SEL */
#define HID_CONSUMER_AC_SPLIT                               0x29A   /**<\brief SEL */
#define HID_CONSUMER_AC_DISRIBUTE_HORIZONTALLY              0x29B   /**<\brief SEL */
#define HID_CONSUMER_AC_DISTRIBUTE_VERTICALLY               0x29C   /**<\brief SEL */

/** @}  */

#endif

