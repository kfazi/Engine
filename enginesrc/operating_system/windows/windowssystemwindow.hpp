#ifdef WINDOWS

#ifndef ENGINE_WINDOWS_SYSTEM_WINDOW_HPP
#define ENGINE_WINDOWS_SYSTEM_WINDOW_HPP

#include <Windows.h>
#undef ERROR
#include "../systemwindow.hpp"

namespace engine
{

class CWindowsSystemWindow: public CSystemWindow
{
	friend class CWindowsSystemDisplay;

	private:
		HWND m_pHWND;
		wchar_t *m_pClassName;

		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	protected:
		CWindowsSystemWindow(int iX, int iY, unsigned int iWidth, unsigned int iHeight, const CString &cCaption, bool bCaptionBar, bool bCloseButton, bool bMaximalizeButton, bool bMinimalizeButton);
		virtual ~CWindowsSystemWindow();
		virtual void ProcessEvents();

	public:
		virtual void Show();
		virtual void Hide();
};

}

#endif /* ENGINE_WINDOWS_SYSTEM_WINDOW_HPP */

#endif /* WINDOWS */

/* EOF */
