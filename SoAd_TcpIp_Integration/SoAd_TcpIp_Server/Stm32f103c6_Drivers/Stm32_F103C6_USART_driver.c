/*
 * Stm32_F103C6_gpio_driver.c
 *
 *  Created on: Jul 23, 2023
 *      Author: Mohamed Salah
 */
#include "Stm32_F103C6_USART_driver.h"

/*
 * ==================================================================
 * 								Generic Variables
 * ==================================================================
 */

USART_Config* Global_USART_Config = NULL;

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



/**================================================================
 * @Fn				-MCAL_USART_Init
 * @brief			-Configure USART Registers and NVIC Corresponding IRQ Mask if IRQ is Enabled
 * @param [in]		-
 * @retval			-
 * Note				-
 */

void MCAL_USART_Init(USART_TypeDef* USARTx, USART_Config* USART_Config){

	uint32_t pclk, BRR;
	uint32_t USARTDIV, USARTDIV_MUL100, USARTDIV_Integer_MUL100, USARTDIV_Fraction;

	Global_USART_Config = USART_Config;

	//Enable Clk for the given USART Peripheral
	if(USARTx == USART1){
		RCC_USART1_CLK_EN();
	}
	else if(USARTx == USART2){
		RCC_USART2_CLK_EN();
	}
	else if(USARTx == USART3){
		RCC_USART3_CLK_EN();
	}

	//Enable USART Module
	USARTx->CR1 |= (1<<13);	// Enable UE Bit

	//Enable TX/RX
	USARTx->CR1 |= USART_Config->USART_Mode;

	//Payload Width (Data Width)
	USARTx->CR1 |= USART_Config->PayLoad_Length;

	//Configure Parity Control Bit Fields
	USARTx->CR1 |= USART_Config->Parity;

	//Configure Number of Stop Bits
	USARTx->CR2 |= USART_Config->Stop_Bits;

	//USART Flow Control
	USARTx->CR3 |= USART_Config->HwFlowCtl;

	//Configure BaudRate of BRR
	//PCLK1 for USART2, 3
	//PCLK2 for USART1
	if (USARTx == USART1){
		pclk = MCAL_RCC_GetPCLK2Freq();
	}
	else{
		pclk = MCAL_RCC_GetPCLK1Freq();
	}
//	USARTDIV = (uint32_t)((pclk) / (16*(USART_Config->BaudRate))); //Integer Part
//	USARTDIV_MUL100 = (uint32_t)(pclk*25) / (4*(USART_Config->BaudRate));
//	USARTDIV_Integer_MUL100 = (uint32_t)(USARTDIV*100);
//	USARTDIV_Fraction = (uint32_t)((USARTDIV_MUL100 - USARTDIV_Integer_MUL100)*16)/100; //Fraction Part
//
//	USARTx->BRR = ((USARTDIV << 4) | (USARTDIV_Fraction & 0xF));

	BRR = UART_BRR_Register(pclk, USART_Config->BaudRate) ;

	USARTx->BRR = BRR ;

	//Enable/Disable Interrupt
	//USART_CR1
	if(USART_Config->IRQ_Enable != USART_IRQ_Enable_NONE ){

		USARTx->CR1 |= USART_Config->IRQ_Enable;

		//Enable NVIC for USART IRQ
		if(USARTx == USART1){
			NVIC_IRQ37_USART1_Enable;
		}
		else if(USARTx == USART2){
			NVIC_IRQ38_USART2_Enable;
		}
		else if(USARTx == USART3){
			NVIC_IRQ39_USART3_Enable;
		}
	}

}

void MCAL_USART_DeInit(USART_TypeDef* USARTx){

	if (USARTx == USART1){

		RCC_USART1_CLK_Reset();
		NVIC_IRQ37_USART1_Disable;
	}
	else if (USARTx == USART2){

		RCC_USART2_CLK_Reset();
		NVIC_IRQ38_USART2_Disable;
	}
	else if (USARTx == USART3){

		RCC_USART3_CLK_Reset();
		NVIC_IRQ39_USART3_Disable;
	}
}

