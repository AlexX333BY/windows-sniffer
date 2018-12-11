#pragma once

#include <stdexcept>
#include <ws2tcpip.h>
#include <mstcpip.h>
#include "Sniffer.h"

namespace WindowsSniffer
{
	Sniffer::Sniffer(PACKET_PROCESS_CALLBACK ppcCallback, LPCSTR lpsIp)
		: m_ppcCallback(ppcCallback), m_bIsRunning(FALSE), m_hProcessThread(NULL)
	{
		if (ppcCallback == NULL)
		{
			throw new std::out_of_range("ppcCallback");
		}

		IN_ADDR iaIp;
		if (inet_pton(AF_INET, lpsIp, &iaIp) != 1)
		{
			throw new std::invalid_argument("lpsIp");
		}

		WSADATA wdData;
		if (WSAStartup(MAKEWORD(2, 2), &wdData) != 0)
		{
			throw new std::runtime_error("Socket init error");
		}

		m_sListenSocket = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
		if (m_sListenSocket == INVALID_SOCKET)
		{
			WSACleanup();
			throw new std::runtime_error("Error creating socket");
		}

		SOCKADDR_IN siAddress;
		siAddress.sin_addr = iaIp;
		siAddress.sin_family = AF_INET;
		siAddress.sin_port = 0;

		if (bind(m_sListenSocket, (sockaddr *)&siAddress, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
		{
			closesocket(m_sListenSocket);
			WSACleanup();
			throw new std::runtime_error("Error binding socket");
		}

		u_long ulArg = RCVALL_ON;
		if (ioctlsocket(m_sListenSocket, SIO_RCVALL, &ulArg) == SOCKET_ERROR)
		{
			closesocket(m_sListenSocket);
			WSACleanup();
			throw new std::runtime_error("Error setting promiscuous mode");
		}
	}
}
