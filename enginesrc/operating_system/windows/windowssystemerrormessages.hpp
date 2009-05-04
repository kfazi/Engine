#ifdef WINDOWS

#ifndef ENGINE_WINDOWS_SYSTEM_ERROR_MESSAGES_HPP
#define ENGINE_WINDOWS_SYSTEM_ERROR_MESSAGES_HPP

#include "../../common.hpp"
#include "../../string.hpp"

namespace engine
{

class CWindowsSystemErrorMessages
{
	public:
		static CString GetError(unsigned int iErrorCode);
};

}

#endif /* ENGINE_WINDOWS_SYSTEM_ERROR_MESSAGES_HPP */

#endif /* WINDOWS */

/* EOF */
