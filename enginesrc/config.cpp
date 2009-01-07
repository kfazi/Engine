#include "config.hpp"

namespace engine
{

CConfig::CConfig(const std::string &cFileName)
{
	Load(cFileName);
}

CConfig::~CConfig()
{
}

void CConfig::Load(const std::string &cFileName)
{
}

void CConfig::Save()
{
}

const std::string &CConfig::GetValue(const std::string &cName, const std::string &cDefaultValue)
{
	return cDefaultValue;
}

void CConfig::SetValue(const std::string &cName, const std::string &cValue)
{
}

void CConfig::SetValue(const std::string &cName, const int iValue)
{
}

void CConfig::SetValue(const std::string &cName, const unsigned int iValue)
{
}

void CConfig::SetValue(const std::string &cName, const double fValue)
{
}

}

/* EOF */
