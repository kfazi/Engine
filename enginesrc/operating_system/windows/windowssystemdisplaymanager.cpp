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

	for (int iDeviceNumber = 0; EnumDisplayDevices(NULL, iDeviceNumber, &sDisplayDevice, 0); ++iDeviceNumber)
	{
		if ((sDisplayDevice.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER) || !(sDisplayDevice.StateFlags & DISPLAY_DEVICE_ACTIVE))
			continue;
		CWindowsSystemDisplay *pDisplay = new CWindowsSystemDisplay(reinterpret_cast<unsigned short *>(sDisplayDevice.DeviceName));
		Debug(Format("DeviceName: %1%") % CString(reinterpret_cast<unsigned short *>(sDisplayDevice.DeviceName)));
		Debug(Format("DeviceString: %1%") % CString(reinterpret_cast<unsigned short *>(sDisplayDevice.DeviceString)));
		Debug(Format("Flags: %1%") % sDisplayDevice.StateFlags);
		if (sDisplayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
			Debug("Primary Display");

		m_cDisplays.push_back(pDisplay);
		AddDisplay(pDisplay, (sDisplayDevice.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE) ? true : false);

		for (unsigned int i = 0; i < pDisplay->GetResolutionsCount(); ++i)
		{
			Debug(Format("%1%x%2%:%3%@%4%") % pDisplay->GetResolution(i).GetWidth() % pDisplay->GetResolution(i).GetHeight() % pDisplay->GetResolution(i).GetBPP() % pDisplay->GetResolution(i).GetRefreshRate());
		}
	}
}

}

#endif /* WINDOWS */

/* EOF */
