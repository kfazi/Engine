#ifndef COMMON_STREAM_BASE_HPP
#define COMMON_STREAM_BASE_HPP

#include "../Internal.hpp"
#include "../Strings/String.hpp"

namespace Common
{

class CStreamBase
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
		CStreamBase();

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

		virtual const String& GetString() = 0;
};

}

#endif /* COMMON_STREAM_BASE_HPP */

/* EOF */
