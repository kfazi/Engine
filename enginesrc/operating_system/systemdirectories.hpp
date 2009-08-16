#ifndef ENGINE_SYSTEM_DIRECTORIES_HPP
#define ENGINE_SYSTEM_DIRECTORIES_HPP

#include "../common.hpp"
#include "../string.hpp"
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>

namespace engine
{

class DLLEXPORTIMPORT CSystemDirectories
{
	public:
		class CFilesList
		{
			public:
				enum EType
				{
					RegularFile,
					Directory,
					SymLink,
					Other
				};

			private:
				typedef boost::shared_ptr<CString> TStringPtr;
				std::vector<TStringPtr> m_cFiles;

			public:
				~CFilesList();
				unsigned int GetCount() const;
				const CString &GetName(unsigned int iFileNumber) const;
				void AddFile(const CString &cPath);
		};

	private:
		CString m_cConfigPath;
		CString m_cExecutablePath;
		CString m_cModsPath;
		CString m_cResourcesPath;
		CString m_cSavesPath;

	protected:
		void SetConfigPath(const CString &cConfigPath);
		void SetExecutablePath(const CString &cExecutablePath);
		void SetModsPath(const CString &cModsPath);
		void SetResourcesPath(const CString &cResourcesPath);
		void SetSavesPath(const CString &cSavesPath);

	public:
		CSystemDirectories();
		virtual ~CSystemDirectories();

		virtual void CorrectPath(CString &cPath) = 0;
		virtual CString GetLibraryPrefix() const = 0;
		virtual CString GetLibraryPostfix() const = 0;

		bool CreateDirectory(const CString &cPath);
		bool Remove(const CString &cPath, bool bRecurring = false);
		CFilesList GetFilesList(const CString &cPath, const CString &cRegexFile);

		const CString &GetConfigPath();
		const CString &GetExecutablePath();
		const CString &GetModsPath();
		const CString &GetResourcesPath();
		const CString &GetSavesPath();
};

}

#endif /* ENGINE_SYSTEM_DIRECTORIES_HPP */

/* EOF */
