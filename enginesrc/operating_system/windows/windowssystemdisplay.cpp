#include <Windows.h>
#undef ERROR
#include "windowssystemdisplay.hpp"
#include "windowssystemresolution.hpp"

namespace engine
{

CWindowsSystemDisplay::CWindowsSystemDisplay(const CString cDisplayName)
{
	m_cDisplayName = cDisplayName;
	RefreshResolutionsList();
}

CWindowsSystemDisplay::~CWindowsSystemDisplay()
{
	for (unsigned int i = 0; i < m_cResolutions.size(); ++i)
		delete m_cResolutions[i];
}

void CWindowsSystemDisplay::RefreshResolutionsList()
{
	DEVMODE sDeviceMode;
	ZeroMemory(&sDeviceMode, sizeof(sDeviceMode));
	sDeviceMode.dmSize = sizeof(sDeviceMode);
	for (int iModeNumber = 0; ::EnumDisplaySettings(reinterpret_cast<const wchar_t *>(m_cDisplayName.ToUTF16().c_str()), iModeNumber, &sDeviceMode); ++iModeNumber)
	{
		CWindowsSystemResolution *pResolution = new CWindowsSystemResolution(sDeviceMode.dmPelsWidth, sDeviceMode.dmPelsHeight, sDeviceMode.dmBitsPerPel, sDeviceMode.dmDisplayFrequency);
		m_cResolutions.push_back(pResolution);
		AddResolution(pResolution);
	}
}

void CWindowsSystemDisplay::SetResolution(const CSystemResolution &cResolution)
{
	SetCurrentResolutionNumber(ResolutionToIndex(cResolution));
}

}

/* EOF */
