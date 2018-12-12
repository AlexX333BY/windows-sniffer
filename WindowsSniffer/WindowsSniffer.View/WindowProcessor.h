#pragma once

#include <windows.h>

namespace WindowsSnifferView
{
	class WindowProcessor
	{
	public:
		static LONG GetWindowFontHeight(HWND hWnd);
		static SIZE GetWindowSize(HWND hWnd);
		static COLORREF GetDefaultBackgroundColor();
	};
}
