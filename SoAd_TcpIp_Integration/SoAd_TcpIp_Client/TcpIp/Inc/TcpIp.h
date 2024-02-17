#ifndef TCPIP_H_
#define TCPIP_H_

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* TCPIP Pre-Compile Configuration Header file */
#include "TcpIp_Cfg.h"



/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
//** Development Errors **//
/* API service called before initializing the module */
#define TCPIP_E_UNINIT							(uint8)0x01

/* API service called with NULL pointer */
#define TCPIP_E_PARAM_POINTER					(uint8)0x02

/* Invalid argument */
#define TCPIP_E_INV_ARG							(uint8)0x03

/* No buffer space available */
#define TCPIP_E_NOBUFS							(uint8)0x04

/* Message too long */
#define TCPIP_E_MSGSIZE							(uint8)0x07

/* Protocol wrong type for socket */
#define TCPIP_E_PROTOTYPE						(uint8)0x08

/* Address already in use */
#define TCPIP_E_ADDRINUSE						(uint8)0x09

/* Can’t assign requested address */
#define TCPIP_E_ADDRNOTAVAIL					(uint8)0x0A

/* Socket is already connected */
#define TCPIP_E_ISCONN							(uint8)0x0B

/* Socket is not connected */
#define TCPIP_E_NOTCONN							(uint8)0x0C

/* Protocol not available */
#define TCPIP_E_NOPROTOOPT						(uint8)0x0D

/* Address family not supported by protocol family */
#define TCPIP_E_AFNOSUPPORT						(uint8)0x0E

/* Invalid configuration set selection */
#define TCPIP_E_INIT_FAILED						(uint8)0x0F

//** Runtime Errors **//
/* Operation timed out */
#define TCPIP_E_TIMEDOUT						(uint8)0x01

/* Connection refused */
#define TCPIP_E_CONNREFUSED						(uint8)0x02

/* No route to host*/
#define TCPIP_E_HOSTUNREACH						(uint8)0x03

/* Path does not support frame size */
#define TCPIP_E_PACKETTOBIG						(uint8)0x04

/* Duplicate IP Address detected */
#define TCPIP_E_DADCONFLICT						(uint8)0x05

/*******************************************************************************
 *                      API Service IDs                                        *
 *******************************************************************************/
/* Service ID for TcpIp_Init */
#define TcpIp_Init_ID							(uint8)0x01

/* Service ID for TcpIp_GetVersionInfo */
#define TcpIp_GetVersionInfo_ID					(uint8)0x02	

/* Service ID for TcpIp_Close */	
#define TcpIp_Close_ID							(uint8)0x04

/* Service ID for TcpIp_Bind */
#define	TcpIp_Bind_ID							(uint8)0x05

/* Service ID for TcpIp_TcpConnect */
#define	TcpIp_TcpConnect_ID						(uint8)0x06

/* Service ID for TcpIp_TcpListen */
#define	TcpIp_TcpListen_ID						(uint8)0x07

/* Service ID for TcpIp_TcpReceived */
#define	TcpIp_TcpReceived_ID					(uint8)0x08

