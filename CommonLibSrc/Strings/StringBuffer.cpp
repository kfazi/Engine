#include "StringBuffer.hpp"
#include "../Algorithms/Swap.hpp"
#include <cstdio>

namespace Common
{

StringBuffer::StringBuffer(): m_cString()
{
	m_iReadIndex = 0;
	m_iWriteIndex = 0;
	ResetFlags();
}

StringBuffer::~StringBuffer()
{
}

void StringBuffer::ResetFlags()
{
	SetBase(DECIMAL);
	SetNotation(NONE);
	SetBoolAlpha(false);
	SetSkipWhitespace(true);
	SetAddBase(true);
	SetBaseUpperCase(false);
	SetNumberUpperCase(false);
	SetShowDecimalPoint(false);
	SetShowPositiveSign(false);
}

void StringBuffer::SetBase(StringBuffer::EBase eBase)
{
	m_eBase = eBase;
}

StringBuffer::EBase StringBuffer::GetBase() const
{
	return m_eBase;
}

void StringBuffer::SetNotation(StringBuffer::ENotation eNotation)
{
	m_eNotation = eNotation;
}

StringBuffer::ENotation StringBuffer::GetNotation() const
{
	return m_eNotation;
}

void StringBuffer::SetBoolAlpha(bool bBoolAlpha)
{
	m_bBoolAlpha = bBoolAlpha;
}

bool StringBuffer::GetBoolAlpha() const
{
	return m_bBoolAlpha;
}

void StringBuffer::SetSkipWhitespace(bool bSkipWhitespace)
{
	m_bSkipWhitespace = bSkipWhitespace;
}

bool StringBuffer::GetSkipWhitespace() const
{
	return m_bSkipWhitespace;
}

void StringBuffer::SetAddBase(bool bAddBase)
{
	m_bAddBase = bAddBase;
}

bool StringBuffer::GetAddBase() const
{
	return m_bAddBase;
}

void StringBuffer::SetBaseUpperCase(bool bUpperCase)
{
	m_bBaseUpperCase = bUpperCase;
}

bool StringBuffer::GetBaseUpperCase() const
{
	return m_bBaseUpperCase;
}

void StringBuffer::SetNumberUpperCase(bool bUpperCase)
{
	m_bNumberUpperCase = bUpperCase;
}

bool StringBuffer::GetNumberUpperCase() const
{
	return m_bNumberUpperCase;
}

void StringBuffer::SetShowDecimalPoint(bool bShowDecimalPoint)
{
	m_bShowDecimalPoint = bShowDecimalPoint;
}

bool StringBuffer::GetShowDecimalPoint() const
{
	return m_bShowDecimalPoint;
}

void StringBuffer::SetShowPositiveSign(bool bShowPositiveSign)
{
	m_bShowPositiveSign = bShowPositiveSign;
}

bool StringBuffer::GetShowPositiveSign() const
{
	return m_bShowPositiveSign;
}

String StringBuffer::ToString(bool bValue) const
{
	if (m_bBoolAlpha)
	{
		String cResult;
		cResult = (bValue) ? "true" : "false";
		if (m_bNumberUpperCase)
			cResult.ToUpper();
		return cResult;
	}
	else
		return (bValue) ? "1" : "0";
}

const char aDigitsUpperCase[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
const char aDigitsLowerCase[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

/*
String StringConvert::NumberToString(unsigned long long iValue) const
{
	String cResult;
	int iBase = m_eBase;
	const char* pDigits;
	if (m_bNumberUpperCase)
		pDigits = aDigitsUpperCase;
	else
		pDigits = aDigitsLowerCase;
	do 
	{
		cResult += pDigits[iValue % iBase];
		iValue /= iBase;
	}
	while (iValue > 0);
	if (m_bAddBase)
	{
		switch (m_eBase)
		{
		case BINARY:
			if (m_bBaseUpperCase)
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
			if (m_bBaseUpperCase)
				cResult += "X0";
			else
				cResult += "x0";
			break;
		}
	}
	cResult.Swap();
	return cResult;
}

String StringConvert::UnsignedNumberToString(unsigned long long iValue) const
{
	String cResult;
	if (m_bShowPositiveSign)
		cResult = "+";
	cResult += NumberToString(iValue);
	return cResult;
}

String StringConvert::SignedNumberToString(signed long long iValue) const
{
	String cResult;
	if (iValue < 0)
	{
		cResult = "-";
		iValue = -iValue;
	}
	else if (m_bShowPositiveSign)
		cResult = "+";
	cResult += NumberToString(iValue);
	return cResult;
}
*/
String StringBuffer::ToString(short iValue) const
{
	String bla;
	SwapRange(&bla[0], &bla[0] + bla.GetLength());
	return bla;
	//return SignedNumberToString(iValue);
}

/*
String StringConvert::ToString(unsigned short iValue) const;
String StringConvert::ToString(int iValue) const;
String StringConvert::ToString(unsigned int iValue) const;
String StringConvert::ToString(long iValue) const;
String StringConvert::ToString(unsigned long iValue) const;
String StringConvert::ToString(float fValue) const;
String StringConvert::ToString(double fValue) const;
String StringConvert::ToString(long double fValue) const;
*/

String StringBuffer::ToString(const void* pValue) const
{
	char aBuffer[sizeof(void *) * 2 + 2];
	::_snprintf(aBuffer, sizeof(void *) * 2 + 2, "%p", pValue);
	aBuffer[sizeof(void *) * 2 + 1] = 0;
	return aBuffer;
}

}

/* EOF */
