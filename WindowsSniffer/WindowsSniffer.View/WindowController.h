#pragma once

#include <Windows.h>
#include <CommCtrl.h>
#include <RichEdit.h>

namespace WindowsSnifferView
{
	typedef enum _ELEMENT_ID
	{
		START_BUTTON,
		STOP_BUTTON,
		FILENAME_TITLE,
		IP_TITLE,
		FILENAME_EDIT,
		IP_EDIT,
		OUTPUT_RICHTEXT
	} ELEMENT_ID;

	class WindowController
	{
	public:
		WindowController(HWND hWnd);
		LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);
	protected:
		HWND m_hWnd;

		SIZE m_sButtonSize;
		SIZE m_sTitleSize;
		SIZE m_sEditSize;
		SIZE m_sRichTextSize;

		LONG m_lDefaultElementHeight;
		LONG m_lDefaultElementInterval;
		LONG m_lTotalWindowWidth;

		VOID InitializeSizes();
		VOID CreateElements();
		VOID CreateButtons();
		VOID CreateTitles();
		VOID CreateEdits();
		VOID CreateRichtext();

		VOID SetSniffingState(BOOL bIsSniffing);
	};
}