/* Service ID for TcpIp_SoAdGetSocket */
#define	TcpIp_SoAdGetSocket_ID					(uint8)0x03

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
//@ref for TcpIp_ParamIdType
/*Specifies the maximum TCP receive window for the socket.[uint16]*/
#define TCPIP_PARAMID_TCP_RXWND_MAX					(uint8)0x00
/*Specifies the maximum TCP receive window for the socket.[uint16]*/
#define TCPIP_PARAMID_FRAMEPRIO						(uint8)0x01
/*Specifies if the Nagle Algorithm according to
IETF RFC 1122(chapter 4.2.3.4 When to Send Data) is enabled or not. [boolean]*/
#define TCPIP_PARAMID_TCP_NAGLE						(uint8)0x02
/*Specifies if TCP Keep Alive Probes are sent on the socket connection. [boolean]*/
#define TCPIP_PARAMID_TCP_KEEPALIVE 				(uint8)0x03
/*Specifies the time to live value for outgoing frames on the socket.
For IPv6 this parameter specifies the value of the HopLimit field
used in the IPv6 header. [uint8]*/
#define TCPIP_PARAMID_TTL							(uint8)0x04
/*Specifies the time in [s] between the last data packet sent
(simple ACKs are not considered data) and the first keepalive probe.[uint32]*/
#define TCPIP_PARAMID_TCP_KEEPALIVE_TIME			(uint8)0x05
/*Specifies the maximum number of
times that a keepalive probe is retransmitted. [uint16]*/
#define TCPIP_PARAMID_TCP_KEEPALIVE_PROBES_MAX		(uint8)0x06
/*Specifies the interval in [s] between subsequent keepalive probes. [uint32]*/
#define TCPIP_PARAMID_TCP_KEEPALIVE_INTERVAL		(uint8)0x07
/*Specifies which TCP option filter shall be applied on the related socket. [uint8]*/
#define TCPIP_PARAMID_TCP_OPTIONFILTER				(uint8)0x08
/*Specifies if the Path MTU Discovery shall be performed on the related socket. [boolean]*/
#define TCPIP_PARAMID_PATHMTU_ENABLE				(uint8)0x09
/*The 20-bit Flow Label according to IETF RFC 6437. [uint32]*/
#define TCPIP_PARAMID_FLOWLABEL						(uint8)0x0a
/*The 6-bit Differentiated Service Code Point according to IETF RFC 2474. [uint8]*/
#define TCPIP_PARAMID_DSCP							(uint8)0x0b
/*0x0c Specifies if UDP checksum handling shall be enabled (TRUE)
or skipped (FALSE) on the related socket. [boolean]*/
#define TCPIP_PARAMID_UDP_CHECKSUM					(uint8)0x0c
/*0x0d is used to assign a TLS connection reference to a TCP socket.*/
#define TCPIP_PARAMID_TLS_CONNECTION_ASSIGNMENT		(uint8)0x0d
/*TCP Retransmission timeout before a unacknowledged segment is retransmitted
(overrides TcpIpTcp RetransmissionTimeout (ECUC_TcpIp_00068))*/
#define TCPIP_PARAMID_TCP_RETRANSMIT_TIMEOUT		(uint8)0x0e
/*Start of vendor specific range of parameter IDs. [vendor specific]*/
#define TCPIP_PARAMID_VENDOR_SPECIFIC				(uint8)0x80


/*@ref TcpIp address families*/
/*
#define TCPIP_AF_INET      		   	    (uint16)0x02
#define TCPIP_AF_INET6      			(uint16)0x1c
 */

/*@ref TcpIp Flags*/
#define TCPIP_URG_FLAG                  0x20
#define TCPIP_ACK_FLAG                  0x10
#define TCPIP_PSH_FLAG                  0x08
#define TCPIP_RST_FLAG                  0x04
#define TCPIP_SYN_FLAG                  0x02
#define TCPIP_FIN_FLAG                    0x01

/*To customize the TcpIp Stack according to the scalability classes*/
typedef enum{
	SC1,
	SC2,
	SC3
}TcpIp_ScalabilityClass;

/* Domain identifier type for TcpIp address families */
/* Set according to @ref TcpIp address families.*/

//typedef uint16              TcpIp_DomainType;

/* Address identification type for unique identification of a local IP address and EthIf Controller
configured in the TcpIp module.*/
typedef uint8               TcpIp_LocalAddrIdType;

/* Socket identifier type for unique identification of a TcpIp stack socket.*/
typedef uint16              TcpIp_SocketIdType;

typedef uint8				TcpIp_ParamIdType;

/* Protocol type used by a socket. */
typedef enum {
	TCPIP_IPPROTO_TCP =      0x06,
	TCPIP_IPPROTO_UDP =      0x11
}TcpIp_ProtocolType;

typedef enum{
	TCPIP_AF_INET,
	TCPIP_AF_INET6
}TcpIp_DomainType;

/* Generic structure used by APIs to specify an IP address. */
typedef struct {
	TcpIp_DomainType       	domain;
} TcpIp_SockAddrType;

/* Defines an IPv4 address type which can be derived from the generic address
structure via cast.*/
typedef struct {
	TcpIp_DomainType      domain;
	uint16                port;
	uint8                addr[4];
} TcpIp_SockAddrInetType;

/* Defines a IPv6 address type which can be derived from the generic address
structure via cast.*/
typedef struct {
	TcpIp_DomainType      domain;
	uint16                port;
	uint32                addr[4];
} TcpIp_SockAddrInet6Type;

/* Specifies the TcpIp state for a specific EthIf controller */
typedef enum {
	TCPIP_STATE_ONLINE,
	TCPIP_STATE_ONHOLD,
	TCPIP_STATE_OFFLINE,
	TCPIP_STATE_STARTUP,
	TCPIP_STATE_SHUTDOWN
}TcpIp_StateType;

