#ifdef WINDOWS

#ifndef ENGINE_WINDOWS_SYSTEM_DISPLAY_MANAGER_HPP
#define ENGINE_WINDOWS_SYSTEM_DISPLAY_MANAGER_HPP

#include "../systemdisplaymanager.hpp"
#include <vector>

namespace engine
{

class CWindowsSystemDisplay;

class CWindowsSystemDisplayManager: public CSystemDisplayManager
{
	private:
		std::vector<CWindowsSystemDisplay *> m_cDisplays;

	public:
		CWindowsSystemDisplayManager();
		virtual ~CWindowsSystemDisplayManager();
		virtual void RefreshDisplaysList();
};

}

#endif /* ENGINE_WINDOWS_SYSTEM_DISPLAY_MANAGER_HPP */

#endif /* WINDOWS */

/* EOF */
