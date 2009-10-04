#ifndef COMMON_STRING_CONVERT_HPP
#define COMMON_STRING_CONVERT_HPP

#include "../Internal.hpp"
#include "CString.hpp"

namespace Common
{

class CStringConvert
{
	public:
		enum EBase
		{
			BINARY,
			DECIMAL,
			HEXADECIMAL,
			OCTAL
		};

		enum ENotation
		{
			NONE,
			FIXED,
			SCIENTIFIC
		};

	private:
		EBase m_eBase;
		ENotation m_eNotation;
		bool m_bBoolAlpha;
		bool m_bSkipWhitespace;
		bool m_bAddBase;
		bool m_bBaseUpperCase;
		bool m_bNumberUpperCase;
		bool m_bShowDecimalPoint;
		bool m_bShowPositiveSign;

	public:
		CStringConvert();
		~CStringConvert();

		void ResetFlags();
		void SetBase(EBase eBase);
		EBase GetBase() const;
		void SetNotation(ENotation eNotation);
		ENotation GetNotation() const;
		void SetBoolAlpha(bool bBoolAlpha);
		bool GetBoolAlpha() const;
		void SetSkipWhitespace(bool bSkipWhitespace);
		bool GetSkipWhitespace() const;
		void SetAddBase(bool bAddBase);
		bool GetAddBase() const;
		void SetBaseUpperCase(bool bUpperCase);
		bool GetBaseUpperCase() const;
		void SetNumberUpperCase(bool bUpperCase);
		bool GetNumberUpperCase() const;
		void SetShowDecimalPoint(bool bShowDecimalPoint);
		bool GetShowDecimalPoint() const;
		void SetShowPositiveSign(bool bShowPositiveSign);
		bool GetShowPositiveSign() const;

		CString ToString(bool bValue) const;
		CString ToString(short iValue) const;
		CString ToString(unsigned short iValue) const;
		CString ToString(int iValue) const;
		CString ToString(unsigned int iValue) const;
		CString ToString(long iValue) const;
		CString ToString(unsigned long iValue) const;
		CString ToString(float fValue) const;
		CString ToString(double fValue) const;
		CString ToString(long double fValue) const;
		CString ToString(const void *pValue) const;

		void FromString(bool &bTarget, const CString &cValue) const;
		void FromString(short &iTarget, const CString &cValue) const;
		void FromString(unsigned short &iTarget, const CString &cValue) const;
		void FromString(int &iTarget, const CString &cValue) const;
		void FromString(unsigned int &iTarget, const CString &cValue) const;
		void FromString(long &iTarget, const CString &cValue) const;
		void FromString(unsigned long &iTarget, const CString &cValue) const;
		void FromString(float &fTarget, const CString &cValue) const;
		void FromString(double &fTarget, const CString &cValue) const;
		void FromString(long double &fTarget, const CString &cValue) const;
		void FromString(const void *&pTarget, const CString &cValue) const;
};

}

#endif /* COMMON_STRING_CONVERT_HPP */

/* EOF */
