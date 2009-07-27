#ifndef ENGINE_SCENEMANAGER_HPP
#define ENGINE_SCENEMANAGER_HPP

#include "../common.hpp"
#include <set>
#include "../string.hpp"
#include "../functionmanager.hpp"

namespace engine
{

class CScene;

class CSceneManager
{
	/* Allow engine to create this class. */
	friend class CCore;
	private:
		std::set<CScene *> m_cScenesSet;
		CSceneManager();
		~CSceneManager();
	public:
		void Add(CScene *pScene);
		bool Remove(CScene *pScene);
};

}

#endif /* ENGINE_SCENEMANAGER_HPP */

/* EOF */

