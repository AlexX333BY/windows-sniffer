#pragma once

#include "..\WindowsSniffer\typedefs.h"
#include <Windows.h>

namespace WindowsSnifferView
{
	typedef enum _IP_PROTOCOL
	{
		ICMP = 0x01,
		TCP = 0x06,
		NVPII = 0x0B,
		UDP = 0x11
	} IP_PROTOCOL;

	class IpPacketProcessor
	{
	public:
		static LPSTR GetIpPacketStringRepresentation(WindowsSniffer::IP_HEADER *ipPacket);
		static LPCSTR GetIpPacketProtocolStringRepresentation(BYTE bProtocol);
	};
}
