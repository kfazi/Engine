#include "systemdisplay.hpp"
#include "systemresolution.hpp"
#include "systemwindow.hpp"
#include "../useful.hpp"
#include <algorithm>

namespace engine
{

const int g_iBasicSize = 1;
const int g_iResizeSize = 4;

unsigned int CSystemDisplay::GetNextWindowId()
{
	while (m_cWindows[m_iNextWindowId] != NULL)
	{
		m_iNextWindowId++;
		if (m_cWindows.capacity() <= m_iNextWindowId)
			m_cWindows.resize(m_cWindows.capacity() + g_iResizeSize, NULL);
	}
	return m_iNextWindowId;
}

CSystemDisplay::CSystemDisplay()
{
	m_iNextWindowId = 0;
	m_cWindows.resize(g_iBasicSize, NULL);
}

CSystemDisplay::~CSystemDisplay()
{
}

void CSystemDisplay::RestoreDefaultResolution()
{
	SetResolution(m_iDefaultResolutionIndex);
}

void CSystemDisplay::ProcessEvents()
{
	for (unsigned int i = 0; i < m_cWindows.size(); ++i)
	{
		if (m_cWindows[i])
			m_cWindows[i]->ProcessEvents();
	}
}

void CSystemDisplay::AddResolution(CSystemResolution *pResolution)
{
	m_cResolutions.push_back(pResolution);
	/* Sort from the smallest to the biggest. */
	std::sort(m_cResolutions.begin(), m_cResolutions.end(), CSystemResolution::LessThanPointer);
	/* Remove duplicates. */
	m_cResolutions.erase(std::unique(m_cResolutions.begin(), m_cResolutions.end(), CSystemResolution::EqualToPointer), m_cResolutions.end());
}

void CSystemDisplay::SetCurrentResolutionIndex(unsigned int iResolutionIndex)
{
	m_iCurrentResolutionIndex = iResolutionIndex;
}

void CSystemDisplay::SetDefaultResolutionIndex(unsigned int iResolutionIndex)
{
	m_iDefaultResolutionIndex = iResolutionIndex;
}

unsigned int CSystemDisplay::ResolutionToIndex(const CSystemResolution &cResolution)
{
	for (unsigned int i = 0; i < m_cResolutions.size(); ++i)
	{
		if (CSystemResolution::EqualToPointer(m_cResolutions[i], &cResolution))
			return i;
	}
	Error("");
	return 0;
}

const CSystemResolution *CSystemDisplay::GetCurrentResolution() const
{
	return m_cResolutions[m_iCurrentResolutionIndex];
}

const CSystemResolution *CSystemDisplay::GetDefaultResolution() const
{
	return m_cResolutions[m_iDefaultResolutionIndex];
}

unsigned int CSystemDisplay::GetCurrentResolutionIndex() const
{
	return m_iCurrentResolutionIndex;
}

void CSystemDisplay::SetResolution(unsigned int iResolutionIndex)
{
	/* Prevent blinking when setting the same resolution second time. */
	if (m_iCurrentResolutionIndex != iResolutionIndex)
	{
		SetCurrentResolutionIndex(iResolutionIndex);
		SetResolutionInternal(*m_cResolutions[iResolutionIndex]);
	}
}

void CSystemDisplay::SetResolution(const CSystemResolution &cResolution)
{
	int iResolutionIndex = ResolutionToIndex(cResolution);
	SetResolution(iResolutionIndex);
}

unsigned int CSystemDisplay::GetResolutionsCount() const
{
	return m_cResolutions.size();
}

const CSystemResolution *CSystemDisplay::GetResolution(unsigned int iResolutionNumber) const
{
	return m_cResolutions[iResolutionNumber];
}

unsigned int CSystemDisplay::AddWindow(int iX, int iY, unsigned int iWidth, unsigned int iHeight, const CString &cCaption)
{
	return AddWindow(iX, iY, iWidth, iHeight, cCaption, false, false, false, false);
}

unsigned int CSystemDisplay::AddWindow(int iX, int iY, unsigned int iWidth, unsigned int iHeight, const CString &cCaption, bool bCaptionBar)
{
	if (bCaptionBar)
		return AddWindow(iX, iY, iWidth, iHeight, cCaption, true, true, true, true);
	else
		return AddWindow(iX, iY, iWidth, iHeight, cCaption, false, false, false, false);
}

unsigned int CSystemDisplay::AddWindow(int iX, int iY, unsigned int iWidth, unsigned int iHeight, const CString &cCaption, bool bCaptionBar, bool bCloseButton, bool bMaximalizeButton, bool bMinimalizeButton)
{
	unsigned int iWindowId = GetNextWindowId();
	CSystemWindow *pWindow = AddWindowInternal(iX, iY, iWidth, iHeight, cCaption, bCaptionBar, bCloseButton, bMaximalizeButton, bMinimalizeButton);
	m_cWindows[iWindowId] = pWindow;
	return iWindowId;
}

void CSystemDisplay::RemoveWindow(unsigned int iWindowId)
{
	RemoveWindowInternal(m_cWindows[iWindowId]);
	m_cWindows[iWindowId] = NULL;
}

CSystemWindow *CSystemDisplay::GetWindow(unsigned int iWindowId)
{
	return m_cWindows[iWindowId];
}

}

/* EOF */
