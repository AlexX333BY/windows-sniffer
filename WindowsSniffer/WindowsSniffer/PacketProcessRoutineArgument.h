#pragma once

#include <Windows.h>
#include "typedefs.h"

namespace WindowsSniffer
{
	class PacketProcessRoutineArgument
	{
	public:
		PacketProcessRoutineArgument(SOCKET sListenSocket, LONG *plIsRunning, PACKET_PROCESS_CALLBACK ppcUserCallback, LPVOID lpUserArgument);
		SOCKET GetSocket();
		LONG *GetIsRunningPtr();
		PACKET_PROCESS_CALLBACK GetUserCallback();
		LPVOID GetUserArgument();
	protected:
		CONST SOCKET m_sListenSocket;
		LONG *m_plIsRunning;
		CONST PACKET_PROCESS_CALLBACK m_ppcUserCallback;
		CONST LPVOID m_lpUserArgument;
	};
}
