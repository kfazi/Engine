#ifndef ENGINE_WINDOWS_SYSTEM_RESOLUTION_HPP
#define ENGINE_WINDOWS_SYSTEM_RESOLUTION_HPP

#include "../../common.hpp"
#include "../systemresolution.hpp"

namespace engine
{

class CWindowsSystemResolution: public CSystemResolution
{
	public:
		CWindowsSystemResolution(unsigned int iWidth, unsigned int iHeight, unsigned int iBPP, unsigned int iRefreshRate);
};

}

#endif /* ENGINE_WINDOWS_SYSTEM_RESOLUTION_HPP */

/* EOF */
