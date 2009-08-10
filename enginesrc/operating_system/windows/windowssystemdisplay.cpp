#include <Windows.h>
#undef ERROR
#include "windowssystemdisplay.hpp"
#include "windowssystemresolution.hpp"
#include "windowssystemwindow.hpp"
#include "../../useful.hpp"

namespace engine
{

void CWindowsSystemDisplay::SetResolutionInternal(const CSystemResolution &cResolution)
{
	DEVMODE sDeviceMode;
	::memset(&sDeviceMode, 0, sizeof(sDeviceMode));
	sDeviceMode.dmSize = sizeof(sDeviceMode);
	sDeviceMode.dmPelsWidth = cResolution.GetWidth();
	sDeviceMode.dmPelsHeight = cResolution.GetHeight();
	sDeviceMode.dmBitsPerPel = cResolution.GetBPP();
	sDeviceMode.dmDisplayFrequency = cResolution.GetRefreshRate();
	sDeviceMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
	::ChangeDisplaySettingsEx(m_cDisplayName.ToWCHAR().c_str(), &sDeviceMode, NULL, 0, NULL);
}

CSystemWindow *CWindowsSystemDisplay::AddWindowInternal(int iX, int iY, unsigned int iWidth, unsigned int iHeight, const CString &cCaption, bool bCaptionBar, bool bCloseButton, bool bMaximalizeButton, bool bMinimalizeButton)
{
	return new CWindowsSystemWindow(iX, iY, iWidth, iHeight, cCaption, bCaptionBar, bCloseButton, bMaximalizeButton, bMinimalizeButton);
}

void CWindowsSystemDisplay::RemoveWindowInternal(CSystemWindow *pWindow)
{
	delete static_cast<CWindowsSystemWindow *>(pWindow);
}

CWindowsSystemDisplay::CWindowsSystemDisplay(const CString cDisplayName)
{
	m_cDisplayName = cDisplayName;

	DEVMODE sDeviceMode;
	DEVMODE sCurrentDeviceMode;
	::memset(&sDeviceMode, 0, sizeof(sDeviceMode));
	::memset(&sCurrentDeviceMode, 0, sizeof(sDeviceMode));
	sDeviceMode.dmSize = sizeof(sDeviceMode);
	sCurrentDeviceMode.dmSize = sizeof(sDeviceMode);
	CWindowsSystemResolution *pCurrentResolution = NULL;
	CWindowsSystemResolution *pDefaultResolution = NULL;
	::EnumDisplaySettings(m_cDisplayName.ToWCHAR().c_str(), ENUM_CURRENT_SETTINGS, &sCurrentDeviceMode);
	for (int iModeNumber = 0; ::EnumDisplaySettings(m_cDisplayName.ToWCHAR().c_str(), iModeNumber, &sDeviceMode); ++iModeNumber)
	{
		CWindowsSystemResolution *pResolution = new CWindowsSystemResolution(sDeviceMode.dmPelsWidth, sDeviceMode.dmPelsHeight, sDeviceMode.dmBitsPerPel, sDeviceMode.dmDisplayFrequency);
		m_cResolutions.push_back(pResolution);
		AddResolution(pResolution);
		if (sDeviceMode.dmPelsWidth == sCurrentDeviceMode.dmPelsWidth && sDeviceMode.dmPelsHeight == sCurrentDeviceMode.dmPelsHeight && sDeviceMode.dmBitsPerPel == sCurrentDeviceMode.dmBitsPerPel && sDeviceMode.dmDisplayFrequency == sCurrentDeviceMode.dmDisplayFrequency)
		{
			pCurrentResolution = pResolution;
			pDefaultResolution = pResolution;
		}
	}
	for (unsigned int iIndex = 0; iIndex < GetResolutionsCount(); ++iIndex)
	{
		const CSystemResolution *pResolution = GetResolution(iIndex);
		if (*pResolution == *pCurrentResolution)
			SetCurrentResolutionIndex(iIndex);
		if (*pResolution == *pDefaultResolution)
			SetDefaultResolutionIndex(iIndex);
	}
}

CWindowsSystemDisplay::~CWindowsSystemDisplay()
{
	for (unsigned int i = 0; i < m_cResolutions.size(); ++i)
		delete m_cResolutions[i];
}

}

/* EOF */
