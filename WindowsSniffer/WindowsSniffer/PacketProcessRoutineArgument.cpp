#include "PacketProcessRoutineArgument.h"
#include <stdexcept>

namespace WindowsSniffer
{
	PacketProcessRoutineArgument::PacketProcessRoutineArgument(SOCKET sListenSocket, LONG *plIsRunning, PACKET_PROCESS_CALLBACK ppcUserCallback, LPVOID lpUserArgument)
		: m_sListenSocket(sListenSocket), m_plIsRunning(plIsRunning), m_ppcUserCallback(ppcUserCallback), m_lpUserArgument(lpUserArgument)
	{
		if (plIsRunning == NULL)
		{
			throw new std::invalid_argument("plIsRunning");
		}
		if (ppcUserCallback == NULL)
		{
			throw new std::invalid_argument("ppcUserCallback");
		}
	}

	LONG *PacketProcessRoutineArgument::GetIsRunningPtr()
	{
		return m_plIsRunning;
	}

	SOCKET PacketProcessRoutineArgument::GetSocket()
	{
		return m_sListenSocket;
	}

	PACKET_PROCESS_CALLBACK PacketProcessRoutineArgument::GetUserCallback()
	{
		return m_ppcUserCallback;
	}

	LPVOID PacketProcessRoutineArgument::GetUserArgument()
	{
		return m_lpUserArgument;
	}
}
