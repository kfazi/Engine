#include "../useful.hpp"
#include "scenemanager.hpp"
#include "scene.hpp"
#include "../engine.hpp"

#include "../time.hpp"

namespace engine
{

CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{
	/* Delete all scenes. */
	for (std::set<CScene *>::iterator cSceneIterator = m_cScenesSet.begin(); cSceneIterator != m_cScenesSet.end(); ++cSceneIterator)
		delete *cSceneIterator;
}

void CSceneManager::Add(CScene *pScene)
{
	m_cScenesSet.insert(pScene);
}

bool CSceneManager::Remove(CScene *pScene)
{
	std::set<CScene *>::iterator cFoundScene = m_cScenesSet.find(pScene);
	if (cFoundScene == m_cScenesSet.end())
	{
		Debug(Format("CSceneManager::Remove - Scene with address %p not found\n") % pScene);
		return false;
	}
	delete *cFoundScene;
	m_cScenesSet.erase(cFoundScene);
	return true;
}

}

/* EOF */

