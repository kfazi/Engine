#ifndef ENGINE_WINDOWS_SYSTEM_DISPLAY_HPP
#define ENGINE_WINDOWS_SYSTEM_DISPLAY_HPP

#include "../../common.hpp"
#include "../../string.hpp"
#include "../systemdisplay.hpp"
#include <vector>

namespace engine
{

class CWindowsSystemResolution;

class CWindowsSystemDisplay: public CSystemDisplay
{
	private:
		CString m_cDisplayName;
		std::vector<CWindowsSystemResolution *> m_cResolutions;

	public:
		CWindowsSystemDisplay(const CString cDisplayName);
		virtual ~CWindowsSystemDisplay();
		virtual void RefreshResolutionsList();
		virtual void SetResolution(const CSystemResolution &cResolution);
};

}

#endif /* ENGINE_WINDOWS_SYSTEM_DISPLAY_HPP */

/* EOF */
