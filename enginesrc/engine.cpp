#include "engine.hpp"
#include "config.hpp"
#include "time.hpp"
#include "debug.hpp"
#include "common.hpp"
#include "functionmanager.hpp"
#include "scene/scenemanager.hpp"
#include <boost/thread.hpp>

namespace kfz
{

CEngine CEngine::cEngine;

CEngine::CEngine()
{
	/* Function manager must be created before other managers. */
	m_pFunctionManager = new CFunctionManager();
	m_pSceneManager = new CSceneManager();
	m_fFrameTime = 0;
}

CEngine::~CEngine()
{
	delete m_pSceneManager;
}

void CEngine::ProcessFrame()
{
	static real fFrameWait = TO_REAL(1.0) / TO_REAL(KFZ_FPS);
	CTime::Update();
	m_fFrameTime += CTime::GetFrameTime();
/*	if (m_fFrameTime < fFrameWait)
	{
		boost::this_thread::sleep(boost::posix_time::milliseconds(static_cast<int>((fFrameWait - m_fFrameTime) * static_cast<real>(1000.0))));
		CTime::Update();
		m_fFrameTime += CTime::GetFrameTime();
	}*/
	while (m_fFrameTime >= fFrameWait)
	{
		m_pFunctionManager->Process();
		m_fFrameTime -= fFrameWait;
	}
}

}

/* EOF */

