#pragma once

#include <Windows.h>

namespace WindowsSniffer
{
	class PacketProcessRoutineArgument
	{
	public:
		PacketProcessRoutineArgument(SOCKET sListenSocket, volatile LONG *plIsRunning, LPVOID lpUserArgument);
		SOCKET GetSocket();
		volatile LONG *GetIsRunningPtr();
		LPVOID GetUserArgument();
	protected:
		CONST SOCKET m_sListenSocket;
		volatile LONG *m_plIsRunning;
		CONST LPVOID m_lpUserArgument;
	};
}
