#ifndef COMMON_OUTPUT_STREAM_HPP
#define COMMON_OUTPUT_STREAM_HPP

#include "../Internal.hpp"
#include "CStreamBase.hpp"

namespace Common
{

class COutputStream: public CStreamBase
{
	private:
		void IntegerToString(unsigned long long iValue);

	protected:
		virtual String& GetWriteBuffer() = 0;

	public:
		virtual void SetWritePosition(unsigned int iPosition) = 0;
		virtual unsigned int GetWritePosition() = 0;
		virtual void Write(const char* pData, unsigned int iDataSize) = 0;

		COutputStream& operator<< (bool bValue);
		COutputStream& operator<< (short iValue);
		COutputStream& operator<< (unsigned short iValue);
		COutputStream& operator<< (int iValue);
		COutputStream& operator<< (unsigned int iValue);
		COutputStream& operator<< (long iValue);
		COutputStream& operator<< (unsigned long iValue);
		COutputStream& operator<< (long long iValue);
		COutputStream& operator<< (unsigned long long iValue);
		COutputStream& operator<< (float fValue);
		COutputStream& operator<< (double fValue);
		COutputStream& operator<< (long double fValue);
		COutputStream& operator<< (const void* pValue);

};

}

#endif /* COMMON_OUTPUT_STREAM_HPP */

/* EOF */
