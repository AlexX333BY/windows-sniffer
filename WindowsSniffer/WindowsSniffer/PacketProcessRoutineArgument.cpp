#include "PacketProcessRoutineArgument.h"
#include <stdexcept>

namespace WindowsSniffer
{
	PacketProcessRoutineArgument::PacketProcessRoutineArgument(SOCKET sListenSocket, LPBOOL lpbIsRunning)
		: m_sListenSocket(sListenSocket), m_lpbIsRunning(lpbIsRunning)
	{
		if (lpbIsRunning == NULL)
		{
			throw new std::invalid_argument("lpTask");
		}
	}

	LPBOOL PacketProcessRoutineArgument::GetIsRunningPtr()
	{
		return m_lpbIsRunning;
	}

	SOCKET PacketProcessRoutineArgument::GetSocket()
	{
		return m_sListenSocket;
	}
}
