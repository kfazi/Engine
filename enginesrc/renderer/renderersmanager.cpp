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
	CString cPattern = CCore::GetInstance()->GetSystemDirectories()->GetLibraryPrefix() + CString(".*") + CCore::GetInstance()->GetSystemDirectories()->GetLibraryPostfix();
	CSystemDirectories::CFilesList cFiles = CCore::GetInstance()->GetSystemDirectories()->GetFilesList(CCore::GetInstance()->GetSystemDirectories()->GetExecutablePath(), cPattern.SecureRegex());
	Debug("Load renderers");
	for (unsigned int i = 0; i < cFiles.GetCount(); ++i)
	{
		Debug(Format("File %1% = %2%") % i % cFiles.GetName(i));
	}
	//CCore::GetInstance()->GetModule()->Load("bla.dll");
}

CRenderersManager::CRenderersManager()
{
	ScanRenderers();
}

CRenderersManager::~CRenderersManager()
{
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
