/*
 * Stm32_F103C6_gpio_driver.c
 *
 *  Created on: Jul 23, 2023
 *      Author: Mohamed Salah
 */
#include "Stm32_F103C6_gpio_driver.h"

uint8_t Get_CRLH_Position(uint16_t PinNumber){

	switch(PinNumber){
	case GPIO_PIN_0:
		return 0;
		break;
	case GPIO_PIN_1:
		return 4;
		break;
	case GPIO_PIN_2:
		return 8;
		break;
	case GPIO_PIN_3:
		return 12;
		break;
	case GPIO_PIN_4:
		return 16;
		break;
	case GPIO_PIN_5:
		return 20;
		break;
	case GPIO_PIN_6:
		return 24;
		break;
	case GPIO_PIN_7:
		return 28;
		break;
	case GPIO_PIN_8:
		return 0;
		break;
	case GPIO_PIN_9:
		return 4;
		break;
	case GPIO_PIN_10:
		return 8;
		break;
	case GPIO_PIN_11:
		return 12;
		break;
	case GPIO_PIN_12:
		return 16;
		break;
	case GPIO_PIN_13:
		return 20;
		break;
	case GPIO_PIN_14:
		return 24;
		break;
	case GPIO_PIN_15:
		return 28;
		break;
	}
	return 0;
}

/**================================================================
 * @Fn				-MCAL_GPIO_Init
 * @brief			-Initializes the GPIOx PINy according to the specified parameters in PinConfig
 * @param [in]		-GPIOx: where x can be (A .. E depending on device used) to select the GPIO Peripheral
 * @param [in]		-PinConfig pointer to a GPIO_PinConfig_t structure that contains
 * 							the configuration information for the specified PIN
 * @retval			-None
 * Note				-Stm32F103C6 MCU has GPIO A, B, C, D, E Modules
 * 							But LQFP48 Package has only GPIO A, B, Part of C, D exported as external PINS from the MCU
 */
void MCAL_GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_PinConfig_t* PinConfig){

	volatile uint32_t* configregister = NULL;
	uint8_t Pin_config = 0;
	configregister = (PinConfig->GPIO_PinNumber < GPIO_PIN_8)?	&GPIOx->CRL:&GPIOx->CRH;
	(*configregister) &= ~(0xf << Get_CRLH_Position(PinConfig->GPIO_PinNumber));


	// If Pin is Output
	if ((PinConfig->GPIO_MODE) == GPIO_MODE_AFIO_OUTPUT_PP || (PinConfig->GPIO_MODE) == GPIO_MODE_AFIO_OUTPUT_OD || (PinConfig->GPIO_MODE) == GPIO_MODE_OUTPUT_OD || (PinConfig->GPIO_MODE) == GPIO_MODE_OUTPUT_PP){

		Pin_config = ( ( ( (PinConfig->GPIO_MODE - 4) << 2) | PinConfig->GPIO_Output_Speed) & 0x0f);
		(*configregister) |= ( (Pin_config) << Get_CRLH_Position(PinConfig->GPIO_PinNumber));
	}
	// if pin is input
	else{
		if ((PinConfig->GPIO_MODE) == GPIO_MODE_Analog || (PinConfig->GPIO_MODE) == GPIO_MODE_INPUT_FLO  ){
			Pin_config = ( ( ( (PinConfig->GPIO_MODE) << 2) | 0x0) & 0x0f);


			(*configregister) |= ((Pin_config) << (Get_CRLH_Position(PinConfig->GPIO_PinNumber)));
		}
		else if((PinConfig->GPIO_MODE) == GPIO_MODE_AFIO_INPUT)
		{
			Pin_config = (((GPIO_MODE_INPUT_FLO << 2) | 0x0) & 0x0f);
			(*configregister) |= ((Pin_config) << (Get_CRLH_Position(PinConfig->GPIO_PinNumber)));
		}
		else{	// PU PD Input
			Pin_config = ( ( (GPIO_MODE_INPUT_PU << 2) | 0x0) & 0x0f);
			(*configregister) |= ( (Pin_config) << (Get_CRLH_Position(PinConfig->GPIO_PinNumber) ) );

			if ((PinConfig->GPIO_MODE) == GPIO_MODE_INPUT_PU){

				(GPIOx->ODR) |= (PinConfig->GPIO_PinNumber);
			}else
			{
				(GPIOx->ODR) &= ~(PinConfig->GPIO_PinNumber);
			}
		}
	}
}

/**================================================================
 * @Fn				-MCAL_GPIO_DeInit
 * @brief			-Resets all GPIOx registers
 * @param [in]		-GPIOx: where x can be (A .. E depending on device used) to select the GPIO Peripheral
 * @retval			-None
 * Note				-None
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef* GPIOx){

	if (GPIOx == GPIOA){
		RCC->APB2RSTR |= (1<<2);
		RCC->APB2RSTR &= ~(1<<2);
	}
	else if(GPIOx == GPIOB){
		RCC->APB2RSTR |= (1<<3);
		RCC->APB2RSTR &= ~(1<<3);

	}else if(GPIOx == GPIOC){
		RCC->APB2RSTR |= (1<<4);
		RCC->APB2RSTR &= ~(1<<4);

	}else if(GPIOx == GPIOD){
		RCC->APB2RSTR |= (1<<5);
		RCC->APB2RSTR &= ~(1<<5);

	}else if(GPIOx == GPIOE){
		RCC->APB2RSTR |= (1<<6);
		RCC->APB2RSTR &= ~(1<<6);
	}
}

/**================================================================
 * @Fn				-MCAL_GPIO_ReadPin
 * @brief			-Read specific Pin
 * @param [in]		-GPIOx: where x can be (A .. E depending on device used) to select the GPIO Peripheral
 * @param [in]		-PinNumber: Set Pin Number according to @ref GPIO_PINS_define
 * @retval			-The input pin value (two values based on @ref GPIO_PIN_STATE)
 * Note				-None
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t PinNumber){

	uint8_t bitStatus;
	if ( ( (GPIOx->IDR) & PinNumber) != (uint32_t)GPIO_PIN_IS_RESET ){
		bitStatus = GPIO_PIN_IS_SET;
	}else{
		bitStatus = GPIO_PIN_IS_RESET;
	}
	return bitStatus;
}

/**================================================================
 * @Fn				-MCAL_GPIO_WritePin
 * @brief			-Write the desired value on a specific Pin
 * @param [in]		-GPIOx: where x can be (A .. E depending on device used) to select the GPIO Peripheral
 * @param [in]		-PinNumber: Set Pin Number according to @ref GPIO_PINS_define
 * @param [in]		-Value: 0 or 1
 * @retval			-None
 * Note				-None
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t PinNumber, uint8_t Value){

	if(Value != GPIO_PIN_IS_RESET){
		GPIOx->ODR |= PinNumber;
	}
	else{
		GPIOx->ODR &= ~PinNumber;
	}
}

uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef* GPIOx){
	uint16_t portVal;
	portVal = (uint16_t)(GPIOx->IDR);
	return portVal;
}

void MCAL_GPIO_WritePort(GPIO_TypeDef* GPIOx, uint16_t Value){
	GPIOx->ODR = (uint32_t)Value;
}

void MCAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t PinNumber){
	(GPIOx->ODR) ^= (PinNumber);
}
