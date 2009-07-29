#ifndef ENGINE_FUCTIONMANAGER_HPP
#define ENGINE_FUCTIONMANAGER_HPP

#include "common.hpp"
#include <map>
#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace engine
{

/**
 * Class for manipulating functions with delayed execution time.
 * Use it through CCore singleton.
 */
class DLLEXPORTIMPORT CFunctionManager
{
	/** Allow CCore to create this class, and run Process() every frame. */
	friend class CCore;

	private:
		/**
		 * Class with private functor data.
		 */
		class CFunctorData
		{
			public:
				/** How many frames the functor still has to wait before it's executed. */
				unsigned int iFramesDelay;

				/** Initial number of frames, the functor has to wait before it's executed. */
				unsigned int iInitialFramesDelay;

				/** User contribued data. */
				void *pArgument;

				/** The functor itself. */
				boost::function<void (const unsigned int, void *)> pFunctor;

				/** Constructor.
				 *
				 * @param[in] pFunctor The functor.
				 * @param[in] pArgument User contribued data.
				 * @param[in] iFramesDelay How many frames the functor has to wait before it's executed.
				 */
				CFunctorData(boost::function<void (const unsigned int, void *)> pFunctor, void *pArgument, const unsigned int iFramesDelay)
				{
					this->iFramesDelay = iFramesDelay;
					this->iInitialFramesDelay = iFramesDelay;
					this->pArgument = pArgument;
					this->pFunctor = pFunctor;
				}
		};

		/** Next ID to assign when new function is added. */
		unsigned int m_iNextId;

		/** Map of functors. */
		std::map<unsigned int, CFunctorData> m_cFunctorMap;

		/** Constructor. */
		CFunctionManager();

		/** Destructor. */
		~CFunctionManager();

		/**
		 * Generates next ID for new function.
		 *
		 * @return Next ID.
		 */
		unsigned int GetNextId();

		/**
		 * Increments time of all functions, and executes when delay has been reached.
		 */
		void Process();

	public:
		/**
		 * Adds new function with explicitly given ID for delayed execution.
		 * Functors have to remove themselves, or they will be executed again after their delay is reached again.
		 *
		 * @param[in] cClass A pointer to the class instance, containing the function.
		 * @param[in] pFunction A pointer to the function, returning void and taking const unsigned int, void * arguments.
		 * @param[in] pArgument User contribued data.
		 * @param[in] iFramesDelay How many frames the function has to wait before it's executed.
		 * @param[in] iId ID of the function.
		 * @return ID of the function.
		 */
		template <class CClass> unsigned int Add(CClass *cClass, void (CClass::*pFunctor)(const unsigned int, void *), void *pArgument, const unsigned int iFramesDelay, const unsigned int iId)
		{
			m_cFunctorMap.insert(std::make_pair(iId, CFunctorData(boost::bind(pFunctor, cClass, _1, _2), pArgument, iFramesDelay)));
			return iId;
		}

		/**
		 * Adds new function for delayed execution.
		 * Functors have to remove themselves, or they will be executed again after their delay is reached again.
		 *
		 * @param[in] cClass A pointer to the class instance, containing the function.
		 * @param[in] pFunction A pointer to the function, returning void and taking const unsigned int, void * arguments.
		 * @param[in] pArgument User contribued data.
		 * @param[in] iFramesDelay How many frames the function has to wait before it's executed.
		 * @return ID of the function.
		 */
		template <class CClass> unsigned int Add(CClass *cClass, void (CClass::*pFunctor)(const unsigned int, void *), void *pArgument, const unsigned int iFramesDelay = 0)
		{
			return Add(cClass, pFunctor, pArgument, iFramesDelay, GetNextId());
		}

		/**
		 * Removes function with given ID.
		 *
		 * @param[in] iId ID of function to remove.
		 * @return True, when function was successfully removed. False otherwise.
		 */
		bool Remove(const unsigned int iId);
};

}

#endif /* ENGINE_FUCTIONMANAGER_HPP */

/* EOF */

