#ifndef ENGINE_SCENE_HPP
#define ENGINE_SCENE_HPP

#include <list>
#include "../common.hpp"
#include "sceneobject.hpp"
#include "scenemanager.hpp"
#include "../functionmanager.hpp"
#include "../engine.hpp"

namespace engine
{

class CScene
{
	private:
		int m_iUpdateID;
		int m_iDestroyID;
		bool m_bPause;
		bool m_bDestroy;
	protected:
		std::list<CSceneObject *> m_cSceneObjectsHiearchy;
		virtual void SetPauseInternal(const bool bPause) = 0;
		virtual void AddObjectInternal(CSceneObject *pSceneObject) = 0;
	public:
		CScene();
		virtual ~CScene();
		virtual void Process(const unsigned int iId, void *pArgument) = 0;
		void Destroy(const unsigned int iId, void *pArgument);
		void SetPause(const bool bPause);
		inline void Pause()
		{
			SetPause(true);
		}
		inline void Resume()
		{
			SetPause(false);
		}
		inline bool GetPause() const
		{
			return m_bPause;
		}
		void SetDestroy(const bool bDestroy);
		inline void Destroy()
		{
			SetDestroy(true);
		}
		inline bool GetDestroy() const
		{
			return m_bDestroy;
		}
};

}

#endif /* ENGINE_SCENE_HPP */

/* EOF */

