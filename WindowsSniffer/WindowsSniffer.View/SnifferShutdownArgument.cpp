#include "SnifferShutdownArgument.h"
#include <stdexcept>

namespace WindowsSnifferView
{
	SnifferShutdownArgument::SnifferShutdownArgument(WindowsSniffer::Sniffer *sSniffer, HWND hWnd, SET_SNIFFING_STATE_CALLBACK callback,
		HANDLE hFile, PacketProcessDelegateArgument *ppdaArgument)
		: m_sSniffer(sSniffer), m_hWnd(hWnd), m_callback(callback), m_hFile(hFile), m_ppdaArgument(ppdaArgument)
	{
		if (sSniffer == NULL)
		{
			throw new std::invalid_argument("sSniffer");
		}
		if (callback == NULL)
		{
			throw new std::invalid_argument("callback");
		}
		if (hWnd == NULL)
		{
			throw new std::invalid_argument("hWnd");
		}
	}

	PacketProcessDelegateArgument *SnifferShutdownArgument::GetArgument()
	{
		return m_ppdaArgument;
	}

	SET_SNIFFING_STATE_CALLBACK SnifferShutdownArgument::GetCallback()
	{
		return m_callback;
	}

	HANDLE SnifferShutdownArgument::GetFile()
	{
		return m_hFile;
	}

	HWND SnifferShutdownArgument::GetHwnd()
	{
		return m_hWnd;
	}

	WindowsSniffer::Sniffer *SnifferShutdownArgument::GetSniffer()
	{
		return m_sSniffer;
	}
}
