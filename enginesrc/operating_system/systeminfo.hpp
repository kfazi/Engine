#ifndef ENGINE_SYSTEM_INFO_HPP
#define ENGINE_SYSTEM_INFO_HPP

#include <string>

namespace engine
{

class CSystemInfo
{
	friend class CEngine;

	protected:
		CSystemInfo()
		{
		}

		virtual ~CSystemInfo()
		{
		}

	public:
		virtual const std::string GetSystemName() = 0;
		virtual long long GetTotalMemory() = 0;
		virtual long long GetFreeMemory() = 0;
};

}

#endif /* ENGINE_SYSTEM_INFO_HPP */

/* EOF */

