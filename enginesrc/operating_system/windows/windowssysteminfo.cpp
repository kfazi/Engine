#ifdef WINDOWS

#include "../../common.hpp"
#include "windowssysteminfo.hpp"
#include "../../useful.hpp"
#include <windows.h>

namespace engine
{

CWindowsSystemInfo::CWindowsSystemInfo()
{
	SYSTEM_INFO sSystemInfo;
	GetSystemInfo(&sSystemInfo);
	OSVERSIONINFOEX sOSVersionInfo;
	ZeroMemory(&sOSVersionInfo, sizeof(OSVERSIONINFOEX));
	sOSVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if (GetVersionEx(reinterpret_cast<OSVERSIONINFO *>(&sOSVersionInfo)))
	{
		std::string cOSName = "";
		std::string cOSServicePack = "";
		if (sOSVersionInfo.dwMajorVersion == 5 && sOSVersionInfo.dwMinorVersion == 0)
			cOSName = " (Windows 2000)";
		else if (sOSVersionInfo.dwMajorVersion == 5 && sOSVersionInfo.dwMinorVersion == 1)
			cOSName = " (Windows XP)";
		else if (sOSVersionInfo.dwMajorVersion == 5 && sOSVersionInfo.dwMinorVersion == 2 && sOSVersionInfo.wProductType == VER_NT_WORKSTATION && sSystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
			cOSName = " (Windows XP Professional x64 Edition)";
		else if (sOSVersionInfo.dwMajorVersion == 5 && sOSVersionInfo.dwMinorVersion == 2 && GetSystemMetrics(SM_SERVERR2) == 0)
			cOSName = " (Windows Server 2003)";
		else if (sOSVersionInfo.dwMajorVersion == 5 && sOSVersionInfo.dwMinorVersion == 2 && sOSVersionInfo.wSuiteMask == 0x00008000/*VER_SUITE_WH_SERVER*/)
			cOSName = " (Windows Home Server)";
		else if (sOSVersionInfo.dwMajorVersion == 5 && sOSVersionInfo.dwMinorVersion == 2 && GetSystemMetrics(SM_SERVERR2) != 0)
			cOSName = " (Windows Server 2003 R2)";
		else if (sOSVersionInfo.dwMajorVersion == 6 && sOSVersionInfo.dwMinorVersion == 0 && sOSVersionInfo.wProductType == VER_NT_WORKSTATION)
			cOSName = " (Windows Vista)";
		else if (sOSVersionInfo.dwMajorVersion == 6 && sOSVersionInfo.dwMinorVersion == 0 && sOSVersionInfo.wProductType != VER_NT_WORKSTATION)
			cOSName = " (Windows Server 2008)";
		else if (sOSVersionInfo.dwMajorVersion == 6 && sOSVersionInfo.dwMinorVersion == 1 && sOSVersionInfo.wProductType != VER_NT_WORKSTATION)
			cOSName = " (Windows Server 2008 R2)";
		else if (sOSVersionInfo.dwMajorVersion == 6 && sOSVersionInfo.dwMinorVersion == 1 && sOSVersionInfo.wProductType == VER_NT_WORKSTATION)
			cOSName = " (Windows 7)";
		if (sOSVersionInfo.wServicePackMajor != 0 || sOSVersionInfo.wServicePackMinor != 0)
			cOSServicePack = (Format(" SP %1%.%2%") % sOSVersionInfo.wServicePackMajor % sOSVersionInfo.wServicePackMinor).str();
		m_cSystemName = (Format("Windows operating system %1%.%2%%3%%4%") % sOSVersionInfo.dwMajorVersion % sOSVersionInfo.dwMinorVersion % cOSName % cOSServicePack).str();
	}
	else
		m_cSystemName = "Unknown Windows operating system";
	MEMORYSTATUSEX sMemoryStatus;
	ZeroMemory(&sMemoryStatus, sizeof(MEMORYSTATUSEX));
	sMemoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&sMemoryStatus);
	m_iNumberOfProcessors = sSystemInfo.dwNumberOfProcessors;
	m_iTotalMemory = sMemoryStatus.ullTotalPhys;
}

CWindowsSystemInfo::~CWindowsSystemInfo()
{
}

const std::string &CWindowsSystemInfo::GetSystemName() const
{
	return m_cSystemName;
}

unsigned long long CWindowsSystemInfo::GetTotalMemory() const
{
	return m_iTotalMemory;
}

unsigned long long CWindowsSystemInfo::GetFreeMemory() const
{
	MEMORYSTATUSEX sMemoryStatus;
	ZeroMemory(&sMemoryStatus, sizeof(MEMORYSTATUSEX));
	sMemoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&sMemoryStatus);
	return sMemoryStatus.ullAvailPhys;
}

int CWindowsSystemInfo::GetNumberOfProcessors() const
{
	return m_iNumberOfProcessors;
}

}

#endif /* WINDOWS */

/* EOF */
