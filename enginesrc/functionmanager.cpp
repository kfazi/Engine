#include "useful.hpp"
#include "functionmanager.hpp"

namespace engine
{

CFunctionManager::CFunctionManager(unsigned int iAllocationBase)
{
	m_cRegisteredFunctors.resize(iAllocationBase, SFunctorData());
}

CFunctionManager::~CFunctionManager()
{
}

bool CFunctionManager::Remove(const unsigned int iId)
{
	if (iId >= m_cRegisteredFunctors.size() || m_cRegisteredFunctors[iId].bRemoved)
	{
		Debug(Format("CFunctionManager::Remove - Functor with ID %1% not found\n") % iId);
		return false;
	}
	m_cRegisteredFunctors[iId].bRemoved = true;
	m_cUnregisteredFunctorsIndices.push(iId);
	return true;
}

unsigned int CFunctionManager::GetNextId()
{
	if (m_cUnregisteredFunctorsIndices.size() > 0)
	{
		unsigned int iNextId = m_cUnregisteredFunctorsIndices.front();
		m_cUnregisteredFunctorsIndices.pop();
		return iNextId;
	}
	return m_cRegisteredFunctors.size();
}

void CFunctionManager::Process()
{
	for (unsigned int iId = 0; iId < m_cRegisteredFunctors.size(); ++iId)
	{
		SFunctorData *pFunctorData = &m_cRegisteredFunctors[iId];
		if (!pFunctorData->bRemoved)
		{
			if (!pFunctorData->iFramesDelay)
			{
				pFunctorData->pFunctor(iId, pFunctorData->pArgument); /* Execute function with it's ID and it's argument. */
				if (!pFunctorData->bRemoved) /* Functor continues executions. */
					pFunctorData->iFramesDelay = pFunctorData->iInitialFramesDelay; /* Reset delay. */
			}
			else
				pFunctorData->iFramesDelay--; /* Decrease delay. */
		}
	}
}

}

/* EOF */

