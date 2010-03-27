#ifndef COMMON_STRING_BUFFER_HPP
#define COMMON_STRING_BUFFER_HPP

#include "../Internal.hpp"
#include "String.hpp"

namespace Common
{

class StringBuffer
{
	public:
		enum EBase
		{
			BINARY = 2,
			OCTAL = 8,
			DECIMAL = 10,
			HEXADECIMAL = 16
		};

		enum ENotation
		{
			NONE,
			FIXED,
			SCIENTIFIC
		};

	private:
		String m_cString;
		unsigned int m_iReadIndex;
		unsigned int m_iWriteIndex;
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
		StringBuffer();
		~StringBuffer();

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

		const String& GetString() const;

		String ToString(bool bValue) const;
		String ToString(short iValue) const;
		String ToString(unsigned short iValue) const;
		String ToString(int iValue) const;
		String ToString(unsigned int iValue) const;
		String ToString(long iValue) const;
		String ToString(unsigned long iValue) const;
		String ToString(signed long long iValue) const;
		String ToString(unsigned long long iValue) const;
		String ToString(float fValue) const;
		String ToString(double fValue) const;
		String ToString(long double fValue) const;
		String ToString(const void* pValue) const;

		void FromString(bool& bTarget, const String& cValue) const;
		void FromString(short& iTarget, const String& cValue) const;
		void FromString(unsigned short& iTarget, const String& cValue) const;
		void FromString(int& iTarget, const String& cValue) const;
		void FromString(unsigned int& iTarget, const String& cValue) const;
		void FromString(long& iTarget, const String& cValue) const;
		void FromString(unsigned long& iTarget, const String& cValue) const;
		void FromString(signed long long& iValue);
		void FromString(unsigned long long& iValue);
		void FromString(float& fTarget, const String& cValue) const;
		void FromString(double& fTarget, const String& cValue) const;
		void FromString(long double& fTarget, const String& cValue) const;
		void FromString(const void *&pTarget, const String& cValue) const;
};

}

#endif /* COMMON_STRING_CONVERT_HPP */

/* EOF */
