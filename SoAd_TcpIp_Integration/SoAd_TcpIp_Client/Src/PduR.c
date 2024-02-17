/*
 * PduR.c
 *
 *  Created on: Feb 15, 2024
 *      Author: USER
 */


#include "PduR.h"

#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_EXTI_driver.h"
#include "Stm32_F103C6_USART_driver.h"

void PduR_SoAdIfRxIndication (PduIdType RxPduId,const PduInfoType* PduInfoPtr){


}

void PduR_SoAdIfTxConfirmation (PduIdType TxPduId,Std_ReturnType result){

}

void PduR_LocalIpAddrAssignmentChg ( SoAd_SoConIdType SoConId, TcpIp_IpAddrStateType State){


}
void PduR_SoConModeChg (SoAd_SoConIdType SoConId, SoAd_SoConModeType Mode){

	 MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_IS_SET);

}

