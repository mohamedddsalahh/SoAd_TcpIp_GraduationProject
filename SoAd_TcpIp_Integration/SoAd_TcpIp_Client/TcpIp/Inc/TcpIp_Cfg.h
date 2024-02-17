#ifndef TCPIP_CFG_H_
#define TCPIP_CFG_H_

#include "Std_Types.h"

/**=====================================================**/
/** TCPIP General Container **/
/*Memory size in bytes reserved for TCP/IP buffers*/
#define TcpIpBufferMemory		1500

/*Switches the development error detection and notification on or off*/
#define TcpIpDevErrorDetect		(STD_ON)

/*Switches the reporting of security events to the IdsM*/
#define TcpIpEnableSecurityEventReporting	(STD_OFF)

/*Period of TcpIp_MainFunction in [s]*/
#define TcpIpMainFunctionPeriod		0

/*In order to customize the TcpIp Stack to the specific needs of the user it can be scaled according to the scalability classes.
SC1 IPv4 - In-Vehicle and Diagnostic Communication
SC2 IPv6 - In-Vehicle and Diagnostic Communication
SC3 IPv4 and IPv6 (Dual Stack) - In-Vehicle and Diagnostic Communication */
#define TcpIpScalabilityClass	(SC1)

/*Enables or disables support of TCP (Transmission Control Protocol)*/
#define TcpIpTcpEnabled			(TRUE)

/*Maximum number of TCP sockets*/
#define TcpIpTcpSocketMax		(2)

/*Enables or disables support of UDP (User Datagram Protocol)*/
#define TcpIpUdpEnabled			(FALSE)

/*Maximum number of UDP sockets*/
#define TcpIpUdpSocketMax		(0)

/*If true the TcpIp_GetVersionInfo API is available*/
#define TcpIpVersionInfoApi		(FALSE)
/**=====================================================**/

/**=====================================================**/
/** TcpIpSocketOwner Container **/
/*This parameter specifies the type of the upper layer module*/
#define TcpIpSocketOwnerUpperLayerType	SOAD
/**=====================================================**/

/**=====================================================**/
/** TcpIpIpV4General Container **/
#define TcpIpIpV4Enabled		(TRUE)
/**=====================================================**/

/**=====================================================**/
/** TcpIpIpV6General Container **/
#define TcpIpIpV6Enabled		(FALSE)
/**=====================================================**/


/**=====================================================**/
/** TcpIpTcpConfig Container **/
/*The maximal time an acknowledgment is delayed for transmission in seconds.*/
#define TcpIpDelayedAckTimeout		(0.5)	//Range [0 .. 0.5], Default [0.5]

/*Enables or disables support of TCP congestion avoidance algorithm*/
#define TcpIpTcpCongestionAvoidanceEnabled	(TRUE)

/*Enables or disables support of TCP Fast Recovery */
#define TcpIpTcpFastRecoveryEnabled			(FALSE)

/*Enables or disables support of TCP Fast Retransmission*/
#define TcpIpTcpFastRetransmitEnabled		(FALSE)

/*Timeout in [s] to receive a FIN from the remote node (after this node has initiated connection termination)*/
#define TcpIpTcpFinWait2Timeout				(0)	//Range [0 .. INF]

/*Maximum Segment size*/			//kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk
#define TcpIpMaxSegmentSize					(1500)

/*Maximum number of times that a TCP segment is retransmitted before the TCP
connection is closed.This parameter also applies for FIN retransmissions*/
#define TcpIpTcpMaxRtx						(0)	//Range [0 .. 255]

/*Maximum segment lifetime in [s]. */
#define TcpIpTcpMsl							(0)	//Range [0 .. INF]

/*Enables or disables support of Nagle’s algorithm*/
#define TcpIpTcpNagleEnabled				(TRUE)

/*Default value of maximum receive window in bytes*/
#define TcpIpTcpReceiveWindowMax			(0)	//Range [0 .. 65535]

/*Timeout in [s] before an unacknowledged TCP segment is sent again. If the timeout is disabled or set to INF,no TCP segments shall be retransmitted. */
#define TcpIpTcpRetransmissionTimeout		(0)	//Range [0.001 .. INF]

/*Enables or disables support of TCP slow start algorithm */
#define TcpIpTcpSlowStartEnabled			(TRUE)

/*Maximum number of times that a TCP SYN is retransmitted. Note: SYN will be retried after TcpIpTcpRetransmissionTimeout. The connection will be dropped if no matching connection request has been received after the last TCP SYN has been sent and TcpIp TcpRetransmissionTimeout has been expired.*/
#define TcpIpTcpSynMaxRtx					(0)	//Range [0 .. 255]

/*Timeout in [s] to complete a remotely initiated TCP connection establishment, i.e.maximum time waiting in SYN-RECEIVED for a confirming connection request
acknowledgment after having both received and sent a connection request.*/
#define TcpIpTcpSynReceivedTimeout			(0)	//Range [0 .. INF]
/**=====================================================**/

#endif
