#ifdef WINDOWS

#include "../../common.hpp"
#include "windowssystemerrormessages.hpp"
#include <windows.h>

namespace engine
{

CString CWindowsSystemErrorMessages::GetError(unsigned int iErrorCode)
{
	wchar_t *pTemp = NULL;
	int nLen = ::FormatMessageW(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, 
		iErrorCode,
		0 /*MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)*/,
		(LPWSTR)&pTemp,
		1,
		NULL);
	/* wchar_t is unsigned short under Windows. */
	CString cResult = reinterpret_cast<unsigned short *>(pTemp);
	::LocalFree(pTemp);
	return cResult;
}

}

#endif /* WINDOWS */

/* EOF */
