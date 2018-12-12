#include "WindowProcessor.h"

namespace WindowsSnifferView
{
	LONG WindowProcessor::GetWindowFontHeight(HWND hWnd)
	{
		HDC hWndDC = GetDC(hWnd);
		TEXTMETRIC tmTextMetric;
		GetTextMetrics(hWndDC, &tmTextMetric);
		ReleaseDC(hWnd, hWndDC);
		return tmTextMetric.tmHeight;
	}

	SIZE WindowProcessor::GetWindowRectSize(HWND hWnd)
	{
		RECT rWndRect;
		GetClientRect(hWnd, &rWndRect);
		SIZE sWndSize;
		sWndSize.cx = rWndRect.right - rWndRect.left;
		sWndSize.cy = rWndRect.bottom - rWndRect.top;
		return sWndSize;
	}

	SIZE WindowProcessor::GetWindowSize(HWND hWnd)
	{
		RECT rWndRect;
		GetWindowRect(hWnd, &rWndRect);
		SIZE sWndSize;
		sWndSize.cx = rWndRect.right - rWndRect.left;
		sWndSize.cy = rWndRect.bottom - rWndRect.top;
		return sWndSize;
	}

	COLORREF WindowProcessor::GetDefaultBackgroundColor()
	{
		return GetSysColor(COLOR_WINDOW);
	}
}
