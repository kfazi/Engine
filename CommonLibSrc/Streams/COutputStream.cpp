#include "COutputStream.hpp"
#include "../Algorithms/Swap.hpp"

namespace Common
{

void COutputStream::IntegerToString(unsigned long long iValue)
{
	static const char aDigitsUpperCase[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	static const char aDigitsLowerCase[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

	String& cResult = GetWriteBuffer();
	int iStartIndex = cResult.GetLength();
	int iBase = GetBase();
	const char* pDigits;
	if (GetNumberUpperCase())
		pDigits = aDigitsUpperCase;
	else
		pDigits = aDigitsLowerCase;
	do 
	{
		cResult += pDigits[iValue % iBase];
		iValue /= iBase;
	}
	while (iValue > 0);
	if (GetAddBase())
	{
		switch (GetBase())
		{
		case BINARY:
			if (GetBaseUpperCase())
				cResult += "B0";
			else
				cResult += "b0";
			break;
		case OCTAL:
			cResult += "0";
			break;
		case DECIMAL:
			break;
		case HEXADECIMAL:
			if (GetBaseUpperCase())
				cResult += "X0";
			else
				cResult += "x0";
			break;
		}
	}
	SwapRange(&cResult[0] + iStartIndex, &cResult[0] + cResult.GetLength());
}

COutputStream& COutputStream::operator<< (bool bValue)
{
	String& cResult = GetWriteBuffer();
	if (GetBoolAlpha())
	{
		String cTemp = (bValue) ? "true" : "false";
		if (GetNumberUpperCase())
			cTemp.ToUpper();
		cResult += cTemp;
	}
	else
		cResult += (bValue) ? "1" : "0";
	return *this;
}

COutputStream& COutputStream::operator<< (short iValue)
{
	return *this;
}

COutputStream& COutputStream::operator<< (unsigned short iValue)
{
	return *this;
}

COutputStream& COutputStream::operator<< (int iValue)
{
	return *this;
}

COutputStream& COutputStream::operator<< (unsigned int iValue)
{
	return *this;
}

COutputStream& COutputStream::operator<< (long iValue)
{
	return *this;
}

COutputStream& COutputStream::operator<< (unsigned long iValue)
{
	return *this;
}

COutputStream& COutputStream::operator<< (long long iValue)
{
	return *this;
}

COutputStream& COutputStream::operator<< (unsigned long long iValue)
{
	return *this;
}

COutputStream& COutputStream::operator<< (float fValue)
{
	return *this;
}

COutputStream& COutputStream::operator<< (double fValue)
{
	return *this;
}

COutputStream& COutputStream::operator<< (long double fValue)
{
	return *this;
}

COutputStream& COutputStream::operator<< (const void* pValue)
{
	return *this;
}

}

/* EOF */
