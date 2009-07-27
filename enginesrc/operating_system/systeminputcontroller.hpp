#ifndef ENGINE_SYSTEM_INPUT_CONTROLLER_HPP
#define ENGINE_SYSTEM_INPUT_CONTROLLER_HPP

#include "../common.hpp"
#include <map>
#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace engine
{

template <class CDeviceClass, typename TEvent> class DLLEXPORTIMPORT CSystemInputController
{
	private:
		typedef boost::function<void (const CDeviceClass *, const TEvent)> TFunctor;
		std::map<unsigned int, TFunctor> m_cFunctorMap;

		/** Next ID to assign when new function is added. */
		unsigned int s_iNextId;

		/**
		 * Generates next ID for new function.
		 *
		 * @return Next ID.
		 */
		unsigned int GetNextId()
		{
			unsigned int iNextId = s_iNextId;
			while (m_cFunctorMap.find(iNextId) != m_cFunctorMap.end()) /* Make sure this ID isn't in use. */
				++iNextId;
			s_iNextId = iNextId + 1;
			return iNextId;
		}

	protected:
		void CallHandlers(const CDeviceClass *pDeviceClass, const TEvent tEvent)
		{
//			for (std::map<unsigned int, TFunctor>::iterator cFunctorIterator = m_cFunctorMap.begin(); cFunctorIterator != m_cFunctorMap.end(); ++cFunctorIterator)
//				(*cFunctorIterator)(pDeviceClass, tEvent);
		}

	public:
		enum EState
		{
			Pressed,
			Released
		};

		bool UnregisterHandler(const unsigned int iId)
		{
//			std::map<unsigned int, TFunctor>::iterator cFoundFunctor = m_cFunctorMap.find(iId);
//			if (cFoundFunctor == m_cFunctorMap.end())
//				return false;
//			m_cFunctorMap.erase(cFoundFunctor);
			return true;
		}

		template <class CClass> unsigned int RegisterHandler(CClass *cClass, void (CClass::*pFunctor)(const CDeviceClass *, const TEvent))
		{
			unsigned int iId = GetNextId();
			m_cFunctorMap.insert(std::make_pair(iId, TFunctor(boost::bind(pFunctor, cClass, _1, _2))));
			return iId;
		}
};

}

#endif /* ENGINE_SYSTEM_INPUT_CONTROLLER_HPP */

/* EOF */
