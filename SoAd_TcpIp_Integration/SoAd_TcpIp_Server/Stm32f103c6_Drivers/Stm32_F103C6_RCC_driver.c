/*
 * Stm32_F103C6_gpio_driver.c
 *
 *  Created on: Jul 23, 2023
 *      Author: Mohamed Salah
 */
#include "Stm32_F103C6_RCC_driver.h"

/*
 * ==================================================================
 * 								Generic Variables
 * ==================================================================
 */

const uint8_t APBPrescTable[8] = {0, 0, 0, 0, 1, 2, 3, 4};

const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

/*
 * ==================================================================
 * 								Generic Macros
 * ==================================================================
 */


/*
 * ==================================================================
 * 							  Generic Functions
 * ==================================================================
 */


uint32_t MCAL_RCC_GetSYS_CLKFreq(void){
	switch((RCC->CFGR >> 2) & 0b11)
	{
	case 0:
		return HSI_RC_CLK;
		break;
	case 1:
		return HSE_CLK;
		break;
	case 2:
		return 16000000;
		break;
	}
}

uint32_t MCAL_RCC_GetHCLKFreq(void){

	return (MCAL_RCC_GetSYS_CLKFreq() >> AHBPrescTable[(RCC->CFGR >> 4) & 0xF]);
}

uint32_t MCAL_RCC_GetPCLK1Freq(void){

	return (MCAL_RCC_GetHCLKFreq() >> APBPrescTable[(RCC->CFGR >> 8) & 0b111]);
}

uint32_t MCAL_RCC_GetPCLK2Freq(void){

	return (MCAL_RCC_GetHCLKFreq() >> APBPrescTable[(RCC->CFGR >> 11) & 0b111]);
}



/**================================================================
 * @Fn				-MCAL_EXTI_GPIO_Init
 * @brief			-Configure EXTI Registers and NVIC Corresponding IRQ Mask
 * @param [in]		-None
 * @retval			-None
 * Note				-Stm32F103C6 MCU has GPIO A, B, C, D, E Modules
 * 							But LQFP48 Package has only GPIO A, B, Part of C, D exported as external PINS from the MCU
 */

