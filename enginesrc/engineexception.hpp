#ifndef ENGINE_EXCEPTION_HPP
#define ENGINE_EXCEPTION_HPP

#include "common.hpp"
#include <exception>
#include "string.hpp"

namespace engine
{

class CEngineException: public std::exception
{
	private:
		CString cMessage;
	public:
		CEngineException(const CString &cMessage)
		{
			this->cMessage = cMessage;
		}

		virtual ~CEngineException() throw()
		{
		}

		virtual const char *what() const throw()
		{
			return cMessage.ToUTF8().c_str();
		}
};

}

#endif /* ENGINE_EXCEPTION_HPP */

/* EOF */

