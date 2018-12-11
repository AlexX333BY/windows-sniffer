#pragma once

#include <Windows.h>

namespace WindowsSniffer
{
	class PacketProcessRoutineArgument
	{
	public:
		PacketProcessRoutineArgument(SOCKET sListenSocket, LPBOOL lpbIsRunning);
		SOCKET GetSocket();
		LPBOOL GetIsRunningPtr();
	protected:
		CONST SOCKET m_sListenSocket;
		CONST LPBOOL m_lpbIsRunning;
	}
}
