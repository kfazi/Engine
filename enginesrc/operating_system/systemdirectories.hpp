#ifndef ENGINE_SYSTEM_DIRECTORIES_HPP
#define ENGINE_SYSTEM_DIRECTORIES_HPP

#include "../common.hpp"
#include "../string.hpp"

namespace engine
{

class DLLEXPORTIMPORT CSystemDirectories
{
	private:
		CString m_cConfigPath;
		CString m_cExecutablePath;
		CString m_cModsPath;
		CString m_cResourcesPath;
		CString m_cSavesPath;

	protected:
		inline void SetConfigPath(const CString &cConfigPath)
		{
			m_cConfigPath = cConfigPath;
		}
		inline void SetExecutablePath(const CString &cExecutablePath)
		{
			m_cExecutablePath = cExecutablePath;
		}
		inline void SetModsPath(const CString &cModsPath)
		{
			m_cModsPath = cModsPath;
		}
		inline void SetResourcesPath(const CString &cResourcesPath)
		{
			m_cResourcesPath = cResourcesPath;
		}
		inline void SetSavesPath(const CString &cSavesPath)
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

		virtual void CorrectPath(CString &cPath) = 0;

		inline const CString &GetConfigPath()
		{
			return m_cConfigPath;
		}
		inline const CString &GetExecutablePath()
		{
			return m_cExecutablePath;
		}
		inline const CString &GetModsPath()
		{
			return m_cModsPath;
		}
		inline const CString &GetResourcesPath()
		{
			return m_cResourcesPath;
		}
		inline const CString &GetSavesPath()
		{
			return m_cSavesPath;
		}
};

}

#endif /* ENGINE_SYSTEM_DIRECTORIES_HPP */

/* EOF */
