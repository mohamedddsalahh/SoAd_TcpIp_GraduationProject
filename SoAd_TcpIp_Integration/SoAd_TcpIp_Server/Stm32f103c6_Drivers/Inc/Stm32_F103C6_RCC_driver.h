/*
 * Stm32_F103C6_gpio_driver.h
 *
 *  Created on: Jul 23, 2023
 *      Author: USER
 */

#ifndef INC_STM32_F103C6_RCC_DRIVER_H_
#define INC_STM32_F103C6_RCC_DRIVER_H_

//-----------------------
//Includes
//-----------------------

#include "stm32f103x6.h"
//-----------------------
//Config Structure
//-----------------------



/*
 * ==================================================================
 * 							 General Macros
 * ==================================================================
 */

#define HSE_CLK				(uint32_t)16000000
#define HSI_RC_CLK			(uint32_t)8000000


/*
 * ==================================================================
 * 							General Functions
 * ==================================================================
 */


uint32_t MCAL_RCC_GetSYS_CLKFreq(void);

uint32_t MCAL_RCC_GetHCLKFreq(void);

uint32_t MCAL_RCC_GetPCLK1Freq(void);

uint32_t MCAL_RCC_GetPCLK2Freq(void);

/*
 * ==================================================================
 * 					APIs Supported by "MCAL RCC DRIVER"
 * ==================================================================
 */





#endif /* INC_STM32_F103C6_GPIO_DRIVER_H_ */
