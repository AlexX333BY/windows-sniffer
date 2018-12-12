#include "WindowController.h"
#include "WindowProcessor.h"

namespace WindowsSnifferView
{
	WindowController::WindowController(HWND hWnd)
		: m_hWnd(hWnd)
	{ }

	VOID WindowController::CreateButtons()
	{
		CreateWindow(WC_BUTTON, "Start",
			WS_VISIBLE | WS_CHILD,
			m_lDefaultElementInterval, m_lDefaultElementInterval, m_sButtonSize.cx, m_sButtonSize.cy,
			m_hWnd, (HMENU)START_BUTTON, NULL, NULL);
		CreateWindow(WC_BUTTON, "Stop",
			WS_VISIBLE | WS_CHILD,
			m_lDefaultElementInterval, m_lDefaultElementInterval * 2 + m_sButtonSize.cy, m_sButtonSize.cx, m_sButtonSize.cy,
			m_hWnd, (HMENU)STOP_BUTTON, NULL, NULL);

	}
	VOID WindowController::CreateTitles()
	{
		CreateWindow(WC_STATIC, "Output file name:",
			WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
			m_sButtonSize.cx + 2 * m_lDefaultElementInterval, m_lDefaultElementInterval, m_sTitleSize.cx, m_sTitleSize.cy,
			m_hWnd, (HMENU)FILENAME_TITLE, NULL, NULL);
		CreateWindow(WC_STATIC, "IP address:",
			WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
			m_sButtonSize.cx + 2 * m_lDefaultElementInterval, m_sTitleSize.cy + 2 * m_lDefaultElementInterval, m_sTitleSize.cx, m_sTitleSize.cy,
			m_hWnd, (HMENU)IP_TITLE, NULL, NULL);
	}

	VOID WindowController::CreateEdits()
	{
		CreateWindow(WC_EDIT, "", WS_VISIBLE | WS_CHILD | WS_BORDER,
			m_sButtonSize.cx + m_sTitleSize.cx + 3 * m_lDefaultElementInterval, m_lDefaultElementInterval, m_sEditSize.cx, m_sEditSize.cy,
			m_hWnd, (HMENU)FILENAME_EDIT, NULL, NULL);
		CreateWindow(WC_IPADDRESS, "", WS_VISIBLE | WS_CHILD | WS_BORDER,
			m_sButtonSize.cx + m_sTitleSize.cx + 3 * m_lDefaultElementInterval, m_sEditSize.cy + 2 * m_lDefaultElementInterval, m_sEditSize.cx, m_sEditSize.cy,
			m_hWnd, (HMENU)IP_EDIT, NULL, NULL);
	}

	VOID WindowController::CreateRichtext()
	{
		LoadLibrary("Riched20.dll");
		CreateWindow(RICHEDIT_CLASS, "", ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_READONLY,
			m_lDefaultElementInterval, 2 * m_lDefaultElementHeight + 3 * m_lDefaultElementInterval,
			m_sRichTextSize.cx, m_sRichTextSize.cy, m_hWnd, (HMENU)OUTPUT_RICHTEXT, NULL, NULL);
	}

	VOID WindowController::CreateElements()
	{
		CreateButtons();
		CreateTitles();
		CreateEdits();
		CreateRichtext();
	}

	VOID WindowController::InitializeSizes()
	{
		SIZE sWindowSize = WindowProcessor::GetWindowSize(m_hWnd);
		SIZE sWindowRectSize = WindowProcessor::GetWindowRectSize(m_hWnd);

		m_lDefaultElementInterval = WindowProcessor::GetWindowFontHeight(m_hWnd);
		m_lDefaultElementHeight = (LONG)(m_lDefaultElementInterval * 1.5);
		m_sButtonSize.cx = 64;
		m_sButtonSize.cy = m_lDefaultElementHeight;
		m_sTitleSize.cx = 128;
		m_sTitleSize.cy = m_lDefaultElementHeight;
		m_sEditSize.cx = 256;
		m_sEditSize.cy = m_lDefaultElementHeight;
		m_lTotalWindowWidth = sWindowSize.cx - sWindowRectSize.cx 
			+ m_sButtonSize.cx + m_sTitleSize.cx + m_sEditSize.cx + 4 * m_lDefaultElementInterval;
		m_sRichTextSize.cx = m_lTotalWindowWidth - 3 * m_lDefaultElementInterval;
		m_sRichTextSize.cy = sWindowRectSize.cy - 2 * m_lDefaultElementHeight - 4 * m_lDefaultElementInterval;
	}

	VOID WindowController::SetSniffingState(BOOL bIsSniffing)
	{
		EnableWindow(GetDlgItem(m_hWnd, START_BUTTON), !bIsSniffing);
		EnableWindow(GetDlgItem(m_hWnd, STOP_BUTTON), bIsSniffing);
		EnableWindow(GetDlgItem(m_hWnd, FILENAME_EDIT), !bIsSniffing);
		EnableWindow(GetDlgItem(m_hWnd, IP_EDIT), !bIsSniffing);
	}

	LRESULT WindowController::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_CREATE:
			InitializeSizes();
			SetWindowPos(m_hWnd, HWND_TOP, CW_USEDEFAULT, CW_USEDEFAULT, 
				m_lTotalWindowWidth, WindowProcessor::GetWindowSize(m_hWnd).cy, SWP_NOMOVE);
			CreateElements();
			SetSniffingState(FALSE);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}

		return DefWindowProc(m_hWnd, message, wParam, lParam);
	}
}
