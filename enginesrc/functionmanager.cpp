#include "debug.hpp"
#include "functionmanager.hpp"

namespace engine
{

CFunctionManager::CFunctionManager()
{
	m_iNextId = 1;
}

CFunctionManager::~CFunctionManager()
{
	for (std::map<unsigned int, CFunctor *>::iterator cFunctionIterator = m_cFunctionMap.begin(); cFunctionIterator != m_cFunctionMap.end(); ++cFunctionIterator)
		delete (*cFunctionIterator).second;
}

bool CFunctionManager::Remove(const unsigned int iId)
{
	if (iId == 0)
		return true;
	std::map<unsigned int, CFunctor *>::iterator cFoundFunction = m_cFunctionMap.find(iId);
	if (cFoundFunction == m_cFunctionMap.end())
	{
		Debug("CFunctionManager::Remove - Function with ID %d not found\n", iId);
		return false;
	}
	delete (*cFoundFunction).second;
	m_cFunctionMap.erase(cFoundFunction);
	return true;
}

unsigned int CFunctionManager::GetNextId()
{
	unsigned int iNextId = m_iNextId;
	while (m_cFunctionMap.find(iNextId) != m_cFunctionMap.end() || m_iNextId == 0) /* Make sure this ID isn't in use. */
		iNextId++;
	m_iNextId = iNextId + 1;
	return iNextId;
}

void CFunctionManager::Process()
{
	for (std::map<unsigned int, CFunctor *>::iterator cFunctionIterator = m_cFunctionMap.begin(); cFunctionIterator != m_cFunctionMap.end(); ++cFunctionIterator)
	{
		CFunctor *cFunctor = (*cFunctionIterator).second;
		unsigned int iId = (*cFunctionIterator).first;
		if (!cFunctor->m_iFramesDelay)
		{
			cFunctor->Call(iId, cFunctor->m_pArgument); /* Execute function with it's ID and it's argument. */
			if (iId == (*cFunctionIterator).first) /* Function continues executions. */
				cFunctor->m_iFramesDelay = cFunctor->m_iInitialFramesDelay; /* Reset delay. */
			else /* Function removed itself. */
				--cFunctionIterator; /* Prevent skipping elements. */
		}
		else
			cFunctor->m_iFramesDelay--; /* Decrease delay. */
	}
}

}

/* EOF */

