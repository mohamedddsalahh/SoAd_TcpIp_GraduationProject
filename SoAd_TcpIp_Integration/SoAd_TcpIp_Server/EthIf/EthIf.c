#include "EthIf.h"
#include "TcpIp.h"
#include <stdio.h>
#include <stdlib.h>
#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_EXTI_driver.h"
#include "Stm32_F103C6_USART_driver.h"

uint8* buffer;
void EthIf_ProvideTxBuffer(uint8 dummy1, uint8 dummy2, uint8 dummy3, uint8 dummy4, uint8** BufPtr, uint16* LenBytePtr)
{
	buffer = (uint8*)calloc(TcpIpBufferMemory, sizeof(uint8));
	*BufPtr = buffer;
}

void EthIf_Transmit(uint8 dummy1, uint8 dummy2, uint8 dummy3, uint8 dummy4, uint16 LenByte, uint8 dummy5)
{
	TcpHeader* packet = (TcpHeader*)buffer;
	/*
    printf("\n\n");

    printf("Source Port: %d\n", packet->srcPort);
    printf("Destination Port: %d\n", packet->destPort);
    printf("Sequence Number: %d\n", packet->seqNum);
    printf("Ack Number: %d\n", packet->ackNum);
    printf("Header Length: %d\n", packet->headerLength);
    printf("Flags: %d\n", packet->flags);
    printf("Window Size: %d\n", packet->windowSize);
    printf("Checksum: %d\n", packet->checkSum);
    printf("Urgent Ptr: %d\n", packet->urgentPointer);

    printf("\n\n");
	 */
	for(int i = 0; i< LenByte; i++){
		uint8_t x = buffer[i];
		MCAL_USART_SendData(USART1, (buffer+i), enable);

	}
	free(buffer);
}
