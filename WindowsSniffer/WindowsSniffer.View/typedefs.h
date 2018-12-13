#pragma once

#include <Windows.h>

namespace WindowsSnifferView
{
	typedef VOID(*SET_SNIFFING_STATE_CALLBACK)(HWND hWnd, BOOL bIsSniffing);
}
