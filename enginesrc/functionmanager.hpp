#ifndef ENGINE_FUCTIONMANAGER_HPP
#define ENGINE_FUCTIONMANAGER_HPP

#include "engine.hpp"
#include "functor.hpp"
#include <map>

namespace engine
{

class CFunctionManager
{
	/** Allow CEngine to create this class. */
	friend class CEngine;
	private:
		class CFunctorData
		{
			public:
				unsigned int m_iFramesDelay;
				unsigned int m_iInitialFramesDelay;
				void *m_pArgument;
		};
		template <class CClass> class CSpecificFunctor: public CFunctor2<CClass, void, const unsigned int, void *>
		{
			public:
				CSpecificFunctor(CClass *pClass, void (CClass::*pFunction)(const unsigned int, void *), void *pArgument, const unsigned int iFramesDelay): CFunctor2<CClass, void, const unsigned int, void *>(pClass, pFunction)
				{
					CFunctorData *pPrivateData = new CFunctorData;
					pPrivateData->m_pArgument = pArgument;
					pPrivateData->m_iFramesDelay = iFramesDelay;
					pPrivateData->m_iInitialFramesDelay = iFramesDelay;
					this->m_pPrivateData = pPrivateData;
				}
				virtual ~CSpecificFunctor()
				{
					delete this->m_pPrivateData;
				}
		};
		unsigned int m_iNextId;
		std::map<unsigned int, CFunctor2Base<void, const unsigned int, void *> *> m_cFunctionMap;
		unsigned int GetNextId();
		CFunctionManager();
		~CFunctionManager();
	public:
		template <class CClass> unsigned int Add(CClass *cClass, void (CClass::*pFunction)(const unsigned int, void *), void *pArgument, const unsigned int iFramesDelay, const unsigned int iId)
		{
			m_cFunctionMap.insert(std::make_pair(iId, new CSpecificFunctor<CClass>(cClass, pFunction, pArgument, iFramesDelay)));
			return iId;
		}
		template <class CClass> unsigned int Add(CClass *cClass, void (CClass::*pFunction)(const unsigned int, void *), void *pArgument, const unsigned int iFramesDelay = 0)
		{
			return Add(cClass, pFunction, pArgument, iFramesDelay, GetNextId());
		}
		bool Remove(const unsigned int iId);
		void Process();
};

}

#endif /* ENGINE_FUCTIONMANAGER_HPP */

/* EOF */

