#ifndef ENGINE_SYSTEM_DISPLAY_MANAGER_HPP
#define ENGINE_SYSTEM_DISPLAY_MANAGER_HPP

#include "../common.hpp"
#include <vector>

namespace engine
{

class CSystemDisplay;

class DLLEXPORTIMPORT CSystemDisplayManager
{
	friend class CCore;

	public:

	private:
		std::vector<CSystemDisplay *> m_cDisplays;

	protected:
		CSystemDisplayManager();
		virtual ~CSystemDisplayManager();
		void ClearDisplaysList();
		void AddDisplay(CSystemDisplay *pDisplay, bool bPrimary);
		void ProcessEvents();

	public:
		unsigned int GetDisplaysCount() const;
		CSystemDisplay &GetDisplay(unsigned int iDisplayNumber);
		virtual void RefreshDisplaysList() = 0;
};

}

#endif /* ENGINE_SYSTEM_DISPLAY_MANAGER_HPP */

/* EOF */
