#pragma once

#include <stdexcept>
#include <ws2tcpip.h>
#include <mstcpip.h>
#include "Sniffer.h"

namespace WindowsSniffer
{
	Sniffer::Sniffer(PACKET_PROCESS_CALLBACK ppcCallback, LPCSTR lpsIp)
		: m_ppcCallback(ppcCallback), m_lIsRunning(FALSE), m_hProcessThread(NULL)
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

	Sniffer::~Sniffer()
	{
		if (m_lIsRunning)
		{
			try
			{
				Stop();
			}
			catch (std::logic_error *ex)
			{
				delete ex;
			}
		}

		closesocket(m_sListenSocket);
		WSACleanup();
	}

	VOID Sniffer::Start(LPVOID lpArgument)
	{
		if (!InterlockedCompareExchange(&m_lIsRunning, TRUE, FALSE))
		{
			PacketProcessRoutineArgument *ppraArgument = new PacketProcessRoutineArgument(m_sListenSocket, &m_lIsRunning, m_ppcCallback, lpArgument);
			m_hProcessThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PacketProcessRoutine, ppraArgument, 0, NULL);

			if (m_hProcessThread == NULL)
			{
				delete ppraArgument;
				throw new std::runtime_error("Error creating thread");
			}
		}
		else
		{
			throw new std::logic_error("Already running");
		}
	}

	VOID Sniffer::Stop()
	{
		Stop(INFINITE);
	}

	VOID Sniffer::Stop(DWORD dwWaitTime)
	{
		if (InterlockedCompareExchange(&m_lIsRunning, FALSE, TRUE))
		{
			if (WaitForSingleObject(m_hProcessThread, dwWaitTime) == WAIT_TIMEOUT)
			{
				TerminateThread(m_hProcessThread, 1);
			}
			CloseHandle(m_hProcessThread);
		}
		else
		{
			throw new std::logic_error("Nothing to stop");
		}
	}

	DWORD WINAPI Sniffer::PacketProcessRoutine(PacketProcessRoutineArgument *lpInstance)
	{
		LONG *plIsRunning = lpInstance->GetIsRunningPtr();
		SOCKET sListenSocket = lpInstance->GetSocket();
		PACKET_PROCESS_CALLBACK ppcUserCallback = lpInstance->GetUserCallback();
		LPVOID lpUserArgument = lpInstance->GetUserArgument();
		BYTE *pbIpPacket = (BYTE *)calloc(MAX_IP_PACKET_LENGTH, sizeof(BYTE));

		while (*plIsRunning)
		{
			if (recv(sListenSocket, (char *)pbIpPacket, MAX_IP_PACKET_LENGTH, 0) != SOCKET_ERROR)
			{
				ppcUserCallback((IP_HEADER *)pbIpPacket, MAX_IP_PACKET_LENGTH, lpUserArgument);
			}
		}

		delete lpInstance;
		return 0;
	}
}
