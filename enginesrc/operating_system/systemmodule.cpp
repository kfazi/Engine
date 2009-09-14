#include "../common.hpp"
#include "../useful.hpp"
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
	if (m_cRemovedModules.size() > 0)
	{
		unsigned int iNextId = m_cRemovedModules.front();
		m_cRemovedModules.pop();
		return iNextId;
	}
	return m_cLoadedModules.size();
}

CSystemModule::CSystemModule(unsigned int iAllocationBase)
{
	m_cLoadedModules.resize(iAllocationBase, NULL);
}

unsigned int CSystemModule::AddModule(CSystemModule::SModule *pModule)
{
	unsigned int iId = GetNextId();
	if (m_cLoadedModules.size() <= iId)
		m_cLoadedModules.resize(m_cLoadedModules.size() * 2 + 1, NULL);
	m_cLoadedModules[iId] = pModule;
	return iId;
}

bool CSystemModule::RemoveModule(unsigned int iModuleId)
{
	if (iModuleId >= m_cLoadedModules.size() || m_cLoadedModules[iModuleId] == NULL)
	{
		Debug(Format("CSystemModule::RemoveModule - Module with ID %1% not found\n") % iModuleId);
		return false;
	}
	m_cLoadedModules[iModuleId] = NULL;
	m_cRemovedModules.push(iModuleId);
	return true;
}

bool CSystemModule::FindModule(unsigned int &iModuleId, const CString &cName)
{
	for (iModuleId = 0; iModuleId < m_cLoadedModules.size(); ++iModuleId)
	{
		if (m_cLoadedModules[iModuleId] != NULL)
		{
			if (m_cLoadedModules[iModuleId]->cName == cName)
			{
				iModuleId = iModuleId;
				return true;
			}
		}
	}
	return false;
}

CSystemModule::SModule *CSystemModule::GetModule(unsigned int iModuleId)
{
	if (iModuleId >= m_cLoadedModules.size() || m_cLoadedModules[iModuleId] == NULL)
		return NULL;
	return m_cLoadedModules[iModuleId];
}

CSystemModule::~CSystemModule()
{
	for (unsigned int iModuleId = 0; iModuleId < m_cLoadedModules.size(); ++iModuleId)
	{
		if (m_cLoadedModules[iModuleId] != NULL)
		{
			m_cLoadedModules[iModuleId]->bResidential = false;
			while (m_cLoadedModules[iModuleId] != NULL)
				Close(iModuleId);
		}
	}
}

void CSystemModule::MakeResident(const unsigned int iModuleId)
{
	SModule *pModule = GetModule(iModuleId);
	if (!pModule)
		Error(Format("CSystemModule::MakeResident - Module with ID %1% not found!") % iModuleId);/* ERROR */
	pModule->bResidential = true;
}

void CSystemModule::Close(const unsigned int iModuleId)
{
	SModule *pModule = GetModule(iModuleId);
	if (!pModule->bResidential)
	{
		pModule->iReferences--;
		UnloadModule(pModule);
		if (!pModule->iReferences)
		{
			RemoveModule(iModuleId);
			delete pModule;
		}
	}
}

}

/* EOF */
