#include "../common.hpp"
#include "scene.hpp"

namespace engine
{

CScene::CScene()
{
	m_iUpdateID = CCore::GetInstance()->GetFunctionManager()->Add(this, &CScene::Process, NULL);
	m_iDestroyID = 0;
}

CScene::~CScene()
{
	CCore::GetInstance()->GetFunctionManager()->Remove(m_iUpdateID);
	CCore::GetInstance()->GetFunctionManager()->Remove(m_iDestroyID);
}

void CScene::Destroy(const unsigned int iId, void *pArgument)
{
	CCore::GetInstance()->GetSceneManager()->Remove(this);
}

void CScene::SetPause(const bool bPause)
{
	if (bPause != m_bPause)
	{
		m_bPause = bPause;
		SetPauseInternal(bPause);
		if (bPause)
		{
			CCore::GetInstance()->GetFunctionManager()->Remove(m_iUpdateID);
			m_iUpdateID = 0;
		}
		else
			m_iUpdateID = CCore::GetInstance()->GetFunctionManager()->Add(this, &CScene::Process, NULL);
	}
}

void CScene::SetDestroy(const bool bDestroy)
{
	if (bDestroy != m_bDestroy)
	{
		m_bDestroy = bDestroy;
		if (bDestroy)
			m_iDestroyID = CCore::GetInstance()->GetFunctionManager()->Add(this, &CScene::Destroy, NULL);
		{
			CCore::GetInstance()->GetFunctionManager()->Remove(m_iDestroyID);
			m_iDestroyID = 0;
		}
	}
}

}

/* EOF */

