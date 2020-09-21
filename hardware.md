## HARDWARE

|     Target     |   Board                    | Notes                                       |
|----------------|----------------------------|---------------------------------------------|
| stm32f103x6    | bluepill                   |                                             |
| stm32f303xe    | NUCLEO-F303RE + NUCLEO2USB |                                             |
| stm32f105xb    | NUCLEO-F105RB + NUCLEO2USB | based on NUCLEO-F103RE, direct replacement  |
| stm32l052x8    | DIY board                  |                                             |
| stm32l100xc    | STM32L100C-DISCO           |                                             |
| stm32l476xg    | NUCLEO-L476RG + NUCLEO2USB |                                             |
| stm32f429xi    | NUCLEO-F429ZI              |                                             |
| stm32f429xi_hs | NUCLEO-F429ZI              |                                             |
| stm32l433cc    | bluepill with STM32L433CC  | direct replacement, R10 removed             |
| stm32f070xb    | bluepill with STM32F070CB  | direct replacemrnt, R10 removed             |
| stm32g431xb    | NUCLEO-G431RB + NUCLEO2USB |                                             |
| stm32f446xc    | NUCLEO-F446RE + NUCLEO2USB |                                             |
| stm32f446xc_hs | NUCLEO-F446RE + NUCLEO2USB |                                             |
| stm32f373xc    | bluepill with STM32F373CC  | 2 cuts + 1 jumper wire                      |
| stm32l053x8    | NUCLEO-L053R8 + NUCLEO2USB |                                             |
| stm32f405xg    | NUCLEO-F405RG + NUCLEO2USB | based on NUCLEO-F103RE, 0.1uF at SB33, SB38 |
| stm32f405xg_hs | NUCLEO-F405RG + NUCLEO2USB | based on NUCLEO-F103RE, 0.1uF at SB33, SB38 |


## NUCLEO2USB SHIELD V0.1

![NUCLEO2USB SHUELD](https://user-images.githubusercontent.com/15378501/89074235-b1c76500-d384-11ea-9881-f75be2e58cda.JPG)

+ Compatible with NUCLEO-64 boards
+ Can be configured as 2xOTGFS, 1xOTGFS, 2xDEVFS, 1xDEVFS, 1xDEVFS+1xOTGFS
+ Can provide power to the baseboard from USB1 USB2 and STLINK(U5V) via E5V pin
+ USB FS/LS override jumper (for the NUCLEO-F303RE / NUCLEO-F103RB)
+ 2x micro USB TYPE B connectors
+ ESCDA5V3SC6 USB ESD protection
+ LM3526L USB-OTG power switch with over-current protection

If you are interested in this device or if you have any questions and suggestions please feel
 free to contact me by e-mail.