typedef enum {
	TCPIP_SOCKET_CLOSED,
	TCPIP_SOCKET_CONNECTED,
	TCPIP_SOCKET_SYN_SENT,
	TCPIP_SOCKET_LISTEN,
	TCPIP_SOCKET_SYN_REC,
	TCPIP_SOCKET_SYN_ACK_REC,
	TCPIP_SOCKET_SYN_ACK_SENT,
	TCPIP_SOCKET_ESTABLISHED,
	TCPIP_SOCKET_TRANSMIT_DONE,
	TCPIP_SOCKET_RETRANSMIT,
	TCPIP_SOCKET_TRANSMIT_ACK_REC,
	TCPIP_SOCKET_RECPETION_SEND_ACK,
	TCPIP_SOCKET_ABORT,
	TCPIP_SOCKET_TERMINATE,
	TCPIP_SOCKET_FIN_WAIT_1,
	TCPIP_SOCKET_FIN_WAIT_2,
	TCPIP_SOCKET_FINAL_ACK,
	TCPIP_SOCKET_CLOSE_WAIT,
	TCPIP_SOCKET_FINAL_ACK_WAIT,
	TCPIP_SOCKET_UNEXPECTED
}TcpIp_SocketState;

/* Specifies the state of local IP address assignment*/
typedef enum {
	TCPIP_IPADDR_STATE_ASSIGNED,
	TCPIP_IPADDR_STATE_ONHOLD,
	TCPIP_IPADDR_STATE_UNASSIGNED
}TcpIp_IpAddrStateType;

/*Specifies Address type*/
typedef enum{
	TCPIP_ANYCAST,
	TCPIP_MULTICAST,
	TCPIP_UNICAST
}TcpIp_AddressType;

/* Events reported by TcpIp.*/
typedef enum {
	TCPIP_TCP_RESET =               0x01,	/*TCP connection was reset, TCP socket and
												all related resources have been released */
	TCPIP_TCP_CLOSED =              0x02,	/*TCP connection was closed successfully,
												TCP socket and all related resources have
												been released*/
	TCPIP_TCP_FIN_RECEIVED =        0x03,	/*A FIN signal was received on the TCP
												connection, TCP socket is still valid.*/
	TCPIP_UDP_CLOSED =              0x04,	/*UDP socket and all related resources have
												been released*/
	TCPIP_TLS_HANDSHAKE_SUCCEEDED = 0x05	/*TLS handshake successfully established,
												TLS connection available.*/
}TcpIp_EventType;

/* Specification of IPv4/IPv6 address assignment policy.*/
typedef enum {
	TCPIP_IPADDR_ASSIGNMENT_STATIC,
	TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL_DOIP,
	TCPIP_IPADDR_ASSIGNMENT_DHCP,
	TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL,
	TCPIP_IPADDR_ASSIGNMENT_IPV6_ROUTER,
	TCPIP_IPADDR_ASSIGNMENT_ALL
}TcpIp_IpAddrAssignmentType;

/* TcpIp specific return type. */
typedef enum {
	TCPIP_E_OK,
	TCPIP_E_NOT_OK,
	TCPIP_E_PHYS_ADDR_MISS,
	TCPIP_E_PENDING
}TcpIp_ReturnType;
/*
typedef enum{
	TCPIP_ANYCAST,
	TCPIP_MULTICAST,
	TCPIP_UNICAST
}TcpIpAddressType;
*/

typedef struct {
	uint32 TcpIpDefaultRouter ; //IP address of default router (gateway)
	uint32 TcpIpNetmask; /*
    Network mask of IPv4 address or address prefix of IPv6 address in CIDR Notation, i.e.
decimal value between 0 and 32 (IPv4) or 0 and 128 (IPv6) that describes the number
of significant bits defining the network number or prefix of an IP address.
	 */
	uint32 TcpIpStaticIpAddress ; //Static IP Address.
}TcpIpStaticIpAddressConfig;

/* Specifies the local IP (Internet Protocol) addresses used for IP communication */
typedef struct{
	TcpIp_AddressType 	TcpIpAddressType_t;
	TcpIp_LocalAddrIdType	TcpIpAddrId;
	TcpIp_DomainType 	TcpIpDomainType_t;
	TcpIpStaticIpAddressConfig	TcpIpStaticIpAddressConfig_t;
}TcpIp_LocalAddr;


typedef struct{

	TcpIp_LocalAddr	TcpIp_LocalAddr_t;
}TcpIpConfig;


