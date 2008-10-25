#include "unixsysteminfo.hpp"
#include "../../useful.hpp"
#include <sys/utsname.h>

namespace engine
{

CUnixSystemInfo::CUnixSystemInfo()
{
}

CUnixSystemInfo::~CUnixSystemInfo()
{
}

const std::string CUnixSystemInfo::GetSystemName()
{
	struct utsname sSystemInfo;
	if (!uname(&sSystemInfo))
		return (Format("%1% operating system, %2% %3% %4%") % sSystemInfo.sysname % sSystemInfo.release % sSystemInfo.version % sSystemInfo.machine).str();
	else
		return "Unknown UNIX operating system";
}

long long CUnixSystemInfo::GetTotalMemory()
{
	long iPages = sysconf(_SC_PHYS_PAGES);
	long iPageSize = sysconf(_SC_PAGESIZE);
	return iPages * iPageSize;
}

long long CUnixSystemInfo::GetFreeMemory()
{
	long iFreePages = sysconf(_SC_AVPHYS_PAGES);
	long iPageSize = sysconf(_SC_PAGESIZE);
	return iFreePages * iPageSize;
}

}

/* EOF */

