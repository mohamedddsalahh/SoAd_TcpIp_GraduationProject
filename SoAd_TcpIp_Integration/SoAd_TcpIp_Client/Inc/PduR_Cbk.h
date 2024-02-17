/******************************************************************************
 *
 * Module: PduR
 *
 * File Name: PduR_Cbk.h
 *
 * Description: Header file for Pdu_SoAd.
 *
 * Author: Kareem Azab / Alyeldeen Khaled
 ******************************************************************************/
#ifndef PDUR_CBK_H_
#define PDUR_CBK_H_

#include "PduR.h"




#define PduR_SoAdRxIndication_SID				(uint8)0x42
#define	PduR_SoAdTpStartOfReception_SID 		(uint8)0x46
#define PduR_SoAdTpCopyTxData_SID				(uint8)0x43
#define PduR_SoAdTpCopyRxData_SID				(uint8)0x44
#define PduR_SoAdTpTxConfirmation_SID    		(uint8)0x48


void PduR_SoAdIfRxIndication (PduIdType RxPduId,const PduInfoType* PduInfoPtr);
void PduR_SoAdIfTxConfirmation (PduIdType TxPduId,Std_ReturnType result);
void PduR_LocalIpAddrAssignmentChg ( SoAd_SoConIdType SoConId, TcpIp_IpAddrStateType State);
void PduR_SoConModeChg (SoAd_SoConIdType SoConId, SoAd_SoConModeType Mode);

#if (PduRZeroCostOperation == STD_OFF) && (PduR_SoAD_Supported == TRUE)

BufReq_ReturnType PduR_SoAdTpStartOfReception (PduIdType id,const PduInfoType* info,PduLengthType TpSduLength,PduLengthType* bufferSizePtr);
BufReq_ReturnType PduR_SoAdTpCopyTxData (PduIdType id,const PduInfoType* info,const RetryInfoType* retry,PduLengthType* availableDataPtr);
BufReq_ReturnType PduR_SoAdTpCopyRxData (PduIdType id,const PduInfoType* info,PduLengthType* bufferSizePtr);
void PduR_SoAdTpRxIndication (PduIdType id,Std_ReturnType result);
void PduR_SoAdTpTxConfirmation (PduIdType id,Std_ReturnType result);

#endif




#endif /* PDUR_CBK_H_ */
