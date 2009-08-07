#include "systemwindow.hpp"

namespace engine
{

CSystemWindow::CSystemWindow(const CString &cCaption, bool bCaptionBar, bool bCloseButton, bool bMaximalizeButton, bool bMinimalizeButton)
{
}

CSystemWindow::~CSystemWindow()
{
}

bool CSystemWindow::OnClose()
{
	if (m_pOnCloseFunctor)
		return m_pOnCloseFunctor();
	return true;
}

bool CSystemWindow::OnMinimalize()
{
	if (m_pOnMinimalizeFunctor)
		return m_pOnMinimalizeFunctor();
	return true;
}

bool CSystemWindow::OnMaximalize()
{
	if (m_pOnMaximalizeFunctor)
		return m_pOnMaximalizeFunctor();
	return true;
}

void CSystemWindow::Show()
{
	m_bVisible = true;
}

void CSystemWindow::Hide()
{
	m_bVisible = false;
}

void CSystemWindow::SetVisible(bool bVisible)
{
	if (bVisible)
		Show();
	else
		Hide();
}

bool CSystemWindow::GetVisible() const
{
	return m_bVisible;
}

}

/* EOF */