typedef struct{
	TcpIp_DomainType		domain;	
	TcpIp_ProtocolType		protocol;
	TcpIp_SocketIdType		socketId;
	TcpIp_LocalAddrIdType	TcpIpAddrId;
	uint16					srcPort;
	/*Source Host Information*/
	TcpIp_SockAddrInetType  localIpV4Address;
#if IPV6_SUPPORT
	TcpIp_SockAddrInet6Type localIpV6Address;
#endif
	/*Destination Host Information*/
	TcpIp_SockAddrInetType  remoteIpV4Address;
#if IPV6_SUPPORT
	TcpIp_SockAddrInet6Type remoteIpV6Address;
#endif
	/*Socket State*/
	boolean                 used;       // FALSE for free to use and TRUE for used 
	TcpIp_SocketState		state;		// Specifies the TcpIp socket state
	uint32                  curSeqNum;
	uint32                  curAckNum;
	uint8					curFlags;
	float32					retransmissionTimeout;
	boolean					startRetransmissionTimeout;
	uint32 					retransmissionCntr;		// Always 0 unless startRetransmissionTimeout is TRUE 
	boolean					retransmit;				
}TcpIp_SocketType;

typedef struct{
	uint16 srcPort;
	uint16 destPort;
	uint32 seqNum;
	uint32 ackNum;
	uint8 reserved1 : 4;
	uint8 headerLength : 4;
	uint8 flags : 6;
	uint8 reserved2 : 2;
	uint16 windowSize;
	uint16 checkSum;
	uint16 urgentPointer;
}TcpHeader;

typedef struct {

}TcpIpGeneral_t;

typedef struct{

}TcpIpTcpConfig_t;

typedef struct{
	TcpIpGeneral_t		TcpIpGeneralConfig;
	TcpIpTcpConfig_t	TcpIpTcpConfiguration;
}TcpIp_ConfigType;

/*************************************************TCP IP BUFFER*************************************************************/
typedef struct{
	boolean acquired;
	uint8 tcpData [TcpIpBufferMemory];
	uint8* bufferPtr;
	uint16 bufferPtrIdx;
	boolean buffReady;

	//IP data here
}TcpIp_Buffer;
 /***************************************************************************************************************************/

/*This parameter specifies the type of the upper layer module*/
typedef enum{
	CDD,	/*Complex Driver*/
	SOAD	/*Socket Adaptor*/
}TcpIpSocketOwnerUpperLayer_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Description: This service initializes the TCP/IP Stack */
void TcpIp_Init (const TcpIp_ConfigType* ConfigPtr);

/* Description: Returns the version information. */
void TcpIp_GetVersionInfo (Std_VersionInfoType* versioninfo);

/* Description: By this API service the TCP/IP stack is requested to close the socket
and release all related resources*/
Std_ReturnType TcpIp_Close (TcpIp_SocketIdType SocketId, boolean Abort);

/* Description: By this API service the TCP/IP stack is requested to bind a UDP
or TCP socket to a local resource*/
Std_ReturnType TcpIp_Bind (TcpIp_SocketIdType SocketId, 
		TcpIp_LocalAddrIdType LocalAddrId, uint16* PortPtr);

/* Description: By this API service the TCP/IP stack is requested to establish
a TCP connection to the configured peer*/
Std_ReturnType TcpIp_TcpConnect (TcpIp_SocketIdType SocketId, const 
		TcpIp_SockAddrType* RemoteAddrPtr);

/* Description: By this API service the TCP/IP stack is requested to listen on the TCP socket
specified by the socket identifier*/
Std_ReturnType TcpIp_TcpListen (TcpIp_SocketIdType SocketId, uint16 MaxChannels);

/* Description: By this API service the reception of socket
data is confirmed to the TCP/IP stack*/
Std_ReturnType TcpIp_TcpReceived (TcpIp_SocketIdType SocketId, uint32 Length);

/* Description: By this API service the TCP/IP stack is requested to change the TcpIp state of the
communication network identified by EthIf controller index*/
Std_ReturnType TcpIp_RequestComMode (uint8 CtrlIdx, TcpIp_StateType State);

/* Description: TCP/IP stack is requested to allocate a new socket. Note: Each
accepted incoming TCP connection also allocates a socket resource.*/
Std_ReturnType TcpIp_SoAdGetSocket (TcpIp_DomainType Domain,
		TcpIp_ProtocolType Protocol,TcpIp_SocketIdType* SocketIdPtr);

Std_ReturnType TcpIp_TcpTransmit (TcpIp_SocketIdType SocketId,
		const uint8* DataPtr, uint32 AvailableLength, boolean ForceRetrieve);

Std_ReturnType TcpIp_TcpReceived (TcpIp_SocketIdType SocketId, uint32 Length);

void TcpIp_MainFunction(void);


extern TcpIp_SocketType socket_list[TcpIpTcpSocketMax];

#endif
