#ifdef WINDOWS

#include "windowssystemwindow.hpp"
#include "../../useful.hpp"

namespace engine
{

LRESULT CALLBACK CWindowsSystemWindow::WindowProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	CWindowsSystemWindow *pObject = reinterpret_cast<CWindowsSystemWindow *>(GetWindowLongPtr(hWnd, GWL_USERDATA));
	switch (iMessage)
	{
		case WM_DESTROY:
			return 0;
		case WM_CLOSE:
			if (pObject->OnClose())
				DestroyWindow(pObject->m_sWindowData.pHWND);
			return 0;
		case WM_SYSCOMMAND:
			switch (wParam)
			{
				case SC_MINIMIZE:
					if (pObject->OnMinimalize())
						::ShowWindow(pObject->m_sWindowData.pHWND, SW_MINIMIZE);
					return 0;
				case SC_RESTORE:
					if (pObject->OnRestore())
						::ShowWindow(pObject->m_sWindowData.pHWND, SW_RESTORE);
					return 0;
			}
			break;
		default:
			break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

CWindowsSystemWindow::CWindowsSystemWindow(int iX, int iY, unsigned int iWidth, unsigned int iHeight, const CString &cCaption, bool bCaptionBar, bool bCloseButton, bool bMaximalizeButton, bool bMinimalizeButton): CSystemWindow(iX, iY, iWidth, iHeight, cCaption, bCaptionBar, bCloseButton, bMaximalizeButton, bMinimalizeButton)
{
	WNDCLASSEX sWindowClass;
	HINSTANCE hInstance = ::GetModuleHandle(NULL);
	CString cClassName = (Format("%1%_%2%") % GAME_NAME % this).str();
	m_pClassName = new wchar_t[cClassName.length() + 1];
	::memcpy(m_pClassName, cClassName.ToWCHAR().c_str(), (cClassName.length() + 1) * sizeof(wchar_t));
	sWindowClass.cbSize = sizeof(WNDCLASSEX);
	sWindowClass.style = CS_HREDRAW | CS_VREDRAW;
	sWindowClass.lpfnWndProc = WindowProc;
	sWindowClass.cbClsExtra = 0;
	sWindowClass.cbWndExtra = 0;
	sWindowClass.hInstance = hInstance;
	sWindowClass.hIcon = NULL;
	sWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	sWindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	sWindowClass.lpszMenuName = NULL;
	sWindowClass.lpszClassName = m_pClassName;
	sWindowClass.hIconSm = NULL;
	if (!RegisterClassEx(&sWindowClass))
		Error(Format("Call to RegisterClassEx failed! (%1%)") % GetLastError());
	int iStyle = 0;
	if (bCaptionBar)
	{
		iStyle |= WS_OVERLAPPED | WS_CAPTION;
		if (bCloseButton || bMaximalizeButton || bMinimalizeButton)
			iStyle |= WS_SYSMENU;
		if (bMaximalizeButton)
			iStyle |= WS_MAXIMIZEBOX;
		if (bMinimalizeButton)
			iStyle |= WS_MINIMIZEBOX;
	}
	else
		iStyle |= WS_POPUP;
	m_sWindowData.pHWND = ::CreateWindow(m_pClassName, cCaption.ToWCHAR().c_str(), iStyle, iX, iY, iWidth, iHeight, NULL, NULL, hInstance, NULL);
	if (!m_sWindowData.pHWND)
		Error(Format("Call to CreateWindow failed! (%1%)") % GetLastError());
	if (bCaptionBar && !bCloseButton)
	{
		HMENU hMenu = ::GetSystemMenu(m_sWindowData.pHWND, FALSE);
		::EnableMenuItem(hMenu, SC_CLOSE, MF_GRAYED);
	}
	SetWindowLongPtr(m_sWindowData.pHWND, GWLP_USERDATA, reinterpret_cast<LONG>(this));
	::UpdateWindow(m_sWindowData.pHWND);
}

CWindowsSystemWindow::~CWindowsSystemWindow()
{
	delete [] m_pClassName;
}

void CWindowsSystemWindow::ProcessEvents()
{
	MSG sMessage;
	if (::PeekMessage(&sMessage, m_sWindowData.pHWND, 0, 0, PM_REMOVE))
	{
		::TranslateMessage(&sMessage);
		::DispatchMessage(&sMessage);
	}
}

const SSystemSpecificWindowData *CWindowsSystemWindow::GetSystemSpecificData() const
{
	return &m_sWindowData;
}

void CWindowsSystemWindow::Show()
{
	CSystemWindow::Show();
	::ShowWindow(m_sWindowData.pHWND, true);
	::UpdateWindow(m_sWindowData.pHWND);
}

void CWindowsSystemWindow::Hide()
{
	CSystemWindow::Hide();
	::ShowWindow(m_sWindowData.pHWND, false);
	::UpdateWindow(m_sWindowData.pHWND);
}

}

#endif /* WINDOWS */

/* EOF */
