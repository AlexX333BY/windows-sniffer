#pragma once

#include <Windows.h>
#include <queue>
#include "PacketProcessRoutineArgument.h"

namespace WindowsSniffer
{
	typedef void (*PACKET_PROCESS_CALLBACK)(LPVOID lpSniffedData, DWORD dwByteCount);

	class Sniffer
	{
	public:
		Sniffer(PACKET_PROCESS_CALLBACK ppcCallback, LPCSTR lpsIp);
		~Sniffer();
		BOOL Start();
		BOOL Stop();
		BOOL Stop(DWORD dwWaitTime);
	protected:
		PACKET_PROCESS_CALLBACK m_ppcCallback;
		volatile BOOL m_bIsRunning;
		HANDLE m_hProcessThread;
		SOCKET m_sListenSocket;

		static DWORD WINAPI PacketProcessRoutine(PacketProcessRoutineArgument *lpInstance);
	};
}
