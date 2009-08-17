#ifndef ENGINE_FUCTIONMANAGER_HPP
#define ENGINE_FUCTIONMANAGER_HPP

#include "common.hpp"
#include <vector>
#include <queue>
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
		 * Struct with private functor data.
		 */
		struct SFunctorData
		{
			/** How many frames the functor still has to wait before it's executed. */
			unsigned int iFramesDelay;

			/** Initial number of frames, the functor has to wait before it's executed. */
			unsigned int iInitialFramesDelay;

			/** User contributed data. */
			void *pArgument;

			/** The functor itself. */
			boost::function<void (const unsigned int, void *)> pFunctor;

			/** Flag indicating if functor has been removed. */
			bool bRemoved;

			/**
			 * Constructor.
			 *
			 * @param[in] pFunctor The functor.
			 * @param[in] pArgument User contributed data.
			 * @param[in] iFramesDelay How many frames the functor has to wait before it's executed.
			 */
			SFunctorData(boost::function<void (const unsigned int, void *)> pFunctor, void *pArgument, const unsigned int iFramesDelay)
			{
				this->iFramesDelay = iFramesDelay;
				this->iInitialFramesDelay = iFramesDelay;
				this->pArgument = pArgument;
				this->pFunctor = pFunctor;
				bRemoved = false;
			}

			/**
			 * Constructor.
			 */
			SFunctorData()
			{
				bRemoved = true;
			}
		};

		/** Registered functors. */
		std::vector<SFunctorData> m_cRegisteredFunctors;

		/** Unregistered functors indices. */
		std::queue<unsigned int> m_cUnregisteredFunctorsIndices;

		/** Constructor. */
		CFunctionManager(unsigned int iAllocationBase = 100);

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
		 * Adds new function for delayed execution.
		 * Functors have to remove themselves, or they will be executed again after their delay is reached again.
		 *
		 * @param[in] cClass A pointer to the class instance, containing the function.
		 * @param[in] pFunction A pointer to the function, returning void and taking const unsigned int, void * arguments.
		 * @param[in] pArgument User contributed data.
		 * @param[in] iFramesDelay How many frames the function has to wait before it's executed.
		 * @return ID of the function.
		 */
		template <class CClass> unsigned int Add(CClass *cClass, void (CClass::*pFunctor)(const unsigned int, void *), void *pArgument, const unsigned int iFramesDelay = 0)
		{
			unsigned int iId = GetNextId();
			if (m_cRegisteredFunctors.size() <= iId)
				m_cRegisteredFunctors.resize(m_cRegisteredFunctors.size() * 2 + 1, SFunctorData());
			m_cRegisteredFunctors[iId] = SFunctorData(boost::bind(pFunctor, cClass, _1, _2), pArgument, iFramesDelay);
			return iId;
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