void MCAL_USART_GPIO_Set_Pins(USART_TypeDef* USARTx){

	GPIO_PinConfig_t	PinConfig;

	if (USARTx == USART1){
		//PA9	TX
		//PA10	RX
		//PA11	CTS
		//PA12	RTS
		//if(Global_USART_Config->USART_Mode == USART_MODE_TX || Global_USART_Config->USART_Mode == USART_MODE_TX_RX ){
			PinConfig.GPIO_PinNumber = GPIO_PIN_9;
			PinConfig.GPIO_MODE = GPIO_MODE_AFIO_OUTPUT_PP;
			PinConfig.GPIO_Output_Speed= GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinConfig);
		//}
		//if(Global_USART_Config->USART_Mode == USART_MODE_RX || Global_USART_Config->USART_Mode == USART_MODE_TX_RX ){
			PinConfig.GPIO_PinNumber = GPIO_PIN_10;
			PinConfig.GPIO_MODE = GPIO_MODE_AFIO_INPUT;
			MCAL_GPIO_Init(GPIOA, &PinConfig);
		//}
		if(Global_USART_Config->HwFlowCtl == USART_HwFlowCtl_CTS || Global_USART_Config->HwFlowCtl == USART_HwFlowCtl_RTS_CTS){
			PinConfig.GPIO_PinNumber = GPIO_PIN_11;
			PinConfig.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinConfig);
		}
		if(Global_USART_Config->HwFlowCtl == USART_HwFlowCtl_RTS || Global_USART_Config->HwFlowCtl == USART_HwFlowCtl_RTS_CTS){
			PinConfig.GPIO_PinNumber = GPIO_PIN_12;
			PinConfig.GPIO_MODE = GPIO_MODE_AFIO_OUTPUT_PP;
			PinConfig.GPIO_Output_Speed= GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinConfig);
		}
	}
	else if (USARTx == USART2){

	}
	else if (USARTx == USART3){

	}

}


void MCAL_USART_SendData(USART_TypeDef* USARTx, uint16_t* pTxBuffer, enum Polling_Mechanism	PollingEn){

	//Wait TXE Flag is Set
	if (PollingEn == enable){
		while(! (USARTx->SR & 1<<7) );
	}

	//Check Word Length for 9Bit or 8Bit in a frame
	if (Global_USART_Config->PayLoad_Length == USART_PayLoad_Length_9B){

		USARTx->DR = (*pTxBuffer & (uint16_t)0x01FF);

	}else{

		USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);

	}
}


void MCAL_USART_RecieveData(USART_TypeDef* USARTx, uint16_t* pRxBuffer, enum Polling_Mechanism	PollingEn){

	//Wait until RXNE Flag is set
	if(PollingEn == enable)
	{
		while(! (USARTx->SR & 1<<5) );
	}

	//Check Word Length
	if (Global_USART_Config->PayLoad_Length == USART_PayLoad_Length_9B){

		if(Global_USART_Config->Parity == USART_Parity_NONE){

			// If no Parity all bits are considered
			*((uint16_t*)pRxBuffer) = USARTx->DR;

		}else{

			//If Parity is enabled, only 8 bits are considered
			*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);

		}
	}else{

		if(Global_USART_Config->Parity == USART_Parity_NONE){

			// If no Parity all bits are considered
			*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);

		}else{

			//If Parity is enabled, only 7 bits are considered
			*((uint16_t*)pRxBuffer) = (USARTx->DR & (uint8_t)0x7F);

		}
	}
}



void MCAL_USART_WAIT_TC(USART_TypeDef* USARTx){

	while(! (USARTx->SR & 1<<6) );

}

// USART ISR Handler

void USART1_IRQHandler(void){

	Global_USART_Config->P_IRQ_CallBack();

}

void USART2_IRQHandler(void){

	Global_USART_Config->P_IRQ_CallBack();

}

void USART3_IRQHandler(void){

	Global_USART_Config->P_IRQ_CallBack();

}




