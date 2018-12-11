#include "PacketProcessRoutineArgument.h"
#include <stdexcept>

namespace WindowsSniffer
{
	PacketProcessRoutineArgument::PacketProcessRoutineArgument(SOCKET sListenSocket, volatile LONG *plIsRunning, LPVOID lpUserArgument)
		: m_sListenSocket(sListenSocket), m_plIsRunning(plIsRunning), m_lpUserArgument(lpUserArgument)
	{
		if (plIsRunning == NULL)
		{
			throw new std::invalid_argument("plIsRunning");
		}
	}

	volatile LONG *PacketProcessRoutineArgument::GetIsRunningPtr()
	{
		return m_plIsRunning;
	}

	SOCKET PacketProcessRoutineArgument::GetSocket()
	{
		return m_sListenSocket;
	}

	LPVOID PacketProcessRoutineArgument::GetUserArgument()
	{
		return m_lpUserArgument;
	}
}
