#include <WS2tcpip.h>
#include "IpPacketProcessor.h"
#include <stdio.h>

namespace WindowsSnifferView
{
	LPSTR IpPacketProcessor::GetIpPacketStringRepresentation(WindowsSniffer::IP_HEADER *ipPacket)
	{
		CONST size_t sIpLen = 15;
		CONST size_t sBufferLen = 127;
		LPSTR lpsResult = (LPSTR)calloc(sBufferLen + 1, sizeof(CHAR));
		IN_ADDR iaAddress;

		LPSTR lpsSource = (LPSTR)calloc(sIpLen + 1, sizeof(CHAR)), lpsDest = (LPSTR)calloc(sIpLen + 1, sizeof(CHAR));
		iaAddress.S_un.S_addr = ipPacket->dwSourceIpAddress;
		inet_ntop(AF_INET, &iaAddress, lpsSource, sIpLen + 1);
		iaAddress.S_un.S_addr = ipPacket->dwDestinationIpAddress;
		inet_ntop(AF_INET, &iaAddress, lpsDest, sIpLen + 1);

		sprintf_s(lpsResult, sBufferLen, "Source: %-15s Destination: %-15s\nTTL: %-3d Length: %-5d Protocol: %s",
			lpsSource, lpsDest, ipPacket->bTimeToLive, ipPacket->wTotalLength, GetIpPacketProtocolStringRepresentation(ipPacket->bProtocol));

		free(lpsSource);
		free(lpsDest);
		return (LPSTR)realloc(lpsResult, (lstrlen(lpsResult) + 1) * sizeof(CHAR));
	}

	LPCSTR IpPacketProcessor::GetIpPacketProtocolStringRepresentation(BYTE bProtocol)
	{
		switch (bProtocol)
		{
		case ICMP:
			return "ICMP";
		case TCP:
			return "TCP";
		case NVPII:
			return "NVP-II";
		case UDP:
			return "UDP";
		default:
			return "UNKNOWN";
		}
	}
}
