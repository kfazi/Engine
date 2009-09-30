#ifndef COMMON_FORMAT_HPP
#define COMMON_FORMAT_HPP

#include "../Internal.hpp"
#include "../Containers/CVector.hpp"
#include "CString.hpp"

namespace Common
{

class CFormat
{
	private:
		struct SData
		{
			unsigned int iIndex;
			CString *pString;
		};
		CString m_cUnformattedBuffer;
		CString *m_pBuffer;
		CVector<SData> *m_pFormatData;
		unsigned int m_iCurrentIndex;
		unsigned int m_iMaxIndex;

	public:
		CFormat(const CString &cString);
		const CString &Get() const;
		const TChar *GetRaw() const;
		CFormat &operator % (const int &iValue)
		{
			delete m_pBuffer;
			m_pBuffer = 0;
			SData sData;
			sData.iIndex = m_iCurrentIndex;
			sData.pString = new CString(1);
			m_pFormatData->PushBack(sData);
			m_iCurrentIndex++;
		}
};

}

#endif /* COMMON_FORMAT_HPP */

/* EOF */
