#ifndef ENGINE_FUCTIONMANAGER_HPP
#define ENGINE_FUCTIONMANAGER_HPP

#include "engine.hpp"
#include <map>

namespace engine
{

class CFunctionManager
{
	friend class CEngine;
	private:
		class CFunctor
		{
			public:
				unsigned int m_iFramesDelay;
				unsigned int m_iInitialFramesDelay;
				void *m_pArgument;
				virtual ~CFunctor()
				{
				}
				virtual void Call(const unsigned int iId, void *pUserData) = 0;
		};
		template <class CClass> class CSpecificFunctor: public CFunctor
		{
			private:
				void (CClass::*m_pFunction)(const unsigned int, void *);
				CClass *m_pClass;
			public:
				CSpecificFunctor(CClass *pClass, void (CClass::*pFunction)(const unsigned int, void *), void *pArgument, const unsigned int iFramesDelay)
				{
					m_pClass = pClass;
					m_pFunction = pFunction;
					m_pArgument = pArgument;
					m_iFramesDelay = iFramesDelay;
					m_iInitialFramesDelay = m_iFramesDelay;
				}
				virtual void Call(const unsigned int iId, void *pUserData)
				{
					(*m_pClass.*m_pFunction)(iId, pUserData);
				}
		};
		unsigned int m_iNextId;
		std::map<unsigned int, CFunctor *> m_cFunctionMap;
		unsigned int GetNextId();
		CFunctionManager();
		~CFunctionManager();
	public:
		template<class CClass> unsigned int Add(CClass *cClass, void (CClass::*pFunction)(const unsigned int, void *), void *pArgument, const unsigned int iFramesDelay, const unsigned int iId)
		{
			m_cFunctionMap.insert(std::make_pair(iId, new CSpecificFunctor<CClass>(cClass, pFunction, pArgument, iFramesDelay)));
			return iId;
		}
		template<class CClass> unsigned int Add(CClass *cClass, void (CClass::*pFunction)(const unsigned int, void *), void *pArgument, const unsigned int iFramesDelay = 0)
		{
			return Add(cClass, pFunction, pArgument, iFramesDelay, GetNextId());
		}
		bool Remove(const unsigned int iId);
		void Process();
};

}

#endif /* ENGINE_FUCTIONMANAGER_HPP */

/* EOF */

