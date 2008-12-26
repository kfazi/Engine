#ifndef ENGINE_SYSTEM_DIRECTORIES_HPP
#define ENGINE_SYSTEM_DIRECTORIES_HPP

#include "../common.hpp"
#include <string>

namespace engine
{

class CSystemDirectories
{
	private:
		std::string m_cConfigPath;
		std::string m_cExecutablePath;
		std::string m_cModsPath;
		std::string m_cResourcesPath;
		std::string m_cSavesPath;

	protected:
		inline void SetConfigPath(const std::string &cConfigPath)
		{
			m_cConfigPath = cConfigPath;
		}
		inline void SetExecutablePath(const std::string &cExecutablePath)
		{
			m_cExecutablePath = cExecutablePath;
		}
		inline void SetModsPath(const std::string &cModsPath)
		{
			m_cModsPath = cModsPath;
		}
		inline void SetResourcesPath(const std::string &cResourcesPath)
		{
			m_cResourcesPath = cResourcesPath;
		}
		inline void SetSavesPath(const std::string &cSavesPath)
		{
			m_cSavesPath = cSavesPath;
		}

	public:
		CSystemDirectories()
		{
		}

		virtual ~CSystemDirectories()
		{
		}

		inline const std::string &GetConfigPath()
		{
			return m_cConfigPath;
		}
		inline const std::string &GetExecutablePath()
		{
			return m_cExecutablePath;
		}
		inline const std::string &GetModsPath()
		{
			return m_cModsPath;
		}
		inline const std::string &GetResourcesPath()
		{
			return m_cResourcesPath;
		}
		inline const std::string &GetSavesPath()
		{
			return m_cSavesPath;
		}
};

}

#endif /* ENGINE_SYSTEM_DIRECTORIES_HPP */

/* EOF */
