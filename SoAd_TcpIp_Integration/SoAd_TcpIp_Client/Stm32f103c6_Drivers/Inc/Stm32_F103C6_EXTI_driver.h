/*
 * Stm32_F103C6_gpio_driver.h
 *
 *  Created on: Jul 23, 2023
 *      Author: USER
 */

#ifndef INC_STM32_F103C6_EXTI_DRIVER_H_
#define INC_STM32_F103C6_EXTI_DRIVER_H_

//-----------------------
//Includes
//-----------------------

#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"
//-----------------------
//Config Structure
//-----------------------
typedef struct{

	uint16_t		EXTI_input_LineNo;
	GPIO_TypeDef*	GPIO_Port;
	uint16_t	  	GPIO_Pin;
	uint8_t		  	IVT_IRQ_Number;

}EXTI_GPIO_Mapping_t;

typedef struct{

	EXTI_GPIO_Mapping_t EXTI_PIN;		// Specifies the External interrupt GPIO mapping
										// This parameter must be based on @ref EXTI_define

	uint8_t				Trigger_Case;	// Specifies the External interrupt Trigger Case
										// This parameter must be based on @ref EXTI_Trigger_define

	uint8_t				IRQ_EN;			// Enable or Disable EXTI IRQ (This will enable IRQ EXTI Mask and NVIC Interrupt Controller  )
										// This parameter must be based on @ref EXTI_IRQ_define

	void(*P_IRQ_CallBack)(void);		//Set the C Function() which will be called once IRQ happens

}EXTI_PinConfig_t;


//===============================
//Macros Configuration Reference
//===============================

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// @ref EXTI_define
//EXTIx
#define	EXTI0A0		(EXTI_GPIO_Mapping_t){EXTI0, GPIOA, GPIO_PIN_0, EXTI0_IRQ}
#define	EXTI0B0		(EXTI_GPIO_Mapping_t){EXTI0, GPIOB, GPIO_PIN_0, EXTI0_IRQ}
#define	EXTI0C0		(EXTI_GPIO_Mapping_t){EXTI0, GPIOC, GPIO_PIN_0, EXTI0_IRQ}
#define	EXTI0D0		(EXTI_GPIO_Mapping_t){EXTI0, GPIOD, GPIO_PIN_0, EXTI0_IRQ}

#define	EXTI1A1		(EXTI_GPIO_Mapping_t){EXTI1, GPIOA, GPIO_PIN_1, EXTI1_IRQ}
#define	EXTI1B1		(EXTI_GPIO_Mapping_t){EXTI1, GPIOB, GPIO_PIN_1, EXTI1_IRQ}
#define	EXTI1C1		(EXTI_GPIO_Mapping_t){EXTI1, GPIOC, GPIO_PIN_1, EXTI1_IRQ}
#define	EXTI1D1		(EXTI_GPIO_Mapping_t){EXTI1, GPIOD, GPIO_PIN_1, EXTI1_IRQ}

#define	EXTI2A2		(EXTI_GPIO_Mapping_t){EXTI2, GPIOA, GPIO_PIN_2, EXTI2_IRQ}
#define	EXTI2B2		(EXTI_GPIO_Mapping_t){EXTI2, GPIOB, GPIO_PIN_2, EXTI2_IRQ}
#define	EXTI2C2		(EXTI_GPIO_Mapping_t){EXTI2, GPIOC, GPIO_PIN_2, EXTI2_IRQ}
#define	EXTI2D2		(EXTI_GPIO_Mapping_t){EXTI2, GPIOD, GPIO_PIN_2, EXTI2_IRQ}

#define	EXTI3A3		(EXTI_GPIO_Mapping_t){EXTI3, GPIOA, GPIO_PIN_3, EXTI3_IRQ}
#define	EXTI3B3		(EXTI_GPIO_Mapping_t){EXTI3, GPIOB, GPIO_PIN_3, EXTI3_IRQ}
#define	EXTI3C3		(EXTI_GPIO_Mapping_t){EXTI3, GPIOC, GPIO_PIN_3, EXTI3_IRQ}
#define	EXTI3D3		(EXTI_GPIO_Mapping_t){EXTI3, GPIOD, GPIO_PIN_3, EXTI3_IRQ}

