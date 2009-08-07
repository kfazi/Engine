#ifdef WINDOWS

#include <Windows.h>
#undef ERROR
#include "../../common.hpp"
#include "windowssystemdisplaymanager.hpp"
#include "windowssystemdisplay.hpp"
#include "../systemresolution.hpp"
#include "../../useful.hpp"

namespace engine
{

CWindowsSystemDisplayManager::CWindowsSystemDisplayManager()
{
	RefreshDisplaysList();
}

CWindowsSystemDisplayManager::~CWindowsSystemDisplayManager()
{
	for (unsigned int i = 0; i < m_cDisplays.size(); ++i)
		delete m_cDisplays[i];
}

void CWindowsSystemDisplayManager::RefreshDisplaysList()
{
	ClearDisplaysList();
	Debug("Refreshing displays list");
	DISPLAY_DEVICE sDisplayDevice;
	sDisplayDevice.cb = sizeof(sDisplayDevice);

	for (int iDeviceNumber = 0; ::EnumDisplayDevices(NULL, iDeviceNumber, &sDisplayDevice, 0); ++iDeviceNumber)
	{
		if ((sDisplayDevice.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER) || !(sDisplayDevice.StateFlags & DISPLAY_DEVICE_ACTIVE))
			continue;
		CWindowsSystemDisplay *pDisplay = new CWindowsSystemDisplay(sDisplayDevice.DeviceName);
		Debug(Format("DeviceName: %1%") % CString(sDisplayDevice.DeviceName));
		Debug(Format("DeviceString: %1%") % CString(sDisplayDevice.DeviceString));
		Debug(Format("Flags: %1%") % sDisplayDevice.StateFlags);
		if (sDisplayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
			Debug("Primary Display");

		m_cDisplays.push_back(pDisplay);
		AddDisplay(pDisplay, (sDisplayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) ? true : false);

		const CSystemResolution *pResolution;
		for (unsigned int i = 0; i < pDisplay->GetResolutionsCount(); ++i)
		{
			pResolution = pDisplay->GetResolution(i);
			Debug(Format("%1%x%2%:%3%@%4%") % pResolution->GetWidth() % pResolution->GetHeight() % pResolution->GetBPP() % pResolution->GetRefreshRate());
		}
		pResolution = pDisplay->GetCurrentResolution();
		Debug(Format("Current %1%x%2%:%3%@%4%") % pResolution->GetWidth() % pResolution->GetHeight() % pResolution->GetBPP() % pResolution->GetRefreshRate());
		pResolution = pDisplay->GetDefaultResolution();
		Debug(Format("Default %1%x%2%:%3%@%4%") % pResolution->GetWidth() % pResolution->GetHeight() % pResolution->GetBPP() % pResolution->GetRefreshRate());
	}
}

}

#endif /* WINDOWS */

/* EOF */
