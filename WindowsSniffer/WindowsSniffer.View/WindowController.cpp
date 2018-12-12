#include "WindowController.h"

namespace WindowsSnifferView
{
	WindowController::WindowController(HWND hWnd)
		: m_hWnd(hWnd)
	{ }

	LRESULT WindowController::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProc(m_hWnd, message, wParam, lParam);
	}
}
