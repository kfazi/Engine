#ifndef ENGINE_CONFIG_HPP
#define ENGINE_CONFIG_HPP

#include <string>

namespace engine
{

class CConfig
{
	friend class CCore;

	private:
		CConfig(const std::string &cFileName);
		~CConfig();
		void Load(const std::string &cFileName);
	public:
		void Save();
		const std::string &GetValue(const std::string &cName, const std::string &cDefaultValue = "");
		void SetValue(const std::string &cName, const std::string &cValue);
		void SetValue(const std::string &cName, const int iValue);
		void SetValue(const std::string &cName, const unsigned int iValue);
		void SetValue(const std::string &cName, const double fValue);
};

}

#endif /* ENGINE_CONFIG_HPP */

/* EOF */
