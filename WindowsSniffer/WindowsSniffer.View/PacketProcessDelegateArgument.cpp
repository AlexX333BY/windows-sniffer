#include "PacketProcessDelegateArgument.h"
#include <stdexcept>

namespace WindowsSnifferView
{
	PacketProcessDelegateArgument::PacketProcessDelegateArgument(HWND hWnd, HANDLE hFile)
		: m_hWnd(hWnd), m_hFile(hFile)
	{
		if (hWnd == NULL)
		{
			throw new std::invalid_argument("hWnd");
		}
	}

	HWND PacketProcessDelegateArgument::GetHwnd()
	{
		return m_hWnd;
	}

	HANDLE PacketProcessDelegateArgument::GetHfile()
	{
		return m_hFile;
	}
}
