#include "errorstack.hpp"

namespace engine
{

boost::thread_specific_ptr<CErrorStack::TStack> CErrorStack::m_cErrors;

void CErrorStack::Init()
{
	m_cErrors.reset(new TStack());
	Push(NO_ERROR, "");
}

void CErrorStack::Push(const CErrorStack::ECode eCode, const CString &cMessage)
{
	TStack *cStack = m_cErrors.get();
	cStack->push(SError(eCode, cMessage));
}

void CErrorStack::Pop()
{
	TStack *cStack = m_cErrors.get();
	if (cStack->size() > 1)
		cStack->pop();
}

void CErrorStack::Clear()
{
	TStack *cStack = m_cErrors.get();
	while (cStack->size() > 1)
		cStack->pop();
}

const CErrorStack::SError &CErrorStack::Check()
{
	TStack *cStack = m_cErrors.get();
	return cStack->top();
}

unsigned int CErrorStack::Count()
{
	TStack *cStack = m_cErrors.get();
	return cStack->size() - 1;
}

}

/* EOF */
