#pragma once

#include <Windows.h>

namespace WindowsSnifferView
{
	class PacketProcessDelegateArgument
	{
	public:
		PacketProcessDelegateArgument(HWND hWnd, HANDLE hFile);
		HWND GetHwnd();
		HANDLE GetHfile();
	protected:
		HWND m_hWnd;
		HANDLE m_hFile;
	};
}
