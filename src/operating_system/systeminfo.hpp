#ifndef ENGINE_SYSTEM_INFO_HPP
#define ENGINE_SYSTEM_INFO_HPP

#include "../common.hpp"
#include "../string.hpp"

namespace engine
{

class CSystemInfo
{
	friend class CCore;

	protected:
		CSystemInfo()
		{
		}

		virtual ~CSystemInfo()
		{
		}

	public:
		virtual const CString &GetSystemName() const = 0;
		virtual unsigned long long GetTotalMemory() const = 0;
		virtual unsigned long long GetFreeMemory() const = 0;
		virtual int GetNumberOfProcessors() const = 0;
};

}

#endif /* ENGINE_SYSTEM_INFO_HPP */

/* EOF */

