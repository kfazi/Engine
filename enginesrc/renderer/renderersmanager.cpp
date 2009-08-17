#include "../common.hpp"
#include "../core.hpp"
#include "renderersmanager.hpp"
#include "renderer.hpp"
#include "../useful.hpp"
#include "../operating_system/systemdirectories.hpp"
#include "../operating_system/systemwindow.hpp"
#include "../operating_system/systemmodule.hpp"

namespace engine
{

void CRenderersManager::ScanRenderers()
{
	CString cPattern = CCore::GetInstance()->GetSystemDirectories()->GetLibraryPrefix().SecureRegex() + CString(".*") + CCore::GetInstance()->GetSystemDirectories()->GetLibraryPostfix().SecureRegex();
	CSystemDirectories::CFilesList cFiles = CCore::GetInstance()->GetSystemDirectories()->GetFilesList(CCore::GetInstance()->GetSystemDirectories()->GetExecutablePath(), cPattern);
	Debug("Load renderers");
	for (unsigned int i = 0; i < cFiles.GetCount(); ++i)
	{
		SRendererDescription sDescription;
		Debug(Format("File %1% = %2%") % i % cFiles.GetName(i));
		unsigned int iModuleId = CCore::GetInstance()->GetModule()->Load(cFiles.GetName(i));
		void *pCreateAddress = CCore::GetInstance()->GetModule()->GetSymbol(iModuleId, "CreateRenderer");
		void *pDestroyAddress = CCore::GetInstance()->GetModule()->GetSymbol(iModuleId, "DestroyRenderer");
		void *pInfoAddress = CCore::GetInstance()->GetModule()->GetSymbol(iModuleId, "GetRendererInfo");
		if (pCreateAddress != NULL && pDestroyAddress != NULL && pInfoAddress != NULL)
		{
			sDescription.cName = cFiles.GetName(i);
			sDescription.iModuleId = iModuleId;
			sDescription.pCreateRenderer = static_cast<TRendererCreateFunction>(pCreateAddress);
			sDescription.pDestroyRenderer = static_cast<TRendererDestroyFunction>(pDestroyAddress);
			m_cRendererDescriptions.push_back(sDescription);
		}
		else
			CCore::GetInstance()->GetModule()->Close(iModuleId);
	}
}

CRenderersManager::CRenderersManager()
{
	ScanRenderers();
}

CRenderersManager::~CRenderersManager()
{
	Debug("Unload renderers");
	for (unsigned int i = 0; i < m_cRendererDescriptions.size(); ++i)
	{
		Debug(m_cRendererDescriptions[i].cName);
		CCore::GetInstance()->GetModule()->Close(m_cRendererDescriptions[i].iModuleId);
	}
}

CString CRenderersManager::GetRendererName(unsigned int iRendererNumber) const
{
	return "";
}

unsigned int CRenderersManager::GetRenderersCount() const
{
	return 0;
}

CRenderer *CRenderersManager::CreateRenderer(unsigned int iRendererNumber, const CSystemWindow &cWindow)
{
	return NULL;
}

void CRenderersManager::DestroyRenderer(CRenderer &cRenderer)
{
}

}

/* EOF */
