#pragma once

#include <stdexcept>
#include <ws2tcpip.h>
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

		if (inet_pton(AF_INET, lpsIp, &m_iaIp) != 1)
		{
			throw new std::invalid_argument("lpsIp");
		}
	}
}
