#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H


/***************************************************************************************************
**                                          Includes                                             **
***************************************************************************************************/
#include "Std_Types.h"

/***************************************************************************************************
**                                        Types Declarations                                     **
***************************************************************************************************/

/**************************************************************************************************
**
Name:                                    PduIdType
Type:                                     uint8, uint16
Description:
                     Variables of this type serve as a unique identifier of a
					PDU within a software module or a set thereof, and also for interaction of two
					software modules where the PduId of the corresponding target module is being used
					for referencing.
																				                **
**************************************************************************************************/
typedef	uint8  PduIdType;

/**************************************************************************************************
**
Name:                                    PduLengthType
Type:                                     uint8, uint16, uint32
Description:
                    Variables of this type serve as length information of a PDU. The
					length information is provided in number of bytes.
					                                                                                                                   **
**************************************************************************************************/
typedef	uint8  PduLengthType;

/**************************************************************************************************
**
Name:                                     PduInfoType
Type:                                      Structure
Description:
                     Variables of this type shall be used to store the basic information about a PDU of
					any type, namely a pointer variable pointing to its SDU (payload), and the
					corresponding length of the SDU in bytes.
																																				**
**************************************************************************************************/
typedef struct {
	PduLengthType                     SduLength;
	uint8*                            SduDataPtr;
}PduInfoType;

/**************************************************************************************************
**
Name:                                     BufReq_ReturnType
Type:                                      Enumeration
Description:
                    Variables of this type shall be used to store the result of a buffer request.
																																				**
**************************************************************************************************/


typedef enum {
	BUFREQ_OK,
	BUFREQ_E_NOT_OK,
	BUFREQ_E_BUSY,
	BUFREQ_E_OVFL
}BufReq_ReturnType;
/**************************************************************************************************/


typedef enum {
    TP_DATACONF,
    TP_DATARETRY,
    TP_CONFPENDING,
    TP_NORETRY,
} TpDataStateType;
typedef struct {
    TpDataStateType TpDataState;
    PduLengthType TxTpDataCnt;
} RetryInfoType;

typedef enum {
    TP_STMIN=0,
    TP_BS,
    TP_BC,
} TPParameterType;


#endif
