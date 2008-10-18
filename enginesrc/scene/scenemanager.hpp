#ifndef ENGINE_SCENEMANAGER_HPP
#define ENGINE_SCENEMANAGER_HPP

#include "../functionmanager.hpp"
#include <string>
#include <set>

namespace engine
{

class CScene;

class CSceneManager
{
	/* Allow engine to create this class. */
	friend class CEngine;
	private:
		std::set<CScene *> m_cScenesSet;
		CSceneManager();
		~CSceneManager();
	public:
		void Add(CScene *pScene);
		bool Remove(CScene *pScene);
		std::string ToString() const
		{
			return std::string("CSceneManager[ ") + std::string(" ]");
		}
};

}

#endif /* ENGINE_SCENEMANAGER_HPP */

/* EOF */

