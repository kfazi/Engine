#include "enginemainimplementation.hpp"

using namespace engine;

namespace framework
{

CEngineMainImplementation::~CEngineMainImplementation()
{

}

void CEngineMainImplementation::Create()
{

}

void CEngineMainImplementation::Run()
{

}

void CEngineMainImplementation::ParseArgument(const engine::CString &cArgumentName, const engine::CString &cArgumentValue)
{
	CCore::GetInstance()->GetLogger()->Log("DUPA");
}

}

/* EOF */
