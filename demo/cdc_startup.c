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

#include "stm32.h"

static void cdc_init_rcc (void) {
#if defined(STM32L0)
    _BST(RCC->APB1ENR, RCC_APB1ENR_PWREN);
    _BMD(PWR->CR, PWR_CR_VOS, PWR_CR_VOS_0);
    _WBC(PWR->CSR, PWR_CSR_VOSF);
    /* set FLASH latency to 1 */
    _BST(FLASH->ACR, FLASH_ACR_LATENCY);
    /* set clock at 32MHz PLL 6/3 HSI */
    _BMD(RCC->CFGR, RCC_CFGR_PLLDIV | RCC_CFGR_PLLMUL | RCC_CFGR_PLLSRC, RCC_CFGR_PLLDIV3 | RCC_CFGR_PLLMUL6);
    _BST(RCC->CR, RCC_CR_HSION);
    _WBS(RCC->CR, RCC_CR_HSIRDY);
    _BST(RCC->CR, RCC_CR_PLLON);
    _WBS(RCC->CR, RCC_CR_PLLRDY);
    /* switch clock to PLL */
    _BMD(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
    _WVL(RCC->CFGR, RCC_CFGR_SWS, RCC_CFGR_SWS_PLL);

#elif defined(STM32L1)
    _BST(RCC->APB1ENR, RCC_APB1ENR_PWREN);
    _BMD(PWR->CR, PWR_CR_VOS, PWR_CR_VOS_0);
    _WBC(PWR->CSR, PWR_CSR_VOSF);
    /* set FLASH latency to 1 */
    _BST(FLASH->ACR, FLASH_ACR_ACC64);
    _BST(FLASH->ACR, FLASH_ACR_LATENCY);
    /* set clock at 32 MHz PLL 6/3 HSI */
    _BMD(RCC->CFGR, RCC_CFGR_PLLDIV | RCC_CFGR_PLLMUL | RCC_CFGR_PLLSRC, RCC_CFGR_PLLDIV3 | RCC_CFGR_PLLMUL6);
    _BST(RCC->CR, RCC_CR_HSION);
    _WBS(RCC->CR, RCC_CR_HSIRDY);
    _BST(RCC->CR, RCC_CR_PLLON);
    _WBS(RCC->CR, RCC_CR_PLLRDY);
    /* switch clock to PLL */
    _BMD(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
    _WVL(RCC->CFGR, RCC_CFGR_SWS, RCC_CFGR_SWS_PLL);

#elif defined(STM32L4)
    _BST(RCC->APB1ENR1, RCC_APB1ENR1_PWREN);
    /* Set power Range 1 */
    _BMD(PWR->CR1, PWR_CR1_VOS, PWR_CR1_VOS_0);
    _WBC(PWR->SR2, PWR_SR2_VOSF);
    /* Adjust Flash latency */
    _BMD(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_2WS);
    /* set clock 48Mhz MSI */
    _BMD(RCC->CR, RCC_CR_MSIRANGE, RCC_CR_MSIRANGE_11 | RCC_CR_MSIRGSEL);
    /* set MSI as 48MHz USB */
    _BMD(RCC->CCIPR, RCC_CCIPR_CLK48SEL, RCC_CCIPR_CLK48SEL_0 | RCC_CCIPR_CLK48SEL_1);
    /* enable GPIOA clock */
    _BST(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN);
    /* set GP11 and GP12 as USB data pins AF10 */
    _BST(GPIOA->AFR[1], (0x0A << 12) | (0x0A << 16));
    _BMD(GPIOA->MODER, (0x03 << 22) | (0x03 << 24), (0x02 << 22) | (0x02 << 24));

#elif defined(STM32F103x6)
    /* set flash latency 1WS */
    _BMD(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_1);
    /* use PLL 48MHz clock from 8Mhz HSI */
    _BMD(RCC->CFGR,
         RCC_CFGR_PLLMULL | RCC_CFGR_PLLSRC | RCC_CFGR_USBPRE,
         RCC_CFGR_PLLMULL12 | RCC_CFGR_USBPRE);
    _BST(RCC->CR, RCC_CR_PLLON);
    _WBS(RCC->CR, RCC_CR_PLLRDY);
    /* switch to PLL */
    _BMD(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
    _WVL(RCC->CFGR, RCC_CFGR_SWS, RCC_CFGR_SWS_PLL);

#elif defined(STM32F303xE)
    /* set flash latency 1WS */
    _BMD(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_1);
    /* use PLL 48MHz clock from 8Mhz HSI */
    _BMD(RCC->CFGR,
         RCC_CFGR_PLLMUL | RCC_CFGR_PLLSRC | RCC_CFGR_USBPRE ,
         RCC_CFGR_PLLMUL12 | RCC_CFGR_USBPRE);
    _BST(RCC->CR, RCC_CR_PLLON);
    _WBS(RCC->CR, RCC_CR_PLLRDY);
    /* switch to PLL */
    _BMD(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
    _WVL(RCC->CFGR, RCC_CFGR_SWS, RCC_CFGR_SWS_PLL);

#elif defined(STM32F429xx)
    /* set flash latency 2WS */
    _BMD(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY_2WS);
    /* setting up PLL 16MHz HSI, VCO=144MHz, PLLP = 72MHz PLLQ = 48MHz  */
    _BMD(RCC->PLLCFGR,
        RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLSRC | RCC_PLLCFGR_PLLQ | RCC_PLLCFGR_PLLP,
        _VAL2FLD(RCC_PLLCFGR_PLLM, 8) | _VAL2FLD(RCC_PLLCFGR_PLLN, 72) | _VAL2FLD(RCC_PLLCFGR_PLLQ, 3));
    /* enabling PLL */
    _BST(RCC->CR, RCC_CR_PLLON);
    _WBS(RCC->CR, RCC_CR_PLLRDY);
    /* switching to PLL */
    _BMD(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
    _WVL(RCC->CFGR, RCC_CFGR_SWS, RCC_CFGR_SWS_PLL);
    /* enabling GPIOA and setting PA11 and PA12 to AF10 (USB_FS) */
    _BST(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);
    _BST(GPIOA->AFR[1], (0x0A << 12) | (0x0A << 16));
    _BMD(GPIOA->MODER, (0x03 << 22) | (0x03 << 24), (0x02 << 22) | (0x02 << 24));

    _BST(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
    _BMD(GPIOC->MODER, (0x03 << 18), (0x02 << 18));
    _BMD(RCC->CFGR, RCC_CFGR_MCO2, RCC_CFGR_MCO2PRE_2);

#else
    #error Not supported
#endif
}

void __libc_init_array(void) {

}

void SystemInit(void) {
    cdc_init_rcc();
}
