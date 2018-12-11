#pragma once

#include <Windows.h>
#include <queue>
#include "PacketProcessRoutineArgument.h"
#include "typedefs.h"

namespace WindowsSniffer
{
	class Sniffer
	{
	public:
		Sniffer(PACKET_PROCESS_CALLBACK ppcCallback, LPCSTR lpsIp);
		~Sniffer();
		VOID Start(LPVOID lpArgument);
		VOID Stop();
		VOID Stop(DWORD dwWaitTime);
	protected:
		PACKET_PROCESS_CALLBACK m_ppcCallback;
		LONG m_lIsRunning;
		HANDLE m_hProcessThread;
		SOCKET m_sListenSocket;

		static DWORD WINAPI PacketProcessRoutine(PacketProcessRoutineArgument *lpInstance);
	};
}
