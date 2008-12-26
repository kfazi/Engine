#ifndef ENGINE_USEFUL_HPP
#define ENGINE_USEFUL_HPP

#include "common.hpp"
#include <string>
#include <boost/format.hpp>
#include "core.hpp"
#include "logger.hpp"

namespace engine
{

inline void Debug(const std::string &cMessage)
{
	if (CCore::m_bDebug)
		CCore::GetInstance()->GetLogger()->Log(cMessage, CLogger::DEBUG);
}

inline void Debug(const boost::format &cFormat)
{
	if (CCore::m_bDebug)
		Debug(boost::str(cFormat));
}

inline void Notify(const std::string &cMessage)
{
	CCore::GetInstance()->GetLogger()->Log(cMessage, CLogger::NOTIFY);
}

inline void Notify(const boost::format &cFormat)
{
	Notify(boost::str(cFormat));
}

inline void Warning(const std::string &cMessage)
{
	CCore::GetInstance()->GetLogger()->Log(cMessage, CLogger::WARNING);
}

inline void Warning(const boost::format &cFormat)
{
	Warning(boost::str(cFormat));
}

inline void Error(const std::string &cMessage)
{
	CCore::GetInstance()->GetLogger()->Log(cMessage, CLogger::FATALERROR);
}

inline void Error(const boost::format &cFormat)
{
	Error(boost::str(cFormat));
}

inline boost::format Format(const std::string &cFormat)
{
	return boost::format(cFormat);
}

}

#endif /* ENGINE_USEFUL_HPP */

/* EOF */

