#include "enginemainimplementation.hpp"

using namespace engine;

namespace framework
{

void CEngineMainImplementation::BasicLog(const engine::CString &cMessage, const engine::CLogger::EMessageType)
{
	m_cLogFile << CTime::GetTotalTime() << " - " << cMessage.ToUTF8() << std::endl;
}

CEngineMainImplementation::~CEngineMainImplementation()
{
}

void CEngineMainImplementation::Create()
{
	m_cLogFile.open("EngineLog.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	CCore::GetInstance()->GetLogger()->Register(this, &CEngineMainImplementation::BasicLog);
}

void CEngineMainImplementation::Destroy()
{
	m_cLogFile.close();
}

void CEngineMainImplementation::ChooseScene()
{
	CCore::GetInstance()->GetLogger()->Log("Start");
}

void CEngineMainImplementation::ParseArgument(const engine::CString &cArgumentName, const engine::CString &cArgumentValue)
{
	CCore::GetInstance()->GetLogger()->Log("DUPA");
}

}

/* EOF */
