#ifdef UNIX

#include <sys/utsname.h>
#include <unistd.h>
#include "../../common.hpp"
#include "unixsysteminfo.hpp"
#include "../../useful.hpp"

namespace engine
{

CUnixSystemInfo::CUnixSystemInfo()
{
	struct utsname sSystemInfo;
	if (!uname(&sSystemInfo))
		m_cSystemName = (Format("%1% operating system, %2% %3% %4%") % sSystemInfo.sysname % sSystemInfo.release % sSystemInfo.version % sSystemInfo.machine).str();
	else
		m_cSystemName = "Unknown UNIX operating system";
}

CUnixSystemInfo::~CUnixSystemInfo()
{
}

const CString &CUnixSystemInfo::GetSystemName() const
{
	return m_cSystemName;
}

unsigned long long CUnixSystemInfo::GetTotalMemory() const
{
	unsigned long iPages = sysconf(_SC_PHYS_PAGES);
	unsigned long iPageSize = sysconf(_SC_PAGESIZE);
	return iPages * iPageSize;
}

unsigned long long CUnixSystemInfo::GetFreeMemory() const
{
	unsigned long iFreePages = sysconf(_SC_AVPHYS_PAGES);
	unsigned long iPageSize = sysconf(_SC_PAGESIZE);
	return iFreePages * iPageSize;
}

int CUnixSystemInfo::GetNumberOfProcessors() const
{
	return static_cast<int>(sysconf(_SC_NPROCESSORS_ONLN));
}

}

#endif /* UNIX */

/* EOF */

