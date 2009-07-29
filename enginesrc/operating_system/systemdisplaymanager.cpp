#include "systemdisplaymanager.hpp"

namespace engine
{

void CSystemDisplayManager::ClearDisplaysList()
{
	m_cDisplays.clear();
}

void CSystemDisplayManager::AddDisplay(CSystemDisplay *pDisplay, bool bPrimary)
{
	if (bPrimary)
		m_cDisplays.insert(m_cDisplays.begin(), pDisplay); /* Primary display is always first on the list. */
	else
		m_cDisplays.push_back(pDisplay);
}

CSystemDisplayManager::~CSystemDisplayManager()
{
}

unsigned int CSystemDisplayManager::GetDisplaysCount() const
{
	return m_cDisplays.size();
}

CSystemDisplay &CSystemDisplayManager::GetDisplay(unsigned int iDisplayNumber)
{
	return *m_cDisplays[iDisplayNumber];
}

}

/* EOF */
