#include "enginemainimplementation.hpp"
#ifdef WINDOWS
#include <windows.h>
#endif /* WINDOWS */

using namespace engine;

namespace framework
{

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
	m_cLogFile.open("EngineLog.txt");
	CCore::GetInstance()->GetLogger()->Register(this, &CEngineMainImplementation::BasicLog);
}

void CEngineMainImplementation::Destroy()
{
	m_cLogFile.close();
	FreeConsole();
}

void CEngineMainImplementation::ChooseScene()
{
	CCore::GetInstance()->GetLogger()->Log("Start");
	CCore::GetInstance()->GetLogger()->Log("Setting resolution number 0");
	CCore::GetInstance()->GetSystemDisplayManager()->GetDisplay(0).SetResolution(0);
	CCore::GetInstance()->GetLogger()->Log("Setting default resolution");
	CCore::GetInstance()->GetSystemDisplayManager()->GetDisplay(0).RestoreDefaultResolution();
}

void CEngineMainImplementation::ParseArgument(const engine::CString &cArgumentName, const engine::CString &cArgumentValue)
{
	CCore::GetInstance()->GetLogger()->Log("DUPA");
}

}

/* EOF */
