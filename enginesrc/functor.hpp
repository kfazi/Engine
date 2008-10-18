#ifndef ENGINE_FUNCTOR_HPP
#define ENGINE_FUNCTOR_HPP

#include <cstring>

namespace engine
{

class CFunctorBase
{
	protected:
	public:
		void *m_pClass;
		void *m_pFunction;
		void *m_pPrivateData;
		int m_iFunctionSize;
	public:
		inline void *GetPrivateData()
		{
			return m_pPrivateData;
		}
		bool operator == (const CFunctorBase &cFunctor) const
		{
			return (m_pClass == cFunctor.m_pClass) && (m_iFunctionSize == cFunctor.m_iFunctionSize) && (!std::memcmp(m_pFunction, cFunctor.m_pFunction, m_iFunctionSize));
		}
};

/* Base */
template <typename TReturnType> class CFunctor0Base: public CFunctorBase
{
	public:
		virtual ~CFunctor0Base() = 0;
		virtual TReturnType Call() = 0;
};

template <typename TReturnType, typename TType1> class CFunctor1Base: public CFunctorBase
{
	public:
		virtual ~CFunctor1Base() = 0;
		virtual TReturnType Call(TType1 tParam1) = 0;
};

template <typename TReturnType, typename TType1, typename TType2> class CFunctor2Base: public CFunctorBase
{
	public:
		virtual ~CFunctor2Base() = 0;
		virtual TReturnType Call(TType1 tParam1, TType2 tParam2) = 0;
};

/* Specific */
template <class CClass, typename TReturnType> class CFunctor0: public CFunctor0Base<TReturnType>
{
	protected:
		typedef TReturnType (CClass::*PFunction)();
	public:
		CFunctor0(CClass *pClass, PFunction pFunction)
		{
			this->m_pClass = pClass;
			this->m_iFunctionSize = sizeof(PFunction);
			this->m_pFunction = new char[this->m_iFunctionSize];
			std::memcpy(this->m_pFunction, pFunction, this->m_iFunctionSize);
		}
		virtual ~CFunctor0()
		{
			delete [] this->m_pFunction;
		}
		TReturnType Call()
		{
			return (*(static_cast<CClass *>(this->m_pClass)).*(static_cast<PFunction>(this->m_pFunction)))();
		}
};

template <class CClass, typename TReturnType, typename TType1> class CFunctor1: public CFunctor1Base<TReturnType, TType1>
{
	protected:
		typedef TReturnType (CClass::*PFunction)(TType1);
	public:
		CFunctor1(CClass *pClass, PFunction pFunction)
		{
			this->m_pClass = pClass;
			this->m_iFunctionSize = sizeof(PFunction);
			this->m_pFunction = new char[this->m_iFunctionSize];
			std::memcpy(this->m_pFunction, pFunction, this->m_iFunctionSize);
		}
		virtual ~CFunctor1()
		{
			delete [] this->m_pFunction;
		}
		TReturnType Call(TType1 tParam1)
		{
			return (*(static_cast<CClass *>(this->m_pClass)).*(static_cast<PFunction>(this->m_pFunction)))(tParam1);
		}
};

template <class CClass, typename TReturnType, typename TType1, typename TType2> class CFunctor2: public CFunctor2Base<TReturnType, TType1, TType2>
{
	protected:
		typedef TReturnType (CClass::*PFunction)(TType1, TType2);
	public:
		CFunctor2(CClass *pClass, PFunction pFunction)
		{
			this->m_pClass = pClass;
			this->m_iFunctionSize = sizeof(PFunction);
			this->m_pFunction = new char[this->m_iFunctionSize];
			std::memcpy(this->m_pFunction, reinterpret_cast<const void *>(pFunction), this->m_iFunctionSize);
		}
		virtual ~CFunctor2()
		{
			delete [] this->m_pFunction;
		}
		TReturnType Call(TType1 tParam1, TType2 tParam2)
		{
			return (*(static_cast<CClass *>(this->m_pClass)).*(static_cast<PFunction>(this->m_pFunction)))(tParam1, tParam2);
		}
};

}

#endif /* ENGINE_FUNCTOR_HPP */

/* EOF */

