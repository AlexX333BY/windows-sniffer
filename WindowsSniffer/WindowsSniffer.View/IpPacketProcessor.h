#pragma once

#include "..\WindowsSniffer\typedefs.h"
#include <Windows.h>

namespace WindowsSnifferView
{
	class IpPacketProcessor
	{
	public:
		static LPSTR GetIpPacketStringRepresentation(WindowsSniffer::IP_HEADER *ipPacket);
	};
}
