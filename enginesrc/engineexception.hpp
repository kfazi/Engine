#ifndef ENGINE_EXCEPTION_HPP
#define ENGINE_EXCEPTION_HPP

#include <exception>
#include <string>
#include "common.hpp"

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

#endif /* ENGINE_EXCEPTION_HPP */

/* EOF */

