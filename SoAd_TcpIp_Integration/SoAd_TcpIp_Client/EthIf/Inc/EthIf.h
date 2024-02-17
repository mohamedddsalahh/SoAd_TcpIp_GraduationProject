#ifndef ETHIF_H_
#define ETHIF_H_

#include "Std_Types.h"

typedef uint8 Eth_FrameType;

void EthIf_ProvideTxBuffer(uint8 dummy1, uint8 dummy2, uint8 dummy3, uint8 dummy4, uint8** BufPtr, uint16* LenBytePtr);
void EthIf_Transmit(uint8 dummy1, uint8 dummy2, uint8 dummy3, uint8 dummy4, uint16 LenByte, uint8 dummy5);

#endif