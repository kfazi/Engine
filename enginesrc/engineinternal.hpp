#ifndef ENGINE_ENGINE_INTERNAL_HPP
#define ENGINE_ENGINE_INTERNAL_HPP

#include <string>
#include <string>
#include <boost/format.hpp>
#include "common.hpp"

int main();

namespace engine
{

class CSceneManager;
class CFunctionManager;
class CSystemWindow;
class CSystemInfo;
class CLogger;

/**
 * Main engine class.
 * This is singleton.
 * Use it to communicate with the engine.
 */
class CEngine
{
	friend int ::main();
	friend void Debug(const std::string &cMessage);
	friend void Debug(const boost::format &cFormat);

	private:
		CSceneManager *m_pSceneManager; /**< Pointer to the scene manager. */
		CFunctionManager *m_pFunctionManager; /**< Pointer to the function manager. */
		CSystemWindow *m_pSystemWindow; /**< Pointer to the system window object. */
		CSystemInfo *m_pSystemInfo; /**< Pointer to the system info object. */
		CLogger *m_pLogger; /**< Pointer to the logger system. */
		double m_fFrameTime; /**< How much time passed in last frame. */
		bool m_bFinished;
		static bool m_bDebug;
		static CEngine *m_pEngine; /**< Makes sure CEngine is created before main(). */

		/**
		 * Private constructor.
		 */
		CEngine();

		/**
		 * Private destructor.
		 */
		~CEngine();

		static void Create(CEngine *pEngine);

	public:
		/**
		 * @return Instance of the engine.
		 */
		inline static CEngine *GetInstance()
		{
			return m_pEngine;
		}

		/**
		 * @return Pointer to the scene manager object.
		 */
		inline CSceneManager *GetSceneManager()
		{
			return m_pSceneManager;
		}

		/**
		 * @return Pointer to the function manager object.
		 */
		inline CFunctionManager *GetFunctionManager()
		{
			return m_pFunctionManager;
		}

		/**
		 * @return Pointer to the system window object.
		 */
		inline CSystemWindow *GetWindow()
		{
			return m_pSystemWindow;
		}

		/**
		 * @return Pointer to the system info object.
		 */
		inline CSystemInfo *GetSystemInfo()
		{
			return m_pSystemInfo;
		}

		/**
		 * @return Pointer to the logger system object.
		 */
		inline CLogger *GetLogger()
		{
			return m_pLogger;
		}

		inline bool Finished() const
		{
			return m_bFinished;
		}

		inline void Finish()
		{
			m_bFinished = true;
		}

		/**
		 * Convert CEngine to a string.
		 * Creates string with all engine objects converted to a string.
		 * @return A string.
		 */
		std::string ToString() const
		{
			return "CEngine[ ";// + m_pSceneManager->ToString() + " ]";
		}

		/**
		 * Processes next frame.
		 */
		void ProcessFrame();
};

}

#endif /* ENGINE_ENGINE_INTERNAL_HPP */

/* EOF */
