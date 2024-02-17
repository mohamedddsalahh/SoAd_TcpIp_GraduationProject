#include "TcpIp.h"

TcpIp_SocketType socket_list[TcpIpTcpSocketMax] = {0};
TcpIp_LocalAddr TcpIpLocalAddr_list[2] = { 0};

//Tcp ip buffer (should probably be protected by mutex by os as it says acquire buffer in seq diagram).
TcpIp_Buffer TcpIpBuffer[TcpIpTcpSocketMax];

TcpIp_ConfigType TcpIpTcpConfig = {};
