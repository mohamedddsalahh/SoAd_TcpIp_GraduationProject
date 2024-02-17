#ifndef SOAD_H_
#define SOAD_H_

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "SoAd_cfg.h"
#include "TcpIp.h"



typedef uint16 SoAd_SoConIdType;

typedef enum{
	SOAD_SOCON_ONLINE,
	SOAD_SOCON_RECONNECT,
	SOAD_SOCON_OFFLINE
}SoAd_SoConModeType;


typedef struct{

	uint8	SoAdSocketTcpImmediateTpTxConfirmation;
	uint8	SoAdSocketTcpInitiate;
	uint8	SoAdSocketTcpKeepAlive;
	uint32	SoAdSocketTcpKeepAliveTime;
	uint32	SoAdSocketTcpRetransmissionTimeout;

}SoAd_SocketTcpType;

typedef enum{
	SOCKET_InUse,
	SOCKET_CREATE,
	SOCKET_Aquired,
	SOCKET_NOT_USED
}Soad_SocketState;

typedef struct{

	SoAd_SocketTcpType	SoAd_SocketTcpConfig;

}SoAd_SocketProtocolType;

typedef struct{

	TcpIp_DomainType	Domain;
	uint16	SoAdSocketRemotePort;
	uint8 SoAdSocketRemoteIpAddress[4];

}SoAd_SocketRemoteAddressType;

typedef struct{

	SoAd_SoConIdType	SoAdSocketId;
	SoAd_SocketRemoteAddressType	SoAd_SocketRemoteAddress;

}SoAd_SocketConnectionType;


typedef struct{

	uint16 SoAdSocketLocalPort;
	TcpIp_LocalAddr SoAdSocketLocalAddressRef;
	SoAd_SocketConnectionType	SoAd_SocketConnection;
	SoAd_SocketProtocolType	SoAd_SocketProtocol;

}SoAd_SocketConnectionGroupType;

typedef enum{
	IF,
	TP
}SoAdTxUpperLayerType;

typedef struct{

	uint16	SoAdRxPduId;

}SoAd_SocketRouteDestType;

typedef struct{

	uint32	SoAdRxPduHeaderId;
	SoAd_SocketConnectionType SoAdTxSocketConn;

}SoAd_PduRouteDestType;

typedef struct{

	SoAdTxUpperLayerType	upperLayer;
	SoAd_PduRouteDestType	SoAdTxPduRef;

}SoAd_PduRouteType;

typedef struct{


	SoAd_SocketConnectionGroupType	SoAd_SockConnGroup[SoAdRoutingGroupMax];

}SoAd_ConfigType;

Std_ReturnType SoAd_IfTransmit (PduIdType TxPduId, const PduInfoType* PduInfoPtr);
Std_ReturnType SoAd_TpCancelTransmit (PduIdType TxPduId );
Std_ReturnType SoAd_TpCancelReceive ( PduIdType RxPduId );
Std_ReturnType SoAd_TcpAccepted (TcpIp_SocketIdType SocketId, TcpIp_SocketIdType SocketIdConnected, const TcpIp_SockAddrType* RemoteAddrPtr);
void SoAd_TcpConnected (TcpIp_SocketIdType SocketId);
void SoAd_TxConfirmation(TcpIp_SocketIdType SocketId, uint16 Length);
void SoAd_RxIndication (TcpIp_SocketIdType SocketId, const TcpIp_SockAddrType* RemoteAddrPtr, const uint8* BufPtr, uint16 Length);


extern SoAd_ConfigType SoAdConfigPtr;

#endif
