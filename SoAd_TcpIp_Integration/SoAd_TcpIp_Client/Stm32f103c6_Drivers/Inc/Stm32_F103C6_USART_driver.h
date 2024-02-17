/*
 * Stm32_F103C6_gpio_driver.h
 *
 *  Created on: Jul 23, 2023
 *      Author: USER
 */

#ifndef INC_STM32_F103C6_USART_DRIVER_H_
#define INC_STM32_F103C6_USART_DRIVER_H_

//-----------------------
//Includes
//-----------------------

#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_RCC_driver.h"

//-----------------------
//Config Structure
//-----------------------
typedef struct{

	uint8_t		  	USART_Mode;	//Specifies TX/RX Enable/Disable
	//This parameter must be set based on @ref USART_Mode_define

	uint32_t		BaudRate;	//Specifies BaudRate
	//	This parameter must be set based on @ref USART_BaudRate_define

	uint8_t 		PayLoad_Length;//Specifies Data
	//	This parameter must be set based on @ref USART_PayLoad_Length_define


	uint8_t			Parity;//Specifies Parity Type EVEN/ODD
	//	This parameter must be set based on @ref USART_Parity_define


	uint8_t			Stop_Bits;//Specifies Number of Stop Bits
	//	This parameter must be set based on @ref_Stop_Bits_define


	uint8_t			HwFlowCtl;//Specifies Hardware Flow Control State
	//	This parameter must be set based on @ref_HwFlowCtl_define


	uint8_t			IRQ_Enable;//Specifies Interrupt State
	//	This parameter must be set based on @ref_Interrupt_define


	void(*P_IRQ_CallBack)(void);	//Set the Call Back Function which is called when IRQ happens

}USART_Config;


//===============================
//Macros Configuration Reference
//===============================

//@ref USART Mode define

#define USART_MODE_RX		(uint32_t)(1<<2)
#define USART_MODE_TX		(uint32_t)(1<<3)
#define USART_MODE_TX_RX	((uint32_t)(1<<2 | 1<<3))

//@ref USART_BaudRate_define

#define USART_BaudRate_2400			2400
#define USART_BaudRate_9600			9600
#define USART_BaudRate_19200		19200
#define USART_BaudRate_57600		57600
#define USART_BaudRate_115200		115200
#define USART_BaudRate_230400		230400
#define USART_BaudRate_460800		460800
#define USART_BaudRate_921600		921600
#define USART_BaudRate_2250000		2250000
#define USART_BaudRate_4500000		4500000

//@ref USART_PayLoad_Length_define
#define USART_PayLoad_Length_8B		(uint32_t)(0)
#define USART_PayLoad_Length_9B		(uint32_t)(1<<12)


//@ref USART_Parity_define
#define USART_Parity_NONE			(uint32_t)(0)
#define USART_Parity_EVEN			(uint32_t)(1<<10)
#define USART_Parity_ODD			((uint32_t)(1<<10 | 1<<9))


//@ref_Stop_Bits_define
#define USART_StopBits_half			(uint32_t)(1<<12)
#define USART_StopBits_1			(uint32_t)(0)
#define USART_StopBits_1_half		(uint32_t)(3<<12)
#define USART_StopBits_2			(uint32_t)(2<<12)


//@ref_HwFlowCtl_define
#define USART_HwFlowCtl_None		(uint32_t)(0)
#define USART_HwFlowCtl_RTS			(uint32_t)(1<<8)
#define USART_HwFlowCtl_CTS			(uint32_t)(1<<9)
#define USART_HwFlowCtl_RTS_CTS		((uint32_t)(1<<8 | 1<<9))


//@ref_Interrupt_define
#define USART_IRQ_Enable_NONE		(uint32_t)(0)
#define USART_IRQ_Enable_TXE		(uint32_t)(1<<7)
#define USART_IRQ_Enable_TC			(uint32_t)(1<<6)
#define USART_IRQ_Enable_RXEINE		(uint32_t)(1<<5)
#define USART_IRQ_Enable_PE			(uint32_t)(1<<8)


#define USARTDIV(_PCLK_, _BAUD_)							(uint32_t) (_PCLK_/(16 * _BAUD_ ))
#define USARTDIV_MUL100(_PCLK_, _BAUD_)						(uint32_t) ( (25 * _PCLK_ ) / (4  * _BAUD_ ))
#define Mantissa_MUL100(_PCLK_, _BAUD_)						(uint32_t) (USARTDIV(_PCLK_, _BAUD_) * 100)
#define Mantissa(_PCLK_, _BAUD_)							(uint32_t) (USARTDIV(_PCLK_, _BAUD_) )
#define DIV_Fraction(_PCLK_, _BAUD_)						(uint32_t) (((USARTDIV_MUL100(_PCLK_, _BAUD_) -  Mantissa_MUL100(_PCLK_, _BAUD_) ) * 16 ) / 100 )
#define UART_BRR_Register(_PCLK_, _BAUD_)					(( Mantissa (_PCLK_, _BAUD_) ) <<4 )|( (DIV_Fraction(_PCLK_, _BAUD_)) & 0xF )






enum Polling_Mechanism{
	enable,
	disable
};


/*
 * ==================================================================
 * 					APIs Supported by "MCAL GPIO DRIVER"
 * ==================================================================
 */

void MCAL_USART_Init(USART_TypeDef* USARTx, USART_Config* USART_Config);

void MCAL_USART_DeInit(USART_TypeDef* USARTx);

void MCAL_USART_GPIO_Set_Pins(USART_TypeDef* USARTx);

void MCAL_USART_SendData(USART_TypeDef* USARTx, uint16_t* pTxBuffer, enum Polling_Mechanism	PollingEn);
void MCAL_USART_RecieveData(USART_TypeDef* USARTx, uint16_t* pRxBuffer, enum Polling_Mechanism	PollingEn);

void MCAL_USART_WAIT_TC(USART_TypeDef* USARTx);



#endif /* INC_STM32_F103C6_USART_DRIVER_H_ */
