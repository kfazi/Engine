#include "CStringBuffer.hpp"
#include "../Algorithms/Swap.hpp"
#include <cstdio>

namespace Common
{

CStringBuffer::CStringBuffer(): m_cString()
{
	m_iReadIndex = 0;
	m_iWriteIndex = 0;
	ResetFlags();
}

CStringBuffer::~CStringBuffer()
{
}

void CStringBuffer::ResetFlags()
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

void CStringBuffer::SetBase(CStringBuffer::EBase eBase)
{
	m_eBase = eBase;
}

CStringBuffer::EBase CStringBuffer::GetBase() const
{
	return m_eBase;
}

void CStringBuffer::SetNotation(CStringBuffer::ENotation eNotation)
{
	m_eNotation = eNotation;
}

CStringBuffer::ENotation CStringBuffer::GetNotation() const
{
	return m_eNotation;
}

void CStringBuffer::SetBoolAlpha(bool bBoolAlpha)
{
	m_bBoolAlpha = bBoolAlpha;
}

bool CStringBuffer::GetBoolAlpha() const
{
	return m_bBoolAlpha;
}

void CStringBuffer::SetSkipWhitespace(bool bSkipWhitespace)
{
	m_bSkipWhitespace = bSkipWhitespace;
}

bool CStringBuffer::GetSkipWhitespace() const
{
	return m_bSkipWhitespace;
}

void CStringBuffer::SetAddBase(bool bAddBase)
{
	m_bAddBase = bAddBase;
}

bool CStringBuffer::GetAddBase() const
{
	return m_bAddBase;
}

void CStringBuffer::SetBaseUpperCase(bool bUpperCase)
{
	m_bBaseUpperCase = bUpperCase;
}

bool CStringBuffer::GetBaseUpperCase() const
{
	return m_bBaseUpperCase;
}

void CStringBuffer::SetNumberUpperCase(bool bUpperCase)
{
	m_bNumberUpperCase = bUpperCase;
}

bool CStringBuffer::GetNumberUpperCase() const
{
	return m_bNumberUpperCase;
}

void CStringBuffer::SetShowDecimalPoint(bool bShowDecimalPoint)
{
	m_bShowDecimalPoint = bShowDecimalPoint;
}

bool CStringBuffer::GetShowDecimalPoint() const
{
	return m_bShowDecimalPoint;
}

void CStringBuffer::SetShowPositiveSign(bool bShowPositiveSign)
{
	m_bShowPositiveSign = bShowPositiveSign;
}

bool CStringBuffer::GetShowPositiveSign() const
{
	return m_bShowPositiveSign;
}

CString CStringBuffer::ToString(bool bValue) const
{
	if (m_bBoolAlpha)
	{
		CString cResult;
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
CString CStringConvert::NumberToString(unsigned long long iValue) const
{
	CString cResult;
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

CString CStringConvert::UnsignedNumberToString(unsigned long long iValue) const
{
	CString cResult;
	if (m_bShowPositiveSign)
		cResult = "+";
	cResult += NumberToString(iValue);
	return cResult;
}

CString CStringConvert::SignedNumberToString(signed long long iValue) const
{
	CString cResult;
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
CString CStringBuffer::ToString(short iValue) const
{
	CString bla;
	SwapRange(&bla[0], &bla[0] + bla.GetLength());
	return bla;
	//return SignedNumberToString(iValue);
}

/*
CString CStringConvert::ToString(unsigned short iValue) const;
CString CStringConvert::ToString(int iValue) const;
CString CStringConvert::ToString(unsigned int iValue) const;
CString CStringConvert::ToString(long iValue) const;
CString CStringConvert::ToString(unsigned long iValue) const;
CString CStringConvert::ToString(float fValue) const;
CString CStringConvert::ToString(double fValue) const;
CString CStringConvert::ToString(long double fValue) const;
*/

CString CStringBuffer::ToString(const void* pValue) const
{
	char aBuffer[sizeof(void *) * 2 + 2];
	::_snprintf(aBuffer, sizeof(void *) * 2 + 2, "%p", pValue);
	aBuffer[sizeof(void *) * 2 + 1] = 0;
	return aBuffer;
}

}

/* EOF */
