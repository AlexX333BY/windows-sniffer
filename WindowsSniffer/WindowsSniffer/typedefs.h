#pragma once

namespace WindowsSniffer
{
	CONST BYTE MAX_OPTIONS_LENGTH = 4 * 4;
	CONST WORD MAX_IP_PACKET_LENGTH = 65535;

	typedef struct _IP_HEADER
	{
		BYTE bVersionIhl;
		BYTE bDscpEcn;
		WORD wTotalLength;
		WORD wIdentification;
		WORD wFlagsFragmentOffset;
		BYTE bTimeToLive;
		BYTE bProtocol;
		WORD wHeaderChecksum;
		DWORD dwSourceIpAddress;
		DWORD dwDestinationIpAddress;
		BYTE abOptions[MAX_OPTIONS_LENGTH];
	} IP_HEADER;

	typedef void(*PACKET_PROCESS_CALLBACK)(IP_HEADER *lpSniffedData, DWORD dwByteCount, LPVOID lpUserArgument);
}
