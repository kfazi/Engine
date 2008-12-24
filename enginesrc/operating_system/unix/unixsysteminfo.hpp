#ifdef UNIX

#ifndef ENGINE_UNIX_SYSTEM_INFO_HPP
#define ENGINE_UNIX_SYSTEM_INFO_HPP

#include "../systeminfo.hpp"

namespace engine
{

class CUnixSystemInfo: public CSystemInfo
{
	friend class CCore;

	private:
		std::string m_cSystemName;

	protected:
		CUnixSystemInfo();

		virtual ~CUnixSystemInfo();

	public:
		virtual const std::string &GetSystemName() const;
		virtual long long GetTotalMemory() const;
		virtual long long GetFreeMemory() const;
		virtual int GetNumberOfProcessors() const;
};

}

#endif /* ENGINE_UNIX_SYSTEM_INFO_HPP */

#endif /* UNIX */

/* EOF */

