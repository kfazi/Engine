#ifndef ENGINE_SYSTEM_RESOLUTION_HPP
#define ENGINE_SYSTEM_RESOLUTION_HPP

#include "../common.hpp"

namespace engine
{

class DLLEXPORTIMPORT CSystemResolution
{
	private:
		unsigned int m_iWidth;
		unsigned int m_iHeight;
		unsigned int m_iBPP;
		unsigned int m_iRefreshRate;

	public:
		CSystemResolution(unsigned int iWidth, unsigned int iHeight, unsigned int iBPP, unsigned int iRefreshRate);
		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		unsigned int GetBPP() const;
		unsigned int GetRefreshRate() const;
		static bool LessThanPointer(const CSystemResolution *pLeft, const CSystemResolution *pRight);
		static bool EqualToPointer(const CSystemResolution *pLeft, const CSystemResolution *pRight);
};

}

#endif /* ENGINE_SYSTEM_RESOLUTION_HPP */

/* EOF */
