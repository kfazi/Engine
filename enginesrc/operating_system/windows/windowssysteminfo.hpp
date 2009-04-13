#ifdef WINDOWS

#ifndef ENGINE_WINDOWS_SYSTEM_INFO_HPP
#define ENGINE_WINDOWS_SYSTEM_INFO_HPP

#include "../systeminfo.hpp"

namespace engine
{

class CWindowsSystemInfo: public CSystemInfo
{
	friend class CCore;

	private:
		CString m_cSystemName;
		int m_iNumberOfProcessors;
		unsigned long long m_iTotalMemory;

	protected:
		CWindowsSystemInfo();

		virtual ~CWindowsSystemInfo();

	public:
		virtual const CString &GetSystemName() const;
		virtual unsigned long long GetTotalMemory() const;
		virtual unsigned long long GetFreeMemory() const;
		virtual int GetNumberOfProcessors() const;
};

}

#endif /* ENGINE_WINDOWS_SYSTEM_INFO_HPP */

#endif /* WINDOWS */

/* EOF */
