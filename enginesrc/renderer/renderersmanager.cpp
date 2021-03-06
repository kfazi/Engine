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

CRenderersManager::SRendererVersion::SRendererVersion(unsigned int iMajor, unsigned int iMinor, unsigned int iBuild)
{
	this->iMajor = iMajor;
	this->iMinor = iMinor;
	this->iBuild = iBuild;
}

CRenderersManager::SRendererVersion::SRendererVersion()
{
	this->iMajor = 0;
	this->iMinor = 0;
	this->iBuild = 0;
}

void CRenderersManager::ScanRenderers()
{
	CString cPattern = CCore::GetInstance()->GetSystemDirectories()->GetLibraryPrefix().SecureRegex() + CString(".*") + CCore::GetInstance()->GetSystemDirectories()->GetLibraryPostfix().SecureRegex();
	CSystemDirectories::CFilesList cFiles = CCore::GetInstance()->GetSystemDirectories()->GetFilesList(CCore::GetInstance()->GetSystemDirectories()->GetExecutablePath(), cPattern);
	Debug("Load renderers");
	for (unsigned int i = 0; i < cFiles.GetCount(); ++i)
	{
		SRendererDescription sDescription;
		unsigned int iModuleId = CCore::GetInstance()->GetModule()->Load(cFiles.GetName(i));
		void *pCreateAddress = CCore::GetInstance()->GetModule()->GetSymbol(iModuleId, "CreateRenderer");
		void *pDestroyAddress = CCore::GetInstance()->GetModule()->GetSymbol(iModuleId, "DestroyRenderer");
		void *pInfoAddress = CCore::GetInstance()->GetModule()->GetSymbol(iModuleId, "GetRendererInfo");
		if (pCreateAddress != NULL && pDestroyAddress != NULL && pInfoAddress != NULL)
		{
			sDescription.iModuleId = iModuleId;
			sDescription.pCreateRenderer = static_cast<TRendererCreateFunction>(pCreateAddress);
			sDescription.pDestroyRenderer = static_cast<TRendererDestroyFunction>(pDestroyAddress);
			sDescription.pGetRendererInfo = static_cast<TGetRendererInfoFunction>(pInfoAddress);
			sDescription.sInfo = *sDescription.pGetRendererInfo();
			m_cRendererDescriptions.push_back(sDescription);
			Debug(Format("Renderer %1% (%2%.%3%.%4%) loaded") % sDescription.sInfo.cName % sDescription.sInfo.sVersion.iMajor % sDescription.sInfo.sVersion.iMinor % sDescription.sInfo.sVersion.iBuild);
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
		CCore::GetInstance()->GetModule()->Close(m_cRendererDescriptions[i].iModuleId);
		Debug(Format("Renderer %1% unloaded") % m_cRendererDescriptions[i].sInfo.cName);
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
