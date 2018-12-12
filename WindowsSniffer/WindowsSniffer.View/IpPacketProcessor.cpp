#include <WS2tcpip.h>
#include "IpPacketProcessor.h"
#include <stdio.h>

namespace WindowsSnifferView
{
	LPSTR IpPacketProcessor::GetIpPacketStringRepresentation(WindowsSniffer::IP_HEADER *ipPacket)
	{
		CONST size_t sIpLen = 15;
		CONST size_t sBufferLen = 128;
		LPSTR lpsResult = (LPSTR)calloc(sBufferLen + 1, sizeof(CHAR));
		IN_ADDR iaAddress;

		LPSTR lpsSource = (LPSTR)calloc(sIpLen + 1, sizeof(CHAR)), lpsDest = (LPSTR)calloc(sIpLen + 1, sizeof(CHAR));
		iaAddress.S_un.S_addr = ipPacket->dwSourceIpAddress;
		inet_ntop(AF_INET, &iaAddress, lpsSource, sIpLen + 1);
		iaAddress.S_un.S_addr = ipPacket->dwDestinationIpAddress;
		inet_ntop(AF_INET, &iaAddress, lpsDest, sIpLen + 1);

		sprintf_s(lpsResult, sBufferLen, "Source: %s Destination: %s Protocol: %s TTL: %d",
			lpsSource, lpsDest, "TODO", ipPacket->bTimeToLive);

		free(lpsSource);
		free(lpsDest);
		return (LPSTR)realloc(lpsResult, (lstrlen(lpsResult) + 1) * sizeof(CHAR));
	}
}
