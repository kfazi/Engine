#ifndef ENGINE_ERROR_STACK_HPP
#define ENGINE_ERROR_STACK_HPP

#include "common.hpp"
#include "string.hpp"
#include <stack>
#include <boost/thread.hpp>

#undef NO_ERROR

namespace engine
{

/**
 * Class for storing error codes.
 */
class CErrorStack
{
	public:
		enum ECode
		{
			NO_ERROR,
			DOES_NOT_EXSISTS,
			IO_ERROR,
			OUT_OF_SPACE,
			OUT_OF_RANGE,
			PERMISSION_DENIED
		};

		struct SError
		{
			const ECode eCode;
			const CString cMessage;
			SError(const ECode eCode, const CString &cMessage): eCode(eCode), cMessage(cMessage)
			{
			}
		};

	private:
		typedef std::stack<const SError> TStack;
		/** Thread independent */
		static boost::thread_specific_ptr<TStack> m_cErrors;

	public:
		static void Init();
		static void Push(const ECode eCode, const CString &cMessage);
		static void Pop();
		static const SError &Check();
		static unsigned int Count();
};

}

#endif /* ENGINE_ERROR_STACK_HPP */

/* EOF */
