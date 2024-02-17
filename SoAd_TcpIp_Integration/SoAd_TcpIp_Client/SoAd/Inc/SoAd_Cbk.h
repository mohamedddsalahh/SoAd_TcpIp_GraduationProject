/*
 * SoAd_Cbk.h
 *
 *  Created on: Dec 27, 2023
 *      Author: USER
 */

#ifndef SOAD_CBK_H_
#define SOAD_CBK_H_

#include "SoAd.h"




Std_ReturnType SoAd_TcpAccepted (TcpIp_SocketIdType SocketId, TcpIp_SocketIdType SocketIdConnected, const TcpIp_SockAddrType* RemoteAddrPtr);
void SoAd_TcpConnected (TcpIp_SocketIdType SocketId);
void SoAd_TxConfirmation(TcpIp_SocketIdType SocketId, uint16 Length);
void SoAd_RxIndication (TcpIp_SocketIdType SocketId, const TcpIp_SockAddrType* RemoteAddrPtr, const uint8* BufPtr, uint16 Length);





#endif /* SOAD_CBK_H_ */
