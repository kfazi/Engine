#include "../common.hpp"
#include "systemmodule.hpp"

namespace engine
{

CSystemModule::SModule::SModule(const CString &cName, void *pHandle)
{
	iReferences = 1;
	bResidential = false;
	this->pHandle = pHandle;
	this->cName = cName;
}

unsigned int CSystemModule::GetNextId()
{
	unsigned int iNextId = m_iNextId;
	while (m_cModulesMap.find(iNextId) != m_cModulesMap.end()) /* Make sure this ID isn't in use. */
		++iNextId;
	m_iNextId = iNextId + 1;
	return iNextId;
}

unsigned int CSystemModule::AddModule(CSystemModule::SModule *pModule)
{
	unsigned int iNextId = GetNextId();
	m_cModulesMap.insert(std::make_pair(iNextId, pModule));
	return iNextId;
}

void CSystemModule::RemoveModule(unsigned int iModuleId)
{
	m_cModulesMap.erase(iModuleId);
}

bool CSystemModule::FindModule(unsigned int &iModuleId, const CString &cName)
{
	for (std::map<unsigned int, SModule *>::iterator cModulesIterator = m_cModulesMap.begin(); cModulesIterator != m_cModulesMap.end(); ++cModulesIterator)
	{
		if ((*cModulesIterator).second->cName == cName)
		{
			iModuleId = (*cModulesIterator).first;
			return true;
		}
	}
	return false;
}

CSystemModule::SModule *CSystemModule::GetModule(unsigned int iModuleId)
{
	std::map<unsigned int, SModule *>::iterator cFoundModule = m_cModulesMap.find(iModuleId);
	if (cFoundModule == m_cModulesMap.end())
		return NULL;
	return (*cFoundModule).second;
}

CSystemModule::~CSystemModule()
{
	for (std::map<unsigned int, SModule *>::iterator cModulesIterator = m_cModulesMap.begin(); cModulesIterator != m_cModulesMap.end(); ++cModulesIterator)
	{
		while ((*cModulesIterator).second->iReferences)
			Close((*cModulesIterator).first);
	}
}

void CSystemModule::MakeResident(const unsigned int iModuleId)
{
	SModule *pModule = GetModule(iModuleId);
	if (!pModule)
		/* ERROR */
	pModule->bResidential = true;
}

}

/* EOF */