#define	EXTI4A4		(EXTI_GPIO_Mapping_t){EXTI4, GPIOA, GPIO_PIN_4, EXTI4_IRQ}
#define	EXTI4B4		(EXTI_GPIO_Mapping_t){EXTI4, GPIOB, GPIO_PIN_4, EXTI4_IRQ}
#define	EXTI4C4		(EXTI_GPIO_Mapping_t){EXTI4, GPIOC, GPIO_PIN_4, EXTI4_IRQ}
#define	EXTI4D4		(EXTI_GPIO_Mapping_t){EXTI4, GPIOD, GPIO_PIN_4, EXTI4_IRQ}

#define	EXTI5A5		(EXTI_GPIO_Mapping_t){EXTI5, GPIOA, GPIO_PIN_5, EXTI5_IRQ}
#define	EXTI5B5		(EXTI_GPIO_Mapping_t){EXTI5, GPIOB, GPIO_PIN_5, EXTI5_IRQ}
#define	EXTI5C5		(EXTI_GPIO_Mapping_t){EXTI5, GPIOC, GPIO_PIN_5, EXTI5_IRQ}
#define	EXTI5D5		(EXTI_GPIO_Mapping_t){EXTI5, GPIOD, GPIO_PIN_5, EXTI5_IRQ}

#define	EXTI6A6		(EXTI_GPIO_Mapping_t){EXTI6, GPIOA, GPIO_PIN_6, EXTI6_IRQ}
#define	EXTI6B6		(EXTI_GPIO_Mapping_t){EXTI6, GPIOB, GPIO_PIN_6, EXTI6_IRQ}
#define	EXTI6C6		(EXTI_GPIO_Mapping_t){EXTI6, GPIOC, GPIO_PIN_6, EXTI6_IRQ}
#define	EXTI6D6		(EXTI_GPIO_Mapping_t){EXTI6, GPIOD, GPIO_PIN_6, EXTI6_IRQ}

#define	EXTI7A7		(EXTI_GPIO_Mapping_t){EXTI7, GPIOA, GPIO_PIN_7, EXTI7_IRQ}
#define	EXTI7B7		(EXTI_GPIO_Mapping_t){EXTI7, GPIOB, GPIO_PIN_7, EXTI7_IRQ}
#define	EXTI7C7		(EXTI_GPIO_Mapping_t){EXTI7, GPIOC, GPIO_PIN_7, EXTI7_IRQ}
#define	EXTI7D7		(EXTI_GPIO_Mapping_t)({EXTI7, GPIOD, GPIO_PIN_7, EXTI7_IRQ}

#define	EXTI8A8		(EXTI_GPIO_Mapping_t){EXTI8, GPIOA, GPIO_PIN_8, EXTI8_IRQ}
#define	EXTI8B8		(EXTI_GPIO_Mapping_t){EXTI8, GPIOB, GPIO_PIN_8, EXTI8_IRQ}
#define	EXTI8C8		(EXTI_GPIO_Mapping_t){EXTI8, GPIOC, GPIO_PIN_8, EXTI8_IRQ}
#define	EXTI8D8		(EXTI_GPIO_Mapping_t){EXTI8, GPIOD, GPIO_PIN_8, EXTI8_IRQ}

#define	EXTI9A9		(EXTI_GPIO_Mapping_t){EXTI9, GPIOA, GPIO_PIN_9, EXTI9_IRQ}
#define	EXTI9B9		(EXTI_GPIO_Mapping_t){EXTI9, GPIOB, GPIO_PIN_9, EXTI9_IRQ}
#define	EXTI9C9		(EXTI_GPIO_Mapping_t){EXTI9, GPIOC, GPIO_PIN_9, EXTI9_IRQ}
#define	EXTI9D9		(EXTI_GPIO_Mapping_t){EXTI9, GPIOD, GPIO_PIN_9, EXTI9_IRQ}

#define	EXTI10A10		(EXTI_GPIO_Mapping_t){EXTI10, GPIOA, GPIO_PIN_10, EXTI10_IRQ}
#define	EXTI10B10		(EXTI_GPIO_Mapping_t){EXTI10, GPIOB, GPIO_PIN_10, EXTI10_IRQ}
#define	EXTI10C10		(EXTI_GPIO_Mapping_t){EXTI10, GPIOC, GPIO_PIN_10, EXTI10_IRQ}
#define	EXTI10D10		(EXTI_GPIO_Mapping_t){EXTI10, GPIOD, GPIO_PIN_10, EXTI10_IRQ}

