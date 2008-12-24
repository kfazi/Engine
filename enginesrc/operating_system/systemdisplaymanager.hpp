#ifndef ENGINE_SYSTEM_DISPLAY_MANAGER_HPP
#define ENGINE_SYSTEM_DISPLAY_MANAGER_HPP

#include "../math/vector3.hpp"
#include "../common.hpp"

namespace engine
{

class CSystemDisplayManager
{
	friend class CEngine;

	protected:
		CSystemDisplayManager()
		{
		}

		virtual ~CSystemDisplayManager()
		{
		}

	public:
		virtual unsigned int GetDisplaysCount() const = 0;
		virtual unsigned int GetResolutionsCount(const unsigned int iDisplayNumber) const = 0;
		virtual const CVector3 *GetDisplayPosition(const unsigned int iDisplayNumber) const = 0;
		virtual void SetDisplayPosition(const unsigned int iDisplayNumber, const CVector3 &cPosition) = 0; 
		virtual void SetDisplayRotation(const unsigned int iDisplayNumber, const CVector3 &cRotation) = 0; 
		virtual const CResolution *GetResolution(const unsigned int iDisplayNumber, const unsigned int iResolutionNumber) const = 0;
		virtual bool SetResolution(const unsigned int iDisplayNumber, const unsigned int iResolutionNumber, const bool bFullScreen) = 0;
		virtual unsigned int GetCurrentResolutionNumber(const unsigned int iDisplayNumber) const = 0;
		virtual unsigned int GetDesktopResolutionNumber(const unsigned int iDisplayNumber) const = 0;
		virtual const std::string &GetDriverName() const = 0;
};

}

#endif /* ENGINE_SYSTEM_DISPLAY_MANAGER_HPP */

/* EOF */
