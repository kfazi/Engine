#include "enginemainimplementation.hpp"
#ifdef WINDOWS
#include <Windows.h>
#endif /* WINDOWS */

using namespace engine;

namespace framework
{

bool CEngineMainImplementation::OnWindowClose()
{
	CCore::GetInstance()->Finish();
	return true;
}

bool CEngineMainImplementation::OnWindowClose2()
{
	return false;
}

void CEngineMainImplementation::BasicLog(const engine::CString &cMessage, const engine::CLogger::EMessageType)
{
	m_cLogFile << CTime::GetTotalTime() << " - " << cMessage.ToUTF8() << std::endl;
	std::cout << CTime::GetTotalTime() << " - " << cMessage.ToUTF8() << std::endl;
}

CEngineMainImplementation::~CEngineMainImplementation()
{
}

void CEngineMainImplementation::Create()
{
#ifdef WINDOWS
	AllocConsole();
	freopen("CONIN$", "rb", stdin);
	freopen("CONOUT$", "wb", stdout);
	freopen("CONOUT$", "wb", stderr);
#endif /* WINDOWS */
	m_cLogFile.open("EngineLog.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
	CCore::GetInstance()->GetLogger()->Register(this, &CEngineMainImplementation::BasicLog);
	CCore::GetInstance()->GetLogger()->Log(CCore::GetInstance()->GetConfig()->GetString("/Zmienna"));
	CCore::GetInstance()->GetConfig()->Set("/Zmienna", "Wartosc");
}

void CEngineMainImplementation::Destroy()
{
	m_cLogFile.close();
	FreeConsole();
}

void CEngineMainImplementation::ChooseScene()
{
	CCore::GetInstance()->GetLogger()->Log("Start");
//	CCore::GetInstance()->GetLogger()->Log("Setting resolution number 0");
//	CCore::GetInstance()->GetSystemDisplayManager()->GetDisplay(0).SetResolution(0);
	CCore::GetInstance()->GetLogger()->Log("Setting default resolution");
	CCore::GetInstance()->GetSystemDisplayManager()->GetDisplay(0).RestoreDefaultResolution();
	int iWindow = CCore::GetInstance()->GetSystemDisplayManager()->GetDisplay(0).AddWindow(10, 10, 500, 500, "DUPA", true, true, true, true);
	CCore::GetInstance()->GetSystemDisplayManager()->GetDisplay(0).GetWindow(iWindow)->SetOnCloseFunction(this, &CEngineMainImplementation::OnWindowClose);
	CCore::GetInstance()->GetSystemDisplayManager()->GetDisplay(0).GetWindow(iWindow)->Show();
	//int iWindow2 = CCore::GetInstance()->GetSystemDisplayManager()->GetDisplay(0).AddWindow(10, 10, 500, 500, "DUPA2", true, true, true, false);
	//CCore::GetInstance()->GetSystemDisplayManager()->GetDisplay(0).GetWindow(iWindow2)->SetOnCloseFunction(this, &CEngineMainImplementation::OnWindowClose2);
	//CCore::GetInstance()->GetSystemDisplayManager()->GetDisplay(0).GetWindow(iWindow2)->Show();
}

void CEngineMainImplementation::ParseArgument(const engine::CString &cArgumentName, const engine::CString &cArgumentValue)
{
	CCore::GetInstance()->GetLogger()->Log("DUPA");
}

}

/* EOF */
