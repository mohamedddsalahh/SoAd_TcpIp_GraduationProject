/*
 * PduR.h
 *
 *  Created on: Jan 3, 2024
 *      Author: USER
 */

#ifndef PDUR_H_
#define PDUR_H_

#include "ComStack_Types.h"
#include "Std_Types.h"
#include "SoAd.h"




void PduR_SoAdIfRxIndication (PduIdType RxPduId,const PduInfoType* PduInfoPtr);
void PduR_SoAdIfTxConfirmation (PduIdType TxPduId,Std_ReturnType result);
void PduR_LocalIpAddrAssignmentChg ( SoAd_SoConIdType SoConId, TcpIp_IpAddrStateType State);
void PduR_SoConModeChg (SoAd_SoConIdType SoConId, SoAd_SoConModeType Mode);

#endif /* PDUR_H_ */
