#ifndef ENGINE_ENGINE_HPP
#define ENGINE_ENGINE_HPP

#include "config.hpp"
#include <string>

#include <iostream>

#include "logger.hpp"

namespace engine
{

class CSceneManager;
class CFunctionManager;
class CLogger;

/**
 * Main engine class.
 * This is singleton.
 * Use it to communicate with the engine.
 */
class CEngine
{
	private:
		CSceneManager *m_pSceneManager; /**< Pointer to the scene manager. */
		CFunctionManager *m_pFunctionManager; /**< Pointer to the function manager. */
		CLogger *m_pLogger; /**< Pointer to the logger system. */
		real m_fFrameTime; /**< How much time passed in last frame. */
		static CEngine cEngine; /**< Makes sure CEngine is created before main(). */
		/**
		 * Private constructor.
		 */
		CEngine();
		/**
		 * Private destructor.
		 */
		~CEngine();

	public:
		/**
		 * @return Instance of the engine.
		 */
		inline static CEngine *GetInstance()
		{
			return &cEngine;
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
		 * @return Pointer to the logger system object.
		 */
		inline CLogger *GetLogger()
		{
			return m_pLogger;
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

/*********************** TEMPORARY TESTING HACKS ***********************/
		void ShowLog(const std::string &cMessage, const CLogger::EMessageType eType)
		{
			std::cout << cMessage << std::endl;
		}
};

}

#endif /* ENGINE_ENGINE_HPP */

/* EOF */