#define	EXTI11A11		(EXTI_GPIO_Mapping_t){EXTI11, GPIOA, GPIO_PIN_11, EXTI11_IRQ}
#define	EXTI11B11		(EXTI_GPIO_Mapping_t){EXTI11, GPIOB, GPIO_PIN_11, EXTI11_IRQ}
#define	EXTI11C11		(EXTI_GPIO_Mapping_t){EXTI11, GPIOC, GPIO_PIN_11, EXTI11_IRQ}
#define	EXTI11D11		(EXTI_GPIO_Mapping_t){EXTI11, GPIOD, GPIO_PIN_11, EXTI11_IRQ}

#define	EXTI12A12		(EXTI_GPIO_Mapping_t){EXTI12, GPIOA, GPIO_PIN_12, EXTI12_IRQ}
#define	EXTI12B12		(EXTI_GPIO_Mapping_t){EXTI12, GPIOB, GPIO_PIN_12, EXTI12_IRQ}
#define	EXTI12C12		(EXTI_GPIO_Mapping_t){EXTI12, GPIOC, GPIO_PIN_12, EXTI12_IRQ}
#define	EXTI12D12		(EXTI_GPIO_Mapping_t){EXTI12, GPIOD, GPIO_PIN_12, EXTI12_IRQ}

#define	EXTI13A13		(EXTI_GPIO_Mapping_t){EXTI13, GPIOA, GPIO_PIN_13, EXTI13_IRQ}
#define	EXTI13B13		(EXTI_GPIO_Mapping_t){EXTI13, GPIOB, GPIO_PIN_13, EXTI13_IRQ}
#define	EXTI13C13		(EXTI_GPIO_Mapping_t){EXTI13, GPIOC, GPIO_PIN_13, EXTI13_IRQ}
#define	EXTI13D13		(EXTI_GPIO_Mapping_t){EXTI13, GPIOD, GPIO_PIN_13, EXTI13_IRQ}

#define	EXTI14A14		(EXTI_GPIO_Mapping_t){EXTI14, GPIOA, GPIO_PIN_14, EXTI14_IRQ}
#define	EXTI14B14		(EXTI_GPIO_Mapping_t){EXTI14, GPIOB, GPIO_PIN_14, EXTI14_IRQ}
#define	EXTI14C14		(EXTI_GPIO_Mapping_t){EXTI14, GPIOC, GPIO_PIN_14, EXTI14_IRQ}
#define	EXTI14D14		(EXTI_GPIO_Mapping_t){EXTI14, GPIOD, GPIO_PIN_14, EXTI14_IRQ}

#define	EXTI15A15		(EXTI_GPIO_Mapping_t){EXTI15, GPIOA, GPIO_PIN_15, EXTI15_IRQ}
#define	EXTI15B15		(EXTI_GPIO_Mapping_t){EXTI15, GPIOB, GPIO_PIN_15, EXTI15_IRQ}
#define	EXTI15C15		(EXTI_GPIO_Mapping_t){EXTI15, GPIOC, GPIO_PIN_15, EXTI15_IRQ}
#define	EXTI15D15		(EXTI_GPIO_Mapping_t){EXTI15, GPIOD, GPIO_PIN_15, EXTI15_IRQ}


#define	EXTI0				0
#define	EXTI1				1
#define	EXTI2				2
#define	EXTI3				3
#define	EXTI4				4
#define	EXTI5				5
#define	EXTI6				6
#define	EXTI7				7
#define	EXTI8				8
#define	EXTI9				9
#define	EXTI10				10
#define	EXTI11				11
#define	EXTI12				12
#define	EXTI13				13
#define	EXTI14				14
#define	EXTI15				15


//---------------------------------------
//@ref EXTI_Trigger_define

#define EXTI_Trigger_RISING				0
#define EXTI_Trigger_FALLING			1
#define EXTI_Trigger_RISING_FALLING		2

//---------------------------------------
//@ref EXTI_IRQ_define
#define EXTI_IRQ_Enable					1
#define EXTI_IRQ_Disable				0




/*
 * ==================================================================
 * 					APIs Supported by "MCAL GPIO DRIVER"
 * ==================================================================
 */

void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t* EXTI_Config);

void MCAL_EXTI_GPIO_DeInit(void);

void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t* EXTI_Config);


#endif /* INC_STM32_F103C6_GPIO_DRIVER_H_ */
