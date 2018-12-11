#pragma once

#include <Windows.h>
#include <queue>
#include "PacketProcessRoutineArgument.h"

namespace WindowsSniffer
{
	typedef void (PACKET_PROCESS_CALLBACK)(LPVOID lpSniffedData, DWORD dwByteCount);

	class Sniffer
	{
	public:
		Sniffer(PACKET_PROCESS_CALLBACK ppcCallback, LPCSTR lpsIpAddress);
		~Sniffer();
		BOOL Start();
		BOOL Stop();
		BOOL Stop(DWORD dwWaitTime);
	protected:
		volatile BOOL m_bIsRunning;
		HANDLE hProcessThread;

		static DWORD WINAPI PacketProcessRoutine(PacketProcessRoutineArgument *lpInstance);
	};
}
