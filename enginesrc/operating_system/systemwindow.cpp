#include "systemwindow.hpp"

namespace engine
{

CSystemWindow::CSystemWindow(int iX, int iY, unsigned int iWidth, unsigned int iHeight, const CString &cCaption, bool bCaptionBar, bool bCloseButton, bool bMaximalizeButton, bool bMinimalizeButton)
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
		m_bMinimalized = m_pOnMinimalizeFunctor();
	else
		m_bMinimalized = true;
	return m_bMinimalized;
}

bool CSystemWindow::OnRestore()
{
	if (m_pOnRestoreFunctor)
		m_bMinimalized = !m_pOnRestoreFunctor();
	else
		m_bMinimalized = false;
	return !m_bMinimalized;
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

bool CSystemWindow::IsMinimalized() const
{
	return m_bMinimalized;
}

}

/* EOF */
