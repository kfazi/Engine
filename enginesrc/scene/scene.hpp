#ifndef KFZ_SCENE_HPP
#define KFZ_SCENE_HPP

#include "sceneobject.hpp"
#include "scenemanager.hpp"
#include "../functionmanager.hpp"
#include "../engine.hpp"
#include <list>

namespace kfz
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
		virtual void Process(void *pArgument) = 0;
		void Destroy(void *pArgument);
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

#endif /* KFZ_SCENE_HPP */

/* EOF */

