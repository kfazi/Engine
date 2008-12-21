#include "scene.hpp"

namespace engine
{

CScene::CScene()
{
	m_iUpdateID = CEngine::GetInstance()->GetFunctionManager()->Add(this, &CScene::Process, NULL);
	m_iDestroyID = 0;
}

CScene::~CScene()
{
	CEngine::GetInstance()->GetFunctionManager()->Remove(m_iUpdateID);
	CEngine::GetInstance()->GetFunctionManager()->Remove(m_iDestroyID);
}

void CScene::Destroy(const unsigned int iId, void *pArgument)
{
	CEngine::GetInstance()->GetSceneManager()->Remove(this);
}

void CScene::SetPause(const bool bPause)
{
	if (bPause != m_bPause)
	{
		m_bPause = bPause;
		SetPauseInternal(bPause);
		if (bPause)
		{
			CEngine::GetInstance()->GetFunctionManager()->Remove(m_iUpdateID);
			m_iUpdateID = 0;
		}
		else
			m_iUpdateID = CEngine::GetInstance()->GetFunctionManager()->Add(this, &CScene::Process, NULL);
	}
}

void CScene::SetDestroy(const bool bDestroy)
{
	if (bDestroy != m_bDestroy)
	{
		m_bDestroy = bDestroy;
		if (bDestroy)
			m_iDestroyID = CEngine::GetInstance()->GetFunctionManager()->Add(this, &CScene::Destroy, NULL);
		{
			CEngine::GetInstance()->GetFunctionManager()->Remove(m_iDestroyID);
			m_iDestroyID = 0;
		}
	}
}

}

/* EOF */

