#include "systemdisplaymanager.hpp"
#include "systemdisplay.hpp"

namespace engine
{

CSystemDisplayManager::CSystemDisplayManager()
{
}

CSystemDisplayManager::~CSystemDisplayManager()
{
}

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

void CSystemDisplayManager::ProcessEvents()
{
	for (unsigned int i = 0; i < m_cDisplays.size(); ++i)
		m_cDisplays[i]->ProcessEvents();
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
