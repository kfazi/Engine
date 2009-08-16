#include "systemdirectories.hpp"
#include <boost/regex.hpp>

namespace engine
{

CSystemDirectories::CFilesList::~CFilesList()
{
}

unsigned int CSystemDirectories::CFilesList::GetCount() const
{
	return m_cFiles.size();
}

const CString &CSystemDirectories::CFilesList::GetName(unsigned int iFileNumber) const
{
	return *m_cFiles[iFileNumber];
}

void CSystemDirectories::CFilesList::AddFile(const CString &cPath)
{
	TStringPtr tStringPtr(new CString(cPath));
	m_cFiles.push_back(tStringPtr);
}

void CSystemDirectories::SetConfigPath(const CString &cConfigPath)
{
	m_cConfigPath = cConfigPath;
}

void CSystemDirectories::SetExecutablePath(const CString &cExecutablePath)
{
	m_cExecutablePath = cExecutablePath;
}

void CSystemDirectories::SetModsPath(const CString &cModsPath)
{
	m_cModsPath = cModsPath;
}

void CSystemDirectories::SetResourcesPath(const CString &cResourcesPath)
{
	m_cResourcesPath = cResourcesPath;
}

void CSystemDirectories::SetSavesPath(const CString &cSavesPath)
{
	m_cSavesPath = cSavesPath;
}

CSystemDirectories::CSystemDirectories()
{
}

CSystemDirectories::~CSystemDirectories()
{
}

bool CSystemDirectories::CreateDirectory(const CString &cPath)
{
	boost::filesystem::create_directories(cPath.ToWCHAR());
	return true;
}

bool CSystemDirectories::Remove(const CString &cPath, bool bRecurring)
{
	boost::filesystem::remove(cPath.ToWCHAR());
	return true;
}

CSystemDirectories::CFilesList CSystemDirectories::GetFilesList(const CString &cPath, const CString &cRegexFile)
{
	CFilesList cFilesList;

	if (!boost::filesystem::exists(cPath.ToWCHAR()) || !boost::filesystem::is_directory(cPath.ToWCHAR()))
		return cFilesList;

	boost::filesystem::wdirectory_iterator iter(cPath.ToWCHAR()), end_iter;
	for (; iter != end_iter; ++iter)
	{
		boost::filesystem::wpath filename = iter->path();
		if (CString(filename.native_file_string()).MatchRegex(cRegexFile))
			cFilesList.AddFile(filename.native_file_string());
	}
	return cFilesList;
}

const CString &CSystemDirectories::GetConfigPath()
{
	return m_cConfigPath;
}

const CString &CSystemDirectories::GetExecutablePath()
{
	return m_cExecutablePath;
}

const CString &CSystemDirectories::GetModsPath()
{
	return m_cModsPath;
}

const CString &CSystemDirectories::GetResourcesPath()
{
	return m_cResourcesPath;
}

const CString &CSystemDirectories::GetSavesPath()
{
	return m_cSavesPath;
}

}

/* EOF */
