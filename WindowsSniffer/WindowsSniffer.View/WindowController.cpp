#include "WindowController.h"
#include "WindowProcessor.h"
#include "IpPacketProcessor.h"
#include "..\WindowsSniffer\typedefs.h"

namespace WindowsSnifferView
{
	WindowController::WindowController(HWND hWnd)
		: m_hWnd(hWnd), m_sSniffer(NULL), m_hFileHandle(NULL), m_ppdaArgument(NULL)
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
		CreateWindow(RICHEDIT_CLASS, "", ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_READONLY | ES_AUTOVSCROLL,
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
		SetSniffingState(m_hWnd, bIsSniffing);
	}

	VOID WindowController::SetSniffingState(HWND hWnd, BOOL bIsSniffing)
	{
		EnableWindow(GetDlgItem(hWnd, START_BUTTON), !bIsSniffing);
		EnableWindow(GetDlgItem(hWnd, STOP_BUTTON), bIsSniffing);
		EnableWindow(GetDlgItem(hWnd, FILENAME_EDIT), !bIsSniffing);
		EnableWindow(GetDlgItem(hWnd, IP_EDIT), !bIsSniffing);
	}

	LRESULT WindowController::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam)
	{
		CONST int iIpLenght = 15;
		LPSTR lpsIp;
		HANDLE hShutdownThread;
		SnifferShutdownArgument *ssaArgument;

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
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case START_BUTTON:
				lpsIp = (LPSTR)calloc(iIpLenght + 1, sizeof(CHAR));
				SetSniffingState(TRUE);
				GetWindowText(GetDlgItem(m_hWnd, IP_EDIT), lpsIp, iIpLenght);
				try
				{
					m_sSniffer = new WindowsSniffer::Sniffer((WindowsSniffer::PACKET_PROCESS_CALLBACK)PacketProcessDelegate, lpsIp);
					LPSTR lpsFilename = (LPSTR)calloc(MAX_PATH, sizeof(CHAR));
					GetWindowText(GetDlgItem(m_hWnd, FILENAME_EDIT), lpsFilename, MAX_PATH - 1);
					m_hFileHandle = CreateFile(lpsFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
					if (m_hFileHandle != INVALID_HANDLE_VALUE)
					{
						m_ppdaArgument = new PacketProcessDelegateArgument(m_hWnd, m_hFileHandle);
						m_sSniffer->Start(m_ppdaArgument);
					}
					else
					{
						m_hFileHandle = NULL;
					}
					free(lpsFilename);
				}
				catch (std::runtime_error *ex)
				{
					delete ex;
					MessageBox(m_hWnd, "Error creating socket with specified IP", "Error", MB_OK | MB_ICONERROR);
					SetSniffingState(FALSE);
				}
				catch (std::invalid_argument *ex)
				{
					delete ex;
					MessageBox(m_hWnd, "Invalid IP", "Error", MB_OK | MB_ICONERROR);
					SetSniffingState(FALSE);
				}

				free(lpsIp);
				break;
			case STOP_BUTTON:
				ssaArgument = new SnifferShutdownArgument(m_sSniffer, m_hWnd, SetSniffingState, m_hFileHandle, m_ppdaArgument);
				hShutdownThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SnifferShutdownCallback, ssaArgument, 0, NULL);
				if (hShutdownThread == NULL)
				{
					MessageBox(m_hWnd, "Error stopping sniffer", "Error", MB_OK | MB_ICONERROR);
				}
				else
				{
					CloseHandle(hShutdownThread);
				}
				break;
			}
			break;
		}

		return DefWindowProc(m_hWnd, message, wParam, lParam);
	}

	DWORD WINAPI WindowController::PacketProcessDelegate(WindowsSniffer::IP_HEADER *lpSniffedData, 
		DWORD dwByteCount, PacketProcessDelegateArgument *ppdaArgument)
	{
		HWND hRichEdit = GetDlgItem(ppdaArgument->GetHwnd(), OUTPUT_RICHTEXT);
		LPSTR lpsPacketInfo = IpPacketProcessor::GetIpPacketStringRepresentation(lpSniffedData);

		int iTotalTextLength = GetWindowTextLength(hRichEdit) + lstrlen(lpsPacketInfo) + 1;
		LPSTR lpsResultText = (LPSTR)calloc(iTotalTextLength + 1, sizeof(CHAR));
		if (lpsResultText != NULL)
		{
			GetWindowText(hRichEdit, lpsResultText, iTotalTextLength);
			strcat_s(lpsResultText, iTotalTextLength + 1, lpsPacketInfo);
			strcat_s(lpsResultText, iTotalTextLength + 1, "\n");
			SetWindowText(hRichEdit, lpsResultText);
			free(lpsResultText);
		}
		free(lpsPacketInfo);

		HANDLE hFile = ppdaArgument->GetHfile();
		DWORD dwWrittenCount;
		if (hFile != NULL)
		{
			WriteFile(hFile, lpSniffedData, lpSniffedData->wTotalLength, &dwWrittenCount, NULL);
		}
		return ((lpsResultText != NULL) && ((hFile == NULL) || (dwWrittenCount == lpSniffedData->wTotalLength))) ? 0 : 1;
	}

	DWORD WINAPI WindowController::SnifferShutdownCallback(SnifferShutdownArgument *ssaArgument)
	{
		WindowsSniffer::Sniffer *sSniffer = ssaArgument->GetSniffer();
		sSniffer->Stop();
		delete sSniffer;

		HANDLE hFile = ssaArgument->GetFile();
		if (hFile != NULL)
		{
			CloseHandle(hFile);
		}

		PacketProcessDelegateArgument *ppdaArgument = ssaArgument->GetArgument();
		if (ppdaArgument != NULL)
		{
			delete ppdaArgument;
		}

		ssaArgument->GetCallback()(ssaArgument->GetHwnd(), FALSE);

		delete ssaArgument;
		return 0;
	}
}
