/*
 * Stm32_F103C6_gpio_driver.h
 *
 *  Created on: Jul 23, 2023
 *      Author: USER
 */

#ifndef INC_STM32_F103C6_GPIO_DRIVER_H_
#define INC_STM32_F103C6_GPIO_DRIVER_H_

//-----------------------
//Includes
//-----------------------

#include "stm32f103x6.h"

//-----------------------
//Config Structure
//-----------------------

typedef struct{
	uint16_t GPIO_PinNumber;	//Specifies the GPIO pins to be configured
	//This parameter can be a value of @ref GPIO_PINS_define

	uint8_t GPIO_MODE;			//Specifies the operating mode for the selected GPIO pins
	//This parameter can be a value of @ref GPIO_MODE_define

	uint8_t GPIO_Output_Speed;	//Specifies the speed for the selected GPIO pins
	//This parameter can be a value of @ref GPIO_SPEED_define
}GPIO_PinConfig_t;

//===============================
//Macros Configuration Reference
//===============================

// @ref GPIO_PORTS_define
#define PORTA_ID				((uint8_t)0x00)
#define PORTB_ID				((uint8_t)0x01)
#define PORTC_ID				((uint8_t)0x02)
#define PORTD_ID				((uint8_t)0x03)
#define PORTE_ID				((uint8_t)0x04)


// @ref GPIO_PINS_define
#define GPIO_PIN_0				((uint16_t)0x0001) /* Pin 0 selected */
#define GPIO_PIN_1				((uint16_t)0x0002) /* Pin 1 selected */
#define GPIO_PIN_2				((uint16_t)0x0004) /* Pin 2 selected */
#define GPIO_PIN_3				((uint16_t)0x0008) /* Pin 3 selected */
#define GPIO_PIN_4				((uint16_t)0x0010) /* Pin 4 selected */
#define GPIO_PIN_5				((uint16_t)0x0020) /* Pin 5 selected */
#define GPIO_PIN_6				((uint16_t)0x0040) /* Pin 6 selected */
#define GPIO_PIN_7				((uint16_t)0x0080) /* Pin 7 selected */
#define GPIO_PIN_8				((uint16_t)0x0100) /* Pin 8 selected */
#define GPIO_PIN_9				((uint16_t)0x0200) /* Pin 9 selected */
#define GPIO_PIN_10				((uint16_t)0x0400) /* Pin 10 selected */
#define GPIO_PIN_11				((uint16_t)0x0800) /* Pin 11 selected */
#define GPIO_PIN_12				((uint16_t)0x1000) /* Pin 12 selected */
#define GPIO_PIN_13				((uint16_t)0x2000) /* Pin 13 selected */
#define GPIO_PIN_14				((uint16_t)0x4000) /* Pin 14 selected */
#define GPIO_PIN_15				((uint16_t)0x8000) /* Pin 15 selected */

#define GPIO_ALL_PINS			((uint16_t)0xFFFF) /* All Pins selected */


// @ref GPIO_MODE_define
#define GPIO_MODE_Analog				0x00u
#define GPIO_MODE_INPUT_FLO				0x01u
#define GPIO_MODE_INPUT_PU				0x02u
#define GPIO_MODE_INPUT_PD				0x03u
#define GPIO_MODE_OUTPUT_PP				0x04u
#define GPIO_MODE_OUTPUT_OD				0x05u
#define GPIO_MODE_AFIO_OUTPUT_PP		0x06u
#define GPIO_MODE_AFIO_OUTPUT_OD		0x07u
#define GPIO_MODE_AFIO_INPUT			0x08u


// @ref GPIO_SPEED_define
#define GPIO_SPEED_10M					0x01u
#define GPIO_SPEED_2M					0x02u
#define GPIO_SPEED_50M					0x03u

// @ref GPIO_PIN_STATE
#define GPIO_PIN_IS_SET					0x01u
#define GPIO_PIN_IS_RESET				0x00u


/*
 * ==================================================================
 * 					APIs Supported by "MCAL GPIO DRIVER"
 * ==================================================================
 */


void MCAL_GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_PinConfig_t* PinConfig);

void MCAL_GPIO_DeInit(GPIO_TypeDef* GPIOx);

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t PinNumber);

void MCAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t PinNumber, uint8_t Value);

uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef* GPIOx);

void MCAL_GPIO_WritePort(GPIO_TypeDef* GPIOx, uint16_t Value);

void MCAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t PinNumber);


#endif /* INC_STM32_F103C6_GPIO_DRIVER_H_ */
