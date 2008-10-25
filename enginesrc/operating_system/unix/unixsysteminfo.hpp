#ifndef ENGINE_UNIX_SYSTEM_INFO_HPP
#define ENGINE_UNIX_SYSTEM_INFO_HPP

#include "../systeminfo.hpp"

namespace engine
{

class CUnixSystemInfo: public CSystemInfo
{
	friend class CEngine;

	protected:
		CUnixSystemInfo();

		virtual ~CUnixSystemInfo();

	public:
		virtual const std::string GetSystemName();
		virtual long long GetTotalMemory();
		virtual long long GetFreeMemory();
};

}

#endif /* ENGINE_UNIX_SYSTEM_INFO_HPP */

/* EOF */

