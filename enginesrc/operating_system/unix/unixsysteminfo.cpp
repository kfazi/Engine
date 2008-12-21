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

const std::string &CUnixSystemInfo::GetSystemName() const
{
	return m_cSystemName;
}

long long CUnixSystemInfo::GetTotalMemory() const
{
	long iPages = sysconf(_SC_PHYS_PAGES);
	long iPageSize = sysconf(_SC_PAGESIZE);
	return iPages * iPageSize;
}

long long CUnixSystemInfo::GetFreeMemory() const
{
	long iFreePages = sysconf(_SC_AVPHYS_PAGES);
	long iPageSize = sysconf(_SC_PAGESIZE);
	return iFreePages * iPageSize;
}

int CUnixSystemInfo::GetNumberOfProcessors() const
{
	return static_cast<int>(sysconf(_SC_NPROCESSORS_ONLN));
}

}

#endif /* UNIX */

/* EOF */

