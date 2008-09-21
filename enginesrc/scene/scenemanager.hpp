#ifndef KFZ_SCENEMANAGER_HPP
#define KFZ_SCENEMANAGER_HPP

#include "../functionmanager.hpp"
#include <string>
#include <set>

namespace kfz
{

class CScene;

class CSceneManager
{
	private:
		std::set<CScene *> m_cScenesSet;
	public:
		CSceneManager();
		~CSceneManager();
		void Add(CScene *pScene);
		bool Remove(CScene *pScene);
		std::string ToString() const
		{
			return std::string("CSceneManager[ ") + std::string(" ]");
		}
};

}

#endif /* KFZ_SCENEMANAGER_HPP */

/* EOF */

