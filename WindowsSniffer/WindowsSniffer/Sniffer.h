#pragma once

#include <Windows.h>
#include <queue>

namespace WindowsSniffer
{
	typedef void (PACKET_PROCESS_CALLBACK)(LPVOID lpSniffedData, DWORD dwByteCount);

	class Sniffer
	{
	public:
		Sniffer(PACKET_PROCESS_CALLBACK ppcCallback);
		Sniffer(PACKET_PROCESS_CALLBACK ppcCallback, LPCSTR lpsIpAddress);
		~Sniffer();
		BOOL Start();
		BOOL Stop();
		BOOL Stop(DWORD dwWaitTime);
	protected:
		static LPCSTR GetLocalIp();
	};
}
