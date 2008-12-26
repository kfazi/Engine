#ifndef ENGINE_EXCEPTION_HPP
#define ENGINE_EXCEPTION_HPP

#include "common.hpp"
#include <exception>
#include <string>

namespace engine
{

class CEngineException: public std::exception
{
	private:
		std::string cMessage;
	public:
		CEngineException(const std::string &cMessage)
		{
			this->cMessage = cMessage;
		}

		virtual ~CEngineException() throw()
		{
		}

		virtual const char *what() const throw()
		{
			return cMessage.c_str();
		}
};

}

#endif /* ENGINE_EXCEPTION_HPP */

/* EOF */

