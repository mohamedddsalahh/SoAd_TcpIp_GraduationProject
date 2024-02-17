#include "TcpIp.h"
#include "EthIf.h"
#include "SoAd.h"
#include "SoAd_Cbk.h"


#define TCPIP_MAIN_FUNCTION_PERIODICITY_MS		100 /* Not Standard */ /**************************/

static TcpIp_LocalAddr TcpIpLocalAddr_list[2];
static TcpIp_Buffer TcpIpBuffer[TcpIpTcpSocketMax];


static TcpIp_SocketIdType getAvailableSocket(){

	TcpIp_SocketIdType curInd;
	TcpIp_SocketIdType availableSocket = 100;

	for(curInd = 0; curInd < TcpIpTcpSocketMax; curInd++){
		if(FALSE == socket_list[curInd].used){
			availableSocket = curInd;
			break;
		}
	}
	return availableSocket;
}

#if TcpIpTcpRetransmissionTimeout != 0
static boolean isTimeout(uint32 mainFunctionCntr, float32 retransmitTimeout)
{
	uint32 retransmitTimeoutMs = retransmitTimeout * 1000;

	if ((mainFunctionCntr * TCPIP_MAIN_FUNCTION_PERIODICITY_MS) >= retransmitTimeoutMs)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
#endif

static Std_ReturnType TcpIp_GetPacket_Header(TcpIp_SocketIdType SocketId, uint8 flags, uint32 seqNum, uint8** bufPtr){

	TcpHeader segment;
	uint8* segmentByte = (uint8*)&segment;

	if(TcpIpTcpSocketMax <= SocketId)
	{
		return E_NOT_OK;
	}

	if(FALSE == socket_list[SocketId].used)
	{
		return E_NOT_OK;
	}

#if TcpIpIpV4Enabled == TRUE
	segment.srcPort = socket_list[SocketId].localIpV4Address.port;
	segment.destPort = socket_list[SocketId].remoteIpV4Address.port;
#endif

#if TcpIpIpV6Enabled == TRUE
	segment.srcPort = socket_list[SocketId].localIpV6Address.port;
	segment.destPort = socket_list[SocketId].remoteIpV6Address.port;
#endif

	segment.seqNum = seqNum;

	if((flags & TCPIP_ACK_FLAG))
	{
		segment.ackNum = socket_list[SocketId].curSeqNum + 1;
	}
	else{
		segment.ackNum = 0;
	}

	segment.headerLength = sizeof(TcpHeader) / 4;
	segment.flags = flags;
	segment.windowSize = 0;
	segment.checkSum = 0;
	segment.urgentPointer = 0;

	for(uint16 curByte = 0; curByte < sizeof(TcpHeader); curByte++){
		(*bufPtr)[curByte] = segmentByte[curByte];
	}

	return E_OK;	
}

static Std_ReturnType TcpIp_GetPacket(TcpIp_SocketIdType SocketId, const uint8* DataPtr, uint32 AvailableLength){

	//Acquire the tcp buffer
	TcpIpBuffer[SocketId].acquired = TRUE;

	//Copy Data from Data ptr to tcp ip buffer
	uint16 bufferCtr = TcpIpBuffer[SocketId].bufferPtrIdx;
	uint16 dataCtr = 0;

	for(bufferCtr; dataCtr < (AvailableLength); bufferCtr++, dataCtr++){
		*(TcpIpBuffer[SocketId].tcpData + bufferCtr) = *(DataPtr+dataCtr);

	}
	TcpIpBuffer[SocketId].bufferPtrIdx = bufferCtr;
	dataCtr = 0;

	TcpIpBuffer[SocketId].buffReady = TRUE;

	return E_OK;
}



static Std_ReturnType TcpIp_DecodePacket(TcpIp_SocketIdType SocketId, const uint8* bufPtr){

	TcpHeader* segmentPtr;

	if(NULL_ptr == bufPtr){
		return E_NOT_OK;
	}

	// Decode Network Header

	segmentPtr = (TcpHeader*)bufPtr;

	if(segmentPtr->destPort != socket_list[SocketId].localIpV4Address.port){
		return E_NOT_OK;
	}

	if(socket_list[SocketId].state == TCPIP_SOCKET_LISTEN){
		socket_list[SocketId].remoteIpV4Address.port = segmentPtr->srcPort;
	}

	if(segmentPtr->srcPort != socket_list[SocketId].remoteIpV4Address.port){
		return E_NOT_OK;
	}

	socket_list[SocketId].curSeqNum = segmentPtr->seqNum;
	socket_list[SocketId].curAckNum = segmentPtr->ackNum;

	socket_list[SocketId].curFlags = segmentPtr->flags;

	// Make CheckSum	

	return E_OK;
} 


static void TcpIp_EthIf_CopyToBuffer(uint8** ethifPtr, uint8** tcpPtr, uint16 length){

	for(uint16 curByte = 0; curByte < length; curByte++){
		(*ethifPtr)[curByte] = (*tcpPtr)[curByte];
	}

}


/* Description: This service initializes the TCP/IP Stack */
void TcpIp_Init (const TcpIp_ConfigType* ConfigPtr){
	/*ConfigPtr: Pointer to the configuration data of the TcpIp module*/

}

/* Description: By this API service the TCP/IP stack is requested to close the socket
and release all related resources*/
Std_ReturnType TcpIp_Close (TcpIp_SocketIdType SocketId, boolean Abort){
	/* SocketId: Socket handle identifying the local socket resource*/
	/* Abort: TRUE: connection will immediately be terminated by sending a
		RST-Segment and releasing all related resources.
		FALSE: connection will be terminated after performing a regular
		connection termination handshake and releasing all related resources*/
	if(TcpIpTcpSocketMax <= SocketId)
	{
		return E_NOT_OK;
	}
	else
	{

	}

	if(FALSE == socket_list[SocketId].used)
	{
		return E_NOT_OK;
	}
	else
	{

	}

	if(Abort)
	{
		socket_list[SocketId].state = TCPIP_SOCKET_ABORT;
	}	
	else
	{
		socket_list[SocketId].state = TCPIP_SOCKET_TERMINATE;
	}

	return E_OK;
}


/* Description: TCP/IP stack is requested to allocate a new socket. Note: Each
accepted incoming TCP connection also allocates a socket resource.*/
Std_ReturnType TcpIp_SoAdGetSocket (TcpIp_DomainType Domain, TcpIp_ProtocolType Protocol, TcpIp_SocketIdType* SocketIdPtr)
{
	/*Domain: IP address family*/
	/*Protocol: Socket protocol as sub-family of parameter type.*/
	/*SocketIdPtr: Pointer to socket identifier representing the requested socket.
		This socket identifier must be provided for all further API calls
		which requires a SocketId. Note: SocketIdPtr is only valid if return
		value is E_OK.*/
	TcpIp_SocketIdType sockIndex;	/*Specifies the available Socket Index*/
	uint8 error_code;

	if(Domain != TCPIP_AF_INET && Domain != TCPIP_AF_INET6){
		/* Address family not supported by protocol family */
		error_code = TCPIP_E_AFNOSUPPORT;
		/*
			Call Det API
		 */
		return E_NOT_OK;
	}

	if (Protocol != TCPIP_IPPROTO_TCP && Protocol != TCPIP_IPPROTO_UDP){
		/* Protocol wrong type for socket */
		error_code = TCPIP_E_PROTOTYPE;
		/*
			Call Det API
		 */
		return E_NOT_OK;
	}

	sockIndex = getAvailableSocket();

	socket_list[sockIndex].domain = Domain;
	socket_list[sockIndex].protocol = Protocol;
	socket_list[sockIndex].socketId = sockIndex;
	socket_list[sockIndex].used = TRUE; 
	socket_list[sockIndex].state = TCPIP_SOCKET_CLOSED;
	socket_list[sockIndex].startRetransmissionTimeout = FALSE;
	*SocketIdPtr = sockIndex;

	return E_OK;
}



/* Description: By this API service the TCP/IP stack is requested to bind a UDP
or TCP socket to a local resource*/
Std_ReturnType TcpIp_Bind (TcpIp_SocketIdType SocketId, TcpIp_LocalAddrIdType LocalAddrId, uint16* PortPtr)
{
	/*SocketId: Socket identifier of the related local socket resource*/
	/*LocalAddrId: IP address identifier representing the local IP address and EthIf
		controller to bind the socket to*/
	/*Pointer to memory where the local port to which the socket shall
		be bound is specified*/	
	uint8 error_code;
	TcpIp_ReturnType Return_State = TCPIP_E_OK;

	/*Check for Development Error*/
	/*Check if address is invalid*/
#if 0
	if(LocalAddrId < MinAddrVal || LocalAddrId > MaxAddrVal){
		error_code = TCPIP_E_ADDRNOTAVAIL;
		/*
			Call Det API
		 */
		return E_NOT_OK;
	}
#endif

	/*Check if there is another socket already bound to the same port,
		protocol and local address for the TCP Protocol*/
	uint8 i = 0;
	/*	for (i = 0; i < TcpIpTcpSocketMax; i++){
		if (i != SocketId){
			if(socket_list[i].srcPort == *PortPtr && socket_list[i].used == 1){
				uint8 temp = socket_list[i].TcpIpAddrId;
				if (temp != LocalAddrId){
					if(TcpIpLocalAddr_list[temp].TcpIpStaticIpAddressConfig_t.TcpIpStaticIpAddress == TcpIpLocalAddr_list[LocalAddrId].TcpIpStaticIpAddressConfig_t.TcpIpStaticIpAddress ){
						error_code = TCPIP_E_ADDRINUSE;

					//	Call Det API

						return E_NOT_OK;
					}
				}
			}
		}
	}
	 */
	socket_list[SocketId].TcpIpAddrId = LocalAddrId;
	socket_list[SocketId].localIpV4Address.port = *PortPtr;
	return E_OK;
}

/* Description: By this API service the TCP/IP stack is requested to establish
a TCP connection to the configured peer*/
Std_ReturnType TcpIp_TcpConnect (TcpIp_SocketIdType SocketId, const TcpIp_SockAddrType* RemoteAddrPtr){
	/* SocketId: Socket identifier of the related local socket resource.
	   RemoteAddrPtr: IP address and port of the remote host to connect to.*/
	uint8 error_code; 
	if(SocketId >= TcpIpTcpSocketMax){
		return E_NOT_OK;
	}

	if (RemoteAddrPtr == NULL_ptr){
		error_code = TCPIP_E_PARAM_POINTER;
		/*
			Call Det API
		 */
		return E_NOT_OK;	
	}

	if(socket_list[SocketId].used == FALSE){
		error_code = TCPIP_E_INV_ARG;
		/*
			Call Det API
		 */
		return E_NOT_OK;	
	}

	if(socket_list[SocketId].state != TCPIP_SOCKET_CLOSED){
		error_code = TCPIP_E_ISCONN;
		/*
			Call Det API
		 */
		return E_NOT_OK;
	}

	/*Check the Domain Type*/
#if TcpIpIpV4Enabled == TRUE
	/*IPV4 is used*/
	if(RemoteAddrPtr->domain == TCPIP_AF_INET){
		TcpIp_SockAddrInetType* remoteAdr = (TcpIp_SockAddrInetType*)RemoteAddrPtr;
		socket_list[SocketId].remoteIpV4Address.domain  = TCPIP_AF_INET;
		socket_list[SocketId].remoteIpV4Address.addr[0] = remoteAdr->addr[0];
		socket_list[SocketId].remoteIpV4Address.addr[1] = remoteAdr->addr[1];
		socket_list[SocketId].remoteIpV4Address.addr[2] = remoteAdr->addr[2];
		socket_list[SocketId].remoteIpV4Address.addr[3] = remoteAdr->addr[3];
		socket_list[SocketId].remoteIpV4Address.port = remoteAdr->port;
	}
	else{
		error_code = TCPIP_E_INV_ARG;
		/*
			Call Det API
		 */
		return E_NOT_OK;
	}
#endif

	/*IPV6 is used*/
#if TcpIpIpV6Enabled == TRUE
	if (RemoteAddrPtr->domain == TCPIP_AF_INET6){
		TcpIp_SockAddrInet6Type* remoteAdr = (TcpIp_SockAddrInet6Type*)RemoteAddrPtr;
		socket_list[SocketId].ipV6Address.domain  = TCPIP_AF_INET6;
		socket_list[SocketId].ipV6Address.addr[0] = remoteAdr->addr[0];
		socket_list[SocketId].ipV6Address.addr[1] = remoteAdr->addr[1];
		socket_list[SocketId].ipV6Address.addr[2] = remoteAdr->addr[2];
		socket_list[SocketId].ipV6Address.addr[3] = remoteAdr->addr[3];
		socket_list[SocketId].ipV6Address.port = remoteAdr->port;
	}
	else{
		error_code = TCPIP_E_INV_ARG;
		/*
			Call Det API
		 */
		return E_NOT_OK;
	}
#endif

	socket_list[SocketId].state = TCPIP_SOCKET_CONNECTED;
	socket_list[SocketId].curSeqNum = 0;
	socket_list[SocketId].curAckNum = 0;

	return E_OK;
}

Std_ReturnType TcpIp_TcpListen (TcpIp_SocketIdType SocketId, uint16 MaxChannels){

	uint8 error_code;
	if(SocketId >= TcpIpTcpSocketMax){
		return E_NOT_OK;
	}

	if(socket_list[SocketId].used == FALSE){
		error_code = TCPIP_E_INV_ARG;
		/*
			Call Det API
		 */
		return E_NOT_OK;	
	}

	if(socket_list[SocketId].state != TCPIP_SOCKET_CLOSED){
		error_code = TCPIP_E_ISCONN;
		/*
			Call Det API
		 */
		return E_NOT_OK;
	}

	socket_list[SocketId].state = TCPIP_SOCKET_LISTEN;

	return E_OK;
}

Std_ReturnType TcpIp_TcpTransmit (TcpIp_SocketIdType SocketId, const uint8* DataPtr, uint32 AvailableLength, boolean ForceRetrieve){

	//Check that socket id passed is within range
	if(SocketId >= TcpIpTcpSocketMax){
		return E_NOT_OK;
	}
	//Checking for socket state and making sure that it's in the connection established state
	if(TCPIP_SOCKET_ESTABLISHED != socket_list[SocketId].state){
		return E_NOT_OK;
	}
	//Check for segment size to be sent whether if its greater than buffer size
	if ((AvailableLength + TcpIpBuffer[SocketId].bufferPtrIdx) > TcpIpMaxSegmentSize){
		return E_NOT_OK;
	}

	if(DataPtr != NULL_ptr){
		TcpIp_GetPacket(SocketId, DataPtr, AvailableLength);
	}
	return E_OK;
}


void TcpIp_MainFunction(void){

	TcpIp_SocketIdType curInd;
	for(curInd = 0; curInd < TcpIpTcpSocketMax; curInd++)
	{
		if(FALSE == socket_list[curInd].used)
		{

		}
		else{
#if TcpIpTcpRetransmissionTimeout != 0
			if(TRUE == socket_list[curInd].startRetransmissionTimeout)
			{
				(socket_list[curInd].retransmissionCntr)++;
				if(TRUE == isTimeout(socket_list[curInd].retransmissionCntr, socket_list[curInd].retransmissionTimeout))
				{
					socket_list[curInd].retransmit = TRUE;
				}
				else
				{
					socket_list[curInd].retransmit = FALSE;
				}
			}
#endif

			/* 3 way handshake Client */
			if(TCPIP_SOCKET_CONNECTED == socket_list[curInd].state){
				uint8* bufPtr;
				EthIf_ProvideTxBuffer(0, 0, 0, 0, &bufPtr, NULL_ptr);
				TcpIp_GetPacket_Header(curInd, TCPIP_SYN_FLAG, 1, &bufPtr);
				EthIf_Transmit(0, 0, 0, 0, 20, 0);

				socket_list[curInd].state = TCPIP_SOCKET_SYN_SENT;

				socket_list[curInd].startRetransmissionTimeout = TRUE;
			}

			/* 3 way handshake Client */
			if(TCPIP_SOCKET_SYN_ACK_REC == socket_list[curInd].state){
				uint8* bufPtr;
				EthIf_ProvideTxBuffer(0, 0, 0, 0, &bufPtr, NULL_ptr);
				TcpIp_GetPacket_Header(curInd, TCPIP_ACK_FLAG, 3, &bufPtr);
				EthIf_Transmit(0, 0, 0, 0, 20, 0);

				socket_list[curInd].state = TCPIP_SOCKET_ESTABLISHED;
				SoAd_TcpConnected (curInd);
			}

			/* 3 way handshake Server */
			if(TCPIP_SOCKET_SYN_REC == socket_list[curInd].state){
				uint8* bufPtr;
				EthIf_ProvideTxBuffer(0, 0, 0, 0, &bufPtr, NULL_ptr);
				TcpIp_GetPacket_Header(curInd, TCPIP_SYN_FLAG | TCPIP_ACK_FLAG, 2, &bufPtr);
				EthIf_Transmit(0, 0, 0, 0, 20, 0);

				socket_list[curInd].state = TCPIP_SOCKET_SYN_ACK_SENT;

				socket_list[curInd].startRetransmissionTimeout = TRUE;
			}

			/* Transmission */
			if(TCPIP_SOCKET_ESTABLISHED == socket_list[curInd].state){

				if(TcpIpBuffer[curInd].buffReady){
					//Get the ethif to allocate it's buffer
					uint8* ptr = (TcpIpBuffer[curInd].tcpData);
					TcpIp_GetPacket_Header(curInd, 0, 4/*Sequence number*/, &ptr);
					uint8* bufPtr;
					EthIf_ProvideTxBuffer(0, 0, 0, 0, &bufPtr, NULL_ptr);
					TcpIp_EthIf_CopyToBuffer(&bufPtr, &ptr, TcpIpBuffer[curInd].bufferPtrIdx);
					EthIf_Transmit(0, 0, 0, 0, TcpIpBuffer[curInd].bufferPtrIdx, 0);
					TcpIpBuffer[curInd].bufferPtrIdx = 20; /*Return To initial Value After Packet is sent*/
					socket_list[curInd].state = TCPIP_SOCKET_TRANSMIT_DONE;
				}
			}

			/* Sending ACK after Reception */
			if(TCPIP_SOCKET_RECPETION_SEND_ACK == socket_list[curInd].state){
				uint8* bufPtr;
				EthIf_ProvideTxBuffer(0, 0, 0, 0, &bufPtr, NULL_ptr);
				TcpIp_GetPacket_Header(curInd, TCPIP_ACK_FLAG, 3, &bufPtr);
				EthIf_Transmit(0, 0, 0, 0, 20, 0);

				socket_list[curInd].state = TCPIP_SOCKET_ESTABLISHED;				
			}

			/* Termination (Requester) */
			if(TCPIP_SOCKET_ABORT == socket_list[curInd].state){
				uint8* bufPtr;
				EthIf_ProvideTxBuffer(0, 0, 0, 0, &bufPtr, NULL_ptr);
				TcpIp_GetPacket_Header(curInd, TCPIP_RST_FLAG, 2, &bufPtr);
				EthIf_Transmit(0, 0, 0, 0, 20, 0);

				socket_list[curInd].state = TCPIP_SOCKET_CLOSED;
				socket_list[curInd].used = FALSE;  				
			}

			/* Termination (Requester) */
			if(TCPIP_SOCKET_TERMINATE == socket_list[curInd].state){
				uint8* bufPtr;
				EthIf_ProvideTxBuffer(0, 0, 0, 0, &bufPtr, NULL_ptr);
				TcpIp_GetPacket_Header(curInd, TCPIP_FIN_FLAG, 2, &bufPtr);
				EthIf_Transmit(0, 0, 0, 0, 20, 0);

				socket_list[curInd].state = TCPIP_SOCKET_FIN_WAIT_1;

				socket_list[curInd].startRetransmissionTimeout = TRUE;		
			}

			/* Termination (Requester) */
			if(TCPIP_SOCKET_FINAL_ACK == socket_list[curInd].state){
				uint8* bufPtr;
				EthIf_ProvideTxBuffer(0, 0, 0, 0, &bufPtr, NULL_ptr);
				TcpIp_GetPacket_Header(curInd, TCPIP_ACK_FLAG, 2, &bufPtr);
				EthIf_Transmit(0, 0, 0, 0, 20, 0);

				socket_list[curInd].state = TCPIP_SOCKET_CLOSED;
				socket_list[curInd].used = FALSE;					
			}

			/* Termination (Responser) */
			if(TCPIP_SOCKET_CLOSE_WAIT == socket_list[curInd].state){
				uint8* ackBufPtr;
				uint8* finBufPtr;
				EthIf_ProvideTxBuffer(0, 0, 0, 0, &ackBufPtr, NULL_ptr);
				TcpIp_GetPacket_Header(curInd, TCPIP_ACK_FLAG, 2, &ackBufPtr);
				EthIf_Transmit(0, 0, 0, 0, 20, 0);

				EthIf_ProvideTxBuffer(0, 0, 0, 0, &finBufPtr, NULL_ptr);
				TcpIp_GetPacket_Header(curInd, TCPIP_FIN_FLAG, 2, &finBufPtr);
				EthIf_Transmit(0, 0, 0, 0, 20, 0);

				socket_list[curInd].state = TCPIP_SOCKET_FINAL_ACK_WAIT;				
			}

			/* Retransmission */
			if(TRUE == socket_list[curInd].retransmit)
			{
				/* Retransmit SYN */
				if(TCPIP_SOCKET_SYN_SENT == socket_list[curInd].state)
				{
					uint8* bufPtr;
					EthIf_ProvideTxBuffer(0, 0, 0, 0, &bufPtr, NULL_ptr);
					TcpIp_GetPacket_Header(curInd, TCPIP_SYN_FLAG, 1, &bufPtr);
					EthIf_Transmit(0, 0, 0, 0, 20, 0);

					socket_list[curInd].retransmissionCntr = 0;	
					socket_list[curInd].retransmit = FALSE;				
				}
				/* Retransmit SYN ACK */
				else if(TCPIP_SOCKET_SYN_ACK_SENT == socket_list[curInd].state)
				{
					uint8* bufPtr;
					EthIf_ProvideTxBuffer(0, 0, 0, 0, &bufPtr, NULL_ptr);
					TcpIp_GetPacket_Header(curInd, TCPIP_SYN_FLAG | TCPIP_ACK_FLAG, 2, &bufPtr);
					EthIf_Transmit(0, 0, 0, 0, 20, 0);		

					socket_list[curInd].retransmissionCntr = 0;	
					socket_list[curInd].retransmit = FALSE;				
				}
				/* Retransmit FIN */
				else if(TCPIP_SOCKET_FIN_WAIT_1 == socket_list[curInd].state)
				{
					uint8* bufPtr;
					EthIf_ProvideTxBuffer(0, 0, 0, 0, &bufPtr, NULL_ptr);
					TcpIp_GetPacket_Header(curInd, TCPIP_FIN_FLAG, 2, &bufPtr);
					EthIf_Transmit(0, 0, 0, 0, 20, 0);	

					socket_list[curInd].retransmissionCntr = 0;	
					socket_list[curInd].retransmit = FALSE;						
				}
			}
		}
	}
}

void TcpIp_RxIndication (uint8 CtrlIdx, Eth_FrameType FrameType, 
	boolean IsBroadcast, const uint8* PhysAddrPtr, const uint8* DataPtr, uint16 LenByte){

	TcpIp_SocketIdType curInd;

	for(curInd = 0; curInd < TcpIpTcpSocketMax; curInd++){
		if(FALSE == socket_list[curInd].used){

		}
		else{
			/* 3 way Handshake Client */
			if(TCPIP_SOCKET_SYN_SENT == socket_list[curInd].state){
				if(E_OK == TcpIp_DecodePacket(curInd, DataPtr)){

					if((socket_list[curInd].curFlags & TCPIP_SYN_FLAG) && (socket_list[curInd].curFlags & TCPIP_ACK_FLAG)){
						socket_list[curInd].state = TCPIP_SOCKET_SYN_ACK_REC;

						socket_list[curInd].startRetransmissionTimeout = FALSE;
						socket_list[curInd].retransmissionCntr = 0;
						socket_list[curInd].retransmit = FALSE;
					}
					else{
						socket_list[curInd].state = TCPIP_SOCKET_UNEXPECTED;
					}
							
				}
			}

			/* 3 way Handshake Server */
			else if(TCPIP_SOCKET_LISTEN == socket_list[curInd].state){
				if(E_OK == TcpIp_DecodePacket(curInd, DataPtr)){

					if(socket_list[curInd].curFlags & TCPIP_SYN_FLAG){
						socket_list[curInd].state = TCPIP_SOCKET_SYN_REC;
					}
					else{
						socket_list[curInd].state = TCPIP_SOCKET_UNEXPECTED;
					}
				}
			}

			/* 3 way Handshake Server */
			else if(TCPIP_SOCKET_SYN_ACK_SENT == socket_list[curInd].state){
				if(E_OK == TcpIp_DecodePacket(curInd, DataPtr)){

					if(socket_list[curInd].curFlags & TCPIP_ACK_FLAG){
						socket_list[curInd].state = TCPIP_SOCKET_ESTABLISHED;

						socket_list[curInd].startRetransmissionTimeout = FALSE;
						socket_list[curInd].retransmissionCntr = 0;
						socket_list[curInd].retransmit = FALSE;

						SoAd_TcpAccepted(curInd, curInd, (TcpIp_SockAddrType*)&socket_list[curInd].remoteIpV4Address);
					}
					else{
						socket_list[curInd].state = TCPIP_SOCKET_UNEXPECTED;
					}

				}
			}

			/* Transmission done with ACK */
			else if(TCPIP_SOCKET_TRANSMIT_DONE == socket_list[curInd].state){
				if(E_OK == TcpIp_DecodePacket(curInd, DataPtr)){
					socket_list[curInd].state = TCPIP_SOCKET_TRANSMIT_ACK_REC;
					TcpIpBuffer[curInd].acquired = FALSE;
					TcpIpBuffer[curInd].buffReady = FALSE;
					SoAd_TxConfirmation(curInd, LenByte);
				}
			}

			/* Reception */
			else if(TCPIP_SOCKET_ESTABLISHED == socket_list[curInd].state)
			{
				TcpIp_SockAddrType* genericAddress = (TcpIp_SockAddrType*)&(socket_list[curInd].remoteIpV4Address);
				SoAd_RxIndication(curInd, genericAddress, DataPtr, LenByte);
			}

			/* Termination (Requester) */
			else if(TCPIP_SOCKET_FIN_WAIT_1 == socket_list[curInd].state){
				if(E_OK == TcpIp_DecodePacket(curInd, DataPtr)){

					if(socket_list[curInd].curFlags & TCPIP_ACK_FLAG){
						socket_list[curInd].state = TCPIP_SOCKET_FIN_WAIT_2;

						socket_list[curInd].startRetransmissionTimeout = FALSE;
						socket_list[curInd].retransmissionCntr = 0;
						socket_list[curInd].retransmit = FALSE;
					}
					else{
						socket_list[curInd].state = TCPIP_SOCKET_UNEXPECTED;
					}
								
				}				
			}

			/* Termination (Requester) */
			else if(TCPIP_SOCKET_FIN_WAIT_2 == socket_list[curInd].state){
				if(E_OK == TcpIp_DecodePacket(curInd, DataPtr)){

					if(socket_list[curInd].curFlags & TCPIP_FIN_FLAG){
						socket_list[curInd].state = TCPIP_SOCKET_FINAL_ACK;
					}
					else{
						socket_list[curInd].state = TCPIP_SOCKET_UNEXPECTED;
					}
					
				}					
			}

			/* Termination (Responser) */
			else if(TCPIP_SOCKET_FINAL_ACK_WAIT == socket_list[curInd].state){
				if(E_OK == TcpIp_DecodePacket(curInd, DataPtr)){

					if(socket_list[curInd].curFlags & TCPIP_ACK_FLAG){
						socket_list[curInd].state = TCPIP_SOCKET_CLOSED;
						socket_list[curInd].used = FALSE;
					}
					else{
						socket_list[curInd].state = TCPIP_SOCKET_UNEXPECTED;
					}
					
				}					
			}
			else{
				socket_list[curInd].state = TCPIP_SOCKET_UNEXPECTED;
			}

			/* Received Unexpected */
			if(socket_list[curInd].state == TCPIP_SOCKET_UNEXPECTED)
			{
				/* Received FIN for termination handshake */
				if(socket_list[curInd].curFlags & TCPIP_FIN_FLAG){

					socket_list[curInd].state = TCPIP_SOCKET_CLOSE_WAIT;

				}
				/* Received RST for immediate termination */
				else if(socket_list[curInd].curFlags & TCPIP_RST_FLAG){

					socket_list[curInd].state = TCPIP_SOCKET_CLOSED;
					socket_list[curInd].used = FALSE;

				}
				else{
					/* 100% Corrupt Data.. */
				}

			}
			else{

			}
		}
	}	
}

Std_ReturnType TcpIp_TcpReceived (TcpIp_SocketIdType SocketId, uint32 Length){
	socket_list[SocketId].state = TCPIP_SOCKET_RECPETION_SEND_ACK;
}
