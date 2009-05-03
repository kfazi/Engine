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
};

}

#endif /* ENGINE_WINDOWS_SYSTEM_DIRECTORIES_HPP */

#endif /* WINDOWS */

/* EOF */
