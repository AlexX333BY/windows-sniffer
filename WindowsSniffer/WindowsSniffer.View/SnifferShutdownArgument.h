#pragma once

#include "..\WindowsSniffer\Sniffer.h"
#include "PacketProcessDelegateArgument.h"
#include "typedefs.h"

namespace WindowsSnifferView
{
	class SnifferShutdownArgument
	{
	public:
		SnifferShutdownArgument(WindowsSniffer::Sniffer *sSniffer, HWND hWnd, SET_SNIFFING_STATE_CALLBACK callback,
			HANDLE hFile, PacketProcessDelegateArgument *ppdaArgument);
		WindowsSniffer::Sniffer *GetSniffer();
		HWND GetHwnd();
		SET_SNIFFING_STATE_CALLBACK GetCallback();
		HANDLE GetFile();
		PacketProcessDelegateArgument *GetArgument();
	protected:
		WindowsSniffer::Sniffer *m_sSniffer;
		HWND m_hWnd;
		SET_SNIFFING_STATE_CALLBACK m_callback;
		HANDLE m_hFile;
		PacketProcessDelegateArgument *m_ppdaArgument;
	};
}
