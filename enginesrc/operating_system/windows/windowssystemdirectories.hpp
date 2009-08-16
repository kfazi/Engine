#ifdef WINDOWS

#ifndef ENGINE_WINDOWS_SYSTEM_DIRECTORIES_HPP
#define ENGINE_WINDOWS_SYSTEM_DIRECTORIES_HPP

#include "../../common.hpp"
#include "../systemdirectories.hpp"

namespace engine
{

class CWindowsSystemDirectories: public CSystemDirectories
{
	public:
		CWindowsSystemDirectories();
		virtual void CorrectPath(CString &cPath);
		virtual CString GetLibraryPrefix() const;
		virtual CString GetLibraryPostfix() const;
};

}

#endif /* ENGINE_WINDOWS_SYSTEM_DIRECTORIES_HPP */

#endif /* WINDOWS */

/* EOF */
