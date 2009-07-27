#include "useful.hpp"
#include "functionmanager.hpp"

namespace engine
{

CFunctionManager::CFunctionManager()
{
	m_iNextId = 0;
}

CFunctionManager::~CFunctionManager()
{
}

bool CFunctionManager::Remove(const unsigned int iId)
{
	std::map<unsigned int, CFunctorData>::iterator cFoundFunctor = m_cFunctorMap.find(iId);
	if (cFoundFunctor == m_cFunctorMap.end())
	{
		Debug(Format("CFunctionManager::Remove - Functor with ID %d not found\n") % iId);
		return false;
	}
	m_cFunctorMap.erase(cFoundFunctor);
	return true;
}

unsigned int CFunctionManager::GetNextId()
{
	unsigned int iNextId = m_iNextId;
	while (m_cFunctorMap.find(iNextId) != m_cFunctorMap.end()) /* Make sure this ID isn't in use. */
		++iNextId;
	m_iNextId = iNextId + 1;
	return iNextId;
}

void CFunctionManager::Process()
{
	for (std::map<unsigned int, CFunctorData>::iterator cFunctorIterator = m_cFunctorMap.begin(); cFunctorIterator != m_cFunctorMap.end(); ++cFunctorIterator)
	{
		CFunctorData *pFunctorData = &((*cFunctorIterator).second);
		unsigned int iId = (*cFunctorIterator).first;
		if (!pFunctorData->iFramesDelay)
		{
			pFunctorData->pFunctor(iId, pFunctorData->pArgument); /* Execute function with it's ID and it's argument. */
			if (iId == (*cFunctorIterator).first) /* Functor continues executions (iterator's ID didn't change, so CFunctionManager::Remove wasn't called). */
				pFunctorData->iFramesDelay = pFunctorData->iInitialFramesDelay; /* Reset delay. */
			else /* Functor removed itself. */
				--cFunctorIterator; /* Prevent skipping elements. */
		}
		else
			--pFunctorData->iFramesDelay; /* Decrease delay. */
	}
}

}

/* EOF */

