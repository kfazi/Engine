#ifndef COMMON_STREAM_BASE_HPP
#define COMMON_STREAM_BASE_HPP

#include "../Internal.hpp"
#include "../Strings/String.hpp"

namespace Common
{

class StreamBase
{
	public:
		enum Base
		{
			BINARY = 2,
			OCTAL = 8,
			DECIMAL = 10,
			HEXADECIMAL = 16
		};

		enum Notation
		{
			NONE,
			FIXED,
			SCIENTIFIC
		};

	private:
		Base mBase;
		Notation mNotation;
		bool mBoolAlpha;
		bool mSkipWhitespace;
		bool mAddBase;
		bool mBaseUpperCase;
		bool mNumberUpperCase;
		bool mShowDecimalPoint;
		bool mShowPositiveSign;

	public:
		StreamBase();

		void ResetFlags();
		void SetBase(Base base);
		Base GetBase() const;
		void SetNotation(Notation notation);
		Notation GetNotation() const;
		void SetBoolAlpha(bool boolAlpha);
		bool GetBoolAlpha() const;
		void SetSkipWhitespace(bool skipWhitespace);
		bool GetSkipWhitespace() const;
		void SetAddBase(bool addBase);
		bool GetAddBase() const;
		void SetBaseUpperCase(bool upperCase);
		bool GetBaseUpperCase() const;
		void SetNumberUpperCase(bool upperCase);
		bool GetNumberUpperCase() const;
		void SetShowDecimalPoint(bool showDecimalPoint);
		bool GetShowDecimalPoint() const;
		void SetShowPositiveSign(bool showPositiveSign);
		bool GetShowPositiveSign() const;

		virtual const String& GetString() = 0;
};

}

#endif /* COMMON_STREAM_BASE_HPP */

/* EOF */
