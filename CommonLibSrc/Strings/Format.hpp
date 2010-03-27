#ifndef COMMON_FORMAT_HPP
#define COMMON_FORMAT_HPP

#include "../Internal.hpp"
#include "../Containers/Vector.hpp"
#include "String.hpp"

namespace Common
{

class CFormat
{
	private:
		struct SData
		{
			unsigned int iIndex;
			String* pString;
		};
		const String& m_cUnformattedBuffer;
		String* m_pBuffer;
		Vector<SData>* m_pFormatData;
		unsigned int m_iCurrentIndex;
		unsigned int m_iMaxIndex;

	public:
		CFormat(const String& cString);
		const String& Get() const;
		const Char* GetRaw() const;
		CFormat& operator% (const int& iValue)
		{
			delete m_pBuffer;
			m_pBuffer = 0;
			SData sData;
			sData.iIndex = m_iCurrentIndex;
			sData.pString = new String(1);
//			m_pFormatData->PushBack(sData);
			m_iCurrentIndex++;
		}
};

}

#endif /* COMMON_FORMAT_HPP */

/* EOF */
