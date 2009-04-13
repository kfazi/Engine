#ifndef ENGINE_USEFUL_HPP
#define ENGINE_USEFUL_HPP

#include "common.hpp"
#include <boost/format.hpp>
#include "core.hpp"
#include "logger.hpp"
#include "string.hpp"

namespace engine
{

inline void Debug(const CString &cMessage)
{
	if (CCore::m_bDebug)
		CCore::GetInstance()->GetLogger()->Log(cMessage, CLogger::DEBUG);
}

inline void Debug(const boost::basic_format<TChar> &cFormat)
{
	if (CCore::m_bDebug)
		Debug(cFormat.str());
}

inline void Notify(const CString &cMessage)
{
	CCore::GetInstance()->GetLogger()->Log(cMessage, CLogger::NOTIFY);
}

inline void Notify(const boost::basic_format<TChar> &cFormat)
{
	Notify(cFormat.str());
}

inline void Warning(const CString &cMessage)
{
	CCore::GetInstance()->GetLogger()->Log(cMessage, CLogger::WARNING);
}

inline void Warning(const boost::basic_format<TChar> &cFormat)
{
	Warning(cFormat.str());
}

inline void Error(const CString &cMessage)
{
	CCore::GetInstance()->GetLogger()->Log(cMessage, CLogger::FATALERROR);
}

inline void Error(const boost::basic_format<TChar> &cFormat)
{
	Error(cFormat.str());
}

inline boost::basic_format<TChar> Format(const CString &cFormat)
{
	return boost::basic_format<TChar>(cFormat);
}

}

#endif /* ENGINE_USEFUL_HPP */

/* EOF */

