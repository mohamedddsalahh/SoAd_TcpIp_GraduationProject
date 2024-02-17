#include "SoAd.h"


SoAd_ConfigType SoAdConfigPtr = {
		.SoAd_SockConnGroup =
		{
				{
						.SoAdSocketLocalPort = 10,
						.SoAdSocketLocalAddressRef = {
								.TcpIpAddressType_t = 0,
								.TcpIpAddrId = 0,
								.TcpIpDomainType_t = 0,
								.TcpIpStaticIpAddressConfig_t = {0,0,0}
						},
						.SoAd_SocketConnection = {
								.SoAdSocketId = 0,
								.SoAd_SocketRemoteAddress = {
										.Domain = TCPIP_AF_INET,
										.SoAdSocketRemotePort = 80,
										.SoAdSocketRemoteIpAddress = {1,1,1,1}
								}
						},
						.SoAd_SocketProtocol = {
								.SoAd_SocketTcpConfig = {
										.SoAdSocketTcpImmediateTpTxConfirmation = FALSE,
										.SoAdSocketTcpInitiate = TRUE,
										.SoAdSocketTcpKeepAlive = FALSE,
										.SoAdSocketTcpKeepAliveTime = 0,
										.SoAdSocketTcpRetransmissionTimeout = 0
								}
						}
				}
		}
};
