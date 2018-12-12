#pragma once

#include <Windows.h>

namespace WindowsSnifferView
{
	class WindowController
	{
	public:
		WindowController(HWND hWnd);
		LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);
	protected:
		HWND m_hWnd;
	};
}
