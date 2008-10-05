#ifndef ENGINE_USEFUL_HPP
#define ENGINE_USEFUL_HPP

#include "engine.hpp"
#include "logger.hpp"
#include <string>
#include <boost/format.hpp>

namespace engine
{

inline void Log(const std::string &cMessage, const CLogger::EMessageType eMessageType = CLogger::NOTIFY)
{
	CEngine::GetInstance()->GetLogger()->Log(cMessage, eMessageType);
}

inline void Log(const boost::format &cFormat, const CLogger::EMessageType eMessageType = CLogger::NOTIFY)
{
	Log(boost::str(cFormat), eMessageType);
}

inline boost::format Format(const std::string &cFormat)
{
	return boost::format(cFormat);
}

}

#endif /* ENGINE_USEFUL_HPP */

/* EOF */

